#pragma once

#include <cassert>

bool g_InvalidInput = false;

class PowerClass {
public:
	/// \brief   Power 计算base的exponent次方
	/// \param   base 底数
	/// \param   exponent 幂
	/// \return 计算结果
	static double Power(double base, int exponent)
	{
		g_InvalidInput = false;
		if (Equal(base, 0.0f) && exponent <= 0) 
		{
			g_InvalidInput = true;
			return 0.0f;
		}
		unsigned int exp = (0 < exponent) ? exponent : -exponent;
		
		double result = Power(base, exp);
		return (0 < exponent) ? result : (1 / result);
	}
private:
	static double Power(double base, unsigned int exponent)
	{
		if (0 == exponent)
			return 1.0f;
		if (1 == exponent)
			return base;
		double result = Power(base, exponent >> 1);
		result *= result;
		if (exponent & 0x1)
			result *= base;
		return result;
	}

	static bool Equal(double num1, double num2)
	{
		if (num1 - num2 > -0.0000001f && num1 - num2 < 0.0000001f)
			return true;
		else
			return false;
	}
};