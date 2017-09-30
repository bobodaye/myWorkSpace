#pragma once

#include <vector>
#include <cassert>

class RotaryArray {
public:
	/// \brief   MinNum 求旋转数组中的最小数字
	/// \param   seq 旋转数组
	/// \return 旋转数组中的最小数字
	static int MinNum(std::vector<int> seq)
	{
		assert(0 < seq.size() );
		int left, right;
		
		left = 0; 
		right = seq.size() - 1;
		int midIndex = 0;
		while (seq[left] >= seq[right])
		{
			if (1 == right - left)
			{
				midIndex = right;
				break;
			}
			midIndex = (left + right) / 2;
			// 如果下标为left、right和midIndex指向的三个数字相等，则只能顺序查找
			if (seq[left] == seq[midIndex] && seq[right] == seq[midIndex])
				return MinInOrder(seq, left, right);
			if (seq[left] <= seq[midIndex])
				left = midIndex;
			else if (seq[right] >= seq[midIndex])
				right = midIndex;
		}
		return seq[midIndex];
	}
private:
	static int MinInOrder(std::vector<int> seq, int left, int right)
	{
		int result = seq[left];
		for (int i = left + 1; i <= right; ++i)
		{
			if (result > seq[i])
				result = seq[i];
		}
		return result;
	}
};