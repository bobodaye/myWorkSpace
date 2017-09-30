#pragma once

#include <vector>

class ReorderOddEven {
public:
	/// \brief   Reorder 调整数组顺序，使得奇数位于偶数前面
	/// \param   pData 数组
	/// \return
	static void Reorder(std::vector<int>& pData)
	{
		int pDataSize;
		if ((pDataSize = pData.size()) < 1)
			return;
		int i;
		int m_p1 = 0, m_p2 = 0;

		while (m_p1 < pDataSize)
		{
			if (!(pData[m_p1] & 0x1) )	//m_p1指向数组中第一个偶数
			{
				m_p2 = m_p1 + 1;
				while (m_p2 < pDataSize && !(pData[m_p2] & 0x1) )	//m_p2指向m_p1之后第一个奇数
					++m_p2;
				if (m_p2 == pDataSize)
					break;
				int m_nData = pData[m_p2];
				i = m_p2;
				while (i > m_p1)
				{
					pData[i] = pData[i - 1];
					--i;
				}
				pData[m_p1] = m_nData;
			}
			++m_p1;
		}
	}
};