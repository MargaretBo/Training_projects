#include "widget.h"

Widget::Widget(QWidget *parent) : QOpenGLWidget{parent} {
  Controller controller;
  loadSettings();
}

Widget::~Widget() { saveSettings(); }

void Widget::initializeGL() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_DEPTH_TEST);  // буффер глубины цветa
  glEnable(GL_CULL_FACE);   // отсечение задних граней
}
/**
 * @brief Resizes the widget
 *
 * @param w - width
 * @param h - height
 */
void Widget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }
/**
 * @brief Sets up the widget
 *
 */
void Widget::paintGL() {
  if (controller->GetNumberOfVertices() == 0 ||
      controller->GetNumberOfFaces() == 0)
    return;
  glClearColor(backgroundColor.redF(), backgroundColor.greenF(),
               backgroundColor.blueF(), 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (checkCentral) {
    glFrustum(-1, 1, -1, 1, 1, 100);
    glTranslated(0, 0, -3);
  } else {
    glOrtho(-1, 1, -1, 1, -100, 100);
  }

  if (checkLineType) {
    glLineStipple(1, 0x00FF);
    glEnable(GL_LINE_STIPPLE);
  }

  glEnableClientState(GL_VERTEX_ARRAY);

  glColor3f(vertexColor.redF(), vertexColor.greenF(), vertexColor.blueF());
  glPointSize(pointSize);
  std::vector<double> vertices = controller->GetVertices();
  glVertexPointer(3, GL_DOUBLE, 0, &vertices[0]);
  if (checkPointType == 1) {
    glEnable(GL_POINT_SMOOTH);
  }
  if (checkPointType) {
    glDrawArrays(GL_POINTS, 0, controller->GetNumberOfVertices() / 3);
  }

  glColor3d(lineColor.redF(), lineColor.greenF(), lineColor.blueF());
  glLineWidth(lineWidth);
  std::vector<int> faces = controller->GetFaces();
  glDrawElements(GL_LINES, controller->GetNumberOfFaces() * 2, GL_UNSIGNED_INT,
                 &faces[0]);

  glDisable(GL_POINT_SMOOTH);
  glDisable(GL_LINE_STIPPLE);
  glDisableClientState(GL_VERTEX_ARRAY);
}
/**
 * @brief Gets the data from the model
 *
 * @param path - path to the file
 */
void Widget::getArrays(std::string path) {
  controller->ParceFigure(path);
  update();
}
/**
 * @brief Sends the value to move the figure along the X axis by arg1 to the
 * model and updates the view
 *
 * @param arg1 - value
 */
void Widget::getMoveX(double arg1) {
  controller->UpdateFigure(3, arg1 - xMove);
  xMove = arg1;
  update();
}
/**
 * @brief Sends the value to move the figure along the Y axis by arg1 to the
 * model and updates the view
 *
 * @param arg1 - value
 */
void Widget::getMoveY(double arg1) {
  controller->UpdateFigure(4, arg1 - yMove);
  yMove = arg1;
  update();
}
/**
 * @brief Sends the value to move the figure along the Z axis by arg1 to the
 * model and updates the view
 *
 * @param arg1 - value
 */
void Widget::getMoveZ(double arg1) {
  controller->UpdateFigure(5, arg1 - zMove);
  zMove = arg1;
  update();
}
/**
 * @brief Sends the value to rotate the figure about the X axis by arg1 to the
 * model and updates the view
 *
 * @param arg1 - value
 */
void Widget::getRotX(double arg1) {
  arg1 = arg1 / M_PI;
  controller->UpdateFigure(0, arg1 - xRot);
  xRot = arg1;
  update();
}
/**
 * @brief Sends the value to rotate the figure about the Y axis by arg1 to the
 * model and updates the view
 *
 * @param arg1 - value
 */
void Widget::getRotY(double arg1) {
  arg1 = arg1 / M_PI;
  controller->UpdateFigure(1, arg1 - yRot);
  yRot = arg1;
  update();
}
/**
 * @brief Sends the value to rotate the figure about the Z axis by arg1 to the
 * model and updates the view
 *
 * @param arg1
 */
void Widget::getRotZ(double arg1) {
  arg1 = arg1 / M_PI;
  controller->UpdateFigure(2, arg1 - zRot);
  zRot = arg1;
  update();
}
/**
 * @brief Sends the value to scale the figure by arg1 to the model and updates
 * the view
 *
 * @param arg1
 */
void Widget::getScale(double arg1) {
  controller->UpdateFigure(6, arg1 / scaleValue);
  scaleValue = arg1;
  update();
}
/**
 * @brief Checks if the projection is central and updates the view
 *
 * @param arg
 */
void Widget::checkCentralProjection(int arg) {
  checkCentral = arg;
  update();
}
/**
 * @brief Returns the number of vertices
 *
 * @return int - number of vertices
 */
int Widget::getCountVertices() { return controller->GetNumberOfVertices() / 3; }
/**
 * @brief Returns the number of faces
 *
 * @return int - number of faces
 */
int Widget::getCountFaces() { return controller->GetNumberOfFaces(); }
/**
 * @brief Changes the background color
 *
 * @param back_color
 */
void Widget::changeBackgroundColor(const QColor &back_color) {
  backgroundColor = back_color;
  update();
}
/**
 * @brief Changes the vertex color
 *
 * @param vertex_color
 */
void Widget::changeVertexColor(const QColor &vertex_color) {
  vertexColor = vertex_color;
  update();
}
/**
 * @brief Changes the vertex type
 *
 * @param arg
 */
void Widget::changeVertexType(int arg) {
  checkPointType = arg;
  update();
}
/**
 * @brief Changes the vertex size
 *
 * @param arg
 */
void Widget::changeVertexSize(int arg) {
  pointSize = arg;
  update();
}
/**
 * @brief Changes the line color
 *
 * @param line_color
 */
void Widget::changeLineColor(const QColor &line_color) {
  lineColor = line_color;
  update();
}
/**
 * @brief Changes the line type
 *
 * @param arg
 */
void Widget::changeLineType(int arg) {
  checkLineType = arg;
  update();
}
/**
 * @brief Changes the line width
 *
 * @param arg
 */
void Widget::changeLineWidth(double arg) {
  lineWidth = arg;
  update();
}
/**
 * @brief Saves the settings
 *
 */
void Widget::saveSettings() {
  QSettings settings;
  settings.beginGroup("WidgetSettings");

  settings.setValue("checkCentral", checkCentral);
  settings.setValue("checkLineType", checkLineType);
  settings.setValue("checkPointType", checkPointType);
  settings.setValue("backgroundColor", backgroundColor);
  settings.setValue("vertexColor", vertexColor);
  settings.setValue("lineColor", lineColor);
  settings.setValue("lineWidth", lineWidth);
  settings.setValue("pointSize", pointSize);

  settings.endGroup();
}
/**
 * @brief Loads the settings
 *
 */
void Widget::loadSettings() {
  QSettings settings;
  settings.beginGroup("WidgetSettings");

  checkCentral = settings.value("checkCentral", 0).toInt();
  checkLineType = settings.value("checkLineType", 0).toInt();
  checkPointType = settings.value("checkPointType", 0).toInt();
  backgroundColor =
      settings.value("backgroundColor", QColorConstants::Black).value<QColor>();
  vertexColor =
      settings.value("vertexColor", QColorConstants::White).value<QColor>();
  lineColor =
      settings.value("lineColor", QColorConstants::Cyan).value<QColor>();
  lineWidth = settings.value("lineWidth", 0.1).toDouble();
  pointSize = settings.value("pointSize", 10.0).toDouble();

  settings.endGroup();
}
