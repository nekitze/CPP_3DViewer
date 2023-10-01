#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent) {
  LoadSettings();
  s21::Model::get_model()->addObserver(this);
}

void GLWidget::initializeGL() {
  glMatrixMode(GL_PROJECTION);
  glEnable(GL_DEPTH);
}

void GLWidget::resizeGL(int w, int h) { glViewport(1, 1, w, h); }

void GLWidget::paintGL() {
  glLoadIdentity();
  if (is_perspective_view) {
    glFrustum(-1, 1, -1, 1, 1, 1000);
    glTranslatef(0, 0, -3);
  } else {
    glOrtho(-1, 1, -1, 1, -2, 1000);
  }

  glClearColor(background_color.redF(), background_color.greenF(),
               background_color.blueF(), background_color.alphaF());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  DrawEdges();
  if (vertex_display != 0) DrawVertices();
}

void GLWidget::DrawVertices() {
  glColor3d(vertex_color.redF(), vertex_color.greenF(), vertex_color.blueF());
  glPointSize(vertex_size);

  if (vertex_display == 1)
    glDisable(GL_POINT_SMOOTH);
  else if (vertex_display == 2)
    glEnable(GL_POINT_SMOOTH);

  std::vector<double> vertices = s21::Model::get_model()->get_points();

  glBegin(GL_POINTS);
  for (size_t i = 0; i < vertices.size(); i += 3) {
    glVertex3d(vertices[i], vertices[i + 1], vertices[i + 2]);
  }
  glEnd();
}

void GLWidget::DrawEdges() {
  std::vector<int> connections = s21::Model::get_model()->get_connections();
  std::vector<double> vertices = s21::Model::get_model()->get_points();

  glColor3d(edges_color.redF(), edges_color.greenF(), edges_color.blueF());
  glLineWidth(edges_width);
  glLineStipple(3, 0x3333);

  if (edges_display == 1)
    glDisable(GL_LINE_STIPPLE);
  else if (edges_display == 2) {
    glEnable(GL_LINE_STIPPLE);
  }

  glBegin(GL_LINES);
  for (auto it = connections.begin(); it != connections.end(); it++) {
    glVertex3d(vertices[*it * 3], vertices[*it * 3 + 1], vertices[*it * 3 + 2]);
  }
  glEnd();
}

void GLWidget::update_gl() {
  SaveSettings();
  update();
}

void GLWidget::SetColors(QColor v, QColor e, QColor b) {
  if (v != nullptr) vertex_color = v;
  if (e != nullptr) edges_color = e;
  if (b != nullptr) background_color = b;

  update_gl();
}

void GLWidget::SetVertexSize(int value) {
  vertex_size = value;
  update_gl();
}

void GLWidget::SetEdgesWidth(int value) {
  edges_width = value;
  update_gl();
}

void GLWidget::SetVertexDisplay(int display) {
  vertex_display = display;
  update_gl();
}

void GLWidget::SetEdgesDisplay(int display) {
  edges_display = display;
  update_gl();
}

void GLWidget::SetDisplayMode(bool is_perspective) {
  is_perspective_view = is_perspective;
  update_gl();
}

void GLWidget::SaveSettings() {
  QSettings settings("MyS21Soft", "3DViewerV2.0");

  settings.setValue("vertex_color", vertex_color);
  settings.setValue("edges_color", edges_color);
  settings.setValue("background_color", background_color);

  settings.setValue("vertex_size", vertex_size);
  settings.setValue("edges_width", edges_width);

  settings.setValue("vertex_display", vertex_display);
  settings.setValue("edges_display", edges_display);

  settings.setValue("is_perspective_view", is_perspective_view);
}

void GLWidget::LoadSettings() {
  QSettings settings("MyS21Soft", "3DViewerV2.0");

  if (!settings.value("vertex_color").isNull())
    vertex_color = settings.value("vertex_color").value<QColor>();
  else
    vertex_color = Qt::green;

  if (!settings.value("edges_color").isNull())
    edges_color = settings.value("edges_color").value<QColor>();
  else
    edges_color = Qt::red;

  if (!settings.value("background_color").isNull())
    background_color = settings.value("background_color").value<QColor>();
  else
    background_color = Qt::blue;

  if (!settings.value("vertex_size").isNull())
    vertex_size = settings.value("vertex_size").value<GLfloat>();
  else
    vertex_size = 20;

  if (!settings.value("edges_width").isNull())
    edges_width = settings.value("edges_width").value<GLfloat>();
  else
    edges_width = 1;

  if (!settings.value("vertex_display").isNull())
    vertex_display = settings.value("vertex_display").value<int>();
  else
    vertex_display = 1;

  if (!settings.value("edges_display").isNull())
    edges_display = settings.value("edges_display").value<int>();
  else
    edges_display = 1;

  if (!settings.value("is_perspective_view").isNull())
    is_perspective_view = settings.value("is_perspective_view").value<bool>();
  else
    is_perspective_view = true;

  update();
}
