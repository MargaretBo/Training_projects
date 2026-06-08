/**
 * @file CalcController.cc
 * @author morrigen
 * @brief This is an implemmentation of the controller
 * @version 0.1
 * @date 2024-06-25
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "CalcController.h"

using namespace s21;
/**
 * Calculates the result of the given equation using the provided variable `x`.
 *
 * @param equation The equation to be calculated.
 * @param x The variable `x` used in the equation.
 *
 * @return The result of the calculation.
 *
 * @throws None.
 */
int CalcController::PerformCalculation(std::string equation, double x) {
  return model->Calculator(equation, x);
}

double CalcController::GetResult() { return model->GetData(); }
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
int CalcController::PerformCreditCalculation(double amount, double percent,
                                             int period, int type) {
  return calcCredit->CalculateCredit(amount, percent, period, type);
}
/**
 * Retrieves the total payment amount from the associated CalcCredit object.
 *
 * @return The total payment amount.
 *
 * @throws None
 */
double CalcController::GetTotalPayment() {
  return calcCredit->GetTotalPayment();
}
/**
 * Retrieves the total interest amount from the associated CalcCredit object.
 *
 * @return The total interest amount.
 *
 * @throws None
 */
double CalcController::GetTotalInterest() {
  return calcCredit->GetTotalInterest();
}
/**
 * Retrieves the monthly payment queue from the associated CalcCredit object.
 *
 * @return The queue of monthly payment amounts.
 *
 * @throws None
 */
std::queue<double> CalcController::GetMonthlyPayment() {
  return calcCredit->GetMonthlyPayment();
}