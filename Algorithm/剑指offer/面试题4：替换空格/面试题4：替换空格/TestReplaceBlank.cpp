#include "ReplaceBlank.h"
#include <iostream>

int main()
{
	char str[20] = "    b";

	ReplaceBlank::Replace(str, sizeof(str) );
	std::cout << str << std::endl;
	
	return 0;
}