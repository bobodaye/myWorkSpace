#pragma once

#include <cassert>

class ReplaceBlank {
public:
	/// \brief   Replace �滻�ַ����е����пո�Ϊ"%20"
	/// \param   str �����µ��ַ���
	/// \param   length �洢�ַ������ַ�����ռ�õ��ڴ��С
	/// \return
	static void Replace(char str[], int length)
	{
		assert(nullptr != str && 0 < length);
		int i, j, blankNums = 0;
		//ԭ���ַ�������
		int oldLen = 0;
		//�����滻�ո���ַ���
		char replaceBlankStr[] = "%20";
		//����str�����Ŀո���
		while ('\0' != str[oldLen])
		{
			if (' ' == str[oldLen])
				blankNums++;
			oldLen++;
		}
		int newLen = oldLen + blankNums * 2;
		assert(newLen <= length);

		i = oldLen;
		j = newLen;
		/*
			Ϊʲôj��i��Ⱦʹ����滻�ո�Ĺ��̽�����
			
			1.��ʼj��i���ո���*2���ֽ�
			2.ÿ���滻�ո�ʱ��j��i��ǰ��2���ֽڡ�
			3.��˵��滻�����пո�ʱ��i��j���Ϊ0��
		*/
		while (j != i)
		{
			if (' ' == str[i])
			{
				int k = sizeof(replaceBlankStr) - 1;
				while (k > 0)
				{
					str[j--] = replaceBlankStr[--k];
				}
				i--;
			}
			else
			{
				str[j--] = str[i--];
			}
		}
	}
};