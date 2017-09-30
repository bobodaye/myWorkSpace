#include "Solution.h"

int main()
{
	std::vector<int> numbers = { 4, 5, 1, 6, 2, 7, 3, 8 };
	Solution solution;

	std::vector<int> result = solution.MinKNumbers(numbers, 5);

	return 0;
}