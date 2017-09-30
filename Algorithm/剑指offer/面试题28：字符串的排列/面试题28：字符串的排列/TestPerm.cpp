#include "Solution.h"

int main()
{
	char strings[] = { 'a', 'c', 'c', 'c' };
	int numbers[] = { 1, 2, 3, 4 }; 

	/*std::vector<std::vector<int> > number_result;
	number_result = Solution::Permutation(numbers);*/
	
	std::vector<std::vector<char> > string_result;
	string_result = Solution::Permutation(strings);

	for (int i = 0; i < string_result.size(); ++i)
	{
		printf_s("(%2d) ", i + 1);
		for (int j = 0; j < sizeof(strings); ++j)
		{
			printf_s("%c  ", string_result[i][j]);
		}
		putchar(10);
	}
	return 0;
}