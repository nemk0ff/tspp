/**
 * @file test.h
 * @author Nemkov Daniil
 * @brief ���������� 䠩�, ����室��� ��� ���樠����樨 ������⥪� ��⮢ googletest
 * @date 23.05.2025
 */
#pragma once
#include <gtest/gtest.h>
#include <iostream>

//! \brief �����, ����뢠�騩 ���� ��� ExpressionParser
class ExpressionParserTest : public testing::Test {
protected:
    //! \brief �����⨬�� ����譮��� �� ���᫥����
    double precision = 1e-5;
};
