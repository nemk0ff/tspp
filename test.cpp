#include "googletest/googletest/include/gtest/gtest.h"
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

TEST_F(ExpressionParserTest, LogarithmicFunctions) {
    ExpressionParser parser;
    EXPECT_NEAR(parser.parse("log(e)"), 1.0, precision);
    EXPECT_NEAR(parser.parse("log10(100)"), 2.0, precision);
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

TEST_F(ExpressionParserTest, ComplexExpressions) {
    ExpressionParser parser;
    EXPECT_DOUBLE_EQ(parser.parse("(3+5)*2/(1-0.5)^(pi/2)"), 24.0);
    EXPECT_DOUBLE_EQ(parser.parse("sqrt(16)-sin(pi/3)+cos(pi/4)"), 2.0);
}

TEST_F(ExpressionParserTest, ParenthesesHandling) {
    ExpressionParser parser;
    EXPECT_DOUBLE_EQ(parser.parse("((3+5)*(1-0.5))^2"), 36.25);
    EXPECT_DOUBLE_EQ(parser.parse("sin(pi/2) + cos(pi/4)"), 1.9999999999999998);
}

TEST_F(ExpressionParserTest, NegativeNumbers) {
    ExpressionParser parser;
    EXPECT_DOUBLE_EQ(parser.parse("-3+5*-2"), -11.0);
    EXPECT_DOUBLE_EQ(parser.parse("-sqrt(16)"), -4.0);
}

TEST_F(ExpressionParserTest, ExponentialFunction) {
    ExpressionParser parser;
    EXPECT_DOUBLE_EQ(parser.parse("exp(pi)"), 23.099019513592744);
    EXPECT_DOUBLE_EQ(parser.parse("exp(-pi)"), 0.00000000000000012246424163156252);
}

TEST_F(ExpressionParserTest, InvalidInputException) {
    ExpressionParser parser;
    EXPECT_ANY_THROW(parser.parse("3/zero"));
    EXPECT_ANY_THROW(parser.parse("3/+5"));
    EXPECT_ANY_THROW(parser.parse("3/0.0"));
}


//int main(int argc, char** argv) {
//    ::testing::InitGoogleTest(&argc, argv);
//    int result = RUN_ALL_TESTS();
//    if (result!= 0) {
//        std::cout << "Tests failed." << std::endl;
//    } else {
//        std::cout << "All tests passed." << std::endl;
//    }
//    return result;
//}