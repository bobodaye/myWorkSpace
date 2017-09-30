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
	/// \brief   ReBuildBTree 根据二叉树的前序和中序序列还原该二叉树
	/// \param   preOrder 前序遍历序列
	/// \param   inOrder 中序遍历序列
	/// \return 二叉树的根节点
	template<typename T>
	static TreeNode<T>* ReBuildBTree(const std::vector<T>& preOrder, const std::vector<T>& inOrder)
	{
		if (0 == preOrder.size() || 0 == inOrder.size() )
			return nullptr;
		int rootIndex = 0;
		return ReBuildBTree(preOrder, inOrder, 0, preOrder.size() - 1, rootIndex);
	}

	/// \brief   InOrderTraverse 中序遍历二叉树
	/// \param   root 二叉树的树根
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

	/// \brief   IsSubStru 面试题18：树的子结构
	/// \param   m_nRootA 树A的根结点
	/// \param   m_nRootB 树B的根结点
	/// \return 如果树B是树A的子结构，返回true，否则，返回false
	template<typename T>
	static bool IsSubStru(TreeNode<T>* m_pRootA, TreeNode<T>* m_pRootB)
	{
		bool m_nLeftFlag = false, m_nRightFlag = false;
		if (m_pRootA && m_pRootB)
		{
			if (m_pRootA->val != m_pRootB->val)
			{
				m_nLeftFlag = IsSubStru(m_pRootA->left, m_pRootB);
				if (!m_nLeftFlag)	//如果左子树不包含树B，再搜索右子树
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

	/// \brief   MirrorImage 面试题19:二叉树的镜像
	/// \param   m_pRoot 二叉树的根结点
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
			//如果是非叶节点，则交换左右子树
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
				
				subRootStack.push(p);	//子树的根暂存到subRootStack中
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