#pragma once

#include <vector>

//���������(�ݹ�ʵ��)
template<typename T>
void AdjustHeap(std::vector<T>& elems, size_t root, size_t size)
{
	int m_nRootValue = elems[root];
	int m_nChild = 2 * root + 1;
	
	if (m_nChild >= size)
		return;
	//ǰ�᣺��������Һ��ӣ������Һ����߽ϴ���Ǹ�
	if (m_nChild + 1 < size && elems[m_nChild] < elems[m_nChild + 1])
		++m_nChild;
	//����ֵ�ͽϴ�ĺ������Ƚϣ�С�������߽��н���
	if (m_nRootValue < elems[m_nChild])
	{
		std::swap(elems[root], elems[m_nChild]);
		AdjustHeap(elems, m_nChild, size);
	}
}

//���������
template<typename T>
void CreateHeap(std::vector<T>& elems)
{
	size_t m_nElemsSize = elems.size();
	//��1����
	for (int i = m_nElemsSize / 2 - 1; i >= 0; --i)
		AdjustHeap(elems, i, m_nElemsSize);
}

//������
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