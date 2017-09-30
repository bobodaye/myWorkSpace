#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <stack>

template<typename T>
struct TreeNode {
	T val;
	struct TreeNode<T>* left;
	struct TreeNode<T>* right;

	TreeNode(const T& value, TreeNode<T>* lf = nullptr, TreeNode<T>* rg = nullptr) :
		left(lf), right(rg), val(value) {}
};

class BTree {
public:
	/// \brief   ReBuildBTree ���ݶ�������ǰ����������л�ԭ�ö�����
	/// \param   preOrder ǰ���������
	/// \param   inOrder �����������
	/// \return �������ĸ��ڵ�
	template<typename T>
	static TreeNode<T>* ReBuildBTree(const std::vector<T>& preOrder, const std::vector<T>& inOrder)
	{
		if (0 == preOrder.size() || 0 == inOrder.size() )
			return nullptr;
		int rootIndex = 0;
		return ReBuildBTree(preOrder, inOrder, 0, preOrder.size() - 1, rootIndex);
	}

	/// \brief   InOrderTraverse �������������
	/// \param   root ������������
	/// \return
	template<typename T>
	static void InOrderTraverse(const TreeNode<T>* root)
	{
		if (nullptr != root)
		{
			InOrderTraverse(root->left);
			std::cout << root->val << " ";
			InOrderTraverse(root->right);
		}
	}

	template<typename T>
	static void LevelTraverse(const TreeNode<T>* root)
	{
		if (!root)
			return;
		std::queue<const TreeNode<T>*> assistQueue;
		assistQueue.push(root);
		while (!assistQueue.empty() )
		{
			const TreeNode<T>* front = assistQueue.front();
			assistQueue.pop();
			std::cout << front->val << " ";
			if (front->left)
				assistQueue.push(front->left);
			if (front->right)
				assistQueue.push(front->right);
		}
	}

	/// \brief   IsSubStru ������18�������ӽṹ
	/// \param   m_nRootA ��A�ĸ����
	/// \param   m_nRootB ��B�ĸ����
	/// \return �����B����A���ӽṹ������true�����򣬷���false
	template<typename T>
	static bool IsSubStru(TreeNode<T>* m_pRootA, TreeNode<T>* m_pRootB)
	{
		bool m_nLeftFlag = false, m_nRightFlag = false;
		if (m_pRootA && m_pRootB)
		{
			if (m_pRootA->val != m_pRootB->val)
			{
				m_nLeftFlag = IsSubStru(m_pRootA->left, m_pRootB);
				if (!m_nLeftFlag)	//�����������������B��������������
					m_nRightFlag = IsSubStru(m_pRootA->right, m_pRootB);
			}
			else
			{
				m_nLeftFlag = IsSubStru(m_pRootA->left, m_pRootB->left);
				m_nRightFlag = IsSubStru(m_pRootA->right, m_pRootB->right);
				return (m_nLeftFlag && m_nRightFlag);
			}
		}
		else if (!m_pRootA && m_pRootB)
			return false;
		else
			return true;
		return (m_nLeftFlag || m_nRightFlag);
	}

	/// \brief   MirrorImage ������19:�������ľ���
	/// \param   m_pRoot �������ĸ����
	/// \return
	template<typename T>
	static void MirrorTransfer(TreeNode<T>* m_pRoot)
	{
		if (m_pRoot)
		{
			MirrorTransfer(m_pRoot->left);
			MirrorTransfer(m_pRoot->right);
			if (!m_pRoot->left && !m_pRoot->right)
				return;
			//����Ƿ�Ҷ�ڵ㣬�򽻻���������
			TreeNode<T>* tmp = m_pRoot->right;
			m_pRoot->right = m_pRoot->left;
			m_pRoot->left = tmp;
		}
	}

	static std::vector<std::vector<int> > FindPath(TreeNode<int>* root, int expectNumber) {
        std::vector<std::vector<int> > allPaths;
        std::vector<int> tmpPath;
        std::stack<TreeNode<int>* > assistStack;
		std::stack<TreeNode<int>* > subRootStack;

        TreeNode<int>* p = root;
		TreeNode<int>* subRoot = nullptr;
		int m_nValue = 0;

        while(!assistStack.empty() || p)
        {
            while(p)
            {
                assistStack.push(p);
                m_nValue += p->val;
                tmpPath.push_back(p->val);
                if(m_nValue == expectNumber && !p->left && !p->right)
                {
                    allPaths.push_back(tmpPath);
                }
                p = p->left;
            }
            if(!assistStack.empty())
            {
				p = assistStack.top();
				assistStack.pop();
				
				subRootStack.push(p);	//�����ĸ��ݴ浽subRootStack��
            }
			if (!(p->right))
			{
				do
				{
					p = subRootStack.top();
					m_nValue -= p->val;
					subRootStack.pop();
					tmpPath.pop_back();
				} while (!subRootStack.empty() && subRootStack.top()->right == p);
			}
            p = p->right;
        }
        return allPaths;
    }
	
	template<typename T>
	static TreeNode<T>* Convert(TreeNode<T>* root)
	{
		if (!root)
			return nullptr;
		TreeNode<T>* headNode = nullptr;
		ConvertNode(root, headNode);
		while(headNode && headNode->left)
			headNode = headNode->left;
		return headNode;
	}

private:
	template<typename T>
	static TreeNode<T>* ReBuildBTree(const std::vector<T>& preOrder, const std::vector<T>& inOrder, int left, int right, int& rootIndex)
	{
		TreeNode<T>* newNode = nullptr;
		int i;
		for (i = left; i <= right; i++)
		{
			if (preOrder[rootIndex] == inOrder[i])
			{
				newNode = new TreeNode<T>(preOrder[rootIndex++]);
				newNode->left = ReBuildBTree(preOrder, inOrder, left, i - 1, rootIndex);
				newNode->right = ReBuildBTree(preOrder, inOrder, i + 1, right, rootIndex);
				return newNode;
			}
		}
		return newNode;
	}

	template<typename T>
	static void ConvertNode(TreeNode<T>* root, TreeNode<T>*& pLastNodeInList)
	{
		if(!root)
			return;
		if(root->left)
			ConvertNode(root->left, pLastNodeInList);
		root->left = pLastNodeInList;
		if(pLastNodeInList)
			pLastNodeInList->right = root;
		pLastNodeInList = root;
		if(root->right)
			ConvertNode(root->right, pLastNodeInList);
	}
};