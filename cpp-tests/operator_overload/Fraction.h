#ifdef _MSC_VER
#pragma once
#endif
#ifndef _FRACTION_H_
#define _FRACTION_H_
#include <ostream>
#include <utility>
class Fraction
{
public:
	friend std::ostream& operator << (std::ostream& o, const Fraction &f);

	friend Fraction operator +(const Fraction &f1, const Fraction &f2);
	friend Fraction operator -(const Fraction &f1, const Fraction &f2);
	friend Fraction operator *(const Fraction &f1, const Fraction &f2);
	friend Fraction operator /(const Fraction &f1, const Fraction &f2);
	friend Fraction operator %(const Fraction &f1, const Fraction &f2) = delete;

	friend bool operator == (const Fraction &f1, const Fraction &f2);
	friend bool operator<(const Fraction &f1, const Fraction &f2);
public:
	Fraction(int numerator, int denominator);

	Fraction operator -() const;
	Fraction operator +() const;
	Fraction operator ~() = delete;

	Fraction& operator++() = delete;
	Fraction& operator++(int) = delete;
	Fraction& operator--() = delete;
	Fraction& operator--(int) = delete;

	Fraction& operator=(const Fraction &other);

	Fraction& operator+=(const Fraction &other);
	Fraction& operator-=(const Fraction &other);
	Fraction& operator*=(const Fraction &other);
	Fraction& operator/=(const Fraction &other);
	Fraction& operator%=(const Fraction &other) = delete;

	operator double() const;
	operator int() const;

private:
	int _numerator;
	int _denominator;
};

using std::rel_ops::operator!=;
using std::rel_ops::operator<=;
using std::rel_ops::operator>;
using std::rel_ops::operator>=;

#endif