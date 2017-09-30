//�����ݽṹ���в����ľ����㷨
#include "ConcreteVisitor1.h"
#include "ConcreteVisitor2.h"
//---------------------------
#include "ObjectStructure.h"

#include "ConcreteElementA.h"
#include "ConcreteElementB.h"

int main()
{
	//��������ݽṹ,һ���ȶ����ױ仯
	ConcreteElementA concreteElementA;
	ConcreteElementB concreteElementB;

	ObjectStructure objectStructure;
	objectStructure.Attach(&concreteElementA);
	objectStructure.Attach(&concreteElementB);

	//objectStructure.Detach(&concreteElementA);

	//����Ĳ����ߣ������������Ӻ�ɾ��
	ConcreteVisitor1 concreteVisitor1;
	ConcreteVisitor2 concreteVisitor2;

	objectStructure.Accept(&concreteVisitor1);
	objectStructure.Accept(&concreteVisitor2);

	return 0;
}