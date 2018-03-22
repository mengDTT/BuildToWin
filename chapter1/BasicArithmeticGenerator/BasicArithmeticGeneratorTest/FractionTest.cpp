// BasicArithmeticGeneratorTest.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "../BasicArithmeticGenerator/fraction.h"
#include "gtest/gtest.h"

TEST(MyFraction, gcd)
{
	EXPECT_EQ(2, GCD(6, 2));
	EXPECT_EQ(1, GCD(19, 3));
	EXPECT_EQ(3, GCD(9, 6));
	EXPECT_EQ(7, GCD(21, 7));
	EXPECT_EQ(7, GCD(0, 7));
}

TEST(MyFraction, FractionAddOperation)
{
	EXPECT_EQ(MyFraction(5, 6), MyFraction(1, 2) + MyFraction(1, 3));
	EXPECT_EQ(MyFraction(5, 6), MyFraction(2, 4) + MyFraction(1, 3));
};

TEST(MyFraction, FractionMinusOperation)
{
	EXPECT_EQ(MyFraction(1, 6), MyFraction(1, 2) - MyFraction(1, 3));
	EXPECT_EQ(MyFraction(0, 1), MyFraction(1, 2) - MyFraction(1, 2));
};

TEST(MyFraction, FractionMultiplyOperation)
{
	EXPECT_EQ(MyFraction(1, 6), MyFraction(1, 2) * MyFraction(1, 3));
	EXPECT_EQ(MyFraction(1, 7), MyFraction(1, 3) * MyFraction(3, 7));
	EXPECT_EQ(MyFraction(0, 1), MyFraction(0, 1) * MyFraction(1, 2));
};

TEST(MyFraction, FractionDivisionOperation)
{
	EXPECT_EQ(MyFraction(3, 2), MyFraction(1, 2) / MyFraction(1, 3));
	EXPECT_EQ(MyFraction(0, 1), MyFraction(0, 2) / MyFraction(1, 3));
};