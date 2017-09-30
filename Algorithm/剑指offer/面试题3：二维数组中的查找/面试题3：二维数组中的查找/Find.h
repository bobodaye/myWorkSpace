#pragma once

#include <vector>

class FindInMatrix {
public:
	/// \brief   Find 在部分有序的二维数组中查找给定的数字
	/// \param   matrix 二维数组
	/// \param   number 待查找的数字
	/// \return 如果number存在，返回true，否则，返回false
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