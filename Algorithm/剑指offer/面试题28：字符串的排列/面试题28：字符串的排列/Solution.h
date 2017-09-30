#include <vector>
#include <string>

class Solution {
public:
	template<typename T, size_t N>
	static std::vector<std::vector<T> > Permutation(T (&array)[N])
	{
		std::vector<std::vector<T> > result;
		Permutation(array, 0, result);
		return result;
	}
	
private:
	template<typename T, size_t N>
	static void Permutation(T (&array)[N], int j, std::vector<std::vector<T> >& output)
	{
		int i;
		for (i = j; i < N; ++i)
		{
			if (i > j && array[i] == array[j])
				continue;
			std::swap(array[i], array[j]);
			Permutation(array, j + 1, output);
			
			if (N - 1 == j)
			{
				std::vector<T> tmp(array, array + N);
				output.push_back(tmp);
			}
			std::swap(array[i], array[j]);
		}
	}
};