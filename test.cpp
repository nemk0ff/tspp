/**
 * @file test.cpp
 * @author Nemkov Daniil
 * @brief Файл исходных кодов тестов класса ExpressionParser, использующий библиотеку googletest
 * @date 23.05.2025
 */
#include <gtest/gtest.h>
#include "test.h"
#include "ExpressionParser.h"

TEST_F(ExpressionParserTest, BasicOperations
) {
ExpressionParser parser;
EXPECT_DOUBLE_EQ(parser
.parse("3+5"), 8.0);
EXPECT_DOUBLE_EQ(parser
.parse("3-5"), -2.0);
EXPECT_DOUBLE_EQ(parser
.parse("3*5"), 15.0);
EXPECT_DOUBLE_EQ(parser
.parse("3/5"), 0.6);
EXPECT_DOUBLE_EQ(parser
.parse("3^5"), 243.0);
}

TEST_F(ExpressionParserTest, TrigonometricFunctions
) {
ExpressionParser parser;
EXPECT_NEAR(parser
.parse("sin(acos(-1)/2)"), 1.0, precision);
EXPECT_NEAR(parser
.parse("cos(0)"), 1.0, precision);
EXPECT_NEAR(parser
.parse("tan(acos(-1)/4)"), 1.0, precision);
EXPECT_NEAR(parser
.parse("cot(acos(-1)/4)"), 1.0, precision);
EXPECT_NEAR(parser
.parse("asin(1)"), asin(1), precision);
EXPECT_NEAR(parser
.parse("acos(1)"), 0, precision);
EXPECT_NEAR(parser
.parse("atan(1)"), atan(1), precision);
EXPECT_NEAR(parser
.parse("acot(1)"), atan(1), precision);
}

TEST_F(ExpressionParserTest, LogarithmicFunctions
) {
ExpressionParser parser;
EXPECT_NEAR(parser
.parse("ln(exp(1))"), 1.0, precision);
EXPECT_NEAR(parser
.parse("lg(100)"), 2.0, precision);
}

TEST_F(ExpressionParserTest, DivisionByZero
) {
ExpressionParser parser;
EXPECT_ANY_THROW(parser
.parse("3/0"));
}

TEST_F(ExpressionParserTest, IncorrectExpression
) {
ExpressionParser parser;
EXPECT_ANY_THROW(parser
.parse("3+"));
}

TEST_F(ExpressionParserTest, UnaryMinus
) {
ExpressionParser parser;
EXPECT_DOUBLE_EQ(parser
.parse("-3"), -3.0);
}

TEST_F(ExpressionParserTest, ComplexExpressions
) {
ExpressionParser parser;
EXPECT_NEAR(parser
.parse("(3+5)*2/(1-0.5)^(acos(-1)/2)"), 47.5309827768, precision);
EXPECT_NEAR(parser
.parse("sqrt(16)-sin(acos(-1)/3)+cos(acos(-1)/4)"), 3.841081377402108877637, precision);
}

TEST_F(ExpressionParserTest, ParenthesesHandling
) {
ExpressionParser parser;
EXPECT_DOUBLE_EQ(parser
.parse("((3+5)*(1-0.5))^2"), 16.0);
EXPECT_NEAR(parser
.parse("sin(acos(-1)/2) + cos(acos(-1)/4)"), 1.7071067811865475, precision);
}

TEST_F(ExpressionParserTest, NegativeNumbers
) {
ExpressionParser parser;
EXPECT_DOUBLE_EQ(parser
.parse("-3+5*(-2)"), -13.0);
EXPECT_DOUBLE_EQ(parser
.parse("-sqrt(16)"), -4.0);
}

TEST_F(ExpressionParserTest, ExponentialFunction
) {
ExpressionParser parser;
EXPECT_NEAR(parser
.parse("exp(acos(-1))"), 23.1406926328, precision);
EXPECT_NEAR(parser
.parse("exp(-acos(-1))"), 0.0432139182638, precision);
}

TEST_F(ExpressionParserTest, InvalidInputException
) {
ExpressionParser parser;
EXPECT_ANY_THROW(parser
.parse("3/zero"));
EXPECT_ANY_THROW(parser
.parse("3/+5"));
EXPECT_ANY_THROW(parser
.parse("3/0.0"));
}

// int main(int argc, char** argv) {
//     ::testing::InitGoogleTest(&argc, argv);
//     int result = RUN_ALL_TESTS();
//     if (result!= 0) {
//         std::cout << "Tests failed." << std::endl;
//     } else {
//         std::cout << "All tests passed." << std::endl;
//     }
//     return result;
// }
