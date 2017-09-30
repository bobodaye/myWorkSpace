#include "RotaryArrayMinNum.h"

int main()
{
	std::vector<int> seq1 = { 1, 0, 1, 1, 1 };
	std::vector<int> seq2 = { 1, 1, 1, 0, 1 };

	int minNum1 = RotaryArray::MinNum(seq1);
	int minNum2 = RotaryArray::MinNum(seq2);

	return 0;
}