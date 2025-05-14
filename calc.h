#pragma once

using value_t = long double;
constexpr value_t
EPS = 1e-10;

#define abs my_abs

value_t my_abs(value_t x);

value_t pow(value_t base, value_t exp);

value_t exp(value_t x);

value_t sqrt(value_t x);

value_t sin(value_t x);

value_t cos(value_t x);

value_t tan(value_t x);

value_t asin(value_t x);

value_t acos(value_t x);

value_t atan(value_t x);

value_t log(value_t x);

value_t log10(value_t x);
