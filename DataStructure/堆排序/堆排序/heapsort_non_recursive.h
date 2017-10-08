#pragma once

#include <vector>

//调整大根堆(迭代实现)
template<typename T>
void AdjustHeap(std::vector<T>& elems, size_t root, size_t size)
{
	int m_nRootValue = elems[root];
	int m_nChild = 2 * root + 1;

	for (; m_nChild < size; m_nChild = 2 * root + 1)
	{
		//前提：如果根有右孩子，找左右孩两者较大的那个
		if (m_nChild + 1 < size && elems[m_nChild] < elems[m_nChild + 1])
			++m_nChild;
		//根的值和较大的孩子做比较，小于则两者进行交换
		if (m_nRootValue < elems[m_nChild])
		{
			elems[root] = elems[m_nChild];
			elems[m_nChild] = m_nRootValue;
		}
		else
			break;
	}
}