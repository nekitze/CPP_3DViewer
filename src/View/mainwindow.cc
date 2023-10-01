#include "mainwindow.h"

#include <QColorDialog>
#include <QFileDialog>
#include <QStandardPaths>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  controller = new s21::Controller(ui->opengl_widget);

  LoadUI();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::LoadUI() {
  ui->vertex_size_text->setText(controller->GetVerticesSize());
  ui->edges_width_text->setText(controller->GetEdgesWidth());

  if (controller->GetIsPerspective()) {
    ui->central_rb->setChecked(true);
    ui->parallel_rb->setChecked(false);
  } else {
    ui->central_rb->setChecked(false);
    ui->parallel_rb->setChecked(true);
  }

  if (controller->GetEdgesDisplay() == 1) {
    ui->solid_rb->setChecked(true);
    ui->dashed_rb->setChecked(false);
  } else {
    ui->solid_rb->setChecked(false);
    ui->dashed_rb->setChecked(true);
  }

  if (controller->GetVertexDisplay() == 0) {
    ui->vertex_none_rb->setChecked(true);
    ui->vertex_square_rb->setChecked(false);
    ui->vertex_rounded_rb->setChecked(false);
  } else if (controller->GetVertexDisplay() == 1) {
    ui->vertex_none_rb->setChecked(false);
    ui->vertex_square_rb->setChecked(true);
    ui->vertex_rounded_rb->setChecked(false);
  } else {
    ui->vertex_none_rb->setChecked(false);
    ui->vertex_square_rb->setChecked(false);
    ui->vertex_rounded_rb->setChecked(true);
  }
}

void MainWindow::on_choose_obj_btn_clicked() {
  QString path = QFileDialog::getOpenFileName(this, "Pick .obj file", "/home",
                                              "Object file (*.obj)");
  if (!path.isEmpty()) {
    ui->file_name_label->setText(path.mid(path.lastIndexOf("/")).remove(0, 1));
    controller->LoadModel(path);

    ResetObjectTransform();

    QString objectInfo =
        "Vertex Count: " + QString::number(controller->GetModelInfo().first) +
        "\nEdges Count: " + QString::number(controller->GetModelInfo().second);

    ui->object_info_label->setText(objectInfo);
  }
}

void MainWindow::ResetObjectTransform() {
  ui->x_pos_slider->setValue(0);
  ui->y_pos_slider->setValue(0);
  ui->z_pos_slider->setValue(0);

  ui->rot_x_slider->setValue(0);
  ui->rot_y_slider->setValue(0);
  ui->rot_z_slider->setValue(0);

  ui->scale_slider->setValue(100);
}

void MainWindow::on_edges_color_btn_clicked() {
  QColor edges_color = QColorDialog::getColor(Qt::green, this);

  if (edges_color.isValid()) {
    controller->SetColors(nullptr, edges_color, nullptr);
  }
}

void MainWindow::on_vertex_color_btn_clicked() {
  QColor vertices_color = QColorDialog::getColor(Qt::white, this);

  if (vertices_color.isValid()) {
    controller->SetColors(vertices_color, nullptr, nullptr);
  }
}

void MainWindow::on_bg_color_btn_clicked() {
  QColor background_color = QColorDialog::getColor(Qt::blue, this);

  if (background_color.isValid()) {
    controller->SetColors(nullptr, nullptr, background_color);
  }
}

void MainWindow::on_vertex_size_text_textChanged(const QString &arg1) {
  controller->SetVerticesSize(arg1.toInt());
}

void MainWindow::on_edges_width_text_textChanged(const QString &arg1) {
  controller->SetEdgesWidth(arg1.toInt());
}

void MainWindow::on_parallel_rb_clicked() {
  ui->central_rb->setChecked(false);
  ui->parallel_rb->setChecked(true);

  controller->SetPerspective(false);
}

void MainWindow::on_central_rb_clicked() {
  ui->central_rb->setChecked(true);
  ui->parallel_rb->setChecked(false);

  controller->SetPerspective(true);
}

void MainWindow::on_solid_rb_clicked() {
  ui->solid_rb->setChecked(true);
  ui->dashed_rb->setChecked(false);

  controller->SetEdgesDisplay(1);
}

void MainWindow::on_dashed_rb_clicked() {
  ui->solid_rb->setChecked(false);
  ui->dashed_rb->setChecked(true);

  controller->SetEdgesDisplay(2);
}

void MainWindow::on_vertex_none_rb_clicked() {
  ui->vertex_none_rb->setChecked(true);
  ui->vertex_square_rb->setChecked(false);
  ui->vertex_rounded_rb->setChecked(false);

  controller->SetVerticesDisplay(0);
}

void MainWindow::on_vertex_square_rb_clicked() {
  ui->vertex_none_rb->setChecked(false);
  ui->vertex_square_rb->setChecked(true);
  ui->vertex_rounded_rb->setChecked(false);

  controller->SetVerticesDisplay(1);
}

void MainWindow::on_vertex_rounded_rb_clicked() {
  ui->vertex_none_rb->setChecked(false);
  ui->vertex_square_rb->setChecked(false);
  ui->vertex_rounded_rb->setChecked(true);

  controller->SetVerticesDisplay(2);
}

void MainWindow::on_screenshot_jpb_bnt_clicked() {
  QString initialPath = QFileDialog::getSaveFileName(
      this, "Save Screenshot",
      QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),
      "Image(*.jpg)");
  if (!initialPath.isNull())
    ui->opengl_widget->grabFramebuffer().save(initialPath);
}

void MainWindow::on_screenshot_bmp_btn_clicked() {
  QString initialPath = QFileDialog::getSaveFileName(
      this, "Save Screenshot",
      QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),
      "Image(*.bmp)");
  if (!initialPath.isNull())
    ui->opengl_widget->grabFramebuffer().save(initialPath);
}

void MainWindow::on_gif_btn_clicked() {}

void MainWindow::on_x_pos_slider_valueChanged(int value) {
  ui->pos_x_text->setText(QString::number(value / 100.f));
}

void MainWindow::on_y_pos_slider_valueChanged(int value) {
  ui->pos_y_text->setText(QString::number(value / 100.f));
}

void MainWindow::on_z_pos_slider_valueChanged(int value) {
  ui->pos_z_text->setText(QString::number(value / 100.f));
}

void MainWindow::on_rot_x_slider_valueChanged(int value) {
  ui->rot_x_text->setText(QString::number(value));
}

void MainWindow::on_rot_y_slider_valueChanged(int value) {
  ui->rot_y_text->setText(QString::number(value));
}

void MainWindow::on_rot_z_slider_valueChanged(int value) {
  ui->rot_z_text->setText(QString::number(value));
}

void MainWindow::on_scale_slider_valueChanged(int value) {
  ui->scale_text->setText(QString::number(value / 100.f));
}

void MainWindow::on_pos_x_text_textChanged(const QString &arg1) {
  ui->x_pos_slider->setValue(arg1.toDouble() * 100);
  controller->MoveModel(0, arg1);
}

void MainWindow::on_pos_y_text_textChanged(const QString &arg1) {
  ui->y_pos_slider->setValue(arg1.toDouble() * 100);
  controller->MoveModel(1, arg1);
}

void MainWindow::on_pos_z_text_textChanged(const QString &arg1) {
  ui->z_pos_slider->setValue(arg1.toDouble() * 100);
  controller->MoveModel(2, arg1);
}

void MainWindow::on_rot_x_text_textChanged(const QString &arg1) {
  ui->rot_x_slider->setValue(arg1.toInt());
  controller->RotateModel(0, arg1);
}

void MainWindow::on_rot_y_text_textChanged(const QString &arg1) {
  ui->rot_y_slider->setValue(arg1.toInt());
  controller->RotateModel(1, arg1);
}

void MainWindow::on_rot_z_text_textChanged(const QString &arg1) {
  ui->rot_z_slider->setValue(arg1.toInt());
  controller->RotateModel(2, arg1);
}

void MainWindow::on_scale_text_textChanged(const QString &arg1) {
  ui->scale_slider->setValue(arg1.toDouble() * 100);
  controller->ScaleModel(arg1);
}
