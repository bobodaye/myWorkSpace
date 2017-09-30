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
	/// \brief   Print ��ӡ1������nλ��
	/// \param   n ������ֵ�λ��
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
	/// \brief   Increment ��number��1
	/// \param   number ��ʾ������
	/// \return number�Ƿ�ﵽ���ֵ������ǣ�����true�����򷵻�false
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

	/// \brief   Show ��ӡnumber��ʾ������
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