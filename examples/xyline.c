#include <stdio.h>
#include <math.h>
#include "radical.h"

typedef enum {
	OK,
	NOROOT,
	INFROOT
}Status;
Status xyline(Fraction* res, Fraction a, Fraction b, Fraction m, 
  Fraction c, Fraction d, Fraction n) {
	Fraction h1 = subFrac(mulFrac(a, d), mulFrac(b, c));
	Fraction t1 = subFrac(mulFrac(d, m), mulFrac(b, n));
	Fraction t2 = subFrac(mulFrac(a, n), mulFrac(c, m));

	if (h1.up == 0 && t1.up != 0) {
		return NOROOT;
	} else if(h1.up != 0 && t2.up == 0) {
		return INFROOT;
	} else {
		res[0] = divFrac(t1, h1);
		res[1] = divFrac(t2, h1);
		return OK;
	}
}
int main(){
	Fraction result[2];
	int a, b, c, d, e, f;
	scanf("%d%d%d%d%d%d", &a, &b, &c, &d, &e, &f);
	Status sta = xyline(result, initFrac(a,1), initFrac(b,1), initFrac(c,1), 
	  initFrac(d,1), initFrac(e,1), initFrac(f,1));
	if (sta == OK) {
		puts("----results:----");
		puts("x:");
		printFrac(result[0]);
		puts("\ny:");
		printFrac(result[1]);
	} else if (sta == NOROOT) {
		printf("No Root\n");
	} else {
		printf("Inf Root\n");
	}
	return 0;
}
