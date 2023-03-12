#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <wchar.h>
#include <locale.h>
#include <string.h>
#include "radical.h"

//tool
Radical initRad(int up, int down, int in){
	Radical tmp = {{ up , down }, in};
	if (down != 0){
		reduceFrac(&(tmp.out));
	}
	Radical res = Radsqrt( tmp.in );
	res.out = mulFrac(res.out, tmp.out);
	return res;
}
Radical Frac2Rad(Fraction a) {
	Radical num = {{ a.up , a.down }, 1};
	reduceFrac(&(num.out));
	return num;
}
Radical int2Rad(int a) {
	Radical num = {a, 1, 1};
	return num;
}

bool printRad(Radical a) {
	setlocale(LC_ALL, "");
	int f = 0;
	if (a.out.up < 0)
		printf("-");
	if (a.in == 1) {
		if (a.out.down == 1) {
			f = printf("%d",abs(a.out.up));
			return f == 1 ? true : false;
		} else {
			f = printf("%d/%d", abs(a.out.up), a.out.down);
			return f == 3 ? true : false;
		}
	} else {
		if (a.out.down == 1) {
			if (a.out.up == 1 || a.out.up == -1) {
				f = wprintf(L"√(%d)", a.in);
				return f == 4 ? true : false;
			} else {
				f = wprintf(L"%d√(%d)", abs(a.out.up), a.in);
				return f == 5 ? true : false;
			}
		} else {
			f = wprintf(L"(%d/%d)√(%d)", abs(a.out.up), a.out.down, a.in);
			return f == 9 ? true : false;
		}
	}
	return false;
}

Str toStrRad(Radical a) {
	Str str;
	str.s[0] = '\0';
	if (a.out.up < 0)
		snprintf(str.s, TYPE_STR_LEN, "-");
	if (a.in == 1) {
		if (a.out.down == 1) {
			snprintf(str.s+strlen(str.s), TYPE_STR_LEN-strlen(str.s), "%d", abs(a.out.up));
		}
		else
			snprintf(str.s+strlen(str.s), TYPE_STR_LEN-strlen(str.s), "%d/%d", abs(a.out.up), a.out.down);
	} else {
		if (a.out.down == 1) {
			if (a.out.up == 1 || a.out.up == -1)
				snprintf(str.s+strlen(str.s), TYPE_STR_LEN-strlen(str.s), "sqrt(%d)", a.in);
			else
				snprintf(str.s+strlen(str.s), TYPE_STR_LEN-strlen(str.s), "%dsqrt(%d)", abs(a.out.up), a.in);
		}
		else
			snprintf(str.s+strlen(str.s), TYPE_STR_LEN-strlen(str.s), "(%d/%d)sqrt(%d)", abs(a.out.up), a.out.down, a.in);
	}
	return str;
}

void pprintRad(Radical a){
	setlocale(LC_ALL, "");
/*
	int len_up   = num_len_frac(a.out.up);
	int len_in   = num_len_frac(a.in);
	if (a.out.down != 1) {
		int len_down = num_len_frac(a.out.down);
		int len_max  = MAX(len_up, len_down);
		int len_min  = MIN(len_up, len_down);		
		
		bool sym = false;   // >0
		if (a.out.up<0) { 
			sym = true;	 // <0
			putchar(' ');
		}
		printf("%d\n", abs(a.out.up));
			
		if (sym)
			putchar('-');
		for (int i = 0; i < len_max; i++)
			putchar('_');
		putchar(' ');
#ifdef _WIN32
		putchar(' ');
#endif
		for (int i = 0; i < len_in; i++)
			putchar('_');
		putchar('\n');

		int len_down_right = (len_max - len_min) / 2;
		int len_down_left  = len_max - len_min - len_down_right;
		if (sym)
			putchar(' ');
		for (int i = 0; i < len_down_left; i++)
			putchar(' ');
		printf("%d", a.out.down);
		for (int i = 0; i < len_down_right; i++)
			putchar(' ');
	} else if (a.out.up != 1){
		printf("%d\n", a.out.up);
		for (int i = 0; i < len_up; i++)
			putchar(' ');
		putchar(' ');
		for (int i = 0; i < len_in; i++)
			putchar('_');
		putchar('\n');
		for (int i = 0; i < len_up; i++)
			putchar(' ');
	} else {
		putchar('\n');
		putchar(' ');
		for (int i = 0; i < len_in; i++)
			putchar('_');
		putchar('\n');
	}
	wprintf(L"√%d", a.in);
*/
	if (a.in == 1) {
		pprintFrac(a.out);
	} else if (a.out.up == 1 || a.out.up == -1) {
		bool sym = false;   // >0
		if (a.out.up < 0) { 
			sym = true;	// <0
		}

	// 1
		if (sym)
			putchar(' ');

		putchar(' ');
	#ifdef _WIN32
		putchar(' ');
	#endif
		for (int i = 0; i < num_len_frac(a.in); ++i)
			putchar('_');
	// end 1
		putchar('\n');
		if (a.out.down == 1) {
	// 2
			if (sym)
				putchar('-');
			wprintf(L"√%d", a.in);
	//end 2
		} else {
			int len_up   = num_len_frac(a.in) + 1;
	#ifdef _WIN32
			++len_up;
	#endif
			int len_down = num_len_frac(a.out.down);
			int len_max  = MAX(len_up, len_down);
			
			int* aptr = &(a.in);
			int len_aptr;
			pprint_up2down:
			len_aptr = num_len_frac(*aptr);
			if (aptr == &(a.in)) {
				++len_aptr;
	#ifdef _WIN32
				++len_aptr;
	#endif
			}
			if (sym)
				putchar(' ');
			if (len_max == len_aptr) {
				if (aptr == &(a.in)) {
					wprintf(L"√");
				}
				printf("%d", abs(*aptr));
			} else {
				int len_right = (len_max - len_aptr) / 2;
				int len_left = len_max - len_aptr - len_right;
				for (int i = 0; i < len_left; i++)
					putchar(' ');
				if (aptr == &(a.in)) {
					wprintf(L"√");
				}
				printf("%d", abs(*aptr));
				for (int i = 0; i < len_right; i++)
					putchar(' ');
			}
			if (aptr == &(a.in)) {
				putchar('\n');
				if (sym)
					putchar('-');
				for (int i = 0; i < len_max; i++)
					putchar('_');
				putchar('\n');
				aptr = &(a.out.down);
				goto pprint_up2down;
			}
		}
	}	
}
Radical Radsqrt( int radicand ){
	Radical res = {.out.up = 0, .out.down = 1, .in = 1};
	if (0 == radicand) {
		return res;
	} else if (radicand < 0) {
		fprintf(stderr, "Radsqrt: negative number, exiting\n");
		exit(1);
	}
	int flag = 0;
	for (int tmp = floor(sqrt(radicand)) ; tmp-1 ; tmp--) {
		if (0 == radicand % (tmp * tmp)) {
			res.out.up = tmp;
			res.in  = radicand / (tmp * tmp);
			flag = 1;
			break;
		}
	}
	if (!flag) {
		res.out.up = 1;
		res.in  = radicand;
	}
	return res;
}
Radical sqrtFrac(Fraction a) {
	Radical u = Radsqrt(a.up) , d = Radsqrt(a.down);
	Fraction tmp = divFrac(u.out, d.out);
	u.in *= d.in;
	d.out.down = d.in;
	d.out.up = 1;
	u.out = mulFrac(tmp, d.out);
	return u;
}
void printPoly(Polynomial ptrl){
	setlocale(LC_ALL, "");
	Polynomial p = ptrl;
	if (p == NULL){
		return;
	} else if (p->next == NULL) {
		printf("0");
	} else {
		p = p->next;
	}

	if (p->num.out.up < 0)
		printf("-");
	while(1){
		if (p->num.in == 1){
			if (p->num.out.down == 1)
				printf("%d",abs(p->num.out.up));
			else
				printf("(%d/%d)", abs(p->num.out.up), p->num.out.down);
		} else {
			if (p->num.out.down == 1){
				if (p->num.out.up == 1 || p->num.out.up == -1)
					wprintf(L"√(%d)", p->num.in);
				else
					wprintf(L"%d√(%d)", abs(p->num.out.up), p->num.in);
			}
			else
				wprintf(L"(%d/%d)√(%d)", abs(p->num.out.up), p->num.out.down, p->num.in);
		}

		if (p->next == NULL){
			break;
		}
		p = p->next;
		if (p->num.out.up >= 0)
			printf(" + ");
		else
			printf(" - ");
	}
}
bool isequalRad(Radical a, Radical b){
	if (a.in == b.in && a.out.up == b.out.up && a.out.down == b.out.down)
		return true;
	else
		return false;
}
/*
int cmpRad(Radical a, Radical b){
	if (a.in == b.in)
		return cmpFrac(a.out, b.out);

	int gcdn1 = gcd_frac(a.out.up, b.out.up);
	int gcdn2 = gcd_frac(a.out.down, b.out.down);
	a.out.up /= gcdn1;
	b.out.up /= gcdn1;
	a.out.down /= gcdn2;
	b.out.down /= gcdn2;

	a.out.up *= b.out.down;
	a.out.down *= b.out.up;
	b.out.up = a.out.down;
	b.out.down = a.out.up;

	long long   aup = a.out.up * b.out.down ,
				adown = a.out.dowm * b.out.up ,
				bup = a.out.down ,
				bdown = a.out.up ;

	int gcdn3 = (int)lgcd_frac((long long)a.in, adown);
	int gcdn4 = (int)lgcd_frac((long long)b.in, bdown);
	a.in /= gcdn3;
	adown /= gcdn3;
	b.in /= gcdn4;
	bdown /= gcdn4;

	aup *= a.in;
	bup *= b.in;
	printRad(a , "\n");
	printRad(b , "\n");
	return cmpFrac(a.out, b.out);
}
*/
//calculation
Radical divRad(Radical a, Radical b){
	Fraction tmp = divFrac(a.out, b.out);
	int gcdn = gcd_frac(a.in, b.in);
	a.in /= gcdn;
	b.in /= gcdn;
	a.in *= b.in;
	b.out.down = b.in;
	b.out.up = 1;
	a.out = mulFrac(tmp, b.out);
	return a;
}
Radical mulRad(Radical a, Radical b){
	Radical res;
	a.out = mulFrac(a.out, b.out);
	a.in *= b.in;
	res = Radsqrt(a.in);
	res.out = mulFrac(a.out, res.out);
	return res;
}

Polynomial addRad(Polynomial ptrl, Radical b) {
	Polynomial p = ptrl;
	if (p == NULL){
		return NULL;
	}
	else if (p->next == NULL){
		insertheadPoly(b, ptrl);
		return ptrl;
	}

	bool flag = false;
	int i = 1;
	do {
		p = p->next;
		if (p->num.in == b.in){
			p->num.out = addFrac(p->num.out, b.out);
			flag = true;
			//if (p->num.out.up == 0 && lenPoly(ptrl) != 1) {
			if (p->num.out.up == 0) {
				deletePoly(i, ptrl);
			}
			break;
		}
		i++;
	}while (p->next != NULL);

	if (!flag) {
		insertheadPoly(b, ptrl);
	}
	return ptrl;
}
Polynomial subRad(Polynomial ptrl, Radical b){
	b.out.up = -b.out.up;
	return addRad(ptrl, b);
}
int gcdPoly(Polynomial ptrl){
	Polynomial p = ptrl;
	if (p == NULL || p->next == NULL){
		return 1;
	}
	p = p->next;
	if (p->next == NULL){
		return p->num.out.up;
	}
	int gcdn = gcd_frac(p->num.out.up, p->next->num.out.up);
	while (gcdn != 1){
		p = p->next;
		if (p->next == NULL)
			break;
		gcdn = gcd_frac(gcdn, p->next->num.out.up);
	}

	return gcdn >= 0 ? gcdn : -gcdn;
}
Polynomial _PolyIntReduce(Polynomial ptrl, int* x){
	Polynomial p = ptrl;
	if (p == NULL || p->next == NULL){
		return ptrl;
	}
	int gcdn = gcd_frac(gcdPoly(ptrl), *x);
	*x /= gcdn;
	do {
		p = p->next;
		p->num.out.up /= gcdn;
	}while (p->next != NULL);
	return ptrl;
}

Radical divintRad(Radical a, int b) {
	a.out = divFrac(a.out, initFrac(b, 1));
	return a;
}

Polynomial divintPoly(Polynomial ptrl, int x) {
	Polynomial p = ptrl;
	if (p == NULL || p->next == NULL){
		return ptrl;
	}
	do {
		p = p->next;
		p->num = divintRad(p->num, x);
	}while (p->next != NULL);
	return ptrl;
}

Fraction squareRad(Radical a) {
	Fraction res;
	if (!(a.in % a.out.down)) {
		a.in /= a.out.down;
		res = initFrac(a.out.up * a.out.up * a.in, a.out.down);
	} else {
		res = initFrac(a.out.up * a.out.up * a.in, a.out.down * a.out.down);
	}
	return res;
}

//list
Polynomial initPoly(){
	Polynomial head = (Node *)malloc(sizeof(Node));
	if (head == NULL){
		fprintf(stderr, "initPoly: failed\n");
		return NULL;
	}
	head->next = NULL;
	return head;
}
void destoryPoly(Polynomial ptrl) {
	if (ptrl == NULL) {
		fprintf(stderr, "destoryPoly: Polynomial doesn't exist.\n");
		return;
	}
	Polynomial p = ptrl;
	Polynomial q; 
	while (p) {
		q = p->next;
		free(p);	
		p = q;
	}
	ptrl = NULL;
}
int lenPoly(Polynomial ptrl){
	Polynomial p = ptrl;
	int j = 0;
	while (p){
		p = p->next;
		j++;
	}
	return j-1;
}

Polynomial findkthPoly(int k, Polynomial ptrl){
	Polynomial p = ptrl;
	int i = 0;
	while ( i < k && p != NULL && p->next != NULL){
		p = p->next;
		i++;
	}
	if ((i) == k)
		return p;
	else
		return NULL;
}

Polynomial findPoly(Radical x, Polynomial ptrl){
	Polynomial p = ptrl;
	while (p != NULL && isequalRad(p->num, x)){
		p = p->next;
	}
	return p;
}

/*
Polynomial insertheadPoly(Radical x, Polynomial ptrl) {
	Node* s = (Node *)malloc(sizeof(Node));
	if (s == NULL) {
		fprintf(stderr, "insertheadPoly: allocate memory failed.\n");
		return ptrl;
	}
	s->num = x;
	s->next = ptrl;
	ptrl = s;
	return ptrl;
}
*/

Polynomial insertheadPoly(Radical x, Polynomial ptrl) {
	if (ptrl == NULL) {
		return ptrl;
	}
	Node* s = (Node *)malloc(sizeof(Node));
	if (s == NULL) {
		fprintf(stderr, "insertheadPoly: allocate memory failed.\n");
		return ptrl;
	}
	s->num = x;
	s->next = ptrl->next;
	ptrl->next = s;
	return ptrl;
}

Polynomial insertPoly(Radical x, int i, Polynomial ptrl) {
	Polynomial p,s;
	p = findkthPoly(i-1, ptrl);
	if (p == NULL) {
		fprintf(stderr, "insertPoly: value of i error\n");
		return NULL;
	}
	else {
		s = (Node *)malloc(sizeof(Node));
		s->num = x;
		s->next = p->next;
		p->next = s;
		return ptrl;
	}
}

Polynomial deletePoly(int i, Polynomial ptrl){
	Polynomial p,s;
	p = findkthPoly(i-1, ptrl);
	if (p == NULL){
		fprintf(stderr, "deletePoly: the %dth node does not exist\n",i-1);
		return NULL;
	}
	else if (p->next == NULL){
		fprintf(stderr, "deletePoly: the %dth node does not exist\n",i);
		return NULL;
	}
	else {
		s = p->next;
		p->next = s->next;
		free(s);
		s = NULL;
		return ptrl;
	}
}

/*
Polynomial Poly_begin(Polynomial p) {
	return p->next;
}

Polynomial Poly_next(Polynomial p) {
	return p->next;
}
*/
