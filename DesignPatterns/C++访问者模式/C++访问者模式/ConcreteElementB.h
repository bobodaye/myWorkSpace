#pragma once

#include "Element.h"

class ConcreteElementB : public Element {
public:
	void Accept(Vistior*);
};

void ConcreteElementB::Accept(Vistior* visitor)
{
	visitor->VisitConcreteElementB(this);
}