#pragma once

#include <vector>

class BSTree {
public:
	static bool IsBSTreePostOrder(const std::vector<int>& postOrder)
	{
		return IsBSTreePostOrder(postOrder, 0, postOrder.size() - 1);
	}
private:
	static bool IsBSTreePostOrder(const std::vector<int>& postOrder, int left, int right)
	{
		bool flag = false;
		int pivot = left, i = 0;
		//ͨ�����ж�����������������λ��
		while (pivot < right && postOrder[right] > postOrder[pivot])
			pivot++;
		i = pivot;
		while (i < right && postOrder[i] > postOrder[right])
		{
			i++;
		}
		if (i == right)
			flag = true;
		//�����������Ԫ��ȫ�����ڸ����ٵݹ�ؼ������������
		if (flag)
		{
			if (left < pivot - 1)
				flag = IsBSTreePostOrder(postOrder, left, pivot - 1);
			if (flag && pivot < right)
				flag = IsBSTreePostOrder(postOrder, pivot, right - 1);
		}
		return flag;
	}
};
