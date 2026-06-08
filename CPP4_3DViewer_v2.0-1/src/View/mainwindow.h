#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define GL_SILENCE_DEPRECATION

#include <QFileDialog>
#include <QMainWindow>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QSettings>
#include <QTimer>

#include "../Controller/Controller.h"

using namespace s21;

enum { kGIF = 0, kJPG = 1, kBMP = 2 };

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
/**
 * @brief This class is for the main window of the project.
 *
 */
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_open_file_clicked();

  void on_back_color_clicked();

  void on_vertex_color_clicked();

  void on_line_color_clicked();

  void on_transl_x_valueChanged(double arg1);

  void on_transl_y_valueChanged(double arg1);

  void on_transl_z_valueChanged(double arg1);

  void on_rotat_x_valueChanged(double arg1);

  void on_rotat_y_valueChanged(double arg1);

  void on_rotat_z_valueChanged(double arg1);

  void on_scale_val_valueChanged(double arg1);
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);

  void on_central_clicked();

  void on_parallel_clicked();

  void on_dashed_clicked();

  void on_solid_clicked();

  void on_line_size_spinBox_valueChanged(int arg1);

  void on_method_none_clicked();

  void on_method_circle_clicked();

  void on_method_square_clicked();

  void on_vertex_size_spinBox_valueChanged(int arg1);

  void on_save_jpeg_clicked();
  void on_save_bmp_clicked();
  void saveSettings();
  void loadSettings();
  void shortDelay(int interval);

  void on_save_gif_clicked();

 private:
  Ui::MainWindow *ui;
  QPoint mPos;
};
#endif  // MAINWINDOW_H
