/**
 * @file math.cpp
 * @author Nemkov Daniil
 * @brief Файл исходного кода, содержащий реализацию математических функций
 * @date 23.05.2025
 */

#include <functional>
#include "math.h"

//! \brief Константа PI для нужд функций
constexpr value_t PI = 3.141592653589793238462643383279;
//! \brief Константа ln(2) для нужд функций
constexpr value_t LN2 = 0.693147180559945309417232121458;

//! \brief Функция, вычисляющая значение факториала n!
//! \param n Аргумент
//! \return Значение факториала n!
constexpr value_t factorial(int n) { return (n == 0 ? 1 : factorial(n - 1) * n); }

value_t my_abs(value_t x) { return (x < 0 ? -x : x); }

//! \brief Функция, вычисляющая сумму первых cnt членов ряда Тейлора в точке x
//! c центром разложения в нуле и коэффициентами, вычисляемыми с помощью функции koef
//! \param koef Функция, возвращающая коэффициент по его номеру
//! \param x Точка, в которой вычисляется ряд
//! \param cnt Число слагаемых
//! \return Значение ряда Тейлора
value_t taylor_series_calc(std::function<value_t(int)> koef, value_t x, int cnt = 100) {
    value_t result = 0;
    value_t x_power = 1;
    for (int k = 0; k < cnt; k++) {
        result += x_power * koef(k);
        x_power *= x;
    }
    return result;
}

value_t exp(value_t x) {
    return taylor_series_calc([](int k) { return 1.0L / factorial(k); }, x);
}

value_t log(value_t x) {
    if (x < EPS) {
        throw "log of negative";
    }

    value_t result = 0;
    while (x > 1.9) {
        x /= 2;
        result += LN2;
    }

    while (x < 0.1) {
        x *= 2;
        result -= LN2;
    }

    result += taylor_series_calc(
            [](int k) {
                if (k == 0) {
                    return 0.0L;
                }

                value_t res = (k % 2 != 0 ? 1 : -1);
                res *= 1.0L / k;
                return res;
            },
            x - 1);

    return result;
}

value_t log10(value_t x) { return log(x) / log(10); }

//! \brief Функция, возводящая число x в положительную степень n
//! \param x Число, которое возводится в степень
//! \param n Положительная степень n
//! \return x^n
value_t bpow(value_t x, long long n) {
    if (n == 0) {
        return 1;
    }

    value_t b = bpow(x, n / 2);
    b *= b;
    b *= (n % 2 == 1 ? x : 1);
    return b;
}

value_t pow(value_t base, value_t exponent) {
    if (base < -EPS && abs(exponent - 1.0L * static_cast<long long>(exponent)) > EPS) {
        throw "invalid power base";
    }

    if (abs(base) < EPS && exponent < EPS) {
        throw "negative power of zero";
    }

    if (abs(base) < EPS) {
        return 0.0L;
    }

    if (abs(exponent - 1.0L * static_cast<long long>(exponent)) < EPS) {
        return bpow(base, static_cast<long long>(exponent));
    }

    return exp(log(base) * exponent);
}

value_t sqrt(value_t x) { return pow(x, 1.0L / 2); }

//! \brief Функция, уменьшающая аргумент тригонометрической функции дло промежутка [-pi;pi]
//! \param x Изначальный аргумент
//! \return (x - k * 2 * pi), где k такое, чтобы это значение попадало в нужной промежуток
value_t trig_arg_reduce(value_t x) {
    while (abs(x) - 2 * PI > 0) {
        value_t k = 1.0L * static_cast<long long>(abs(x) / (2 * PI));
        if (k < 0) {
            k = abs(x) / (2 * PI);
        }

        if (x - PI > 0) {
            x -= k * 2 * PI;
        } else {
            x += k * 2 * PI;
        }
    }

    while (abs(x) - PI > 0) {
        if (x - PI > 0) {
            x -= 2 * PI;
        } else {
            x += 2 * PI;
        }
    }

    return x;
}

value_t sin(value_t x) {
    x = trig_arg_reduce(x);
    return taylor_series_calc(
            [](int k) {
                if (k % 2 == 0) {
                    return 0.0L;
                }

                value_t res = ((k / 2) % 2 == 0 ? 1 : -1);
                res *= 1.0L / factorial(k);
                return res;
            },
            x);
}

value_t cos(value_t x) {
    x = trig_arg_reduce(x);
    return taylor_series_calc(
            [](int k) {
                if (k % 2 == 1) {
                    return 0.0L;
                }

                value_t res = ((k / 2) % 2 == 0 ? 1 : -1);
                res *= 1.0L / factorial(k);
                return res;
            },
            x);
}

value_t tan(value_t x) { return sin(x) / cos(x); }

value_t atan(value_t x) {
    return taylor_series_calc(
            [](int k) {
                if (k % 2 == 0) {
                    return 0.0L;
                }

                value_t res = ((k / 2) % 2 == 0 ? 1 : -1);
                res *= 1.0L / k;
                return res;
            },
            x, 5000000);
}

value_t asin(value_t x) { return 2 * atan(x / (1 + sqrt(1 - x * x))); }

value_t acos(value_t x) { return PI / 2 - asin(x); }
