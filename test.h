#pragma once

#include "googletest/googletest/include/gtest/gtest.h"
#include <iostream>

class ExpressionParserTest : public testing::Test {
protected:
    double precision = 1e-5;
};