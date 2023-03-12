#include <stdio.h>
#include <math.h>
#include "radical.h"

int main() {
	/*
	Radical a = initRad(-1, 2, 1);
	printRad(a);
	putchar('\n');
	printf("toStrRad: %s\n", toStrRad(a).s);
	Fraction b = initFrac(-1, 114514);
	pprintFrac(b);
	putchar('\n');
	printf("toStrFrac: %s\n", toStrFrac(b).s);
	printf("%d %d\n", b.up, b.down);
	*/
	/*
	char buffer[13];
	snprintf(buffer, 13,"lalalala");
	printf("%s\n", buffer);
	snprintf(buffer + strlen(buffer), 13-strlen(buffer),"hahahaha");
	printf("%s\n", buffer);
	*/
	Radical a = {{1,1}, 1};
	_Bool f = printRad(a);
	putchar('\n');
	printf("f: %d\n", f);
	int n = -1234;
	printf("len_n: %d\n", num_len_frac(n));
	return 0;
}
