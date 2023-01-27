#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <errno.h>
#include "fraction.h"

static void error_print_frac
(const char* error_function, const char* error_content) {
	fprintf(stderr, "Error: Fraction: %s: %s\n", 
			error_function, error_content);
}

//math
/*
int gcd_frac(int a, int b){
	if (0 == a || 0 == b){
		return 1;
	}
	int tmp;
	while ((tmp = a % b)){
		a = b;
		b = tmp;
	}
	return b > 0 ? b : -b;
}

long long lgcd_frac(long long a, long long b){
	if (0 == a || 0 == b){
		return 1;
	}
	long long tmp;
	while ((tmp = a % b)){
		a = b;
		b = tmp;
	}
	return b > 0 ? b : -b;
}
*/

/* Unlike the normal gcd function, this version never returns 0. 
e.g. gcd(0,0) returns 1;
	 gcd(1,0) returns 1;
	 gcd(0,114514) returns 1.
*/
int gcd_frac(int a,int b) {
	if (a && b) {
		while((a%=b) && (b%=a));
		return a+b;
	} else {
		return 1;
	}
}
int lcm_frac(int a, int b){
	return a / gcd_frac(a, b) * b ;
}
int qpow_frac(int base, int expt){
	int res = 1;
	while (expt){
		if (expt & 1)
			res *= base ;
		base *= base;
		expt >>= 1;
	}
	return res;
}

//tool
Fraction initFrac(int up, int down){
	Fraction res = {up , down};
	if (down != 0)
		reduceFrac(&res);
	return res;
}
void fixsignFrac(Fraction* a){
	if (0 == a->down){
		//fprintf(stderr, "Fraction: fixsignFrac: Fatal error: Zero in denominators.\n");
		error_print_frac("fixsignFrac", "Zero in denominators.");
		exit(EDOM);
	}
	if (0 == a->up){
		a->down = 1;
		return;
	}
	if (a->down < 0){
		a->up = -(a->up);
		a->down = -(a->down);
		return;
	}
}
void reduceFrac(Fraction* a){
	fixsignFrac(a);
	int gcdn = gcd_frac(a->up, a->down);
	a->up /= gcdn;
	a->down /= gcdn;
}
void reduce_num_frac(int* a, int* b){
	int gcdn = gcd_frac(*a, *b);
	*a /= gcdn;
	*b /= gcdn;
}
void printFrac(Fraction a){
	//printf("(%d/%d)%s", a.up, a.down, end);
	printf("(%d", a.up);
	if (a.down != 1) {
		printf("/%d", a.down);
	}
	printf(")");
}
int num_len_frac(int n) {
	/* int len = n <= 0 ? 1 : 0; */
	int len = 0;
	do {
		n /= 10;
		len++;
	} while (n);
	return len;
}
void pprintFrac(Fraction a) {
	if (a.down == 1) {
		printf("%d", a.up);
		return;
	}
	int len_up   = num_len_frac(a.up);
	int len_down = num_len_frac(a.down);
	int len_max  = MAX(len_up, len_down);
	int len_min  = MIN(len_up, len_down);
	
	bool sym = 0;   // >0
	if (a.up < 0) { 
		sym = 1;	// <0
		putchar(' ');
	}
	printf("%d\n", abs(a.up));
	if (sym)
		putchar('-');
	for (int i = 0; i < len_max; i++)
		putchar('_');
	putchar('\n');
		
	int len_down_right = (len_max - len_min) / 2;
	int len_down_left  = len_max - len_min - len_down_right;
	if (sym)
		putchar(' ');
	for (int i = 0; i < len_down_left; i++)
		putchar(' ');
	printf("%d", a.down);
	for (int i = 0; i < len_down_right; i++)
		putchar(' ');
}
int cmpFrac(Fraction a, Fraction b){
	if (b.down == 0){
		return 2;
	}
	if ((a.up == b.up && a.down == b.down) || (a.up == 0 && b.up == 0))
		return 0;
	else if (a.up < 0 && b.up > 0)
		return -1;
	else if (a.up > 0 && b.up < 0)
		return 1;
	reduce_num_frac(&a.up, &b.up);
	reduce_num_frac(&a.down, &b.down);
	long long resup = a.up * b.down;
	long long resdown = a.down * b.up;
	if (resup < resdown)
		return -1;
	else if (resup > resdown)
		return 1;
}

Fraction calcFrac(char myope, ...){
	va_list alist;
	va_start(alist, myope);
	Fraction argval = va_arg(alist, Fraction);
	Fraction res = argval;
	argval = va_arg(alist, Fraction);
	switch (myope){
		case '+' :
			while (argval.down){
				res = addFrac(res, argval);
				argval = va_arg(alist, Fraction);
			}
			break;
		case '-' :
			while (argval.down){
				res = subFrac(res, argval);
				argval = va_arg(alist, Fraction);
			}
			break;
		case '*' :
			while (argval.down){
				res = mulFrac(res, argval);
				argval = va_arg(alist, Fraction);
			}
			break;
		case '/' :
			while (argval.down){
				res = divFrac(res, argval);
				argval = va_arg(alist, Fraction);
			}
			break;
		default:
			//fprintf(stderr,"calcFrac: Invalid Operator\n");
			error_print_frac("calcFrac", "Invalid Operator.");
			exit(EPERM);
	}
	va_end(alist);
	return res;
}

//calculation
Fraction addFrac(Fraction a, Fraction b){
	int lcmn = lcm_frac(a.down, b.down);
	a.up = lcmn / a.down * a.up + lcmn / b.down * b.up;
	a.down = lcmn;
	reduceFrac(&a);
	return a;
}
Fraction subFrac(Fraction a, Fraction b){
	b.up = -b.up;
	return addFrac(a, b);
}
Fraction mulFrac(Fraction a, Fraction b){
	int gcdn1 = gcd_frac(a.up, b.down);
	int gcdn2 = gcd_frac(a.down, b.up);
	a.up /= gcdn1;
	b.down /= gcdn1;
	a.down /= gcdn2;
	b.up /= gcdn2;
	a.up *= b.up;
	a.down *= b.down;
	fixsignFrac(&a);
	return a;
}
Fraction divFrac(Fraction a, Fraction b){
	b.up ^= b.down ^= b.up ^= b.down;
	return mulFrac(a, b);
}
Fraction powFrac(Fraction a, int expt){
	a.up = qpow_frac(a.up, expt);
	a.down = qpow_frac(a.down, expt);
	return a;
}

