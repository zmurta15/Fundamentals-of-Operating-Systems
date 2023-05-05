#include <stdio.h>

int BypassMySin = 1;

double mySin(double a);

int main(int argc, char *argv[]) {
	printf("And my number is... %f\n", mySin(3.14159/4));
	BypassMySin= 0;
	printf("And my number is... %f\n", mySin(3.14159/4));

	return 0;
}
