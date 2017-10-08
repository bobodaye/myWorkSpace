#pragma once

#include <vector>

//调整大根堆(递归实现)
template<typename T>
void AdjustHeap(std::vector<T>& elems, size_t root, size_t size)
{
	int m_nRootValue = elems[root];
	int m_nChild = 2 * root + 1;
	
	if (m_nChild >= size)
		return;
	//前提：如果根有右孩子，找左右孩两者较大的那个
	if (m_nChild + 1 < size && elems[m_nChild] < elems[m_nChild + 1])
		++m_nChild;
	//根的值和较大的孩子做比较，小于则两者进行交换
	if (m_nRootValue < elems[m_nChild])
	{
		std::swap(elems[root], elems[m_nChild]);
		AdjustHeap(elems, m_nChild, size);
	}
}

//创建大根堆
template<typename T>
void CreateHeap(std::vector<T>& elems)
{
	size_t m_nElemsSize = elems.size();
	//差1错误
	for (int i = m_nElemsSize / 2 - 1; i >= 0; --i)
		AdjustHeap(elems, i, m_nElemsSize);
}

//堆排序
template<typename T>
void HeapSort(std::vector<T>& elems)
{
	if (elems.size() <= 0)
		return;
	CreateHeap(elems);

	for (int i = elems.size() - 1; i > 0; --i)
	{
		std::swap(elems[0], elems[i]);
		AdjustHeap(elems, 0, i);
	}	
}