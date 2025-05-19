#pragma once

#include <stack>
#include <string>
#include "math.h"

class ExpressionParser {
    size_t cur_index;
    std::string s;
    std::stack<value_t> values;

    void S(bool unary_minus = false);

    void M();

    void P();

    void V();

    void D();

public:
    long double parse(const std::string &s_);
};