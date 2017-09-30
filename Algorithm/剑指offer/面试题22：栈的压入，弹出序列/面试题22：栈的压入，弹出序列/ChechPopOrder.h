#pragma once

#include <vector>
#include <stack>

class ChechPopOrder {
public:
	/// \brief   IsPopOrder 检查栈的压入序列seqPush是否可以构成弹出序列seqPop
	/// \param   seqPush 压入序列
	/// \param   seqPop 弹出序列
	/// \return 如果可以，返回true，否则返回false
	template<typename T>
	static bool IsPopOrder(const std::vector<T>& seqPush, const std::vector<T>& seqPop)
	{
		int m_nSeqPushSize = seqPush.size();
		int m_nSeqPopSize = seqPop.size();
		int i, j = 0;
		if (m_nSeqPopSize <= 0 || m_nSeqPushSize <= 0 || m_nSeqPushSize != m_nSeqPopSize )
			return false;
		std::stack<T> assistStack;
		for (i = 0; i < m_nSeqPushSize; ++i)
		{
			assistStack.push(seqPush[i]);
			while (assistStack.size() > 0 && assistStack.top() == seqPop[j])
			{
				assistStack.pop();
				++j;
			}
		}
		return assistStack.size() > 0 ? false : true;
	}
};