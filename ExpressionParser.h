#pragma once

#include <stack>
#include <string>
#include "calc.h"

class ExpressionParser {
    size_t cur_index;
    std::string s;
    std::stack <value_t> values;

    void S(); // sum
    void M(); // multiply
    void P(); // power
    void V(); // value
    void D(); // digit
public:
    long double parse(const std::string &s_);
};