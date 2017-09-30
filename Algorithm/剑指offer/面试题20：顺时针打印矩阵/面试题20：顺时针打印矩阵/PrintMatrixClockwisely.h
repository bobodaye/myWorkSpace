#pragma once

#include <vector>
#include <iostream>

class PrintMatrixClockwisely {
public:
	/// \brief   Print		顺时针打印矩阵
	/// \param   m_nMatrix  二维矩阵
	/// \return
	static void Print(const std::vector<std::vector<int> >& m_nMatrix)
	{
		if (0 >= m_nMatrix.size() )
			return;
		return Print(m_nMatrix, 0, m_nMatrix.size() - 1, 0, m_nMatrix[0].size() - 1);
	}
private:
	/// \brief   Print		顺时针打印矩阵
	/// \param   m_nMatrix  二维矩阵
	/// \param   upBound	上界
	/// \param   downBound  下界
	/// \param   leftBound  左界
	/// \param   rightBound 右界
	/// \return
	static void Print(const std::vector<std::vector<int> >& m_nMatrix, 
		int upBound, int downBound, int leftBound, int rightBound)
	{
		int m_nRows = m_nMatrix.size();
		int m_nCols = m_nMatrix[0].size();
		
		if (upBound < 0 || leftBound < 0)
			return;
		if (upBound > downBound || leftBound > rightBound 
			|| downBound >= m_nRows || rightBound >= m_nCols)
			return;
		int i, j;
		while (upBound <= downBound && leftBound <= rightBound)
		{
			i = upBound;
			for (j = leftBound; j <= rightBound; ++j)
				std::cout << m_nMatrix[i][j] << " ";
			++upBound;
			for (i = upBound; i <= downBound; ++i)
				std::cout << m_nMatrix[i][j - 1] << " ";
			--rightBound;
			for (j = rightBound; j >= leftBound && upBound <= i - 1; --j)
				std::cout << m_nMatrix[i - 1][j] << " ";
			--downBound;
			for (i = downBound; i >= upBound && rightBound >= j + 1; --i)
				std::cout << m_nMatrix[i][j + 1] << " ";
			++leftBound;
		}
		std::cout << "\n";
	}
};