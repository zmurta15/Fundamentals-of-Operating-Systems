#include <stdio.h>


int main(int argc, char *argv[]) {
	double arr[100];
	double max = 0;
	int j = 0;
	for(int i=0; i<100; i++) {
		j = i+1;
		double result1 = arr[i]- arr[j];
		double result2 = result1/ arr[j];
		if(result2 >= max){
			max = result2;
		}
	}
	return 0;
}
