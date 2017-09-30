#pragma once

#include <vector>
#include <cassert>

class RotaryArray {
public:
	/// \brief   MinNum ����ת�����е���С����
	/// \param   seq ��ת����
	/// \return ��ת�����е���С����
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
			// ����±�Ϊleft��right��midIndexָ�������������ȣ���ֻ��˳�����
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