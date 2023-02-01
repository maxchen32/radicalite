#include <stdio.h>
#include "fraction.h"

int main() {
	Fraction a = initFrac(-2, 1);
	pprintFrac(powFrac(a, -5));
	
	return 0;
}
