#ifndef WIDGET_H
#define WIDGET_H

#define GL_SILENCE_DEPRECATION
#include <QOpenGLWidget>
#include <QSettings>

#include "../Controller/Controller.h"

using namespace s21;

class Widget : public QOpenGLWidget {
  Q_OBJECT
 public:
  explicit Widget(QWidget* parent = nullptr);
  ~Widget();

  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();
  void getArrays(std::string path);
  void getMoveX(double arg1);
  void getMoveY(double arg1);
  void getMoveZ(double arg1);
  void getRotX(double arg1);
  void getRotY(double arg1);
  void getRotZ(double arg1);
  void getScale(double arg1);
  int getCountVertices();
  int getCountFaces();
  void checkCentralProjection(int arg);
  void changeBackgroundColor(const QColor& back_color);
  void changeVertexColor(const QColor& vertex_color);
  void changeVertexType(int arg);
  void changeVertexSize(int arg);
  void changeLineColor(const QColor& line_color);
  void changeLineType(int arg);
  void changeLineWidth(double arg);

 protected:
 private:
  Controller* controller;
  float xRot = 0, yRot = 0, zRot = 0;
  float xMove = 0, yMove = 0, zMove = 0;
  float scaleValue = 1;
  int checkCentral = 0;
  int checkLineType = 0;
  int checkPointType = 0;
  QColor backgroundColor = QColorConstants::Black;
  QColor vertexColor = QColorConstants::White;
  QColor lineColor = QColorConstants::Cyan;
  double lineWidth = 0.1;
  double pointSize = 10;
  void saveSettings();
  void loadSettings();
};

#endif  // WIDGET_H
