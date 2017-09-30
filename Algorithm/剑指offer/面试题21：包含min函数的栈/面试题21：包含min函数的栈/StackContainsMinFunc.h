#pragma once

#include <stack>
#include <cassert>

template<typename T>
class StackContainsMinFunc {
public:
	void push(const T& value)
	{
		_stack.push(value);
		if (0 >= assistStack.size() || value < assistStack.top())
			assistStack.push(value);
		else
			assistStack.push(assistStack.top());
	}

	T pop()
	{
		assert(_stack.size() > 0);
		T m_nStackTopValue = _stack.top();
		_stack.pop();
		assistStack.pop();
		return m_nStackTopValue;
	}

	T min()
	{
		assert(assistStack.size() > 0);
		return assistStack.top();
	}

private:
	std::stack<T> _stack;
	std::stack<T> assistStack;
};