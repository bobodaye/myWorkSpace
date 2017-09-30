#pragma once

#include <cassert>

class ReplaceBlank {
public:
	/// \brief   Replace 替换字符串中的所有空格为"%20"
	/// \param   str 待更新的字符串
	/// \param   length 存储字符串的字符数组占用的内存大小
	/// \return
	static void Replace(char str[], int length)
	{
		assert(nullptr != str && 0 < length);
		int i, j, blankNums = 0;
		//原来字符串长度
		int oldLen = 0;
		//用来替换空格的字符串
		char replaceBlankStr[] = "%20";
		//计算str包含的空格数
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
			为什么j和i相等就代表替换空格的过程结束？
			
			1.开始j和i相差空格数*2个字节
			2.每次替换空格时，j比i多前进2个字节。
			3.因此当替换完所有空格时，i和j相差为0。
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