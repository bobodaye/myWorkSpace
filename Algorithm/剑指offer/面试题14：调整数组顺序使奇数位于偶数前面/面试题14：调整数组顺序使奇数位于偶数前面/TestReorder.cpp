#include "ReorderOddEven.h"

int main()
{
	std::vector<int> array1 = { 5, 3, 8, 7, 6, 2, 1, 4 };
	std::vector<int> array2 = { 2, 3, 4, 5, 6, 7, 8, 9 };
	//std::vector<int> array3 = { 4, 4, 4, -1 };

	ReorderOddEven::Reorder(array1);
	ReorderOddEven::Reorder(array2);
	//ReorderOddEven::Reorder(array3);

	return 0;
}