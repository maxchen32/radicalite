#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include "fraction.h"

static void error_print_frac
(const char* error_function, const char* error_content) {
	fprintf(stderr, "Error: Fraction: %s: %s\n", 
			error_function, error_content);
}

//math

/** @warning Unlike the normal gcd function, \n
 *  this function never returns 0 and negative number. \n
 *	e.g. gcd(0,0) returns 1; \n
 *		 gcd(1,0) returns 1; \n
 *		 gcd(0,114514) returns 1.
 */
int gcd_frac(int a,int b) {
	if (a && b) {
		while((a%=b) && (b%=a));
		return abs(a+b);
	} else {
		return 1;
	}
}
int lcm_frac(int a, int b){
	return a / gcd_frac(a, b) * b ;
}
Fraction qpow_frac(int base, int expt){
	if(base == 0)
		return initFrac(0, 1);
	int res = 1;
	bool flag = true;
	if (expt < 0) {
		expt = -expt;
		flag = false;
	}
	while (expt){
		if (expt & 1)
			res *= base ;
		base *= base;
		expt >>= 1;
	}
	return flag ? initFrac(res, 1) : initFrac(1, res);
}

//tool
Fraction initFrac(int up, int down){
	Fraction res = {up , down};
	if (down != 0)
		reduceFrac(&res);
	return res;
}

Fraction int2Frac(int up) {
	Fraction res = {up , 1};
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
	printf("%d", a.up);
	if (a.down != 1) {
		printf("/%d", a.down);
	}
}

Str toStrFrac(Fraction a){
	Str str;
	str.s[0] = '\0';
    snprintf(str.s, TYPE_STR_LEN,"%d", a.up);
	if (a.down != 1) {
		snprintf(str.s+strlen(str.s), TYPE_STR_LEN-strlen(str.s),"/%d", a.down);
	}
	return str;
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
	int len_max  = len_up > len_down ? len_up: len_down;
	
	bool sym = false;   // >0
	if (a.up < 0) { 
		sym = true;	// <0
		//putchar(' ');
	}
	//printf("%d\n", abs(a.up));
	int* aptr = &(a.up);
	int len_aptr;
	pprint_up2down:
	len_aptr = num_len_frac(*aptr);
	if (sym)
		putchar(' ');
	if (len_max == len_aptr) {
		printf("%d", abs(*aptr));
	} else {
		int len_right = (len_max - len_aptr) / 2;
		int len_left = len_max - len_aptr - len_right;		
		for (int i = 0; i < len_left; i++)
			putchar(' ');
		printf("%d", abs(*aptr));
		for (int i = 0; i < len_right; i++)
			putchar(' ');
	}
	if (aptr == &(a.up)) {
		putchar('\n');
		if (sym)
			putchar('-');
		for (int i = 0; i < len_max; i++)
			putchar('_');
		putchar('\n');
		aptr = &(a.down);
		goto pprint_up2down;
	}
}
int cmpFrac(Fraction a, Fraction b){
	if (!(a.down && b.down)){
		error_print_frac("cmpFrac", "Zero in denominators.");
		exit(EDOM);
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
	error_print_frac("cmpFrac", "Unknown error.");
	exit(1);
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
	if (!cmpFrac(b, int2Frac(0))) {
		error_print_frac("divFrac", "division by zero.");
		exit(EDOM);
	}
	int temp = b.up;
	//b.up ^= b.down ^= b.up ^= b.down;
	b.up = b.down;
	b.down = temp;
	return mulFrac(a, b);
}
Fraction powFrac(Fraction a, int expt){
	Fraction up = qpow_frac(a.up, expt);
	Fraction down = qpow_frac(a.down, expt);
	return divFrac(up, down);
}

