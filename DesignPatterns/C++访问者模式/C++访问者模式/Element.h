#pragma once

#include "Visitor.h"

class Element {
public:
	virtual void Accept(Vistior*) = 0;
};