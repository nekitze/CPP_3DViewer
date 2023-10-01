#include "affine.h"

namespace s21 {

void AffineRotation::execute(std::vector<double> &points, int axis,
                             double value) {
  for (int i = 0; i < (int)points.size(); i += 3) {
    int x = -1;
    int y = -1;
    for (int j = 0; j < 3; j++) {
      if (axis != j && (x != -1)) y = i + j;
      if (axis != j && (x == -1)) x = i + j;
    }
    double temp_x = points[x], temp_y = points[y];
    points[x] = cos(value) * temp_x + sin(value) * temp_y;
    points[y] = -sin(value) * temp_x + cos(value) * temp_y;
  }
}

void AffineShift::execute(std::vector<double> &points, int axis, double value) {
  for (int i = 0; i < (int)points.size(); i += 3) {
    for (int j = 0; j < 3; j++) {
      if (j == axis) points[i + j] += value;
    }
  }
}

void AffineScale::execute(std::vector<double> &points, int axis, double value) {
  for (int i = 0; i < (int)points.size(); i++) points[i + axis] *= value;
}

Context::Context(Affine *other) { this->affine = other; }

void Context::execute(std::vector<double> &points, int axis, double value) {
  this->affine->execute(points, axis, value);
}

}  // namespace s21
