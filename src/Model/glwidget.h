#ifndef GLWIDGET_H
#define GLWIDGET_H

#define GL_SILENCE_DEPRECATION
#include <QOpenGLWidget>
#include <QSettings>

#include "model.h"

/**
 * @brief The GLWidget class
 */
class GLWidget : public QOpenGLWidget, public s21::IObserver {
 public:
  explicit GLWidget(QWidget *parent = nullptr);

  /**
   * @brief SetColors
   * @param v - vertices color
   * @param e - edges color
   * @param b - background color
   */
  void SetColors(QColor v, QColor e, QColor b);

  /**
   * @brief SetVertexSize
   * @param value in pixels
   */
  void SetVertexSize(int value);

  /**
   * @brief SetEdgesWidth
   * @param value in pixels
   */
  void SetEdgesWidth(int value);

  /**
   * @brief SetVertexDisplay
   * @param display 0, 1, 2
   */
  void SetVertexDisplay(int display);

  /**
   * @brief SetEdgesDisplay
   * @param display 1, 2
   */
  void SetEdgesDisplay(int display);

  /**
   * @brief SetDisplayMode
   * @param display mode
   */
  void SetDisplayMode(bool is_perspective);

  /**
   * @brief Save settings to registry
   */
  void SaveSettings();

  /**
   * @brief GetVertexSize
   * @return vertex size in pixels
   */
  int GetVertexSize() { return vertex_size; }

  /**
   * @brief GetEdgesWidth
   * @return edges width in pixels
   */
  int GetEdgesWidth() { return edges_width; }

  /**
   * @brief GetVertexDisplay
   * @return vertex display mode
   */
  int GetVertexDisplay() { return vertex_display; }

  /**
   * @brief GetEdgesDisplay
   * @return edges display mode
   */
  int GetEdgesDisplay() { return edges_display; }

  /**
   * @brief IsPerspective
   * @return is model view perspective
   */
  bool IsPerspective() { return is_perspective_view; }

 protected:
  virtual void initializeGL() override;
  virtual void resizeGL(int w, int h) override;
  virtual void paintGL() override;

 private:
  /**
   * @brief LoadSettings from registry
   */
  void LoadSettings();

  /**
   * @brief DrawVertices
   */
  void DrawVertices();

  /**
   * @brief DrawEdges
   */
  void DrawEdges();

  void update_gl() override;

  QColor vertex_color;
  QColor edges_color;
  QColor background_color;

  int vertex_size;
  int edges_width;

  int vertex_display;
  int edges_display;

  bool is_perspective_view;
};

#endif  // GLWIDGET_H
