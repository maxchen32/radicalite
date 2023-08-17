#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "radical.h"

int main() {
    puts("Please input the 3 arguments of (a/b)sqrt(c)");
    fflush(stdout);
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
	if (!b || !c) {
		puts("No zero on denominator or in radical");
		exit(1);
	}
    Radical sin = initRad(a, b, c);
	if (sqrt(sin.in) * abs(sin.out.up) > sin.out.down) {
		puts("The range of values of sin is [-1, 1]");
		exit(1);
	}
	Polynomial list = initPoly();
    list = addRad(list, initRad(1, 1, 1));
    list = subRad(list, mulRad(sin, sin));
    Node *tmpout = findkthPoly(1, list);
    if (tmpout == NULL) {
        puts("0");
        return 0;
    }
    Radical tmp = sqrtFrac(tmpout->num.out);
    list = deletePoly(1, list);
    list = addRad(list, tmp);
	printRad(list->next->num);puts("");
    //printPoly(list); puts("");
    
    destoryPoly(list);
    return 0;
}
