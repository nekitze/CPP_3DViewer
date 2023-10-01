#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QMessageBox>
#include <QString>

#include "../Model/glwidget.h"
#include "../Model/model.h"

/**
 * S21 Namespace
 */
namespace s21 {

/**
 * @brief The Controller class
 */
class Controller {
 public:
  Controller(GLWidget *widget) : glWidget(widget) {}

  /**
   * @brief LoadModel
   * @param path to obj file
   */
  void LoadModel(QString path);

  /**
   * @brief GetModelInfo
   * @return Returns count of vertices and edges as pair
   */
  std::pair<int, int> GetModelInfo();

  /**
   * @brief MoveModel
   * @param axis
   * @param value
   */
  void MoveModel(int axis, QString value);

  /**
   * @brief RotateModel
   * @param axis
   * @param value
   */
  void RotateModel(int axis, QString value);

  /**
   * @brief Method to scale model
   * @param value
   */
  void ScaleModel(QString value);

  /**
   * @brief GetVerticesSize
   * @return size in pixels
   */
  QString GetVerticesSize() {
    return QString::number(glWidget->GetVertexSize());
  }

  /**
   * @brief GetEdgesWidth
   * @return width in pixels
   */
  QString GetEdgesWidth() { return QString::number(glWidget->GetEdgesWidth()); }

  /**
   * @brief GetVertexDisplay
   * @return display mode
   */
  int GetVertexDisplay() { return glWidget->GetVertexDisplay(); }

  /**
   * @brief GetEdgesDisplay
   * @return display mode
   */
  int GetEdgesDisplay() { return glWidget->GetEdgesDisplay(); }

  /**
   * @brief GetIsPerspective
   * @return is view of model perspective
   */
  bool GetIsPerspective() { return glWidget->IsPerspective(); }

  /**
   * @brief Change colors of display
   * @param v - vertices color
   * @param e - edges color
   * @param b - background color
   */
  void SetColors(QColor v, QColor e, QColor b) { glWidget->SetColors(v, e, b); }

  /**
   * @brief Method to change size of model vertices;
   * @param value in pixels
   */
  void SetVerticesSize(int value) { glWidget->SetVertexSize(value); }

  /**
   * @brief Method to change display of model vertices
   * @param 0 - none; 2 - squared; 3 - rounded;
   */
  void SetVerticesDisplay(int display) { glWidget->SetVertexDisplay(display); }

  /**
   * @brief Method to change width of model edges
   * @param value in pixels
   */
  void SetEdgesWidth(int value) { glWidget->SetEdgesWidth(value); }

  /**
   * @brief Method to change display of model edges
   * @param 1 - solid; 2 - dotted;
   */
  void SetEdgesDisplay(int display) { glWidget->SetEdgesDisplay(display); }

  /**
   * @brief Method to change projection of our model
   * @param true - perspective; false - central
   */
  void SetPerspective(bool value) { glWidget->SetDisplayMode(value); }

 private:
  GLWidget *glWidget;
};
}  // namespace s21

#endif  // CONTROLLER_H
