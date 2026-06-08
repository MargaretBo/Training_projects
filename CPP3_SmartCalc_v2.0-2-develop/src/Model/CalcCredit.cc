/**
 * @file CalcCredit.cc
 * @author morrigen
 * @brief Credit calculations
 * @version 0.1
 * @date 2024-06-25
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "CalcCredit.h"

using namespace s21;
/**
 * Calculates the credit based on the amount, percent, period, and type.
 *
 * @param amount The principal amount of the credit
 * @param percent The interest rate of the credit
 * @param period The period for which the credit is taken
 * @param type The type of credit calculation method
 *
 * @return The calculated credit amount
 *
 * @throws None
 */
int CalcCredit::CalculateCredit(double amount, double percent, int period,
                                int type) {
  int result = 0;
  switch (type) {
    case 1:
      result = CalculateCreditAnnuity(amount, percent, period);
      break;
    case 2:
      result = CalculateCreditDifferentiated(amount, percent, period);
      break;
    default:
      result = -1;
      break;
  }
  return result;
}

/**
 * Calculates the annuity payment for a credit based on the principal amount,
 * interest rate, and period.
 *
 * @param amount The principal amount of the credit.
 * @param percent The interest rate of the credit, expressed as a decimal.
 * @param period The period for which the credit is taken, in months.
 *
 * @return The calculated annuity payment, rounded to two decimal places.
 *
 * @throws None
 */
int CalcCredit::CalculateCreditAnnuity(double amount, double percent,
                                       int period) {
  int result = 0;
  totalPayment_ = 0;
  totalInterest_ = 0;
  monthlyPayment_.push(
      amount * ((percent / 1200) / (1 - pow(1 + percent / 1200, -period))));
  totalPayment_ = std::round(monthlyPayment_.front() * 100) / 100 * period;
  totalInterest_ = totalPayment_ - amount;
  return result;
}

/**
 * Calculates the differentiated payment for a credit based on the principal
 * amount, interest rate, and period.
 *
 * @param amount The principal amount of the credit.
 * @param percent The interest rate of the credit, expressed as a decimal.
 * @param period The period for which the credit is taken, in months.
 *
 * @return The calculated differentiated payment.
 *
 * @throws None
 */
int CalcCredit::CalculateCreditDifferentiated(double amount, double percent,
                                              int period) {
  int result = 0;
  totalPayment_ = 0;
  totalInterest_ = 0;
  double mainPayment = amount / period;
  double monthlyPayment = 0;
  for (int i = 0; i < period; i++) {
    monthlyPayment =
        mainPayment + ((amount - mainPayment * i) * (percent / 1200));
    monthlyPayment_.push(monthlyPayment);
    totalPayment_ += monthlyPayment;
  }
  totalInterest_ = totalPayment_ - amount;
  return result;
}