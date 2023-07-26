//Some simple computation of space vectors.
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <wchar.h>
#include <stdarg.h>
#include "radical.h"

#define flush_stdin() {while(getchar()!='\n');}

typedef struct Svector {
	Radical x, y, z;
} Svector;

int scan_rad(int argcnt, ...);

Svector int2Svec(int x, int y, int z) {
	Svector vec = {int2Rad(x), int2Rad(y), int2Rad(z)};
	return vec;
}
Svector Frac2Svec(Fraction x, Fraction y, Fraction z) {
	Svector vec = {Frac2Rad(x), Frac2Rad(y), Frac2Rad(z)};
	return vec;
}

// 内积
Polynomial innerSvec(Svector a, Svector b) {
	//Radical res;
	Polynomial list = initPoly();
	list = addRad(list, mulRad(a.x, b.x));
	list = addRad(list, mulRad(a.y, b.y));
	list = addRad(list, mulRad(a.z, b.z));
	return list;
}

// 取模
Radical normSvec(Svector a) {
	Fraction square_sum = addFrac(addFrac(squareRad(a.x), squareRad(a.y)),
								  squareRad(a.z));
	return sqrtFrac(square_sum);
}

// 角度的cos值
Polynomial cosSvec(Svector a, Svector b) {
	Polynomial mul_res = innerSvec(a, b);
	Radical norms_product = mulRad(normSvec(a), normSvec(b));
	Polynomial ptrl = mul_res;
	if (ptrl) {
		while ((ptrl = ptrl->next)) {
			ptrl->num = divRad(ptrl->num, norms_product);
		}
	}
	return mul_res;
}

// 法向量
Svector normalSvec(Svector a, Svector b) {
	Svector res;
	Polynomial normal_x = initPoly();
	Polynomial normal_y = initPoly();
	Polynomial normal_z = initPoly();
	normal_x = subRad(addRad(normal_x, mulRad(a.y, b.z)), mulRad(a.z, b.y));
	normal_y = subRad(addRad(normal_y, mulRad(a.z, b.x)), mulRad(a.x, b.z));
	normal_z = subRad(addRad(normal_z, mulRad(a.x, b.y)), mulRad(a.y, b.x));
	if (lenPoly(normal_x) == 1 && lenPoly(normal_y) == 1 && lenPoly(normal_z) == 1) {
		res.x = findkthPoly(1, normal_x)->num;
		res.y = findkthPoly(1, normal_y)->num;
		res.z = findkthPoly(1, normal_z)->num;
		int dlcm = lcm_frac(lcm_frac(res.x.out.down, res.y.out.down), res.z.out.down);
		//printf("dlcm: %d\n", dlcm);
		res.x.out.up *= dlcm / res.x.out.down;
		res.y.out.up *= dlcm / res.y.out.down;
		res.z.out.up *= dlcm / res.z.out.down;
		res.x.out.down = res.y.out.down = res.z.out.down = 1;
		destoryPoly(normal_x);
		destoryPoly(normal_y);
		destoryPoly(normal_z);
		return res;
	} else {
		wprintf(L"法向量: ");
		putchar('(');
		printPoly(normal_x); 
		printf(", ");
		printPoly(normal_y);
		printf(", ");
		printPoly(normal_z);
		putchar(')');
		putchar('\n');
		wprintf(L"坐标为多项根式的向量的其他运算尚未实现，退出……\n");
		destoryPoly(normal_x);
		destoryPoly(normal_y);
		destoryPoly(normal_z);
		exit(0);
	}
}


Svector input_Svector() {
	Svector vec;
	//char ch;
	int f;
	do {
		wprintf(L"输入x,y,z坐标，以空格分隔，回车提交（分数：形如 1/2 ；二次根式：形如 1/2sqrt3 或 2sqrt3 或 sqrt3）：\n");
		f = scan_rad(3, &vec.x, &vec.y, &vec.z);
	} while (f != 3);
	
	wprintf(L"读入的向量：(%s, %s, %s)\n", toStrRad(vec.x).s,
			toStrRad(vec.y).s, toStrRad(vec.z).s);
	return vec;
}

void inner_product_calc() {
	Svector num1, num2;
	num1 = input_Svector();
	num2 = input_Svector();
	
	Polynomial mulres = innerSvec(num1, num2);
	wprintf(L"内积：");
	printPoly(mulres);
	destoryPoly(mulres);
	putchar('\n');
}

void norm_calc() {
	Svector num1;
	num1 = input_Svector();
	
	Radical norm1 = normSvec(num1);
	wprintf(L"模长：");
	printRad(norm1);
	putchar('\n');
}

void cos_calc() {
	Svector num1, num2;
	num1 = input_Svector();
	num2 = input_Svector();
	
	Polynomial cosres = cosSvec(num1, num2);
	wprintf(L"角度的cos值：");
	printPoly(cosres);
	destoryPoly(cosres);
	putchar('\n');
}

void normal_calc() {
	Svector num1, num2;
	num1 = input_Svector();
	num2 = input_Svector();
	
	Svector vec = normalSvec(num1, num2);
	wprintf(L"法向量：");
	printf("(%s, %s, %s)\n", toStrRad(vec.x).s,
			toStrRad(vec.y).s, toStrRad(vec.z).s);
}

int scan_rad(int argcnt, ...) {
	va_list p_args;
	va_start(p_args, argcnt);
	int t, u, v;
	//char ch[2];
	char ch;
	char sqrt_sign[5];
	int i;
	Radical* radptr;
	
	for (i = 0; i < argcnt; ++i) {
	ch = t = u = v = 0;
	memset(sqrt_sign, 0, sizeof(sqrt_sign)/sizeof(sqrt_sign[0]));
	radptr = va_arg(p_args, Radical*);
	if (scanf("%d", &t)) {
		//printf("t = %d\n", t);
		//ch[1] = '\0';
		ch = getchar();
		//printf("ch[0] = %c\n", ch[0]);
		if (ch == '/') {
			if (scanf("%d", &u)) {
				//printf("u = %d\n", u);
				sqrt_sign[0] = getchar();
				//printf("sqrt_sign[0] = %c\n", sqrt_sign[0]);
				if (!isspace(sqrt_sign[0])) {
					scanf("%3s", sqrt_sign+1);
					//printf("sqrt_sign = %s\n", sqrt_sign);
					if (!strcmp(sqrt_sign ,"sqrt")) {
						scanf("%d", &v);
						//printf("v = %d\n", v);
						//printf("read: %d%s%d%s%d\n\n", t, ch, u, sqrt_sign, v);
						*radptr = initRad(t, u, v);
					} else {
						fprintf(stderr, "Input Error: Incorrect \"sqrt\" sign, got \"%s\" . Please check your input.\n", sqrt_sign);
						//flush_stdin();
						return i;
					}
				} else {
					//printf("read: %d%s%d\n\n", t, ch, u);
					*radptr = initRad(t, u, 1);
				}
			} else {
				fprintf(stderr, "Input Error: Can't get denominator. Please check your input.\n");
				//flush_stdin();
				return i;
			}
		} else if (isspace(ch)) {
			//printf("read: %d\n\n", t);
			*radptr = initRad(t, 1, 1);
		} else if((scanf("%3s", sqrt_sign+1), sqrt_sign[0] = ch) && !strcmp(sqrt_sign ,"sqrt")) {
			scanf("%d", &v);
			//printf("v = %d\n", v);
			//printf("read: %d%s%d\n\n", t, sqrt_sign, v);
			*radptr = initRad(t, 1, v);
		} else {			
			fprintf(stderr, "Input Error: Incorrect separator. Please check your input.\n");
			//flush_stdin();
			return i;
		}
	} else {
		if (scanf("%4s", sqrt_sign) && !strcmp(sqrt_sign ,"sqrt")) {
			scanf("%d", &v);
			//printf("v = %d\n", v);
			//printf("read: %s%d\n\n", sqrt_sign, v);
			*radptr = initRad(1, 1, v);
		} else {
			fprintf(stderr, "Input Error: Incorrect \"sqrt\" sign, got \"%s\". Please check your input.\n", sqrt_sign);
			//flush_stdin();
			return i;
		}
	}
	}
	return i;
}

// 示例
int main() {
	setlocale(LC_ALL, "");

choose_mode:
	wprintf(L"1. 内积\n");
	wprintf(L"2. 取模\n");
	wprintf(L"3. 角度的cos值\n");
	wprintf(L"4. 法向量\n");
	wprintf(L"请选择模式：[1,2,3,4] ");
	char op;
	scanf("%c", &op);
	
	flush_stdin();
	
	if (op == '1') {
		inner_product_calc();
	} else if (op == '2') {
		norm_calc();
	} else if (op == '3') {
		cos_calc();
	} else if (op == '4') {
		normal_calc();
	} else if (op == 'q' || op == 'Q') {
		exit(0);
	}else {
		goto choose_mode;
	}
	
	flush_stdin();
	wprintf(L"\n按下回车开始下一次计算: ");
	char if_next = getchar();
	if (if_next == '\n') {
		goto choose_mode;
	}
	
	return 0;
}
