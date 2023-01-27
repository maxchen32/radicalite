#include <stdio.h>
#include <stdlib.h>

#include "radical.h"

void eyyc(int a, int b, int c);
int main(int argc, char * argv[]) {
	if (argc == 3+1){
		eyyc(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
	}
	else {
		printf("Usage: eyyc a b c\nfor a*x^2 + b*x + c = 0\n");
	}
	return 0;
}

void eyyc(int a, int b, int c){	 //0=ax^2+bx+c
	Polynomial list = initPoly();
	Polynomial list2 = initPoly();
	int delta = b * b - 4 * a * c;
	if (delta >= 0){
		Radical rb = initRad(-b, 1, 1);
		list = addRad(addRad(list, rb), Radsqrt(delta));
		divintPoly(list, 2 * a);
		printPoly(list);
		destoryPoly(list);
		
		printf("\nor\n");
		
		list2 = subRad(addRad(list2, rb), Radsqrt(delta));
		divintPoly(list2, 2 * a);
		printPoly(list2);
		destoryPoly(list2);
	}
	else {
		printf("delta = %d < 0\n",delta);
	}	
}
