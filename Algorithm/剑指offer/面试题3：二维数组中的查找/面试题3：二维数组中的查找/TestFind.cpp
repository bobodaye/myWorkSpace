#include "Find.h"

#if 0
template<size_t R, size_t C>
void InitMatrix(std::vector<std::vector<int> >& matrix, int (&array)[R][C])
{
	matrix.resize(R, std::vector<int>(C, 0) );

	for (int i = 0; i < R; i++)
	for (int j = 0; j < C; j++)
		matrix[i][j] = array[i][j];
}
#endif

//int array1[][4] = {
//	{ 1, 2,  8,  9 },
//	{ 2, 4,  9, 12 },
//	{ 4, 7, 10, 13 },
//	{ 6, 8, 11, 15 }
//};

//通过二维数组初始化vector
std::vector<std::vector<int> > matrix = 
{
	{ 1, 2,  8,  9 },
	{ 2, 4,  9, 12 },
	{ 4, 7, 10, 13 },
	{ 6, 8, 11, 15 }
};

int main()
{
	/*std::vector<std::vector<int> > matrix;
	InitMatrix(matrix, array1);*/

	bool flag = false;
	flag = FindInMatrix::Find(matrix, 8);

	return 0;
}