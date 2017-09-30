#pragma once

class ConcreteElementA;
class ConcreteElementB;

class Vistior {
public:
	virtual void VisitConcreteElementA(ConcreteElementA*) = 0;
	virtual void VisitConcreteElementB(ConcreteElementB*) = 0;
};