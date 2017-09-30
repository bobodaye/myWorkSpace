#include <iostream>
#include "StackImpQueue.h"

int main()
{
	CQueue<int> q;
	q.appendTail(1);
	q.appendTail(2);

	std::cout << q.deleteHead() << std::endl;
	std::cout << q.deleteHead() << std::endl;
	std::cout << q.deleteHead() << std::endl;

	return 0;
}