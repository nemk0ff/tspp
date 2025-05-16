#include "ExpressionParser.h"

// �㭪�� ��� ������ ��� �宦����� �����ப� � ��ப�
void replace_all(std::string &s, std::string const &toReplace, std::string const &replaceWith) {
    std::string buf;
    std::size_t pos = 0;
    std::size_t prevPos;

    // ����ࢨ�㥬 ������ ��� ����, �⮡� �������� ���������� �����।������
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

// ��ࠡ�⪠ ᫮����� � ���⠭��
void ExpressionParser::S() {
    M(); // ���砫� ��ࠡ��뢠�� 㬭������/�������
    while (cur_index < s.size()) {
        char c = s[cur_index];
        if (c == '+' or c == '-') {
            cur_index++;
            M(); // ��ࠡ��뢠�� ᫥���騩 ���࠭�

            // ��������� ��� ��᫥���� ���祭�� �� �⥪�
            value_t r = values.top();
            values.pop();
            value_t l = values.top();
            values.pop();

            // �믮��塞 ������ � ����頥� १���� ���⭮ � �⥪
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

// ��ࠡ�⪠ 㬭������ � �������
void ExpressionParser::M() {
    P(); // ���砫� ��ࠡ��뢠�� �⥯���
    while (cur_index < s.size()) {
        char c = s[cur_index];
        if (c == '*' or c == '/') {
            cur_index++;
            P(); // ��ࠡ��뢠�� ᫥���騩 ���࠭�

            // ��������� ��� ��᫥���� ���祭�� �� �⥪�
            value_t r = values.top();
            values.pop();
            value_t l = values.top();
            values.pop();

            // �믮��塞 ������ � ����頥� १���� ���⭮ � �⥪
            value_t res;
            if (c == '*') {
                res = l * r;
            } else {
                if (abs(r) < EPS) {
                    throw "divide by zero"; // �஢�ઠ ������� �� ����
                }
                res = l / r;
            }

            values.push(res);
        } else {
            return;
        }
    }
}

// ��ࠡ�⪠ ���������� � �⥯���
void ExpressionParser::P() {
    V(); // ���砫� ��ࠡ��뢠�� ���祭��
    if (s[cur_index] == '^') {
        cur_index++;
        P(); // �����ᨢ�� ��ࠡ��뢠�� �⥯���

        // ��������� ��� ��᫥���� ���祭�� �� �⥪�
        value_t r = values.top();
        values.pop();
        value_t l = values.top();
        values.pop();

        value_t res = pow(l, r);
        values.push(res);
    }
}

// ��ࠡ�⪠ ���祭��: �㭪樨, ᪮���, �᫠
void ExpressionParser::V() {
    if (s[cur_index] == 's') { // ��ࠡ�⪠ �㭪権, ��稭������ �� 's': sin, sqrt
        cur_index++;
        if (s[cur_index] == 'i') { // sin
            if (s[++cur_index] != 'n') {
                throw "unknown operation at index " + std::to_string(cur_index);
            }
            if (s[++cur_index] != '(') {
                throw "parenthesis not found at index " + std::to_string(cur_index);
            }
            V(); // �����ᨢ�� ��ࠡ��뢠�� ��㬥�� �㭪樨

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
            V(); // �����ᨢ�� ��ࠡ��뢠�� ��㬥�� �㭪樨

            value_t x = values.top();
            values.pop();
            values.push(sqrt(x));
        } else {
            throw "unknown operation at index " + std::to_string(cur_index);
        }
    }
        // �������筮 ��ࠡ��뢠���� ��㣨� �㭪樨
        // � ᪮��� � 㭠�� ����ᮬ
    else if (s[cur_index] == '(') {
        cur_index++;
        bool unary_minus = false;
        if (s[cur_index] == '-') {
            cur_index++;
            unary_minus = true;
        }
        S(); // �����ᨢ�� ��ࠡ��뢠�� ��ࠦ���� � ᪮����
        if (s[cur_index] != ')') {
            throw "unclosed parenthesis at index " + std::to_string(cur_index);
        }
        if (unary_minus) {
            value_t x = values.top();
            values.pop();
            values.push(-x); // �ਬ��塞 㭠�� �����
        }
        cur_index++;
    } else {
        D(); // ��ࠡ�⪠ �ᥫ
    }
}

// ��ࠡ�⪠ �ᥫ (楫�� � �஡���)
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

// �᭮���� ��⮤ ��� ���ᨭ�� � ��।������ ��ࠦ����
long double ExpressionParser::parse(const std::string &s_) {
    s = "(" + s_ + ")"; // ������� ᪮��� ��� ��饭�� ���ᨭ��
    replace_all(s, " ", "");
    cur_index = 0;

    S(); // ��稭��� ���ᨭ�

    if (cur_index != s.size()) {
        throw "incorrect expression";
    }

    return values.top();
}