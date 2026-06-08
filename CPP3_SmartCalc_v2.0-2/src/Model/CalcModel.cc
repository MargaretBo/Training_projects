/**
 * @file CalcModel.cc
 * @author morrigen
 * @brief This is a source file for calculations in the model
 * @version 0.1
 * @date 2024-06-25
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "CalcModel.h"

using namespace s21;

double CalcModel::GetData() { return data_; }
/**
 * Set the priority, number, and operation for the StackToken.
 *
 * @param prioprity the priority value to set
 * @param number the number value to set
 * @param operation the operation value to set
 */
void StackToken::SetToken(int prioprity, double number, int operation) {
  prioprity_ = prioprity;
  number_ = number;
  operation_ = operation;
}
/**
 * Parses a token from the given equation at the specified index.
 *
 * @param equation The equation to parse from.
 * @param index Pointer to the current index in the equation.
 *
 * @return Returns 0 if the token was successfully parsed, -1 if the token is
 * invalid.
 *
 * @throws None
 */
int StackToken::ParceToken(std::string equation, long unsigned int *index) {
  int result = 0;
  if (equation[*index] <= '9' && equation[*index] >= '0') {
    std::string sub = equation.substr(*index);
    size_t pos;
    double num = std::stod(sub, &pos);
    SetToken(-1, num, -1);
    *index = *index + pos - 1;
  } else if (equation[*index] == '+') {
    SetToken(1, -1, PLUS);
  } else if (equation[*index] == '-') {
    SetToken(1, -1, MINUS);
  } else if (equation[*index] == '*') {
    SetToken(2, -1, MUL);
  } else if (equation[*index] == '/') {
    SetToken(2, -1, DIV);
  } else if (equation[*index] == '^') {
    SetToken(3, -1, POW);
  } else if (equation[*index] == '(') {
    SetToken(0, -1, LEFT_BRACKET);
  } else if (equation[*index] == ')') {
    SetToken(0, -1, RIGHT_BRACKET);
  } else if (equation[*index] == 'x') {
    SetToken(-1, -1, X_VALUE);
  } else if (equation[*index] >= 'a' && equation[*index] <= 't') {
    result = FunctionChecker(equation, index);
  } else
    result = -1;
  *index = *index + 1;
  return result;
}

/**
 * Parses a token from the given equation at the specified index.
 *
 * @param equation The equation to parse from.
 * @param index Pointer to the current index in the equation.
 *
 * @return Returns 0 if the token was successfully parsed, 1 if the token is
 * invalid.
 *
 * @throws None
 */
int StackToken::FunctionChecker(std::string equation,
                                long unsigned int *index) {
  int result = 0;
  if (equation[*index] == 's') {
    if (equation[*index + 1] == 'i') {
      SetToken(3, -1, SIN);
      *index += 2;
    } else if (equation[*index + 1] == 'q') {
      SetToken(3, -1, SQRT);
      *index += 3;
    }
  } else if (equation[*index] == 'c') {
    SetToken(3, -1, COS);
    *index += 2;
  } else if (equation[*index] == 't') {
    SetToken(3, -1, TAN);
    *index += 2;
  } else if (equation[*index] == 'l') {
    if (equation[*index + 1] == 'n') {
      SetToken(3, -1, LN);
      *index += 1;
    } else if (equation[*index + 1] == 'o') {
      SetToken(3, -1, LOG);
      *index += 2;
    }
  } else if (equation[*index] == 'a') {
    if (equation[*index + 1] == 'c') {
      SetToken(3, -1, ACOS);
      *index += 3;
    } else if (equation[*index + 1] == 's' && equation[*index + 2] == 'i') {
      SetToken(3, -1, ASIN);
      *index += 3;
    } else if (equation[*index + 1] == 't' && equation[*index + 2] == 'a') {
      SetToken(3, -1, ATAN);
      *index += 3;

    } else
      return 1;
  } else if (equation[*index] == 'm') {
    SetToken(1, -1, MOD);
    *index += 2;
  } else
    result = 1;
  return result;
}

/**
 * Processes unary operators in the given equation.
 *
 * @param equation The equation to process.
 * @param index Pointer to the current index in the equation.
 * @param parcedQueue The queue to store parsed tokens.
 *
 * @throws None.
 */
void CalcModel::UnaryOperator(std::string equation, unsigned long int *index,
                              std::queue<StackToken> *parcedQueue) {
  switch (equation[*index]) {
    case '+':
      if (*index == 0 || equation[*index - 1] == '(') {
        *index += 1;
      }
      break;
    case '-':
      if (*index == 0 || equation[*index - 1] == '(') {
        StackToken temp;
        temp.SetToken(-1, 0, -1);
        parcedQueue->push(temp);
      }
      break;
    default:
      break;
  }
}

/**
 * Parses the given equation and stores the parsed tokens in the provided queue.
 *
 * @param equation The equation to parse.
 * @param parcedQueue The queue to store the parsed tokens.
 *
 * @return 0 if the parsing is successful, otherwise an error code.
 *
 * @throws None.
 */
int CalcModel::ParceEquation(std::string equation,
                             std::queue<StackToken> *parcedQueue) {
  long unsigned int index = 0;
  int result = 0;
  while (index < equation.length() && result == 0) {
    StackToken temp;
    if (equation[index] == '-' || equation[index] == '+') {
      UnaryOperator(equation, &index, parcedQueue);
    }
    result = temp.ParceToken(equation, &index);
    if (result == 0) {
      parcedQueue->push(temp);
    }
  }
  return result;
}

/**
 * Converts the given parsed queue of tokens to Reverse Polish Notation (RPN)
 * using the Shunting Yard algorithm.
 *
 * @param parcedQueue The parsed queue of tokens.
 * @param RPNqueue The queue to store the RPN tokens.
 *
 * @return 0 if the conversion is successful, otherwise an error code.
 *
 * @throws None.
 */
int CalcModel::RevercePolishNotation(std::queue<StackToken> *parcedQueue,
                                     std::queue<StackToken> *RPNqueue) {
  int result = 0;
  std::stack<StackToken> RPNstack;
  while (!parcedQueue->empty() && result == 0) {
    StackToken temp = parcedQueue->front();
    parcedQueue->pop();
    switch (temp.GetOperation()) {
      case NUMBER:
      case X_VALUE:
        RPNqueue->push(temp);
        break;
      case COS:
      case SIN:
      case TAN:
      case SQRT:
      case LN:
      case LOG:
      case ACOS:
      case ASIN:
      case ATAN:
        RPNstack.push(temp);
        break;
      case PLUS:
      case MINUS:
      case MUL:
      case DIV:
      case POW:
      case MOD:
        while (!RPNstack.empty() &&
               RPNstack.top().GetOperation() != LEFT_BRACKET &&
               (RPNstack.top().GetPrioprity() > temp.GetPrioprity() ||
                (RPNstack.top().GetPrioprity() == temp.GetPrioprity() &&
                 temp.GetOperation() != POW))) {
          RPNqueue->push(RPNstack.top());
          RPNstack.pop();
        }
        RPNstack.push(temp);
        break;
      case LEFT_BRACKET:
        RPNstack.push(temp);
        break;
      case RIGHT_BRACKET:
        while (!RPNstack.empty() &&
               RPNstack.top().GetOperation() != LEFT_BRACKET) {
          RPNqueue->push(RPNstack.top());
          RPNstack.pop();
        }
        if (RPNstack.top().GetOperation() == LEFT_BRACKET) {
          RPNstack.pop();
          if (!RPNstack.empty() && RPNstack.top().GetOperation() >= COS &&
              RPNstack.top().GetOperation() <= LOG) {
            RPNqueue->push(RPNstack.top());
            RPNstack.pop();
          }
        } else {
          result = 1;
        }
      default:
        break;
    }
  }
  while (!RPNstack.empty() && result == 0) {
    if (RPNstack.top().GetOperation() == LEFT_BRACKET) {
      result = 1;
    }
    RPNqueue->push(RPNstack.top());
    RPNstack.pop();
  }
  return result;
}

/**
 * Calculates the result of the given Reverse Polish Notation (RPN) expression
 * for the provided value of x.
 *
 * @param RPNqueue A pointer to a queue of StackToken objects representing the
 * RPN expression.
 * @param x The value of the variable x in the expression.
 *
 * @return 0 if the calculation is successful, 1 if there is an error in the
 * expression.
 *
 * @throws None.
 */
int CalcModel::Calculate(std::queue<StackToken> *RPNqueue, double x) {
  int result = 0;
  std::stack<double> numberStack;
  while (!RPNqueue->empty() && result == 0) {
    StackToken temp = RPNqueue->front();
    RPNqueue->pop();
    if (temp.GetPrioprity() == -1) {
      if (temp.GetOperation() == X_VALUE) {
        numberStack.push(x);
      } else {
        numberStack.push(temp.GetNumber());
      }
    } else if (temp.GetOperation() >= PLUS && temp.GetOperation() <= POW) {
      double a = numberStack.top();
      numberStack.pop();
      double b = numberStack.top();
      numberStack.pop();
      switch (temp.GetOperation()) {
        case PLUS:
          numberStack.push(a + b);
          break;
        case MINUS:
          numberStack.push(b - a);
          break;
        case MUL:
          numberStack.push(a * b);
          break;
        case DIV:
          numberStack.push(b / a);
          break;
        case POW:
          numberStack.push(powl(b, a));
          break;
        case MOD:
          numberStack.push(fmod(b, a));
          break;
        default:
          break;
      }
    } else {
      double a = numberStack.top();
      numberStack.pop();
      switch (temp.GetOperation()) {
        case COS:
          numberStack.push(cos(a));
          break;
        case SIN:
          numberStack.push(sin(a));
          break;
        case TAN:
          numberStack.push(tan(a));
          break;
        case SQRT:
          numberStack.push(sqrt(a));
          break;
        case LN:
          numberStack.push(log(a));
          break;
        case LOG:
          numberStack.push(log10(a));
          break;
        case ACOS:
          numberStack.push(acos(a));
          break;
        case ASIN:
          numberStack.push(asin(a));
          break;
        case ATAN:
          numberStack.push(atan(a));
          break;
        default:
          break;
      }
    }
  }
  data_ = numberStack.top();
  numberStack.pop();
  if (!numberStack.empty()) {
    result = 1;
  }
  return result;
}

int CalcModel::ParanthesisValidity(std::string equation) {
  int result = 0;
  std::stack<char> stack;
  for (long unsigned i = 0; i < equation.length() && result == 0; i++) {
    switch (equation[i]) {
      case '(':
        stack.push('(');
        break;
      case ')':
        if (stack.empty()) {
          result = 1;
        } else {
          stack.pop();
        }
        break;
      default:
        break;
    }
  }
  if (!stack.empty()) result = 1;
  return result;
}

/**
 * Calculates the result of the given equation using the provided variable `x`.
 *
 * @param equation The equation to be calculated.
 * @param x The variable `x` used in the equation.
 *
 * @return 0 if the calculation is successful, otherwise an error code.
 *
 * @throws None.
 */
int CalcModel::Calculator(std::string equation, double x) {
  int result = 0;
  std::queue<StackToken> parcedQueue;
  result = ParanthesisValidity(equation);
  if (result == 0) {
    result = ParceEquation(equation, &parcedQueue);
    if (result == 0) {
      std::queue<StackToken> RPNqueue;
      result = RevercePolishNotation(&parcedQueue, &RPNqueue);
      if (result == 0) result = Calculate(&RPNqueue, x);
    }
  }
  return result;
}
