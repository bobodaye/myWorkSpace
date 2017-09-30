#pragma once

#include <queue>
#include <cassert>

template<typename T> class CStack {
public:
	CStack() {}
	~CStack() {}

	void push(const T& node)
	{
		queue1.push(node);
	}

	T pop()
	{
		assert(0 < queue1.size() || 0 < queue2.size() );
		T headNode = T();
		if (0 >= queue1.size() )
		{
			while (1 != queue2.size() )
			{
				queue1.push(queue2.front() );
				queue2.pop();
			}
			headNode = queue2.front();
			queue2.pop();
		}
		else 
		{
			while (1 != queue1.size() )
			{
				queue2.push(queue1.front() );
				queue1.pop();
			}
			headNode = queue1.front();
			queue1.pop();
		}

		return headNode;
	}

private:
	std::queue<T> queue1;
	std::queue<T> queue2;
};