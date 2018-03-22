#pragma once
#include <string>
using namespace std;

struct MyFraction
{
	MyFraction(int a = 0, int b = 1) :numerator(a), denominator(b) {};

	MyFraction reduction() const;
	MyFraction reciprocal() const;
	
	bool is_proper_fraction() const;
	wstring output_nonproper_fraction() const;
	wstring output_proper_fraction() const;
	wstring format_output();

	int numerator;
	int denominator;
};

int GCD(int a, int b);

bool operator ==(const MyFraction & lhs, const MyFraction & rhs);
MyFraction operator +(const MyFraction & lhs, const MyFraction & rhs);
MyFraction operator -(const MyFraction & lhs, const MyFraction & rhs);
MyFraction operator *(const MyFraction & lhs, const MyFraction & rhs);
MyFraction operator /(const MyFraction & lhs, const MyFraction & rhs);
bool operator <(const MyFraction & lhs, const MyFraction & rhs);
wostream & operator <<(wostream &os, const MyFraction & rhs);

