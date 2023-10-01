#include "model.h"

namespace s21 {

Model* Model::pointer_ = nullptr;

Model* Model::get_model() {
  if (pointer_ == nullptr) pointer_ = new Model();
  return pointer_;
}

void Model::set_model(std::string file_name) {
  pars_.get_data(file_name);
  for (int i = 0; i < 3; ++i) {
    previous_rot[i] = 0;
    previous_shift[i] = 0;
  }
  previous_scale = 1;
  notify();
}

std::vector<int> Model::get_connections() { return pars_.get_connections(); }

std::vector<double> Model::get_points() { return pars_.get_points(); }

void Model::set_connections(const std::vector<int>& other) {
  pars_.set_connections(other);
}

void Model::set_points(const std::vector<double>& other) {
  pars_.set_points(other);
  notify();
}

void Model::affine_rotate(int axis, double angle) {
  if (pointer_ != nullptr) {
    AffineRotation ar;
    Context context(&ar);
    std::vector<double> buffer = get_points();
    angle = angle * (3.14 / 180.0);
    angle = GetRotationValue(axis, angle);
    context.execute(buffer, axis, angle);
    set_points(buffer);
  }
}

void Model::affine_scale(double size) {
  if (pointer_ != nullptr) {
    AffineScale as;
    Context context(&as);
    std::vector<double> buffer = get_points();
    size = GetScaleValue(size);
    context.execute(buffer, 0, size);
    set_points(buffer);
  }
}

void Model::affine_shift(int axis, double shift) {
  if (pointer_ != nullptr) {
    AffineShift as;
    Context context(&as);
    std::vector<double> buffer = get_points();
    shift = GetPositionValue(axis, shift);
    context.execute(buffer, axis, shift);
    set_points(buffer);
  }
}

double Model::GetPositionValue(int axis, double value) {
  double delta = 0;
  delta = value - previous_shift[axis];
  previous_shift[axis] = value;

  return delta;
}

double Model::GetRotationValue(int axis, double value) {
  double delta = 0;
  delta = value - previous_rot[axis];
  previous_rot[axis] = value;

  return delta;
}

double Model::GetScaleValue(double value) {
  double delta = 0;

  if (value <= 0.001) {
    value = 0.001;
  }

  delta = value / previous_scale;
  previous_scale = value;

  return delta;
}

}  // namespace s21
