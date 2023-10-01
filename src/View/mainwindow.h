#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Controller/controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_choose_obj_btn_clicked();

  void on_edges_color_btn_clicked();

  void on_vertex_color_btn_clicked();

  void on_bg_color_btn_clicked();

  void on_vertex_size_text_textChanged(const QString &arg1);

  void on_edges_width_text_textChanged(const QString &arg1);

  void on_parallel_rb_clicked();

  void on_central_rb_clicked();

  void on_solid_rb_clicked();

  void on_dashed_rb_clicked();

  void on_vertex_none_rb_clicked();

  void on_vertex_square_rb_clicked();

  void on_vertex_rounded_rb_clicked();

  void on_screenshot_jpb_bnt_clicked();

  void on_screenshot_bmp_btn_clicked();

  void on_gif_btn_clicked();

  void on_x_pos_slider_valueChanged(int value);

  void on_y_pos_slider_valueChanged(int value);

  void on_z_pos_slider_valueChanged(int value);

  void on_rot_x_slider_valueChanged(int value);

  void on_rot_y_slider_valueChanged(int value);

  void on_rot_z_slider_valueChanged(int value);

  void on_scale_slider_valueChanged(int value);

  void on_pos_x_text_textChanged(const QString &arg1);

  void on_pos_y_text_textChanged(const QString &arg1);

  void on_pos_z_text_textChanged(const QString &arg1);

  void on_rot_x_text_textChanged(const QString &arg1);

  void on_rot_y_text_textChanged(const QString &arg1);

  void on_rot_z_text_textChanged(const QString &arg1);

  void on_scale_text_textChanged(const QString &arg1);

 private:
  void LoadUI();
  void ResetObjectTransform();

  Ui::MainWindow *ui;
  s21::Controller *controller;
};
#endif  // MAINWINDOW_H
