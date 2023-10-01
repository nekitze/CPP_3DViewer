#include "controller.h"

namespace s21 {

void Controller::LoadModel(QString path) {
  try {
    s21::Model::get_model()->set_model(path.toStdString());
  } catch (const std::exception& e) {
    QMessageBox::critical(nullptr, "Error", e.what());
  }
}

std::pair<int, int> Controller::GetModelInfo() {
  return std::pair<int, int>(
      s21::Model::get_model()->get_points().size() / 3,
      s21::Model::get_model()->get_connections().size() / 2);
}

void Controller::MoveModel(int axis, QString value) {
  s21::Model::get_model()->affine_shift(axis, value.toDouble());
}

void Controller::RotateModel(int axis, QString value) {
  s21::Model::get_model()->affine_rotate(axis, value.toDouble());
}

void Controller::ScaleModel(QString value) {
  s21::Model::get_model()->affine_scale(value.toDouble());
}

}  // namespace s21
