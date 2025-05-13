#include <gtest/gtest.h>
#include "test.h"
#include "ExpressionParser.h"

TEST_F(ExpressionParserTest, BasicOperations) {
    ExpressionParser parser;
    EXPECT_DOUBLE_EQ(parser.parse("3+5"), 8.0);
    EXPECT_DOUBLE_EQ(parser.parse("3-5"), -2.0);
    EXPECT_DOUBLE_EQ(parser.parse("3*5"), 15.0);
    EXPECT_DOUBLE_EQ(parser.parse("3/5"), 0.6);
    EXPECT_DOUBLE_EQ(parser.parse("3^5"), 243.0);
}

TEST_F(ExpressionParserTest, TrigonometricFunctions) {
    ExpressionParser parser;
    EXPECT_NEAR(parser.parse("sin(pi/2)"), 1.0, precision);
    EXPECT_NEAR(parser.parse("cos(0)"), 1.0, precision);
    EXPECT_NEAR(parser.parse("tan(pi/4)"), 1.0, precision);
    EXPECT_NEAR(parser.parse("asin(1)"), asin(1), precision);
    EXPECT_NEAR(parser.parse("acos(1)"), 0, precision);
    EXPECT_NEAR(parser.parse("atan(1)"), atan(1), precision);
}

TEST_F(ExpressionParserTest, DivisionByZero) {
    ExpressionParser parser;
    EXPECT_ANY_THROW(parser.parse("3/0"));
}

TEST_F(ExpressionParserTest, IncorrectExpression) {
    ExpressionParser parser;
    EXPECT_ANY_THROW(parser.parse("3+"));
}

TEST_F(ExpressionParserTest, UnaryMinus) {
    ExpressionParser parser;
    EXPECT_DOUBLE_EQ(parser.parse("-3"), -3.0);
}