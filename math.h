/**
 * @file math.h
 * @author Nemkov Daniil
 * @brief ���������� 䠩�, ॠ�����騩 ����室��� ��⥬���᪨� �㭪樨
 * @date 23.05.2025
 */

#pragma once

//! \brief �ᯮ��㥬� � �������� ⨯ ��� �࠭���� �ᥫ
using value_t = long double;
//! \brief ��筮��, �ᯮ��㥬�� ��� ��।������ ࠢ���⢠ �ᥫ � ������饩 �窮�
constexpr value_t EPS = 1e-10;

//! \brief ������, �易��� � ⥬, �� �����-� �ᮡ� ���७�� 祫���� ������ �㭪�� abs � ��������筨� functional
#define abs my_abs
//! \brief �㭪��, ॠ������� ���᫥��� ����� �᫠
value_t my_abs(value_t x);

//! \brief �㭪��, ॠ������� ���������� �ᯮ����� � �⥯��� x
//! \param x �⥯��� ��� �ᯮ�����
value_t exp(value_t x);
//! \brief �㭪��, ॠ������� ���᫥��� ����ࠫ쭮�� �����䬠 x
//! \param x ��᫮ ��� �����䬮�
value_t log(value_t x);
//! \brief �㭪��, ॠ������� ���᫥��� �����䬠 x �� �᭮����� 10
//! \param x ��᫮ ��� �����䬮�
value_t log10(value_t x);

//! \brief �㭪��, ॠ������� ���������� base � �⥯��� exp
//! \param base ��᫮, ���஥ ���������� � �⥯���
//! \param exp ��᫮, ��।����饥 �⥯���, � ������ ����室��� ������� base
value_t pow(value_t base, value_t exp);
//! \brief �㭪��, ॠ������� ���᫥��� ���� �᫠ x
//! \param x ��᫮, �� ���ண� ������ ��७�
value_t sqrt(value_t x);

//! \brief �㭪��, ॠ������� ���᫥��� ᨭ�� x ࠤ���
//! \param x ��㬥�� � ࠤ�����
//! \return ����稭� � �஬���⪥ [-1; -1]
value_t sin(value_t x);
//! \brief �㭪��, ॠ������� ���᫥��� ��ᨭ�� x ࠤ���
//! \param x ��㬥�� � ࠤ�����
//! \return ����稭� � �஬���⪥ [-1; -1]
value_t cos(value_t x);
//! \brief �㭪��, ॠ������� ���᫥��� ⠭���� x ࠤ���
//! \param x ��㬥�� � ࠤ�����
value_t tan(value_t x);

//! \brief �㭪��, ॠ������� ���᫥��� ��ᨭ�� x
//! \return ����稭� � �஬���⪥ [-pi/2; pi/2]
value_t asin(value_t x);
//! \brief �㭪��, ॠ������� ���᫥��� �પ�ᨭ�� x
//! \return ����稭� � �஬���⪥ [0; pi]
value_t acos(value_t x);
//! \brief �㭪��, ॠ������� ���᫥��� ��⠭���� x
//! \return ����稭� � �஬���⪥ [-pi/2; pi/2]
value_t atan(value_t x);