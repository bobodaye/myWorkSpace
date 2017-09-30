#include "StackContainsMinFunc.h"

int main()
{
	StackContainsMinFunc<int> myStack;

	myStack.push(7);
	myStack.push(5);
	myStack.push(11);
	myStack.push(3);

	int m_nStackTopValue = myStack.pop();

	int m_nMinValue = myStack.min();


	return 0;
}