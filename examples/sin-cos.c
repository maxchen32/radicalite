#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include "radical.h"

int main() {
	setlocale(LC_ALL, "chs");
    printf("          _\n");
    wprintf(L"输入a/b*√c中的三个参数：\n");
    fflush(stdout);
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    Polynomial list = initPoly();
    list = addRad(list, Radsqrt(1));    
    Radical sin = initRad(a, b, c);
    //printRad(sin);puts("");
    list = subRad(list, mulRad(sin, sin));
    Node *tmpout = findkthPoly(1, list);
    if (tmpout == NULL) {
        puts("Out of domain of definition.");
        exit(EDOM);
    }
    Radical tmp = sqrtFrac(tmpout->num.out);
    list = deletePoly(1, list);
    list = addRad(list, tmp);
    printPoly(list); puts("");
    
    destoryPoly(&list);
    return 0;
}
