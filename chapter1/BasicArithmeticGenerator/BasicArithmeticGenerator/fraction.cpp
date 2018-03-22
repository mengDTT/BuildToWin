#include "stdafx.h"
#include "fraction.h"


MyFraction MyFraction::reduction() const
{
	int gcd = abs(GCD(numerator, denominator));
	return MyFraction(numerator/gcd, denominator/gcd);
}

MyFraction MyFraction::reciprocal() const
{
	return MyFraction(denominator, numerator);
}

bool MyFraction::is_proper_fraction() const
{
	return numerator < denominator;
}

wstring MyFraction::output_nonproper_fraction() const
{
	wstring result;
	unsigned base = numerator / denominator;
	unsigned numerator2 = numerator % denominator;
	result.append(to_wstring(base)).append(L"'");
	result.append(MyFraction(numerator2, denominator).output_proper_fraction());

	return result;
}

wstring MyFraction::output_proper_fraction() const
{
	wstring result;
	result.append(to_wstring(numerator));
	result.append(L"/");
	result.append(to_wstring(denominator));

	return result;
}

wstring MyFraction::format_output()
{
	wstring result;

	if (denominator == 1)
	{
		return to_wstring(numerator);
	}

	if (!is_proper_fraction())
	{
		return output_nonproper_fraction();
	}
	else
	{
		return output_proper_fraction();
	}
}

int GCD(int a, int b)
{
	int c;
	while (a % b != 0)
	{
		c = a % b;
		a = b;
		b = c;
	}

	return b;
}

bool operator==(const MyFraction & lhs, const MyFraction & rhs)
{
	MyFraction f1 = lhs.reduction();
	MyFraction f2 = rhs.reduction();
	return f1.numerator == f2.numerator && f1.denominator == f2.denominator;
}

MyFraction operator +(const MyFraction & lhs, const MyFraction & rhs)
{
	int a = lhs.numerator * rhs.denominator + lhs.denominator * rhs.numerator;
	int b = lhs.denominator * rhs.denominator;

	return MyFraction(a, b).reduction();
}

MyFraction operator -(const MyFraction & lhs, const MyFraction & rhs)
{
	MyFraction rhs2(rhs);
	rhs2.numerator = -rhs2.numerator;
	return lhs + rhs2;
}

MyFraction operator *(const MyFraction & lhs, const MyFraction & rhs)
{
	int a = lhs.numerator * rhs.numerator;
	int b = lhs.denominator * rhs.denominator;

	return MyFraction(a, b).reduction();
}

MyFraction operator /(const MyFraction & lhs, const MyFraction & rhs)
{
	MyFraction result = lhs * rhs.reciprocal();
	return result.reduction();
}

bool operator<(const MyFraction & lhs, const MyFraction & rhs)
{
	MyFraction diff = lhs - rhs;
	return diff.numerator < 0 ? true : false;
}

wostream & operator<<(wostream &os, const MyFraction & rhs)
{
	MyFraction f = rhs.reduction();

	os << f.format_output();

	return os;
}
