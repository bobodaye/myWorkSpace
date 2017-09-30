#pragma once

#include <iostream>
#include "Visitor.h"

class ConcreteVisitor1 : public Vistior {
public:
	void VisitConcreteElementA(ConcreteElementA*);
	void VisitConcreteElementB(ConcreteElementB*);
};

/*
	�򵥵�Demo���������£�
	1.��ӡ����������
	2.��ӡ����Ԫ��
*/
void ConcreteVisitor1::VisitConcreteElementA(ConcreteElementA* concreteElementA)
{
	std::cout << "\"" << typeid(*this).name() << "\":" << typeid(*concreteElementA).name() << std::endl;
}

void ConcreteVisitor1::VisitConcreteElementB(ConcreteElementB* concreteElementB)
{
	std::cout << "\"" << typeid(*this).name() << "\":" << typeid(*concreteElementB).name() << std::endl;
}