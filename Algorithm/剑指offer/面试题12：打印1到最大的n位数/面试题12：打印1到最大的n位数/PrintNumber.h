#pragma once

#include <cassert>
#include <vector>
#include <iostream>

//struct Number
//{
//	unsigned char num1 : 4;
//	unsigned char num2 : 4;
//};

class PrintNumber {
public:
	/// \brief   Print 打印1到最大的n位数
	/// \param   n 最大数字的位数
	/// \return
	static void Print(int n)
	{
		if (n <= 0)
			return;

		std::vector<char>* number = new std::vector<char>(n, '0');
		assert(nullptr != number);

		while (!Increment(*number) )
		{
			Show(*number);
		}
		delete number;
	}
private:
	/// \brief   Increment 对number加1
	/// \param   number 表示的数字
	/// \return number是否达到最大值，如果是，返回true，否则返回false
	static bool Increment(std::vector<char>& number)
	{
		int i, carry = 0;
		for (i = number.size() - 1; i >= 0; i--)
		{
			int tmp = 0;
			tmp += (number[i] - '0' + 1);
			carry = tmp / 10;
			number[i] = tmp % 10 + '0';
			if (!carry)
				break;
			if (0 == i /* && true == carry*/)
				return true;
		}
		return false;
	}

	/// \brief   Show 打印number表示的数字
	/// \param   number
	/// \return
	static void Show(std::vector<char>& number)
	{
		int numberSize = number.size();
		int i;
		bool isBeginning = true;

		for (i = 0; i < numberSize; i++)
		{
			if (isBeginning && 0 != number[i])
				isBeginning = false;

			if (!isBeginning)
				std::cout << number[i];
		}
		std::cout << "\n";
	}
};