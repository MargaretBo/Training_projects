/**
 * @file mainwindow.cpp
 * @author morrigen
 * @brief This file contains the implementation of the View
 * @version 0.1
 * @date 2024-06-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "mainwindow.h"

#include <iostream>

#include "ui_mainwindow.h"

using namespace s21;

double defaultValue = 0;
double defaultUpperValue = 10;
double defaultLowerValue = -10;

/**
 * Function to check if the input string is a removable value.
 *
 * @param input The input string to be checked.
 *
 * @return true if the input is a removable value, false otherwise.
 */
int RemovableString(QString input) {
  return (input == "0") || (input == "0.000000") || (input == "inf") ||
         (input == "-inf") || (input == "nan") ||
         (input == "Invalid expression");
}

/**
 * Constructor for the MainWindow class.
 *
 * @param parent A pointer to the parent widget.
 *
 * @return void
 *
 * @throws None
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->Display->setText(QString::number(defaultValue));

  ui->LineEditForX->setText(QString::number(defaultValue));

  //  ui->UpperLimitOfX->setText(QString::number(defaultUpperValue));
  //  ui->UpperLimitOfY->setText(QString::number(defaultUpperValue));
  //  ui->LowerLimitOfX->setText(QString::number(defaultLowerValue));
  //  ui->LowerLimitOfY->setText(QString::number(defaultLowerValue));

  QPushButton *numberButton[10];
  for (int i = 0; i < 10; ++i) {
    QString buttonName = "Button" + QString::number(i);
    numberButton[i] = MainWindow::findChild<QPushButton *>(buttonName);
    connect(numberButton[i], SIGNAL(released()), this, SLOT(NumberPressed()));
  }
  connect(ui->XButton, SIGNAL(released()), this, SLOT(NumberPressed()));
  connect(ui->LeftBracketButton, SIGNAL(released()), this,
          SLOT(NumberPressed()));
  connect(ui->RightBracketButton, SIGNAL(released()), this,
          SLOT(NumberPressed()));
  connect(ui->DivisionButton, SIGNAL(released()), this,
          SLOT(BinaryOperatorPressed()));
  connect(ui->MultiplicationButton, SIGNAL(released()), this,
          SLOT(BinaryOperatorPressed()));
  connect(ui->AdditionButton, SIGNAL(released()), this,
          SLOT(BinaryOperatorPressed()));
  connect(ui->SubstractionButton, SIGNAL(released()), this,
          SLOT(BinaryOperatorPressed()));
  connect(ui->ModButton, SIGNAL(released()), this,
          SLOT(BinaryOperatorPressed()));
  connect(ui->PowerButton, SIGNAL(released()), this,
          SLOT(BinaryOperatorPressed()));
  connect(ui->PeriodButton, SIGNAL(released()), this,
          SLOT(PeriodButtonPressed()));
  connect(ui->ClearButton, SIGNAL(released()), this,
          SLOT(ClearButtonPressed()));
  connect(ui->SinButton, SIGNAL(released()), this,
          SLOT(UnaryOperatorPressed()));
  connect(ui->CosButton, SIGNAL(released()), this,
          SLOT(UnaryOperatorPressed()));
  connect(ui->TanButton, SIGNAL(released()), this,
          SLOT(UnaryOperatorPressed()));
  connect(ui->AsinButton, SIGNAL(released()), this,
          SLOT(UnaryOperatorPressed()));
  connect(ui->AcosButton, SIGNAL(released()), this,
          SLOT(UnaryOperatorPressed()));
  connect(ui->AtanButton, SIGNAL(released()), this,
          SLOT(UnaryOperatorPressed()));
  connect(ui->SqrtButton, SIGNAL(released()), this,
          SLOT(UnaryOperatorPressed()));
  connect(ui->LnButton, SIGNAL(released()), this, SLOT(UnaryOperatorPressed()));
  connect(ui->LogButton, SIGNAL(released()), this,
          SLOT(UnaryOperatorPressed()));
  connect(ui->EqualsButton, SIGNAL(released()), this,
          SLOT(EqualButtonPressed()));
  connect(ui->TheButton, SIGNAL(released()), this, SLOT(PlotButtonPressed()));
  connect(ui->Calculate_button, SIGNAL(released()), this,
          SLOT(CreditCalcButtonPressed()));
}

MainWindow::~MainWindow() { delete ui; }
/**
 * Handles the event when a number button is pressed.
 *
 * @throws None
 */
void MainWindow::NumberPressed() {
  QPushButton *button = (QPushButton *)sender();
  QString buttonValue = button->text();
  QString newDisplayValue;
  QString displayValue;
  if (ui->Display->hasFocus()) {
    displayValue = ui->Display->text();
    if (RemovableString(displayValue)) {
      ui->Display->setText(buttonValue);
    } else {
      newDisplayValue = displayValue + buttonValue;
      ui->Display->setText(newDisplayValue);
    }
  } else if (ui->LineEditForX->hasFocus()) {
    if (buttonValue != "x") {
      displayValue = ui->LineEditForX->text();
      if (RemovableString(displayValue)) {
        ui->LineEditForX->setText(buttonValue);
      } else {
        newDisplayValue = displayValue + buttonValue;
        ui->LineEditForX->setText(newDisplayValue);
      }
    }
  }
}

/**
 * Handles the event when a binary operator button is pressed.
 */
void MainWindow::BinaryOperatorPressed() {
  QString displayValue = ui->Display->text();
  QPushButton *button = (QPushButton *)sender();
  QString buttonValue = button->text();
  QString newDisplayValue = displayValue + buttonValue;
  ui->Display->setText(newDisplayValue);
}
/**
 * Handles the event when a period button is pressed.
 *
 * @throws None
 */
void MainWindow::PeriodButtonPressed() {
  QPushButton *button = (QPushButton *)sender();
  QString buttonValue = button->text();
  QString displayValue;
  QString newDisplayValue;
  if (ui->Display->hasFocus()) {
    displayValue = ui->Display->text();
    newDisplayValue = displayValue + buttonValue;
    ui->Display->setText(newDisplayValue);
  } else if (ui->LineEditForX->hasFocus()) {
    displayValue = ui->LineEditForX->text();
    newDisplayValue = displayValue + buttonValue;
    ui->LineEditForX->setText(newDisplayValue);
  }
}
/**
 * Handles the event when a unary operator button is pressed.
 *
 * @throws None
 */
void MainWindow::UnaryOperatorPressed() {
  QString displayValue = ui->Display->text();
  QPushButton *button = (QPushButton *)sender();
  QString buttonValue = button->text();
  if (RemovableString(displayValue)) {
    QString newDisplayValue = buttonValue + "(";
    ui->Display->setText(newDisplayValue);
  } else {
    QString newDisplayValue = displayValue + buttonValue + "(";
    ui->Display->setText(newDisplayValue);
  }
}

/**
 * Handles the event when the equal button is pressed in the MainWindow.
 *
 * This function retrieves the equation from the display and the value of X from
 * the line edit. It then checks the validity of the equation and the value of X
 * using the EquationCheckerTable. If both are valid, it performs the
 * calculation using the CalcController and updates the display accordingly. If
 * the value of X is not a number, it displays an error message. If the equation
 * is invalid, it displays an error message. If both are invalid, it displays an
 * error message.
 *
 * @return void
 *
 * @throws None
 */
void MainWindow::EqualButtonPressed() {
  std::string equation = ui->Display->text().toStdString();
  bool validityOfX = false;
  double valueOfX = ui->LineEditForX->text().toDouble(&validityOfX);
  EquationCheckerTable eqCheck;
  int validityOfEquation = eqCheck.InitialEquationChecker(equation);
  if (validityOfX && validityOfEquation == 0) {
    CalcController controller;
    int error = controller.PerformCalculation(equation, valueOfX);
    if (!error) {
      ui->Display->setText(QString::number(controller.GetResult(), 'g', 7));
    } else {
      ui->Display->setText("Invalid expression");
    }
  } else if (!validityOfX) {
    ui->Display->setText("X must be a number");
  } else {
    ui->Display->setText("Invalid input");
  }
}
/**
 * Handles the event when the credit calculation button is pressed in the
 * MainWindow.
 *
 * This function retrieves the loan amount, loan term, and interest rate from
 * the UI and checks their validity. If all inputs are valid and satisfy the
 * conditions, it creates a CalcController object and performs a credit
 * calculation using the PerformCreditCalculation method. The total payment and
 * total interest are then displayed in the UI. If the inputs are invalid, an
 * error message is displayed.
 *
 * @throws None
 */
void MainWindow::CreditCalcButtonPressed() {
  bool validityOfAmount = false;
  bool validityOfTerm = false;
  bool validityOfInterest = false;
  double amount = ui->Loan_Amount->text().toDouble(&validityOfAmount);
  int term = ui->Loan_Term->text().toInt(&validityOfTerm);
  double interest = ui->Interest_Rate->text().toDouble(&validityOfInterest);
  if (validityOfAmount && validityOfTerm && validityOfInterest && amount > 0 &&
      term > 0 && interest > 0 && interest < 100) {
    CalcController controller;
    if (ui->Annuity->isChecked()) {
      controller.PerformCreditCalculation(amount, interest, term, 1);
    } else {
      controller.PerformCreditCalculation(amount, interest, term, 2);
    }
    ui->Total_Amount->setText(
        QString::number(controller.GetTotalPayment(), 'f', 2));
    ui->Total_Interest->setText(
        QString::number(controller.GetTotalInterest(), 'f', 2));
    QueueToList(controller.GetMonthlyPayment());
  } else
    ui->Display->setText("Invalid input");
}
/**
 * Populates the Monthly_Payments list widget with the values from the given
 * queue of doubles.
 *
 * @param que The queue of doubles to populate the list widget with.
 *
 * @throws None
 */
void MainWindow::QueueToList(std::queue<double> que) {
  ui->Monthly_Payments->clear();
  QStringList list;
  while (!que.empty()) {
    QString temp = QString::number(que.front(), 'f', 2);
    que.pop();
    list.push_front(temp);
  }
  foreach (QString item, list) {
    ui->Monthly_Payments->addItem(item);
  }
}
/**
 * Handles the event when the clear button is pressed in the MainWindow.
 *
 * @param None
 *
 * @return void
 *
 * @throws None
 */
void MainWindow::ClearButtonPressed() {
  ui->Display->setText(QString::number(defaultValue));
}
/**
 * Handles the event when the plot button is pressed in the MainWindow. Plots a
 * graph of a function provided by the user
 *
 * @throws None
 */
void MainWindow::PlotButtonPressed() {
  double upperLimitOfX = ui->UpperLimitOfX->text().toDouble();
  double upperLimitOfY = ui->UpperLimitOfY->text().toDouble();
  double lowerLimitOfX = ui->LowerLimitOfX->text().toDouble();
  double lowerLimitOfY = ui->LowerLimitOfY->text().toDouble();
  double intervalX = upperLimitOfX - lowerLimitOfX;
  double intervalY = upperLimitOfY - lowerLimitOfY;
  if (intervalX <= 0 || intervalY <= 0) {
    ui->Display->setText(
        "The upper limit should be higher than the lower one.");
  } else {
    std::string equation = ui->Display->text().toStdString();
    int numberOfPoints = (intervalX > 100) ? 5000 : 700;
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setPen(QPen(Qt::green));
    QVector<double> x1(numberOfPoints), y1(numberOfPoints);
    double step = intervalX / (double)numberOfPoints;
    int error = 0;
    EquationCheckerTable eqCheck;
    int validityOfEquation = eqCheck.InitialEquationChecker(equation);
    if (validityOfEquation == 0) {
      for (int i = 0; i < numberOfPoints; ++i) {
        x1[i] = lowerLimitOfX + i * step;

        CalcController controller;
        int error = controller.PerformCalculation(equation, x1[i]);
        ;
        if (!error) {
          y1[i] = controller.GetResult();
        } else {
          break;
        }
      }
    }
    if (!error && validityOfEquation == 0) {
      ui->customPlot->xAxis2->setVisible(true);
      ui->customPlot->xAxis2->setTickLabels(false);
      ui->customPlot->yAxis2->setVisible(true);
      ui->customPlot->yAxis2->setTickLabels(false);
      connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)),
              ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
      connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)),
              ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));
      ui->customPlot->graph(0)->setData(x1, y1);
      ui->customPlot->graph(0)->rescaleAxes();
      ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                                      QCP::iSelectPlottables);
      ui->customPlot->xAxis->setRange(lowerLimitOfX, upperLimitOfX);
      ui->customPlot->yAxis->setRange(lowerLimitOfY, upperLimitOfY);
    } else {
      ui->Display->setText("Invalid expression");
    }
  }
}
