/**
 * @file CalcController.h
 * @author morrigen
 * @brief This is a header file for the controller
 * @version 0.1
 * @date 2024-06-25
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef SMARTCALC_CONTROLLER_CALCCONTROLLER_H
#define SMARTCALC_CONTROLLER_CALCCONTROLLER_H

#include "../Model/CalcCredit.h"
#include "../Model/CalcModel.h"

namespace s21 {
/**
 * @brief This is a controller class
 *
 */
class CalcController {
 public:
  CalcController() {
    model = new CalcModel();
    calcCredit = new CalcCredit();
  };
  ~CalcController() {
    delete model;
    delete calcCredit;
  }
  int PerformCalculation(std::string equation, double x);
  double GetResult();
  int PerformCreditCalculation(double amount, double percent, int period,
                               int type);
  double GetTotalPayment();
  double GetTotalInterest();
  std::queue<double> GetMonthlyPayment();

 private:
  CalcModel *model;
  CalcCredit *calcCredit;
};
}  // namespace s21

#endif