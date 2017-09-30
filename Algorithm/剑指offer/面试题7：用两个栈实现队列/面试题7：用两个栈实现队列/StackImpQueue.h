#pragma once

#include <stack>

template<typename T> class CQueue {
public:
	CQueue() {}
	~CQueue() {}

	void appendTail(const T& node)
	{
		stack1.push(node);
	}

	T deleteHead()
	{
		if (0 == stack2.size() )
		{
			while (0 != stack1.size() )
			{
				stack2.push(stack1.top() );
				stack1.pop();
			}
		}
		if (0 == stack2.size() )
			throw new std::exception("queue is empty");

		T headNode = stack2.top();
		stack2.pop();

		return headNode;
	}

private:
	std::stack<T> stack1;
	std::stack<T> stack2;
};