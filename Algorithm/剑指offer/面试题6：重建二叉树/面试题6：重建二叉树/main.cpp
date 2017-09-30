#pragma once

#include "BTree.h"

int main()
{
	//树A
	std::vector<char> preOrderA = { 'A', 'B', 'D', 'H', 'E', 'C', 'F', 'G' };
	std::vector<char> inOrderA = { 'H', 'D', 'B', 'E', 'A', 'F', 'C', 'G' };

	TreeNode<char>* rootA = BTree::ReBuildBTree(preOrderA, inOrderA);

	//树B
	std::vector<int> preOrderB = { 6, 4, 5, 7 };
	std::vector<int> inOrderB = { 4, 5, 6, 7 };

	TreeNode<int>* rootB = BTree::ReBuildBTree(preOrderB, inOrderB);

	//bool flag = BTree<char>::IsSubStru(rootA, rootB);
	BTree::LevelTraverse(rootA);
	//BTree::MirrorTransfer(rootA);
	//BTree::InOrderTraverse(rootA);
	TreeNode<int>* headNode = BTree::Convert(rootB);

	return 0;
}

int main3()
{
	std::vector<int> pre = { 7, 8, 9 };
	std::vector<int> in = { 7, 8, 9 };

	TreeNode<int>* root = BTree::ReBuildBTree(pre, in);

	std::vector<std::vector<int> > allPaths = BTree::FindPath(root, 15);
	return 0;
}