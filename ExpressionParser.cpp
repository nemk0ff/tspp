#include "ExpressionParser.h"

// Функция для замены всех вхождений подстроки в строке
void replace_all(std::string &s, std::string const &toReplace, std::string const &replaceWith) {
    std::string buf;
    std::size_t pos = 0;
    std::size_t prevPos;

    // Резервируем память для буфера, чтобы избежать многократных перераспределений
    buf.reserve(s.size());

    while (true) {
        prevPos = pos;
        pos = s.find(toReplace, pos);
        if (pos == std::string::npos) {
            break;
        }
        buf.append(s, prevPos, pos - prevPos);
        buf += replaceWith;
        pos += toReplace.size();
    }

    buf.append(s, prevPos, s.size() - prevPos);
    s.swap(buf);
}

// Обработка сложения и вычитания
void ExpressionParser::S() {
    M(); // Сначала обрабатываем умножение/деление
    while (cur_index < s.size()) {
        char c = s[cur_index];
        if (c == '+' or c == '-') {
            cur_index++;
            M(); // Обрабатываем следующий операнд

            // Извлекаем два последних значения из стека
            value_t r = values.top();
            values.pop();
            value_t l = values.top();
            values.pop();

            // Выполняем операцию и помещаем результат обратно в стек
            value_t res;
            if (c == '+') {
                res = l + r;
            } else {
                res = l - r;
            }

            values.push(res);
        } else {
            return;
        }
    }
}

// Обработка умножения и деления
void ExpressionParser::M() {
    P(); // Сначала обрабатываем степень
    while (cur_index < s.size()) {
        char c = s[cur_index];
        if (c == '*' or c == '/') {
            cur_index++;
            P(); // Обрабатываем следующий операнд

            // Извлекаем два последних значения из стека
            value_t r = values.top();
            values.pop();
            value_t l = values.top();
            values.pop();

            // Выполняем операцию и помещаем результат обратно в стек
            value_t res;
            if (c == '*') {
                res = l * r;
            } else {
                if (abs(r) < EPS) {
                    throw "divide by zero"; // Проверка деления на ноль
                }
                res = l / r;
            }

            values.push(res);
        } else {
            return;
        }
    }
}

// Обработка возведения в степень
void ExpressionParser::P() {
    V(); // Сначала обрабатываем значение
    if (s[cur_index] == '^') {
        cur_index++;
        P(); // Рекурсивно обрабатываем степень

        // Извлекаем два последних значения из стека
        value_t r = values.top();
        values.pop();
        value_t l = values.top();
        values.pop();

        value_t res = pow(l, r);
        values.push(res);
    }
}

// Обработка значений: функции, скобки, числа
void ExpressionParser::V() {
    if (s[cur_index] == 's') { // Обработка функций, начинающихся на 's': sin, sqrt
        cur_index++;
        if (s[cur_index] == 'i') { // sin
            if (s[++cur_index] != 'n') {
                throw "unknown operation at index " + std::to_string(cur_index);
            }
            if (s[++cur_index] != '(') {
                throw "parenthesis not found at index " + std::to_string(cur_index);
            }
            V(); // Рекурсивно обрабатываем аргумент функции

            value_t x = values.top();
            values.pop();
            values.push(sin(x));
        } else if (s[cur_index] == 'q') { // sqrt
            if (s[++cur_index] != 'r') {
                throw "unknown operation at index " + std::to_string(cur_index);
            }
            if (s[++cur_index] != 't') {
                throw "unknown operation at index " + std::to_string(cur_index);
            }
            if (s[++cur_index] != '(') {
                throw "parenthesis not found at index " + std::to_string(cur_index);
            }
            V(); // Рекурсивно обрабатываем аргумент функции

            value_t x = values.top();
            values.pop();
            values.push(sqrt(x));
        } else {
            throw "unknown operation at index " + std::to_string(cur_index);
        }
    }
        // Аналогично обрабатываются другие функции
        // и скобки с унарным минусом
    else if (s[cur_index] == '(') {
        cur_index++;
        bool unary_minus = false;
        if (s[cur_index] == '-') {
            cur_index++;
            unary_minus = true;
        }
        S(); // Рекурсивно обрабатываем выражение в скобках
        if (s[cur_index] != ')') {
            throw "unclosed parenthesis at index " + std::to_string(cur_index);
        }
        if (unary_minus) {
            value_t x = values.top();
            values.pop();
            values.push(-x); // Применяем унарный минус
        }
        cur_index++;
    } else {
        D(); // Обработка чисел
    }
}

// Обработка чисел (целых и дробных)
void ExpressionParser::D() {
    if (!isdigit(s[cur_index])) {
        throw "expected number at index " + std::to_string(cur_index);
    }

    value_t res = s[cur_index] - '0';
    while (isdigit(s[++cur_index])) {
        res = res * 10 + (s[cur_index] - '0');
    }

    if (s[cur_index] == '.') {
        value_t cur_power = 1;
        while (isdigit(s[++cur_index])) {
            cur_power *= 0.1;
            res = res + cur_power * (s[cur_index] - '0');
        }
    }

    values.push(res);
}

// Основной метод для парсинга и определения выражения
long double ExpressionParser::parse(const std::string &s_) {
    s = "(" + s_ + ")"; // добавлю скобки для упрощения парсинга
    replace_all(s, " ", "");
    cur_index = 0;

    S(); // Начинаем парсинг

    if (cur_index != s.size()) {
        throw "incorrect expression";
    }

    return values.top();
}