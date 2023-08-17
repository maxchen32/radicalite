/**
 * @file radical.h
 * @brief radical.c的头文件
 * @details 包含Radical结构体、Node结构体和各种处理Radical和Polynomial的函数。
 * @author maxchen32
 * @version 1.0.2
 * @copyright 2020-2023 maxchen32
 */

#ifndef _RADICAL_H
#define _RADICAL_H

#include "fraction.h"
#include <stdbool.h>

/// 二次根式类
typedef struct Radical {
	Fraction out;           ///< 在根号外面的部分，是一个分数
	int in;                 ///< 在根号里面的部分，是一个整数
} Radical;


typedef struct Node Node;   ///< struct Node别名Node
typedef Node* Polynomial;   ///< 多项式（单链表）

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
//void  pprintRad(Radical a);               // pprintRad is not yet available
Radical Radsqrt(int radicand);              ///< 把一个int数开根变为二次根式（即in设为int值）
Radical sqrtFrac(Fraction a);               ///< 分数开方
void    printPoly(Polynomial ptrl);         ///< 向stdout输出Polynomial多项式，末尾没有空格或回车
int     cmpRad(Radical a, Radical b);       ///< 比较大小，返回 -1, 0, 1
bool    isequalRad(Radical a, Radical b);   ///< 比较两个Radical是否相等

//calculation
Radical		divRad(Radical a, Radical b);
Radical 	divintRad(Radical a, int b);
Polynomial  divintPoly(Polynomial ptrl, int x);
Radical		mulRad(Radical a, Radical b);
Polynomial 	addRad(Polynomial ptrl, Radical b);
Polynomial 	subRad(Polynomial ptrl, Radical b);
int			gcdPoly(Polynomial ptrl);
Polynomial 	_PolyIntReduce(Polynomial ptrl, int* x);
Fraction    squareRad(Radical a);
Polynomial  mulRadPoly(Polynomial ptrl, Radical a);
Polynomial  divRadPoly(Polynomial ptrl, Radical a);
Polynomial  mulPoly(Polynomial ptrla, Polynomial ptrlb);
//Polynomial  mapRRPoly(Polynomial ptrl, Radical (*Cb_rad_rad)(Radical, Radical), Radical a);
Polynomial  addPoly(Polynomial ptrla, Polynomial ptrlb);
Polynomial  subPoly(Polynomial ptrla, Polynomial ptrlb);

//list
Polynomial	initPoly();
void 		destoryPoly(Polynomial ptrl);
int 		lenPoly(Polynomial ptrl);
Polynomial	findPoly(Radical x, Polynomial ptrl);
Polynomial	findkthPoly(int k, Polynomial ptrl);
Polynomial	insertPoly(Radical x, int i, Polynomial ptrl);
Polynomial  insertheadPoly(Radical x, Polynomial ptrl);
Polynomial  copyPoly(Polynomial ptrl);
Polynomial	deletePoly(int i, Polynomial ptrl);
//Polynomial  Poly_next(Polynomial p);

#endif
