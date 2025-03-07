/**
 * @file fraction.h
 * @brief fraction.c的头文件
 * @details 包含Fraction结构体、Str结构体、通用的宏和各种处理Fraction的函数。
 * @author maxchen32
 * @version 1.0.2
 * @copyright 2020-2024 maxchen32
 */

#ifndef _FRACTION_H
#define _FRACTION_H

#define TYPE_STR_LEN 45 //!< Str的最大长度

#define Fraction0() initFrac(0, 1)
#define FractionN(up) initFrac((up), 1)
#define Fraction(up, down) initFrac((up), (down))
#define iszeroFrac(a) ((a).up == 0 ? 1 : 0)

/// 分数类
typedef struct Fraction{
	int up;				//!< 分子
	int down;			//!< 分母
} Fraction;

/// 字符串类，用于接受Fraction或Radical转换成的字符数组
typedef struct Str {
    char s[TYPE_STR_LEN];	///< 长度为TYPE_STR_LEN的字符数组
}Str;

// 数学 math
int       gcd_frac(int a, int b);						//!< 最大公因数
int       lcm_frac(int a, int b);						//!< 最小公倍数
Fraction  qpow_frac(int base, int expt);				//!< 快速幂
void      reduce_num_frac(int* a, int* b);		//!< 两个整数约分（会改变传入的参数）
int       num_len_frac(int n);					//!< 数的绝对值的长度

// 工具 tool
Fraction initFrac(int up ,int down);       //!< 初始化一个Fraction
Fraction int2Frac(int up);					///< 转换int类型到Fraction
void     fixsignFrac(Fraction* a);				//!< 符号修正、错误处理
void     reduceFrac(Fraction* a);				//!< 分数约分
void     printFrac(Fraction a);    //!< 打印
Str      toStrFrac(Fraction a);		///< 转换Fraction类型到Str字符串
void     pprintFrac(Fraction a);   //!< （实验性的）美观打印
int      cmpFrac(Fraction a, Fraction b);       //!< 比较 返回-1 , 0 , 1
Fraction calcFrac(char myope, ...);               //!< 运算器

// 运算 operator
Fraction addFrac(Fraction a, Fraction b);	//!< 加法
Fraction subFrac(Fraction a, Fraction b);	//!< 减法
Fraction mulFrac(Fraction a, Fraction b);	//!< 乘法
Fraction divFrac(Fraction a, Fraction b);	//!< 除法
Fraction powFrac(Fraction a, int expt);		//!< 乘方

#endif

