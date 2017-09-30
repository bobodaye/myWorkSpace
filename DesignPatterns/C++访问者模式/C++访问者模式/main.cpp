//在数据结构进行操作的具体算法
#include "ConcreteVisitor1.h"
#include "ConcreteVisitor2.h"
//---------------------------
#include "ObjectStructure.h"

#include "ConcreteElementA.h"
#include "ConcreteElementB.h"

int main()
{
	//具体的数据结构,一般稳定不易变化
	ConcreteElementA concreteElementA;
	ConcreteElementB concreteElementB;

	ObjectStructure objectStructure;
	objectStructure.Attach(&concreteElementA);
	objectStructure.Attach(&concreteElementB);

	//objectStructure.Detach(&concreteElementA);

	//具体的操作者，可以灵活的增加和删除
	ConcreteVisitor1 concreteVisitor1;
	ConcreteVisitor2 concreteVisitor2;

	objectStructure.Accept(&concreteVisitor1);
	objectStructure.Accept(&concreteVisitor2);

	return 0;
}