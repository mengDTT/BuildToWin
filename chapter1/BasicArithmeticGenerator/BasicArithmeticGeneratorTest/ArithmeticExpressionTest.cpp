#include "stdafx.h"
#include "../BasicArithmeticGenerator/arithmetic_expression.h"
#include "gtest/gtest.h"
#include <iostream>
#include <random>
using namespace std;

TEST(ArithmeticExpression, InfixToPostfixExpressionWithoutBracket)
{
	EXPECT_EQ(wstring(L"3 4 2 x + "), infix_to_postfix_expression(wstring(L"3 + 4 x 2 ")));

	EXPECT_EQ(wstring(L"3 2 - 1 - "), infix_to_postfix_expression(wstring(L"3 - 2 - 1 ")));

	EXPECT_EQ(wstring(L"2 2 3 ^ ^ "), infix_to_postfix_expression(wstring(L"2 ^ 2 ^ 3 ")));
}

TEST(ArithmeticExpression, InfixToPostfixExpressionWithBracket)
{
	EXPECT_EQ(wstring(L"3 4 2 x 1 5 - 2 3 ^ ^ ¡Â + "), infix_to_postfix_expression(wstring(L"3 + 4 x 2 ¡Â ( 1 - 5 ) ^ 2 ^ 3 ")));
}

TEST(ArithmeticExpression, PostToInfixExpressionWithBracket)
{
	EXPECT_EQ(wstring(L"1 + 2 - 3"), postfix_to_infix_expression(wstring(L"1 2 + 3 -")));
	EXPECT_EQ(wstring(L"1 + 2 + 3"), postfix_to_infix_expression(wstring(L"1 2 + 3 +")));
	EXPECT_EQ(wstring(L"(1 - 2) x (3 - 4)"), postfix_to_infix_expression(wstring(L"1 2 - 3 4 - x")));
	EXPECT_EQ(wstring(L"(1 - 2) ¡Â (3 x 4)"), postfix_to_infix_expression(wstring(L"1 2 - 3 4 x ¡Â")));
	EXPECT_EQ(wstring(L"3 + 4 x 2 ¡Â (1 - 5) ^ (2 ^ 3)"), postfix_to_infix_expression(wstring(L"3 4 2 x 1 5 - 2 3 ^ ^ ¡Â + ")));
	EXPECT_EQ(wstring(L"1 + 2 x 3 + (4 x 5 + 6) x 7"), postfix_to_infix_expression(wstring(L"1 2 3 x + 4 5 x 6 + 7 x +")));
}

TEST(ArithmeticExpression, GenerateExpression)
{
	vector<arithmetic_expression> exp(10, { 10, 3 });
	wcout.imbue(locale(""));
	for (auto &item : exp)
	{
		item.generate_expression();
		wcout << item.root->exp << " = " << item.root->value << endl;
	}
}
