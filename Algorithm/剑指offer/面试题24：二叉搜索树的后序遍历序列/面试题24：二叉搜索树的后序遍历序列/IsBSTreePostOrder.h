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
		//通过根判断左子树和右子树的位置
		while (pivot < right && postOrder[right] > postOrder[pivot])
			pivot++;
		i = pivot;
		while (i < right && postOrder[i] > postOrder[right])
		{
			i++;
		}
		if (i == right)
			flag = true;
		//如果右子树的元素全部大于根，再递归地检查其左右子树
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
