#pragma once

#include <vector>

//���������(����ʵ��)
template<typename T>
void AdjustHeap(std::vector<T>& elems, size_t root, size_t size)
{
	int m_nRootValue = elems[root];
	int m_nChild = 2 * root + 1;

	for (; m_nChild < size; m_nChild = 2 * root + 1)
	{
		//ǰ�᣺��������Һ��ӣ������Һ����߽ϴ���Ǹ�
		if (m_nChild + 1 < size && elems[m_nChild] < elems[m_nChild + 1])
			++m_nChild;
		//����ֵ�ͽϴ�ĺ������Ƚϣ�С�������߽��н���
		if (m_nRootValue < elems[m_nChild])
		{
			elems[root] = elems[m_nChild];
			elems[m_nChild] = m_nRootValue;
		}
		else
			break;
	}
}