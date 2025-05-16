#pragma once

#include <stack>
#include <string>
#include "calc.h"

// парсер и определитель математических выражений
class ExpressionParser {
    size_t cur_index;
    std::string s;
    std::stack<value_t> values;  // для хранения промежуточных значений вычислений

    // методы для обработки:
    void S(); // сложения и вычитания
    void M(); // умножения и деления
    void P(); // возведения в степень
    void V(); // значений (функции, скобки, числа)
    void D(); // цифр (целых и дробных чисел)
public:
    long double parse(const std::string &s_);
};