/**
 * @file CalcModel.h
 * @author morrigen
 * @brief This is a header file for calculations in the model
 * @version 0.1
 * @date 2024-06-25
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef SMARTCALC_MODEL_CALCMODEL_H
#define SMARTCALC_MODEL_CALCMODEL_H

#include <cmath>
#include <queue>
#include <stack>
#include <string>

namespace s21 {
enum Operation {
  NUMBER = -1,
  PLUS = 1,
  MINUS = 2,
  MUL = 3,
  DIV = 4,
  MOD = 5,
  POW = 6,
  LEFT_BRACKET = 7,
  RIGHT_BRACKET = 8,
  COS = 9,
  SIN = 10,
  TAN = 11,
  ACOS = 12,
  ASIN = 13,
  ATAN = 14,
  SQRT = 15,
  LN = 16,
  LOG = 17,
  X_VALUE = 18
};

class StackToken;
/**
 * @brief This is a class for calculations in the model
 *
 */
class CalcModel {
 public:
  CalcModel() : data_(0){};
  int Calculator(std::string equation, double x);
  double GetData();

 private:
  int ParanthesisValidity(std::string equation);
  int ParceEquation(std::string equation, std::queue<StackToken> *parcedQueue);
  int Calculate(std::queue<StackToken> *RPNqueue, double x);
  int RevercePolishNotation(std::queue<StackToken> *parcedQueue,
                            std::queue<StackToken> *RPNqueue);
  void UnaryOperator(std::string equation, unsigned long int *index,
                     std::queue<StackToken> *parcedQueue);
  double data_;
};
/**
 * @brief This is a class for processing tokens in the equation
 *
 */
class StackToken {
 public:
  StackToken() : prioprity_(-1), number_(-1), operation_(-1){};
  int ParceToken(std::string equation, long unsigned int *index);
  void SetToken(int prioprity, double number, int operation);
  int GetPrioprity() { return prioprity_; }
  double GetNumber() { return number_; }
  int GetOperation() { return operation_; }

 private:
  int FunctionChecker(std::string equation, long unsigned int *index);
  int prioprity_;
  double number_;
  int operation_;
};

}  // namespace s21
#endif