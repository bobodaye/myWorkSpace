#pragma once

#include "Element.h"

class ConcreteElementA : public Element {
public:
	void Accept(Vistior*);
};

/*
	双分派技术：执行的操作决定于访问者的种类和两个接收者的类型
	------------------------------------------------------------
	1.客户端将visitor作为参数传递给ConcreteElementA类完成第一次分派。
	2.visitor调用具体接收者方法，并将自己(this)作为参数传递进去，完成二次分派。

*/
void ConcreteElementA::Accept(Vistior* visitor)
{
	visitor->VisitConcreteElementA(this);
}