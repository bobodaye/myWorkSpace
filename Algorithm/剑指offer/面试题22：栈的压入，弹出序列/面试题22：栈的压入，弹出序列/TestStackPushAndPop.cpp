#include "ChechPopOrder.h"

int main()
{
	std::vector<int> seqPush = { 1, 2, 3, 4, 5 };

	std::vector<int> seqPop1 = { 4, 3, 5, 1, 2 };
	std::vector<int> seqPop2 = { 2, 3, 1, 5, 4 };


	bool flag = ChechPopOrder::IsPopOrder(seqPush, seqPop1);
	flag = ChechPopOrder::IsPopOrder(seqPush, seqPop2);

	return 0;
}