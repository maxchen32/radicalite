#ifndef _FRACTION_H
#define _FRACTION_H

#define MAX(x, y)  ({\
typeof(x) _x = x;\
typeof(y) _y = y;\
(void)(&_x == &_y);\
_x > _y ? _x : _y;\
})

#define MIN(x, y)  ({\
typeof(x) _x = x;\
typeof(y) _y = y;\
(void)(&_x == &_y);\
_x < _y ? _x : _y;\
})

#define Fraction0() initFrac(0, 1)
#define FractionN(up) initFrac(up, 1)
#define Fraction(up, down) initFrac(up, down)
#define iszeroFrac(a) ((a).up == 0 ? 1 : 0)

typedef struct Fraction{
	int up;
	int down;
} Fraction;                 //分数

//数学 math
int       gcd_frac(int a, int b);						//最大公因数
long long lgcd_frac(long long a, long long b);
int       lcm_frac(int a, int b);						//最小公倍数
int       qpow_frac(int base, int expt);				//快速幂
void      reduce_num_frac(int* a, int* b);		//数约分
int       num_len_frac(int n);					//数的绝对值的长度

//工具 tool
Fraction initFrac(int up ,int down);       //初始化
void     fixsignFrac(Fraction* a);				//符号修正、错误处理
void     reduceFrac(Fraction* a);				//分数约分
void     printFrac(Fraction a);    //打印
void     pprintFrac(Fraction a);   //（实验性的）美观打印
int      cmpFrac(Fraction a, Fraction b);       //比较 返回-1 , 0 , 1
Fraction calcFrac(char myope, ...);               //运算器

//运算 operator
Fraction addFrac(Fraction a, Fraction b);	//加法
Fraction subFrac(Fraction a, Fraction b);	//减法
Fraction mulFrac(Fraction a, Fraction b);	//乘法
Fraction divFrac(Fraction a, Fraction b);	//除法
Fraction powFrac(Fraction a, int expt);		//乘方

#endif

