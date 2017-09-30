#pragma once

#include <vector>

struct RandomListNode {
	int				label;
	RandomListNode* next;
	RandomListNode* random;
	RandomListNode(int val, RandomListNode* next = nullptr, RandomListNode* sibling = nullptr)
		: label(val), next(next), random(sibling) {}
};

class Solution {
public:
	RandomListNode* Clone(RandomListNode* pHead)
	{
		if (!pHead)
			return pHead;
		RandomListNode* m_pNewHead = CloneWithoutSibling(pHead);
		m_pNewHead = Clone(m_pNewHead, CalcSiblingPos(pHead));
		return m_pNewHead;
	}
private:
	RandomListNode* CloneWithoutSibling(RandomListNode* pHead)
	{
		if (!pHead)
			return pHead;
		RandomListNode* p_NewHead = nullptr;
		RandomListNode* p = nullptr;

		while (pHead)
		{
			if (!p_NewHead)
				p_NewHead = p = new RandomListNode(pHead->label);
			else
			{
				p->next = new RandomListNode(pHead->label);
				p = p->next;
			}
			pHead = pHead->next;
		}
		return p_NewHead;
	}

	/// \brief   CalcSiblingPos 计算复杂链表中每个结点的m_pSibling在链表中的位置
	/// \param   pHead 复杂链表的头结点
	/// \return
	std::vector<int> CalcSiblingPos(RandomListNode* pOriginalHead)
	{
		std::vector<int> SlibingPos;
		if (!pOriginalHead)
			return SlibingPos;
		RandomListNode* m_p1 = nullptr;
		RandomListNode* m_p2 = nullptr;
		int pos = 0;
		for (m_p1 = pOriginalHead; m_p1; m_p1 = m_p1->next)
		{
			if (m_p1->random)
			{
				m_p2 = pOriginalHead;
				pos = 0;
				while (m_p2 && m_p2 != m_p1->random)
				{
					pos++;
					m_p2 = m_p2->next;
				}
				if (m_p2 == m_p1->random)
					SlibingPos.push_back(pos);
			}
			else
				SlibingPos.push_back(-1);
		}
		return SlibingPos;
	}

	RandomListNode* Clone(RandomListNode* m_pNewHead, const std::vector<int>& siblingPos)
	{
		if (!m_pNewHead)
			return m_pNewHead;
		RandomListNode* m_p1 = nullptr;
		RandomListNode* m_p2 = nullptr;
		int index = 0;	//当前指向结点的索引

		for (m_p1 = m_pNewHead; m_p1; m_p1 = m_p1->next)
		{
			if (-1 != siblingPos[index])
			{
				m_p2 = m_pNewHead;
				for (int j = 0; j < siblingPos[index]; j++)
					m_p2 = m_p2->next;
				m_p1->random = m_p2;
			}
			index++;
		}
		return m_pNewHead;
	}
};