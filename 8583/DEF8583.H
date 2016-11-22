/***************************************************************
	def8583.h version 1.0 2000.8.27 by Felix
-----------------------------------------------------------------
	The define table of ISO8583/2000
		{
		 len:	Max LENgth or Fix LENgth;
		 type:	Data Type
					bit 0: C/D data field
					bit 1: BCD field
					bit 2: track2/track3 data field and PAN!
					bit 3: BIN data field
		 flag:	LENgth Type
					0--Fix LENgth,
					1--var LENgth (00--99),
					2--var LENgth (00--999);
		}
***************************************************************/
#include "iso8583.h"
/*flag*/
#define		FIX_LEN		0	/*(LENgth fix 是指由ISO_8583中的长度决定该域的长度)*/
#define		LLVAR_LEN	1	/*(LENgth 00~99)*/
#define		LLLVAR_LEN	2	/*(LENgth 00~999)*/
/*type*/
#define		L_BCD		0	/*左对齐BCD码*/
#define		L_ASC		1	/*左对齐ASC码*/
#define		R_BCD		2	/*右对齐BCD码*/
#define		R_ASC		3	/*右对齐ASC码*/

struct	ISO_8583 iso8583[128] = 
{
	{  8, L_ASC, FIX_LEN},  
	{ 19, L_BCD, LLVAR_LEN}, //2
	{  6, L_BCD, FIX_LEN},	//3
	{  12, R_BCD, FIX_LEN},	//4
	{  8, L_BCD, FIX_LEN},	//5
	{  8, L_BCD, FIX_LEN},	//6
	{ 99, R_BCD, LLVAR_LEN},//7
	{  8, R_BCD, FIX_LEN},	//8
	{  8, R_BCD, FIX_LEN}, //9
	{  8, R_BCD, FIX_LEN}, //10
	{  6, R_BCD, FIX_LEN},	//11
	{  6, R_BCD, FIX_LEN},	//12
	{  4, R_BCD, FIX_LEN},	//13
	{  4, R_BCD, FIX_LEN},	//14
	{  4, R_BCD, FIX_LEN},	//15
	{  4, R_BCD, FIX_LEN},	//16
	{  4, R_BCD, FIX_LEN},	//17
	{  4, R_BCD, FIX_LEN},	//18
	{  4, R_BCD, FIX_LEN},	//19
	{  4, R_BCD, FIX_LEN},	//20
	{  4, R_BCD, FIX_LEN},	//21
	{  3, R_BCD, FIX_LEN}, 	//22
	{  3, R_BCD, FIX_LEN},	//23
	{  4, R_BCD, FIX_LEN},	//24
	{  2, R_BCD, FIX_LEN},	//25
	{  2, L_BCD, FIX_LEN},	//26
	{  99, L_BCD, LLVAR_LEN},	//27
	{  99, L_BCD, LLVAR_LEN},	//28
	{  99, L_BCD, LLVAR_LEN},	//29
	{  99, L_BCD, LLVAR_LEN},	//30
	{  99, L_BCD, LLVAR_LEN},	//31
	{  99, L_BCD, LLVAR_LEN},	//32
	{  99, L_BCD, LLVAR_LEN},	//33
	{ 999, L_BCD, LLLVAR_LEN},	//34
	{ 37,  L_BCD, LLVAR_LEN},	//35
	{104,  L_BCD, LLLVAR_LEN},	//36
	{ 12,  L_ASC, FIX_LEN},		//37
	{  6,  L_ASC, FIX_LEN},		//38
	{  2,  L_ASC, FIX_LEN},		//39
	{ 99,  L_ASC, LLVAR_LEN},	//40
	{ 18,  L_ASC, FIX_LEN},		//41
	{ 15,  L_ASC, FIX_LEN},		//42
	{ 99,  L_BCD, LLVAR_LEN},	//43
	{ 99,  L_ASC, LLVAR_LEN},	//44
	{ 99,  L_BCD, LLVAR_LEN},	//45
	{999, R_BCD, LLLVAR_LEN},	//46
	{999, R_BCD, LLLVAR_LEN},	//47
	{999, R_BCD, LLLVAR_LEN},	//48
	{  3, R_ASC, FIX_LEN},		//49
	{  3, R_BCD, FIX_LEN},		//50
	{  3, R_BCD, FIX_LEN},		//51
	{  8, R_BCD, FIX_LEN},		//52
	{ 16, R_ASC, FIX_LEN},		//53
	{999, R_ASC, LLLVAR_LEN},	//54
	{255, R_ASC, LLLVAR_LEN},	//55
	{999, R_BCD, LLLVAR_LEN},	//56
	{999, R_BCD, LLLVAR_LEN},	//57
	{999, R_BCD, LLLVAR_LEN},	//58
	{999, R_BCD, LLLVAR_LEN},	//59
	{999, R_BCD, LLLVAR_LEN},	//60
	{99,  L_ASC, LLVAR_LEN},	//61
	{999, L_ASC, LLLVAR_LEN},	//62
	{999, L_ASC, LLLVAR_LEN},	//63
	{ 8,  L_ASC, FIX_LEN},		//64
	{  8, R_BCD, FIX_LEN},
	{  1, R_ASC, FIX_LEN},
	{  2, R_ASC, FIX_LEN},
	{  3, R_ASC, FIX_LEN},
	{  3, R_ASC, FIX_LEN},
	{  3, R_ASC, FIX_LEN},
	{  4, R_ASC, FIX_LEN},
	{  4, R_ASC, FIX_LEN},
	{  6, R_ASC, FIX_LEN},
	{ 10, R_ASC, FIX_LEN},
	{ 10, R_ASC, FIX_LEN},
	{ 10, R_ASC, FIX_LEN},
	{ 10, R_ASC, FIX_LEN},
	{ 10, R_ASC, FIX_LEN},
	{ 10, R_ASC, FIX_LEN},
	{ 10, R_ASC, FIX_LEN},
	{ 10, R_ASC, FIX_LEN},
	{ 12, R_ASC, FIX_LEN},
	{ 12, R_ASC, FIX_LEN},
	{ 12, R_ASC, FIX_LEN},
	{ 12, R_ASC, FIX_LEN},
	{ 16, R_ASC, FIX_LEN},
	{ 16, R_ASC, FIX_LEN},
	{ 16, R_ASC, FIX_LEN},
	{ 16, R_ASC, FIX_LEN},
	{ 42, R_ASC, FIX_LEN},
	{  1, R_BCD, FIX_LEN},
	{  2, R_BCD, FIX_LEN},
	{  5, R_BCD, FIX_LEN},
	{  7, R_BCD, FIX_LEN},
	{ 42, R_BCD, FIX_LEN},
	{  8, R_BCD, FIX_LEN},
	{ 16, R_BCD, FIX_LEN},
	{ 25, R_BCD, FIX_LEN},
	{ 11, R_ASC, LLVAR_LEN},
	{ 11, R_ASC, LLVAR_LEN},
	{ 17, R_BCD, LLVAR_LEN},
	{ 28, R_BCD, LLVAR_LEN},
	{ 28, R_BCD, LLVAR_LEN},
	{10,  R_BCD, LLLVAR_LEN},
	{999, R_BCD, LLLVAR_LEN},
	{999, R_BCD, LLLVAR_LEN},
	{999, R_BCD, LLLVAR_LEN},
	{999, R_BCD, LLLVAR_LEN},
	{999, R_BCD, LLLVAR_LEN},
	{999, R_BCD, LLLVAR_LEN},
	{999, R_BCD, LLLVAR_LEN},
	{999, R_BCD, LLLVAR_LEN},
	{999, R_BCD, LLLVAR_LEN},
	{999, R_BCD, LLLVAR_LEN},
	{999, R_BCD, LLLVAR_LEN},
	{999, R_BCD, LLLVAR_LEN},
	{999, R_BCD, LLLVAR_LEN},
	{999, R_BCD, LLLVAR_LEN},
	{999, R_BCD, LLLVAR_LEN},
	{999, R_BCD, LLLVAR_LEN},
	{999, R_BCD, LLLVAR_LEN},
	{999, R_BCD, LLLVAR_LEN},
	{999, R_BCD, LLLVAR_LEN},
	{999, R_BCD, LLLVAR_LEN},
	{999, R_BCD, LLLVAR_LEN},
	{999, R_BCD, LLLVAR_LEN},
	{999, R_BCD, LLLVAR_LEN},
	{  8, R_BCD, FIX_LEN}
};



