#pragma once

#include <stack>
#include <string>
#include "calc.h"

// ����� � ��।���⥫� ��⥬���᪨� ��ࠦ����
class ExpressionParser {
    size_t cur_index;
    std::string s;
    std::stack<value_t> values;  // ��� �࠭���� �஬������� ���祭�� ���᫥���

    // ��⮤� ��� ��ࠡ�⪨:
    void S(); // ᫮����� � ���⠭��
    void M(); // 㬭������ � �������
    void P(); // ���������� � �⥯���
    void V(); // ���祭�� (�㭪樨, ᪮���, �᫠)
    void D(); // ��� (楫�� � �஡��� �ᥫ)
public:
    long double parse(const std::string &s_);
};