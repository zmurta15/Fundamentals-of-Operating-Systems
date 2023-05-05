#include <math.h>

int BypassMySin= 1;

double mySin(double a) {
	if (BypassMySin)
		return 0.0;
	else
		return sin(a);
}
