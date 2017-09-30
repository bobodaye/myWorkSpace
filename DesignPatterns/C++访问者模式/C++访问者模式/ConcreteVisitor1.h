#pragma once

#include <iostream>
#include "Visitor.h"

class ConcreteVisitor1 : public Vistior {
public:
	void VisitConcreteElementA(ConcreteElementA*);
	void VisitConcreteElementB(ConcreteElementB*);
};

/*
	简单的Demo，作用如下：
	1.打印访问者类型
	2.打印访问元素
*/
void ConcreteVisitor1::VisitConcreteElementA(ConcreteElementA* concreteElementA)
{
	std::cout << "\"" << typeid(*this).name() << "\":" << typeid(*concreteElementA).name() << std::endl;
}

void ConcreteVisitor1::VisitConcreteElementB(ConcreteElementB* concreteElementB)
{
	std::cout << "\"" << typeid(*this).name() << "\":" << typeid(*concreteElementB).name() << std::endl;
}