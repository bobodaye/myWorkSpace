#pragma once

#include <iostream>
#include "Visitor.h"

class ConcreteVisitor2 : public Vistior {
public:
	void VisitConcreteElementA(ConcreteElementA*);
	void VisitConcreteElementB(ConcreteElementB*);
};

void ConcreteVisitor2::VisitConcreteElementA(ConcreteElementA* concreteElementA)
{
	std::cout << "\"" << typeid(*this).name() << "\":" << typeid(*concreteElementA).name() << std::endl;
}

void ConcreteVisitor2::VisitConcreteElementB(ConcreteElementB* concreteElementB)
{
	std::cout << "\"" << typeid(*this).name() << "\":" << typeid(*concreteElementB).name() << std::endl;
}