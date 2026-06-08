#include "mainwindow.h"

#include <QColorDialog>
#include <QOpenGLWidget>
#include <QPainter>

#include "../Controller/Controller.h"
#include "../gif/gif.h"
#include "ui_mainwindow.h"
/**
 * @brief Construct a new Main Window:: Main Window object
 *
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  loadSettings();
}
/**
 * @brief Destroy the Main Window:: Main Window object
 *
 */
MainWindow::~MainWindow() {
  saveSettings();
  delete ui;
}
/**
 * @brief Opens the file dialog and sends the path to the model
 *
 */
void MainWindow::on_open_file_clicked() {
  QString m_path;
  m_path = QFileDialog::getOpenFileName(this, "Выбор файла", "~/",
                                        "Объектные файлы (*.obj)");
  ui->name_file->setText(m_path);
  std::string pathString = ui->name_file->text().toStdString();
  ui->openGLWidget->getArrays(pathString);
  ui->vertices->setText(QString::number(ui->openGLWidget->getCountVertices()));
  ui->edges->setText(QString::number(ui->openGLWidget->getCountFaces()));
  ui->openGLWidget->update();
  ui->transl_x->setValue(0.f);
  ui->transl_y->setValue(0.f);
  ui->transl_z->setValue(0.f);
  ui->rotat_x->setValue(0.f);
  ui->rotat_y->setValue(0.f);
  ui->rotat_z->setValue(0.f);
  ui->scale_val->setValue(1.0);
}
/**
 * @brief Opens the color dialog and changes the background color
 *
 */
void MainWindow::on_back_color_clicked() {
  QColor back_color =
      QColorDialog::getColor(Qt::white, this, "Select background color");

  if (back_color.isValid()) {
    ui->openGLWidget->changeBackgroundColor(back_color);
  }
}
/**
 * @brief Opens the color dialog and changes the vertex color
 *
 */
void MainWindow::on_vertex_color_clicked() {
  QColor vertex_color =
      QColorDialog::getColor(Qt::white, this, "Select vertex color");

  if (vertex_color.isValid()) {
    ui->openGLWidget->changeVertexColor(vertex_color);
  }
}
/**
 * @brief Opens the color dialog and changes the line color
 *
 */
void MainWindow::on_line_color_clicked() {
  QColor line_color =
      QColorDialog::getColor(Qt::white, this, "Select line color");

  if (line_color.isValid()) {
    ui->openGLWidget->changeLineColor(line_color);
  }
}
/**
 * @brief Sends the value for transition along the X axis to the model and
 * updates the view
 *
 * @param arg1 - value
 */
void MainWindow::on_transl_x_valueChanged(double arg1) {
  ui->openGLWidget->getMoveX(arg1);
  ui->openGLWidget->update();
}
/**
 * @brief Sends the value for transition along the Y axis to the model and
 * updates the view
 *
 * @param arg1 - value
 */
void MainWindow::on_transl_y_valueChanged(double arg1) {
  ui->openGLWidget->getMoveY(arg1);
  ui->openGLWidget->update();
}
/**
 * @brief Sends the value for transition along the Z axis to the model and
 * updates the view
 *
 * @param arg1 - value
 */
void MainWindow::on_transl_z_valueChanged(double arg1) {
  ui->openGLWidget->getMoveZ(arg1);
  ui->openGLWidget->update();
}
/**
 * @brief Sends the value for rotation about the X axis to the model and updates
 * the view
 *
 * @param arg1 - value
 */
void MainWindow::on_rotat_x_valueChanged(double arg1) {
  ui->openGLWidget->getRotX(arg1);
  ui->openGLWidget->update();
}
/**
 * @brief Sends the value for rotation about the Y axis to the model and updates
 * the view
 *
 * @param arg1 - value
 */
void MainWindow::on_rotat_y_valueChanged(double arg1) {
  ui->openGLWidget->getRotY(arg1);
  ui->openGLWidget->update();
}
/**
 * @brief Sends the value for rotation about the Z axis to the model and updates
 * the view
 *
 * @param arg1 - value
 */
void MainWindow::on_rotat_z_valueChanged(double arg1) {
  ui->openGLWidget->getRotZ(arg1);
  ui->openGLWidget->update();
}
/**
 * @brief Sends the value for scaling to the model and updates the view
 *
 * @param arg1 - value
 */
void MainWindow::on_scale_val_valueChanged(double arg1) {
  ui->openGLWidget->getScale(arg1);
  ui->openGLWidget->update();
}

void MainWindow::mousePressEvent(QMouseEvent *event) { mPos = event->pos(); }

/**
 * @brief This function is for rotating the figure about X and Y axis with mouse
 * movements
 *
 * @param event
 */
void MainWindow::mouseMoveEvent(QMouseEvent *event) {
  double xRot = (event->pos().y() - mPos.y()) / M_PI;
  double yRot = (event->pos().x() - mPos.x()) / M_PI;
  ui->rotat_x->setValue(ui->rotat_x->value() + xRot);
  ui->rotat_y->setValue(ui->rotat_y->value() + yRot);
  mPos = event->pos();
}
/**
 * @brief Changes the projection of the figure to central
 *
 */
void MainWindow::on_central_clicked() {
  ui->openGLWidget->checkCentralProjection(1);
}
/**
 * @brief Changes the projection of the figure to parallel
 *
 */
void MainWindow::on_parallel_clicked() {
  ui->openGLWidget->checkCentralProjection(0);
}
/**
 * @brief Changes the line type to dashed
 *
 */
void MainWindow::on_dashed_clicked() { ui->openGLWidget->changeLineType(1); }
/**
 * @brief Changes the line type to solid
 *
 */

void MainWindow::on_solid_clicked() { ui->openGLWidget->changeLineType(0); }
/**
 * @brief Changes the line width to the value
 *
 * @param arg1 - value
 */
void MainWindow::on_line_size_spinBox_valueChanged(int arg1) {
  ui->openGLWidget->changeLineWidth(arg1 / 10.);
}
/**
 * @brief Changes the vertex type to no vertex
 *
 */
void MainWindow::on_method_none_clicked() {
  ui->openGLWidget->changeVertexType(0);
}
/**
 * @brief Changes the vertex type to circle
 *
 */
void MainWindow::on_method_circle_clicked() {
  ui->openGLWidget->changeVertexType(1);
}
/**
 * @brief Changes the vertex type to square
 *
 */
void MainWindow::on_method_square_clicked() {
  ui->openGLWidget->changeVertexType(2);
}
/**
 * @brief Changes the vertex size to the value after spinbox is changed
 *
 * @param arg1 - value
 */
void MainWindow::on_vertex_size_spinBox_valueChanged(int arg1) {
  ui->openGLWidget->changeVertexSize(arg1 / 10.);
}
/**
 * @brief Saves an image of the figure in jpeg format
 *
 */
void MainWindow::on_save_jpeg_clicked() {
  QDateTime currentDateTime = QDateTime::currentDateTime();
  QString nameSecondPart = currentDateTime.toString("_dd.MM.yyyy_hh.mm.ss");
  QString name = "~/Cнимок экрана" + nameSecondPart;
  QString fileName = QFileDialog::getSaveFileName(this, "Сохранение файла",
                                                  name, "JPEG (*.jpeg)");
  if (fileName != "") {
    QImage pic(ui->openGLWidget->size(), QImage::Format_RGB32);
    QPainter m_painter(&pic);
    ui->openGLWidget->render(&m_painter);
    pic.save(fileName);
  }
}
/**
 * @brief Saves an image of the figure in bmp format
 *
 */
void MainWindow::on_save_bmp_clicked() {
  QDateTime currentDateTime = QDateTime::currentDateTime();
  QString nameSecondPart = currentDateTime.toString("_dd.MM.yyyy_hh.mm.ss");
  QString name = "~/Cнимок экрана" + nameSecondPart;
  QString fileName = QFileDialog::getSaveFileName(this, "Сохранение файла",
                                                  name, "BMP (*.bmp)");
  if (fileName != "") {
    QImage pic(ui->openGLWidget->size(), QImage::Format_RGB32);
    QPainter m_painter(&pic);
    ui->openGLWidget->render(&m_painter);
    pic.save(fileName);
  }
}
/**
 * @brief Saves the settings
 *
 */
void MainWindow::saveSettings() {
  QSettings settings;
  settings.beginGroup("Settings");

  settings.setValue("checkCentral", ui->central->isChecked());
  settings.setValue("checkLineType", ui->dashed->isChecked());
  settings.setValue("checkPointTypeBall", ui->method_circle->isChecked());
  settings.setValue("checkPointTypeSquare", ui->method_square->isChecked());
  settings.setValue("lineWidth", ui->line_size_spinBox->value());
  settings.setValue("pointSize", ui->vertex_size_spinBox->value());

  settings.endGroup();
}
/**
 * @brief Loads the settings
 *
 */
void MainWindow::loadSettings() {
  QSettings settings;
  settings.beginGroup("Settings");
  if (settings.value("checkCentral", 0).toBool())
    ui->central->setChecked(true);
  else
    ui->parallel->setChecked(true);
  if (settings.value("checkLineType", 0).toBool())
    ui->dashed->setChecked(true);
  else
    ui->solid->setChecked(true);
  if (settings.value("checkPointTypeBall", 0).toBool())
    ui->method_circle->setChecked(true);
  else if (settings.value("checkPointTypeSquare", 0).toBool())
    ui->method_square->setChecked(true);
  else
    ui->method_none->setChecked(true);
  ui->line_size_spinBox->setValue(settings.value("lineWidth", 100).toInt());
  ui->vertex_size_spinBox->setValue(settings.value("pointSize", 10).toInt());

  settings.endGroup();
}
/**
 * @brief A function that delays the program for a certain amount of time
 *
 * @param interval - amount of time to delay
 */
void MainWindow::shortDelay(int interval) {
  QTimer timer;
  timer.setSingleShot(true);
  timer.setInterval(interval);
  QEventLoop loop;
  QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
  timer.start();
  loop.exec();
}
/**
 * @brief Saves a gif of the figure
 *
 */
void MainWindow::on_save_gif_clicked() {
  QVector<QImage> frames;
  int framesNumber = 50;
  for (int i = 0; i < framesNumber; i++) {
    QImage frame = ui->openGLWidget->grab()
                       .scaled(640, 480, Qt::IgnoreAspectRatio)
                       .toImage();
    frames.append(frame);
    shortDelay(100);
  }
  QDateTime currentDateTime = QDateTime::currentDateTime();
  QString nameSecondPart = currentDateTime.toString("_dd.MM.yyyy_hh.mm.ss");
  QString name = "~/Запись экрана" + nameSecondPart;
  QString fileName = QFileDialog::getSaveFileName(this, "Сохранение файла",
                                                  name, "GIF (*.gif)");
  GifWriter gwriter;
  GifBegin(&gwriter, fileName.toLocal8Bit(), 640, 480, 10, 8, false);
  for (int i = 0; i < framesNumber; i++) {
    GifWriteFrame(&gwriter,
                  frames[i]
                      .convertToFormat(QImage::Format_Indexed8)
                      .convertToFormat(QImage::Format_RGBA8888)
                      .constBits(),
                  640, 480, 10, 8, false);
  }
  GifEnd(&gwriter);
}
