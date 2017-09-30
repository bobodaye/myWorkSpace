#pragma once

#include <vector>
#include <stack>

class ChechPopOrder {
public:
	/// \brief   IsPopOrder ���ջ��ѹ������seqPush�Ƿ���Թ��ɵ�������seqPop
	/// \param   seqPush ѹ������
	/// \param   seqPop ��������
	/// \return ������ԣ�����true�����򷵻�false
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