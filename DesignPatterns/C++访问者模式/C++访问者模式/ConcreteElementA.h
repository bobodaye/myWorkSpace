#pragma once

#include "Element.h"

class ConcreteElementA : public Element {
public:
	void Accept(Vistior*);
};

/*
	˫���ɼ�����ִ�еĲ��������ڷ����ߵ���������������ߵ�����
	------------------------------------------------------------
	1.�ͻ��˽�visitor��Ϊ�������ݸ�ConcreteElementA����ɵ�һ�η��ɡ�
	2.visitor���þ�������߷����������Լ�(this)��Ϊ�������ݽ�ȥ����ɶ��η��ɡ�

*/
void ConcreteElementA::Accept(Vistior* visitor)
{
	visitor->VisitConcreteElementA(this);
}