/**
 * @file mainwindow.h
 * @author morrigen
 * @brief This is a header for the view implementation
 * @version 0.1
 * @date 2024-06-25
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "../Controller/CalcController.h"
#include "EquationCheckerTable.h"

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
  void NumberPressed();
  void EqualButtonPressed();
  void UnaryOperatorPressed();
  void BinaryOperatorPressed();
  void ClearButtonPressed();
  void PeriodButtonPressed();
  void PlotButtonPressed();
  void CreditCalcButtonPressed();
  void QueueToList(std::queue<double> que);

 private:
  Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
