#pragma once

#include <vector>
#include "Element.h"

class ObjectStructure {
	std::vector<Element*> elements;
public:
	void Attach(Element*);
	void Detach(Element*);
	void Accept(Vistior*);
};

void ObjectStructure::Attach(Element* element)
{
	elements.push_back(element);
}

void ObjectStructure::Detach(Element* element)
{
	std::vector<Element*>::iterator iter = elements.begin();
	while (iter != elements.end()) {
		if (*iter == element)
			break;
		iter++;
	}
	if (iter == elements.end())
		return;
	elements.erase(iter);
}

void ObjectStructure::Accept(Vistior* visitor)
{
	std::vector<Element*>::iterator iter = elements.begin();
	while (iter != elements.end()) {
		(*iter++)->Accept(visitor);
	}
}