#pragma once

template<typename T> struct ListNode
{
	T _value;
	struct ListNode<T>* _next;
	ListNode(const T& value = T(), ListNode<T>* next = nullptr)
		: _value(value), _next(next) {}
};

template<typename T> class MyList;
template<typename T> ListNode<T>* MergeTwoList(MyList<T>& m_nList1, MyList<T>& m_nList2);
template<typename T> ListNode<T>* MergeTwoListRec(MyList<T>& m_nList1, MyList<T>& m_nList2);

template<typename T> class MyList {
public:
	void InsertNode(const T& value)
	{
		return InsertNode(m_pHeadNode, value);
	}

	ListNode<T>* FindBack(int k)
	{
		return FindBack(m_pHeadNode, k);
	}

	void DeleteNode(ListNode<T>* pToBeDeleted)
	{
		return DeleteNode(m_pHeadNode, pToBeDeleted);
	}

	void Reverse()
	{
		m_pHeadNode = Reverse(m_pHeadNode);
	}
	
	friend ListNode<T>* MergeTwoList(MyList<T>& m_nList1, MyList<T>& m_nList2)
	{
		return MyList<T>::MergeTwoList(m_nList1.m_pHeadNode, m_nList2.m_pHeadNode);
	}
	
	friend ListNode<T>* MergeTwoListRec(MyList<T>& m_nList1, MyList<T>& m_nList2)
	{
		return MyList<T>::MergeTwoListRec(m_nList1.m_pHeadNode, m_nList2.m_pHeadNode);
	}
private:
	/// \brief   InsertNode 向链表中插入结点
	/// \param   headNode 链表头结点
	/// \param   value 待插入的值
	/// \return
	void InsertNode(ListNode<T>*& headNode, const T& value)
	{
		ListNode<T>* preceding = nullptr;
		ListNode<T>* following = headNode;

		while (following && value > following->_value)
		{
			preceding = following;
			following = following->_next;
		}
		ListNode<T>* newNode = new ListNode<T>(value, following);
		if (!newNode)
			return;

		if (preceding)
			preceding->_next = newNode;
		else
			headNode = newNode;
		++m_nSize;
	}
	
	/// \brief   DeleteNode 在O(1)时间内删除链表中给定的结点
	/// \param   headNode 链表头结点
	/// \param   pToBeDeleted 待删除的结点（前提：保证存在于链表中）
	/// \return
	void DeleteNode(ListNode<T>*& headNode, ListNode<T>* pToBeDeleted)
	{
		if(!headNode && !pToBeDeleted)
			return;

		if(pToBeDeleted->_next)
		{
			ListNode<T>* pNext = pToBeDeleted->_next;
			pToBeDeleted->_value = pNext->_value;
			pToBeDeleted->_next = pNext->_next;

			delete pNext;
			pNext = nullptr;
		}
		else if(headNode == pToBeDeleted)
		{
			delete pToBeDeleted;
			pToBeDeleted = nullptr;
			headNode = nullptr;
		}
		else
		{
			ListNode<T>* p = headNode;
			while (p->_next != pToBeDeleted)
				p = p->_next;
			p->_next = nullptr;

			delete pToBeDeleted;
			pToBeDeleted = nullptr;
		}
		--m_nSize;
	}

	/// \brief   FindBack 面试题14：链表中倒数第k个结点
	/// \param   headNode 链表头结点
	/// \param   k 倒数的顺序
	/// \return 链表倒数第k个结点，不存在则返回nullptr
	ListNode<T>* FindBack(ListNode<T>*& headNode, int k)
	{
		if (!headNode || 0 >= k)
			return nullptr;
		int i = 0;
		ListNode<T>* m_p1, *m_p2;
		m_p2 = headNode;
		
		while (m_p2 && i < k - 1)
		{
			m_p2 = m_p2->_next;
			++i;
		}
		if (!m_p2)	//如果链表结点个数小于k，则返回nullptr
			return nullptr;
		m_p1 = headNode;
		while (m_p2->_next)
		{
			m_p2 = m_p2->_next;
			m_p1 = m_p1->_next;
		}
		return m_p1;
	}

	/// \brief   Reverse 翻转链表
	/// \param   headNode 链表原来的头结点
	/// \return 翻转后的头结点
	ListNode<T>* Reverse(ListNode<T>* headNode)
	{
		ListNode<T>* m_pNewHead = nullptr;
		if (headNode && headNode->_next)
		{
			m_pNewHead = Reverse(headNode->_next);
			headNode->_next->_next = headNode;
			headNode->_next = nullptr;
			return m_pNewHead;
		}
		else
		{
			return headNode;
		}
	}

	/// \brief   MergeTwoList 面试题17：合并两个有序单链表（迭代版本）
	/// \param   pHead1 链表1的头结点
	/// \param   pHead2 链表2的头结点
	/// \return 合并后链表的头结点
	static ListNode<T>* MergeTwoList(ListNode<T>* pHead1, ListNode<T>* pHead2)
	{
		if (!pHead1)
			return pHead2;
		if (!pHead2)
			return pHead1;
		ListNode<T>* m_pMergedHead = nullptr;
		ListNode<T>* m_pEnd = nullptr;

		while (pHead1 && pHead2)
		{
			if (pHead1->_value < pHead2->_value)
			{
				if (!m_pMergedHead)
					m_pEnd = m_pMergedHead = pHead1;
				else
				{
					m_pEnd->_next = pHead1;
					m_pEnd = m_pEnd->_next;
				}
				pHead1 = pHead1->_next;
			}
			else
			{
				if (!m_pMergedHead)
					m_pEnd = m_pMergedHead = pHead2;
				else
				{
					m_pEnd->_next = pHead2;
					m_pEnd = m_pEnd->_next;
				}
				pHead2 = pHead2->_next;
			}
		}
		if (pHead1)
			m_pEnd->_next = pHead1;
		if (pHead2)
			m_pEnd->_next = pHead2;
		return m_pMergedHead;
	}

	/// \brief   MergeTwoListRec 面试题17：合并两个排序的链表（递归版本）
	/// \param   pHead1 链表1的头结点
	/// \param   pHead2 链表2的头结点
	/// \return 合并后链表的头结点
	static ListNode<T>* MergeTwoListRec(ListNode<T>* pHead1, ListNode<T>* pHead2)
	{
		if (!pHead1)
			return pHead2;
		else if (!pHead2)
			return pHead1;
		ListNode<T>* m_pMergedHead = nullptr;

		if (pHead1->_value < pHead2->_value)
		{
			m_pMergedHead = pHead1;
			m_pMergedHead->_next = MergeTwoListRec(pHead1->_next, pHead2);
		}
		else
		{
			m_pMergedHead = pHead2;
			m_pMergedHead->_next = MergeTwoListRec(pHead1, pHead2->_next);
		}
		return m_pMergedHead;
	}
private:
	ListNode<T>* m_pHeadNode = nullptr;
	size_t m_nSize = 0;
};