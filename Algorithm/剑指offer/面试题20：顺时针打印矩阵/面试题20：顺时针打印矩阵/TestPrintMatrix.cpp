#include "PrintMatrixClockwisely.h"

int main()
{
	std::vector<std::vector<int> > m_nMatrix1 = 
	{
		{  1,  2,  3,  4 },
		{  5,  6,  7,  8 },
		{  9, 10, 11, 12 },
		{ 13, 14, 15, 16 }
	};

	std::vector<std::vector<int> > m_nMatrix2 = 
	{
		{  1,  2,  3,  4 }
	};

	std::vector<std::vector<int> > m_nMatrix3 = 
	{
		{  1 },
		{  5 },
		{  9 },
		{ 13 }
	};

	std::vector<std::vector<int> > m_nMatrix4 = 
	{
		{ 1 }
	};

	PrintMatrixClockwisely::Print(m_nMatrix1);
	PrintMatrixClockwisely::Print(m_nMatrix2);
	PrintMatrixClockwisely::Print(m_nMatrix3);
	PrintMatrixClockwisely::Print(m_nMatrix4);

	return 0;
}