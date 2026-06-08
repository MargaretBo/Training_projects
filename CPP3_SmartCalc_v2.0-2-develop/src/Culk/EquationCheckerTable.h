/**
 * @file EquationCheckerTable.h
 * @author morrigen
 * @brief This is a header file for checking equations
 * @version 0.1
 * @date 2024-06-25
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef SMARTCALC_CULK_EQCHECKER_H
#define SMARTCALC_CULK_EQCHECKER_H

#include <array>
#include <map>
#include <string>

namespace s21 {
/**
 * @brief This is a class for checking equations
 *
 */
class EquationCheckerTable {
 public:
  /**
   * Checks if the combination of two characters is valid.
   *
   * @param first_char The first character to check.
   * @param second_char The second character to check.
   *
   * @return The result of the check. Returns -1 if either character is not
   * valid.
   *
   * @throws None
   */
  int SymbolCombinationChecker(char first_char, char second_char) {
    int SymbolTable[24][24] = {
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
         1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0,
         0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
         0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1,
         0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1,
         0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1,
         0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1,
         0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1,
         0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1,
         0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0},
    };
    if (first_char >= '0' && first_char <= '9') first_char = '1';
    if (second_char >= '0' && second_char <= '9') second_char = '1';
    std::map<char, int> table_connection = {
        {'m', 0},  {'d', 1},  {'c', 2},  {'o', 3},  {'s', 4},  {'i', 5},
        {'n', 6},  {'t', 7},  {'a', 8},  {'q', 9},  {'r', 10}, {'l', 11},
        {'g', 12}, {'(', 13}, {')', 14}, {'x', 15}, {'+', 16}, {'-', 17},
        {'*', 18}, {'/', 19}, {'^', 20}, {'1', 21}, {'.', 22}, {'e', 23}};
    if (table_connection.find(first_char) == table_connection.end() ||
        table_connection.find(second_char) == table_connection.end())
      return -1;
    return SymbolTable[table_connection[first_char]]
                      [table_connection[second_char]];
  }
  /**
   * A function to check if the input symbol is a binary operator.
   *
   * @param symbol the symbol to check
   *
   * @return 1 if the symbol is a binary operator, 0 otherwise
   *
   * @throws None
   */
  int IsBinaryOperator(char symbol) {
    if (symbol == '*' || symbol == '/' || symbol == '^') {
      return 1;
    } else {
      return 0;
    }
  }
  /**
   * Checks the initial part of an equation for correctness.
   *
   * @param equation The equation to be checked.
   *
   * @return -1 if the equation is invalid, 0 if it is valid.
   *
   * @throws None.
   */
  int InitialEquationChecker(std::string equation) {
    int length = equation.length();
    if (equation[0] == 'm' || IsBinaryOperator(equation[0])) return -1;
    if (length < 2 &&
        (equation[0] == 'x' || (equation[0] >= '0' && equation[0] <= '9'))) {
      return 0;
    } else if (length < 2)
      return -1;
    else {
      for (int i = 0; i < length - 1; i++) {
        int result = SymbolCombinationChecker(equation[i], equation[i + 1]);
        if (result == -1) return -1;
        if (result == 0) return -1;
      }
    }
    if (equation[length - 1] != ')' && equation[length - 1] != 'x' &&
        (equation[length - 1] < '0' || equation[length - 1] > '9')) {
      return -1;
    }
    return 0;
  }
};
}  // namespace s21

#endif