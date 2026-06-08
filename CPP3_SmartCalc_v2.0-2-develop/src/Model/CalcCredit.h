/**
 * @file CalcCredit.h
 * @author morrigen
 * @brief This is a header file for calculating credit
 * @version 0.1
 * @date 2024-06-25
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef SMARTCALC_MODEL_CALCCREDIT_H
#define SMARTCALC_MODEL_CALCCREDIT_H

#include <cmath>
#include <queue>

namespace s21 {
class CalcCredit {
 public:
  CalcCredit() = default;
  ~CalcCredit() = default;
  int CalculateCredit(double amount, double percent, int period, int type);
  std::queue<double> GetMonthlyPayment() { return monthlyPayment_; }
  double GetTotalPayment() { return totalPayment_; }
  double GetTotalInterest() { return totalInterest_; }

 private:
  int CalculateCreditAnnuity(double amount, double percent, int period);
  int CalculateCreditDifferentiated(double amount, double percent, int period);
  std::queue<double> monthlyPayment_{};
  double totalPayment_{};
  double totalInterest_{};
};
}  // namespace s21

#endif  // CALC_CREDIT_H