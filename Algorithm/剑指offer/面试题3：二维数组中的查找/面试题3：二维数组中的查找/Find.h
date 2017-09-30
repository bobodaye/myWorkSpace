#pragma once

#include <vector>

class FindInMatrix {
public:
	/// \brief   Find �ڲ�������Ķ�ά�����в��Ҹ���������
	/// \param   matrix ��ά����
	/// \param   number �����ҵ�����
	/// \return ���number���ڣ�����true�����򣬷���false
	static bool Find(const std::vector<std::vector<int> >& matrix, int number)
	{
		int i, j;
		int rows, cols;
		rows = matrix.size();
		cols = matrix[0].size();
		i = 0;
		j = cols - 1;

		for (;;)
		{ 
			if (number == matrix[i][j])
				return true;

			while (i < rows && number > matrix[i][j])
			{
				i++;
			}
			if (i == rows)
				break;
			while (j >= 0 && number < matrix[i][j])
			{
				j--;
			}
			if (0 > j)
				break;	
		}
		return false;
	}
};