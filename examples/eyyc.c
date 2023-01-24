#include <stdio.h>
#include <stdlib.h>

#include "radical.h"

void eyyc(int a, int b, int c);
int main(int argc, char * argv[]) {
    if (argc == 3+1){
        eyyc(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
    }
    else {
        printf("Usage: eyyc num1 num2 num3\nfor ax^2 + bx + c = 0\n");
    }
    return 0;
}

void eyyc(int a, int b, int c){     //0=ax^2+bx+c
    Polynomial list = initPoly();
    Polynomial list2 = initPoly();
    int delta = b * b - 4 * a * c;
    if (delta >= 0){
        Radical nb = initRad(-b, 1, 1);
        list = addRad(addRad(list, nb), Radsqrt(delta));
        int da = 2 * a;
        _PolyIntReduce(list, &da);
        printPoly(list);
        printf("\n");
        if (da != 1 && da != 0){
	    printf("----------\n");
            printf("%d\n",da);
	}
    	destoryPoly(&list);
	printf("\nor\n\n");
        
	da = 2 * a;
        list2 = subRad(addRad(list2, nb), Radsqrt(delta));
        _PolyIntReduce(list2, &da);
        printPoly(list2);
        printf("\n");
        if (da != 1 && da != 0){
	    printf("----------\n");
            printf("%d\n",da);
	}
    }
    else {
        printf("delta = %d < 0\n",delta);
    }

    destoryPoly(&list2);
}
