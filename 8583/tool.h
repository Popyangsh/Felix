#ifndef __TOOL__H_
#define __TOOL__H_

#include <string.h>
#include <stdio.h>
#include <time.h>
#define FAIL     -1
#define SUCCESS   0

#define	STX1	0xC0
#define	ETX1	0xC1
#define	STX2	0xC2
#define	ETX2	0xC3

typedef  unsigned char   BYTE;
class CTool  
{
public:
	char	m_intoHex[20];
	char	m_TimeData[30];
public:
	char* GetSysTime();
	int PackData(int Addr,int Port,unsigned char *Buffer,int Len);
	int BuildData(unsigned char MacNum,int Flag,unsigned char *commision,unsigned char CommByte,int InDataLen,unsigned char * InData,unsigned char *OutData,int Level,unsigned char *Level_Array);
	int CRC_CCITT(unsigned char len,unsigned char *in,BYTE* out);
	CTool();
	BYTE* AscToBcd(BYTE* ascbuf, int ascbuf_len, BYTE* bcdbuf);
	BYTE* BcdToAsc(BYTE* bcdbuf, int bcdbuf_len,BYTE* ascbuf );
	char* IntToHex(int data);
	char* ltrim(char* str);
	char* rtrim(char* str);
	char* trim(char* str);
	char* HeadAddStr(char* str, int num, char type);
	bool  CheckStrHex(char* str );
	int  HexToInt(unsigned char* HexData,  int len);
		
	void SmartEncrypt(BYTE E_number,BYTE* ID, BYTE* Plain)
	{
		Plain[0] = (Plain[0] ^ (ID[0] + E_number))  +1;
		Plain[1] = (Plain[1] ^ (ID[1] + E_number))  +2;
		Plain[2] = (Plain[2] ^ (ID[2] + E_number))  +3;
		Plain[3] = (Plain[3] ^ (ID[3] + E_number))  +4;
		Plain[4] = (Plain[4] ^ (~ID[0] + E_number)) +5;
		Plain[5] = (Plain[5] ^ (~ID[1] + E_number)) +6;
		Plain[6] = (Plain[6] ^ (~ID[2] + E_number)) +7;
		Plain[7] = (Plain[7] ^ (~ID[3] + E_number)) +8;
		Plain[8] = (Plain[8] ^ (ID[0] + ID[1] + ID[2] + ID[3] + E_number)) +9;
		return;
	}

	virtual ~CTool();

};



#endif 
