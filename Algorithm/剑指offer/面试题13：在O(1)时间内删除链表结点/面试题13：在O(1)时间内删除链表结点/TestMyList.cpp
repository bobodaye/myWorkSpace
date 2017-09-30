#include <iostream>
#include "MyList.h"

int main()
{
	MyList<int> m_nList1;

	m_nList1.InsertNode(1);
	m_nList1.InsertNode(3);
	m_nList1.InsertNode(5);
	m_nList1.InsertNode(7);

	MyList<int> m_nList2;

	m_nList2.InsertNode(2);
	m_nList2.InsertNode(4);
	m_nList2.InsertNode(6);
	m_nList2.InsertNode(8);
	m_nList2.InsertNode(10);

	//ListNode<int>* m_pMergedList = MergeTwoListRec(m_nList1, m_nList2);
	ListNode<int>* m_pMergedList = MergeTwoList(m_nList1, m_nList2);

	return 0;
}