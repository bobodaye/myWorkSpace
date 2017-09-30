#include "IsBSTreePostOrder.h"

int main()
{
	std::vector<int> postOrder1 = { 5, 7, 6, 9, 11, 10, 8 };
	std::vector<int> postOrder2 = { 7, 4, 6, 5 };
	std::vector<int> postOrder3 = { 0, 7, 5, 4 };

	//bool flag = BSTree::IsBSTreePostOrder(postOrder1);
	//flag = BSTree::IsBSTreePostOrder(postOrder2);
	bool flag = BSTree::IsBSTreePostOrder(postOrder3);


	return 0;
}