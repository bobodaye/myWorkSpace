#pragma once
#include <vector>

//ѡ������
template<typename T>
void SelectSort(std::vector<T>& elems)
{
	int max_value_in_elems;
	int max_value_index;

	for (int i = elems.size(); i > 0; --i)
	{
		//��ʼ��
		max_value_in_elems = 0x80000000; //ʮ���Ʊ�ʾ��-2,147,483,648
		max_value_index = 0;
		for (int j = 0; j < i; ++j)
		{
			if (max_value_in_elems < elems[j])	//�����������Ԫ��
			{
				max_value_in_elems = elems[j];
				max_value_index = j;
			}		
		}
		elems[max_value_index] = elems[i - 1];	//�������Ԫ�غ�elems[i-1]
		elems[i - 1] = max_value_in_elems;
	}
}