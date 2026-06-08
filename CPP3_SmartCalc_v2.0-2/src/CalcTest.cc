#include <gtest/gtest.h>

#include "Controller/CalcController.h"
#include "Culk/EquationCheckerTable.h"

using namespace s21;

TEST(TokenTest, Constructor) {
  StackToken temp;
  EXPECT_EQ(temp.GetPrioprity(), -1);
  EXPECT_EQ(temp.GetNumber(), -1);
  EXPECT_EQ(temp.GetOperation(), -1);
}

TEST(ModelTest, InvalidInput1) {
  EquationCheckerTable eqCheck;
  int error = eqCheck.InitialEquationChecker("whyamiinput");
  EXPECT_EQ(error, -1);
}

TEST(ModelTest, InvalidInput2) {
  EquationCheckerTable eqCheck;
  int error = eqCheck.InitialEquationChecker("(+)");
  EXPECT_EQ(error, -1);
}

TEST(ModelTest, InvalidInput8) {
  EquationCheckerTable eqCheck;
  int error = eqCheck.InitialEquationChecker("156.9+4+a");
  EXPECT_EQ(error, -1);
}

TEST(ModelTest, InvalidInput3) {
  CalcModel model;
  int error = model.Calculator("())", 0.0);
  EXPECT_EQ(error, 1);
}

TEST(ModelTest, InvalidInput4) {
  EquationCheckerTable eqCheck;
  int error = eqCheck.InitialEquationChecker("sin(5)-+6");
  EXPECT_EQ(error, -1);
}

TEST(ModelTest, InvalidInput5) {
  CalcModel model;
  int error = model.Calculator("at(3)", 0.0);
  EXPECT_EQ(error, 1);
}

TEST(ModelTest, OneNumber) {
  EquationCheckerTable eqCheck;
  int error = eqCheck.InitialEquationChecker("2");
  EXPECT_EQ(error, 0);
}

TEST(ModelTest, InvalidInput6) {
  EquationCheckerTable eqCheck;
  int error = eqCheck.InitialEquationChecker("*2+3");
  EXPECT_EQ(error, -1);
}

TEST(ModelTest, InvalidInput7) {
  EquationCheckerTable eqCheck;
  int error = eqCheck.InitialEquationChecker("^");
  EXPECT_EQ(error, -1);
}

TEST(ModelTest, Plus) {
  CalcModel model;
  int error = model.Calculator("1+2", 0.0);
  EXPECT_EQ(error, 0);
  EXPECT_EQ(model.GetData(), 3.0);
}

TEST(ModelTest, UnaryOperator) {
  CalcModel model;
  int error = model.Calculator("+1-(-2)", 0.0);
  EXPECT_EQ(error, 0);
  EXPECT_EQ(model.GetData(), 3.0);
}

TEST(ModelTest, Minus) {
  CalcModel model;
  int error = model.Calculator("1-2", 0.0);
  EXPECT_EQ(error, 0);
  EXPECT_EQ(model.GetData(), -1.0);
}

TEST(ModelTest, Mult) {
  CalcModel model;
  int error = model.Calculator("7*8", 0.0);
  EXPECT_EQ(error, 0);
  EXPECT_EQ(model.GetData(), 56.0);
}

TEST(ModelTest, Div) {
  CalcModel model;
  int error = model.Calculator("5/2", 0.0);
  EXPECT_EQ(error, 0);
  EXPECT_EQ(model.GetData(), 2.5);
}

TEST(ModelTest, Pow) {
  CalcModel model;
  int error = model.Calculator("2^2^3", 0.0);
  EXPECT_EQ(error, 0);
  EXPECT_EQ(model.GetData(), 256.0);
}

TEST(ModelTest, Mod) {
  CalcModel model;
  int error = model.Calculator("5mod3", 0.0);
  EXPECT_EQ(error, 0);
  EXPECT_EQ(model.GetData(), 2.0);
}

TEST(ModelTest, Sin) {
  CalcModel model;
  int error = model.Calculator("sin(0)", 0.0);
  EXPECT_EQ(error, 0);
  EXPECT_EQ(model.GetData(), 0.0);
}

TEST(ModelTest, Mod_negative) {
  EquationCheckerTable eqCheck;
  int error = eqCheck.InitialEquationChecker("5modx");
  EXPECT_EQ(error, 0);
  CalcModel model;
  error = model.Calculator("5modx", 2.0);
  EXPECT_EQ(error, 0);
  EXPECT_EQ(model.GetData(), 1.0);
}

TEST(ModelTest, Cos) {
  CalcModel model;
  int error = model.Calculator("cos(0)", 0.0);
  EXPECT_EQ(error, 0);
  EXPECT_EQ(model.GetData(), 1.0);
}

TEST(ModelTest, Tan) {
  CalcModel model;
  int error = model.Calculator("tan(0)", 0.0);
  EXPECT_EQ(error, 0);
  EXPECT_EQ(model.GetData(), 0.0);
}
TEST(ModelTest, Asin) {
  CalcModel model;
  int error = model.Calculator("asin(0)", 0.0);
  EXPECT_EQ(error, 0);
  EXPECT_EQ(model.GetData(), 0.0);
}

TEST(ModelTest, Acos) {
  CalcModel model;
  int error = model.Calculator("acos(0)", 0.0);
  EXPECT_EQ(error, 0);
  EXPECT_EQ(model.GetData(), 1.5707963267948966);
}

TEST(ModelTest, Atan) {
  CalcModel model;
  int error = model.Calculator("atan(0)", 0.0);
  EXPECT_EQ(error, 0);
  EXPECT_EQ(model.GetData(), 0.0);
}
TEST(ModelTest, Ln) {
  CalcModel model;
  int error = model.Calculator("ln(1)", 0.0);
  EXPECT_EQ(error, 0);
  EXPECT_EQ(model.GetData(), 0.0);
}

TEST(ModelTest, Log) {
  CalcModel model;
  int error = model.Calculator("log(1)", 0.0);
  EXPECT_EQ(error, 0);
  EXPECT_EQ(model.GetData(), 0.0);
}

TEST(ModelTest, Sqrt) {
  CalcModel model;
  int error = model.Calculator("sqrt(4)", 0.0);
  EXPECT_EQ(error, 0);
  EXPECT_EQ(model.GetData(), 2.0);
}

TEST(ControllerTest, Test1) {
  CalcController controller;
  int error = controller.PerformCalculation("sin(cos(2*tan(4)))", 0.0);
  EXPECT_EQ(error, 0);
  EXPECT_NEAR(controller.GetResult(), -0.627127, 0.000001);
}

TEST(ControllerTest, Test2) {
  CalcController controller;
  int error = controller.PerformCalculation("sin((x)", 0.0);
  EXPECT_EQ(error, 1);
}

TEST(ControllerTest, Test3) {
  CalcController controller;
  int error = controller.PerformCalculation("16*x+x-14", 2.0);
  EXPECT_EQ(error, 0);
  EXPECT_EQ(controller.GetResult(), 20.0);
}

TEST(ControllerTest, Test5) {
  CalcController controller;
  int error = controller.PerformCalculation(
      "((cos(3))^2+(sin(3))^2-5mod3)/2*tan(1)+ln(log(2))+sqrt(4)", 0.0);
  EXPECT_EQ(error, 0);
  EXPECT_NEAR(controller.GetResult(), 0.02075077184, 0.000001);
}

TEST(ControllerTest, Test6) {
  CalcController controller;
  int error = controller.PerformCalculation("-atan(x)+asin(x)+acos(x)", 1.0);
  EXPECT_EQ(error, 0);
  EXPECT_NEAR(controller.GetResult(), 0.7853981633974483, 0.000001);
}

TEST(ControllerTest, Test7) {
  CalcController controller;
  int error = controller.PerformCalculation("cosin(2)", 1.0);
  EXPECT_EQ(error, 1);
}
TEST(CreditTest, Test1) {
  CalcCredit credit;
  int error = credit.CalculateCredit(100000, 10, 12, 1);
  EXPECT_EQ(error, 0);
  EXPECT_NEAR(credit.GetTotalInterest(), 5499.08, 0.01);
  EXPECT_NEAR(credit.GetTotalPayment(), 105499.08, 0.01);
  EXPECT_NEAR(credit.GetMonthlyPayment().front(), 8791.59, 0.01);
}

TEST(CreditTest, Test2) {
  CalcCredit credit;
  int error = credit.CalculateCredit(100000, 10, 12, 2);
  EXPECT_EQ(error, 0);
  EXPECT_NEAR(credit.GetTotalInterest(), 5416.67, 0.01);
  EXPECT_NEAR(credit.GetTotalPayment(), 105416.67, 0.01);
  EXPECT_NEAR(credit.GetMonthlyPayment().front(), 9166.67, 0.01);
}

TEST(CreditTest, Test3) {
  CalcCredit credit;
  int error = credit.CalculateCredit(100000, 10, 12, 3);
  EXPECT_EQ(error, -1);
}

TEST(ControllerTest, Test4) {
  CalcController controller;
  int error = controller.PerformCreditCalculation(50000, 15, 24, 1);
  EXPECT_EQ(error, 0);
  EXPECT_NEAR(controller.GetTotalPayment(), 58183.92, 0.01);
  EXPECT_NEAR(controller.GetTotalInterest(), 8183.92, 0.01);
  EXPECT_NEAR(controller.GetMonthlyPayment().front(), 2424.33, 0.01);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
