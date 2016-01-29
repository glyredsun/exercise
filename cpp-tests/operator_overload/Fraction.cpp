#include "Fraction.h"

std::ostream& operator<<(std::ostream& o, const Fraction &f)
{
	return o << f._numerator << "/" << f._denominator;
}

Fraction operator +(const Fraction &f1, const Fraction &f2)
{
	return Fraction(f1._numerator*f2._denominator + f2._numerator*f1._denominator, f1._denominator*f2._denominator);
}

Fraction operator -(const Fraction &f1, const Fraction &f2)
{
	return Fraction(f1._numerator*f2._denominator - f2._numerator*f1._denominator, f1._denominator*f2._denominator);
}

Fraction operator *(const Fraction &f1, const Fraction &f2)
{
	return Fraction(f1._numerator*f1._numerator, f2._denominator*f2._denominator);
}

Fraction operator /(const Fraction &f1, const Fraction &f2)
{
	return Fraction(f1._numerator*f2._denominator, f1._denominator*f2._numerator);
}

bool operator==(const Fraction &f1, const Fraction &f2)
{
	return (&f1 == &f2) || (f1._denominator * f2._numerator == f2._denominator * f1._numerator);
}

bool operator<(const Fraction &f1, const Fraction &f2)
{
	return static_cast<double>(f1) < static_cast<double>(f2);
}

Fraction::Fraction(int numerator, int denominator)
: _numerator(numerator)
, _denominator(denominator)
{

}

Fraction Fraction::operator -() const
{
	return Fraction(-this->_numerator, this->_denominator);
}

Fraction Fraction::operator +() const
{
	return *this;
}

Fraction& Fraction::operator=(const Fraction& other)
{
	if (this != &other) 
	{
		this->_numerator = other._numerator;
		this->_denominator = other._denominator;
	}	
	return *this;
}

Fraction& Fraction::operator+=(const Fraction &other)
{
	this->_numerator = this->_numerator*other._denominator + other._numerator*this->_denominator;
	this->_denominator *= other._denominator;
	return *this;
}

Fraction& Fraction::operator-=(const Fraction &other)
{
	this->_numerator = this->_numerator*other._denominator - other._numerator*this->_denominator;
	this->_denominator *= other._denominator;
	return *this;
}

Fraction& Fraction::operator*=(const Fraction &other)
{
	this->_numerator *= other._numerator;
	this->_denominator *= other._denominator;
	return *this;
}

Fraction& Fraction::operator/=(const Fraction &other)
{
	this->_numerator *= other._denominator;
	this->_denominator *= other._numerator;
	return *this;
}

Fraction::operator double() const
{
	return static_cast<double>(_numerator) / _denominator;
}

Fraction::operator int() const
{
	return _numerator / _denominator;
}