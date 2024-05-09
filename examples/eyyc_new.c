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

void eyyc(int a, int b, int c){	                                          // ax^2+bx+c=0
	int delta = b * b - 4 * a * c;	                                      // 计算判别式Δ

	if (delta >= 0){                                                      // Δ >= 0，有解
		Radical sqrtDelta = Radsqrt(delta);                               // sqrtDelta: √Δ
		Radical bRad = int2Rad(-b);                                       // 把 -b 转换成二次根式 (-b/1)sqrt(1)

		Polynomial list = initPoly();                                     // 初始化一个算式
		list = divintPoly(addRad(addRad(list, bRad), sqrtDelta), 2 * a);  // (-b + √Δ) / (2 * a)
		printPoly(list);                                                  // 输出结果
		destoryPoly(list);                                                // 销毁算式
	
		if (delta) {                                                         // Δ > 0，有两解
			printf("\nOR\n");
			
			list = initPoly();                                               // 初始化一个算式
			list = divintPoly(subRad(addRad(list, bRad), sqrtDelta), 2 * a); // (-b - √Δ) / (2 * a)
			printPoly(list);                                                 // 输出结果
			destoryPoly(list);                                               // 销毁算式
		}
	} else {                                                              // Δ < 0，无解
		printf("delta = %d < 0, no root.\n", delta);
	}	
}
