#include <vector>

class Solution {
public:
	std::vector<int> MinKNumbers(std::vector<int>& numbers, int k)
	{
		if (k > numbers.size())
			return std::vector<int>();
		if (k < numbers.size())
			MinKNumbers(numbers, 0, numbers.size() - 1, k);
		return std::vector<int>(numbers.begin(), numbers.begin() + k);
	}
private:
	int Partition(std::vector<int>& numbers, int low, int high)
	{
		int pivot_value = numbers[low];
		int left = low, right = high;
		
		while (left < right)
		{
			while (left < right && numbers[right] >= pivot_value)
				--right;
			numbers[left] = numbers[right];
			while (left < right && numbers[left] < pivot_value)
				++left;
			numbers[right] = numbers[left];
		}
		numbers[right] = pivot_value;
		return right;
	}

	void MinKNumbers(std::vector<int>& numbers, int low, int high, int k)
	{
		if (low < high && k > 0)
		{
			int pivot_index = Partition(numbers, low, high);
			if (k < pivot_index)
				MinKNumbers(numbers, low, pivot_index - 1, k);
			else if (k > pivot_index + 1)
				MinKNumbers(numbers, pivot_index + 1, high, k - pivot_index - 1);
		}
	}
};