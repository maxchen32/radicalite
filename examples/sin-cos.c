#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include "radical.h"

int main() {
	setlocale(LC_ALL, "chs");
#ifdef _WIN32
    putchar(' ');
#endif
	printf("         _\n");
    wprintf(L"输入a/b*√c中的三个参数：\n");
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
