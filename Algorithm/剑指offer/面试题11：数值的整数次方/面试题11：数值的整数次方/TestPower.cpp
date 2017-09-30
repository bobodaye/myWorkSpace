#include "Power.h"

int main()
{
	double d1 = PowerClass::Power(2.0, -2);
	double d2 = PowerClass::Power(2.0, 0);
	double d3 = PowerClass::Power(0, -2);
	double d4 = PowerClass::Power(0, 0);
	double d5 = PowerClass::Power(2, 10);

	return 0;
}