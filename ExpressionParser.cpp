#include "ExpressionParser.h"

void replace_all(std::string &s, std::string const &toReplace, std::string const &replaceWith) {
    std::string buf;
    std::size_t pos = 0;
    std::size_t prevPos;

    // Reserves rough estimate of final size of string.
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

void ExpressionParser::S() {
    M();
    while (cur_index < s.size()) {
        char c = s[cur_index];
        if (c == '+' or c == '-') {
            cur_index++;
            M();

            value_t r = values.top();
            values.pop();
            value_t l = values.top();
            values.pop();

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

void ExpressionParser::M() {
    while (cur_index < s.size()) {
        char c = s[cur_index];
        if (c == '*' or c == '/') {
            cur_index++;

            value_t r = values.top();
            values.pop();
            value_t l = values.top();
            values.pop();

            value_t res;
            if (c == '*') {
                res = l * r;
            } else {
                if (abs(r) < EPS) {
                    throw "divide by zero";
                }
                res = l / r;
            }

            values.push(res);
        } else {
            return;
        }
    }
}

void ExpressionParser::V() {
    if (s[cur_index] == 's') { // sin, sqrt
        cur_index++;
        if (s[cur_index] == 'i') {
            if (s[++cur_index] != 'n') {
                throw "unknown operation at index " + std::to_string(cur_index);
            }
            if (s[++cur_index] != '(') {
                throw "parenthesis not found at index " + std::to_string(cur_index);
            }
            V();

            value_t x = values.top();
            values.pop();
            values.push(sin(x));
        }
    } else if (s[cur_index] == 'c') { // cos, ctg
        cur_index++;
        if (s[cur_index] == 'o') {
            if (s[++cur_index] != 's') {
                throw "unknown operation at index " + std::to_string(cur_index);
            }
            if (s[++cur_index] != '(') {
                throw "parenthesis not found at index " + std::to_string(cur_index);
            }
            V();

            value_t x = values.top();
            values.pop();
            values.push(cos(x));
        } else if (s[cur_index] == 't') {
            if (s[++cur_index] != 'g') {
                throw "unknown operation at index " + std::to_string(cur_index);
            }
            if (s[++cur_index] != '(') {
                throw "parenthesis not found at index " + std::to_string(cur_index);
            }
            V();

            value_t x = values.top();
            values.pop();
            values.push(1 / tan(x));
        } else {
            throw "unknown operation at index " + std::to_string(cur_index);
        }
    } else if (s[cur_index] == 't') { // tg
        if (s[++cur_index] != 'g') {
            throw "unknown operation at index " + std::to_string(cur_index);
        }
        if (s[++cur_index] != '(') {
            throw "parenthesis not found at index " + std::to_string(cur_index);
        }
        V();

        value_t x = values.top();
        values.pop();
        values.push(tan(x));
    } else if (s[cur_index] == 'a') { // asin, acos, atg
        cur_index++;
        if (s[cur_index] == 's') {
            if (s[++cur_index] != 'i') {
                throw "unknown operation at index " + std::to_string(cur_index);
            }
            if (s[++cur_index] != 'n') {
                throw "unknown operation at index " + std::to_string(cur_index);
            }
            if (s[++cur_index] != '(') {
                throw "parenthesis not found at index " + std::to_string(cur_index);
            }
            V();

            value_t x = values.top();
            values.pop();
            values.push(asin(x));
        } else if (s[cur_index] == 'c') {
            if (s[++cur_index] != 'o') {
                throw "unknown operation at index " + std::to_string(cur_index);
            }
            if (s[++cur_index] != 's') {
                throw "unknown operation at index " + std::to_string(cur_index);
            }
            if (s[++cur_index] != '(') {
                throw "parenthesis not found at index " + std::to_string(cur_index);
            }
            V();

            value_t x = values.top();
            values.pop();
            values.push(acos(x));
        } else if (s[cur_index] == 't') {
            if (s[++cur_index] != 'g') {
                throw "unknown operation at index " + std::to_string(cur_index);
            }
            if (s[++cur_index] != '(') {
                throw "parenthesis not found at index " + std::to_string(cur_index);
            }
            V();

            value_t x = values.top();
            values.pop();
            values.push(atan(x));
        } else {
            throw "unknown operation at index " + std::to_string(cur_index);
        }
    } else if (s[cur_index] == '(') {
        cur_index++;
        bool unary_minus = false;
        if (s[cur_index] == '-') {
            cur_index++;
            unary_minus = true;
        }
        S();
        if (s[cur_index] != ')') {
            throw "unclosed parenthesis at index " + std::to_string(cur_index);
        }
        if (unary_minus) {
            value_t x = values.top();
            values.pop();
            values.push(-x);
        }
        cur_index++;
    } else {
        D();
    }
}

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

long double ExpressionParser::parse(const std::string &s_) {
    s = "(" + s_ + ")";
    replace_all(s, " ", "");
    cur_index = 0;

    S();

    if (cur_index != s.size()) {
        throw "incorrect expression";
    }

    return values.top();
}
