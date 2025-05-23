/**
 * @file test.h
 * @author Nemkov Daniil
 * @brief Заголовочный файл, необходимый для инициализации библиотеки тестов googletest
 * @date 23.05.2025
 */
#pragma once
#include <gtest/gtest.h>
#include <iostream>

//! \brief Класс, описывающий тесты для ExpressionParser
class ExpressionParserTest : public testing::Test {
protected:
    //! \brief Допустимая погрешность при вычислениях
    double precision = 1e-5;
};
