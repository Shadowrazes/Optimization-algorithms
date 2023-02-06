//-------------------------------------------------------------------------------------------
// SimpleFraction.h
// Description: Класс, реализующий простые дроби
// Date: 31.01.2023
// Authors: Хьюго М.А. & Наумов Н.В.
// Ⓒ Sibsutis university
//-------------------------------------------------------------------------------------------

#include <iostream>

#pragma once

namespace Fraction {
class SimpleFraction {
public:
	SimpleFraction();
	SimpleFraction(int divisible, int divider);

	void Reduction();
	
	void SetDivisible(int divisible) { m_divisible = divisible; }
	int  GetDivisible() const { return m_divisible; }

	void SetDivider(int divider) { m_divider = divider; }
	int  GetDivider() const { return m_divider; }

	bool IsOne() const { return m_divisible == m_divider; }
	bool IsZero() const { return m_divisible == 0; }

	static void ToDivider(SimpleFraction& first, SimpleFraction& second);
	SimpleFraction ToAbs();

	SimpleFraction operator+(SimpleFraction second);
	SimpleFraction& operator+=(SimpleFraction second);
	SimpleFraction operator-(SimpleFraction second);
	SimpleFraction& operator-=(SimpleFraction second);
	SimpleFraction operator*(SimpleFraction second);
	SimpleFraction& operator*=(SimpleFraction second);
	SimpleFraction operator/(SimpleFraction second);
	SimpleFraction& operator/=(SimpleFraction second);

	friend inline std::ostream& operator<< (std::ostream& out, const Fraction::SimpleFraction& fraction);

	friend bool operator== (SimpleFraction first, SimpleFraction second);
	friend bool operator!= (SimpleFraction first, SimpleFraction second);
	friend bool operator> (SimpleFraction first, SimpleFraction second);
	friend bool operator< (SimpleFraction first, SimpleFraction second);

protected:
	int m_divisible;	// Делимое
	int m_divider;		// Делитель

	static int	NOD(int a, int b);
	static int	NOK(int a, int b);
};

inline std::ostream& operator<< (std::ostream& out, const SimpleFraction& fraction) {
	if (fraction.m_divider == 1) {
		out << fraction.m_divisible;
	}
	else {
		out << fraction.m_divisible << "/" << fraction.m_divider;
	}
	return out;
}

inline bool operator== (SimpleFraction first, SimpleFraction second)
{
	return first.m_divisible == second.m_divisible && first.m_divider == second.m_divider;
}

inline bool operator!= (SimpleFraction first, SimpleFraction second)
{
	return first.m_divisible != second.m_divisible || first.m_divider != second.m_divider;
}

inline bool operator> (SimpleFraction first, SimpleFraction second)
{
	SimpleFraction tempFirst = first;
	SimpleFraction tempSecond = second;

	SimpleFraction::ToDivider(tempFirst, tempSecond);
	
	return tempFirst.m_divisible > tempSecond.m_divisible;
}

inline bool operator< (SimpleFraction first, SimpleFraction second)
{
	SimpleFraction tempFirst = first;
	SimpleFraction tempSecond = second;

	SimpleFraction::ToDivider(tempFirst, tempSecond);

	return tempFirst.m_divisible < tempSecond.m_divisible;
}
}