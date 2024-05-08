/**
 * @file radical.h
 * @brief radical.c的头文件
 * @details 包含Radical结构体、Node结构体和各种处理Radical和Polynomial的函数。
 * @author maxchen32
 * @version 1.0.2
 * @copyright 2020-2024 maxchen32
 */

#ifndef _RADICAL_H
#define _RADICAL_H

#include "fraction.h"
#include <stdbool.h>

/**
   \struct Radical 
   \brief 二次根式类
   \details 单项根式，形如 a/b*sqrt(c) 的数。
   \note “二次根式”指单项根式，形如 a/b*sqrt(c) 的数，不包含加减。
        形如 a/b*sqrt(c) + d/e*sqrt(f) 的数属于Polynomial（多项式）类。
 */
typedef struct Radical {
	Fraction out;           ///< 在根号外面的部分，是一个分数
	int in;                 ///< 在根号里面的部分，是一个整数
} Radical;                  ///< 二次根式类


typedef struct Node Node;   ///< struct Node别名Node
typedef Node* Polynomial;   ///< 多项式类（单链表）

/// 多项式节点
struct Node {
	Radical num;            ///< 节点里的数据，是一个二次根式
	Polynomial next;        ///< 指向下一个节点的指针
};

//////////////////
/*
typedef struct Node {
    SLIST_ENTRY(Node) field;
    Radical num;
} Node;
typedef Node* Polynomial;
*/
//////////////////

//tool
Radical	initRad(int up, int down, int in);  ///< 初始化一个Radical类型的值（默认在栈中所以不需要手动free）
Radical Frac2Rad(Fraction a);               ///< 把Fraction类型转换为Radical（out设为Fraction值，in设为1）
Radical int2Rad(int a);                     ///< 把int类型转换为Radical（out.up设为int值，out.down和in设为1）
double  Rad2double(Radical a);              ///< 求一个Radical值的 ** 近似 ** 数值
bool    printRad(Radical a);                ///< 向stdout输出Radical，末尾没有空格或回车
Str     toStrRad(Radical a);                ///< 把Radical转换为Str类型的字符串
//void  pprintRad(Radical a);               // 美观打印Radical，还没完全实现
Radical Radsqrt(int radicand);              ///< 把一个int数开根变为二次根式（即in设为int值）
Radical sqrtFrac(Fraction a);               ///< 分数开方
void    printPoly(Polynomial ptrl);         ///< 向stdout输出Polynomial多项式，末尾没有空格或回车
int     cmpRad(Radical a, Radical b);       ///< 比较大小，返回 -1, 0, 1
bool    isequalRad(Radical a, Radical b);   ///< 比较两个Radical是否相等

//calculation
Radical		divRad(Radical a, Radical b);            ///< 二次根式 a 除以 b
Radical 	divintRad(Radical a, int b);             ///< 二次根式除以整数
Polynomial  divintPoly(Polynomial ptrl, int x);      ///< 多项式除以整数
Radical		mulRad(Radical a, Radical b);            ///< 两个二次根式相乘
Polynomial 	addRad(Polynomial ptrl, Radical b);      ///< 向多项式加入一个单项二次根式
Polynomial 	subRad(Polynomial ptrl, Radical b);      ///< 从多项式减去一个单项二次根式
int			gcdPoly(Polynomial ptrl);                ///< 求多项式的各个项的分数部分的分子的最大公因数
Polynomial 	_PolyIntReduce(Polynomial ptrl, int* x); ///< 让多项式和一个整数约分（会改变整数的值）
Fraction    squareRad(Radical a);                    ///< 平方一个二次根式
Polynomial  mulRadPoly(Polynomial ptrl, Radical a);  ///< 让多项式的各项乘以一个单项二次根式
Polynomial  divRadPoly(Polynomial ptrl, Radical a);  ///< 让多项式的各项除以一个单项二次根式
Polynomial  mulPoly(Polynomial ptrla, Polynomial ptrlb); ///< 两个多项式相乘
//Polynomial  mapRRPoly(Polynomial ptrl, Radical (*Cb_rad_rad)(Radical, Radical), Radical a);
Polynomial  addPoly(Polynomial ptrla, Polynomial ptrlb); ///< 两个多项式相加
Polynomial  subPoly(Polynomial ptrla, Polynomial ptrlb); ///< 多项式 a 减多项式 b

//list
Polynomial	initPoly();                              ///< 初始化一个多项式
void 		destoryPoly(Polynomial ptrl);            ///< 销毁一个多项式
int 		lenPoly(Polynomial ptrl);                ///< 多项式长度
Polynomial	findPoly(Radical x, Polynomial ptrl);    ///< 从多项式中找出和x相等的第一项，返回指向这项的指针
Polynomial	findkthPoly(int k, Polynomial ptrl);     ///< 获取多项式的第k项
Polynomial	insertPoly(Radical x, int i, Polynomial ptrl); ///< 往多项式第i项插入一个单项二次根式
Polynomial  insertheadPoly(Radical x, Polynomial ptrl);    ///< 往多项式头部插入一个单项二次根式
Polynomial  copyPoly(Polynomial ptrl);                     ///< 复制一个多项式（深拷贝）
Polynomial	deletePoly(int i, Polynomial ptrl);            ///< 删除多项式第i项
//Polynomial  Poly_next(Polynomial p);

#endif
