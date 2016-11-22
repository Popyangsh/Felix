
/********************************************************************
	created:	2016/04/07
	file base:	export
	file ext:	cpp
	author:		Felix
	purpose:	
*********************************************************************/

#include "export.h"
#include "tool.h"

CISO8583 m_iso8583;
/*=================================================================
 * Function ID :  strtoiso
 * Input       :  unsigned char *str
 * Output      :  ISO_data *iso
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  success 0 fail -1
 * Description :  将按8583包格式的数据串装载到8583包中
 * Notice	   :  
 *					
 *=================================================================*/
int __stdcall smt_strtoiso(unsigned char *dstr, ISO_data *iso)
{	
	return m_iso8583.strtoiso(dstr,iso);
}

/*=================================================================
 * Function ID :  isotostr
 * Input       :  ISO_data *iso
 * Output      :  unsigned char *str
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  success 0 fail -1
 * Description :  将8583包解包成为一个数据串str
 * Notice	   :  
 *					
 *=================================================================*/
int  __stdcall  smt_isotostr(unsigned char *dstr, ISO_data *iso)
{
	return m_iso8583.isotostr(dstr,iso);
}

/*=================================================================
 * Function ID :  setbit
 * Input       :  int n,unsigned char *str,int len
 * Output      :  ISO_data * iso
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  success 0 fail -1
 * Description :  将第n域加载到8583包(ISO_data)中.
 * Notice	   :  n->第几个域 str->需要打包的字符串 len->字符串的长度
 *					
 *=================================================================*/
int  __stdcall  smt_setbit(ISO_data * iso,int n,unsigned char *str,int len)
{
	return m_iso8583.setbit(iso,n,str,len);
}

/*=================================================================
 * Function ID :  getbit
 * Input       :  ISO_data *iso, int n
 * Output      :  unsigned char *str
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  success 0 fail -1
 * Description :  从8583包(ISO_data)中取第n域的值
 * Notice	   :  n->第几个域 str->取出的字符串
 *					
 *=================================================================*/
int  __stdcall smt_getbit(ISO_data *iso, int n, unsigned char *str)
{
	return m_iso8583.getbit(iso,n,str);	
}

/*=================================================================
 * Function ID :  smt_clearbit
 * Input       :  ISO_data *iso
 * Output      :  
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  
 * Description :  
 * Notice	   :  将8583包清空
 *					
 *=================================================================*/
void __stdcall smt_clearbit(ISO_data *iso)
{
	m_iso8583.clearbit(iso);
}
/*=================================================================
 * Function ID :  smt_GenMac2
 * Input       :  
 * Output      :  
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  
 * Description :  
 * Notice	   :  计算MAC(银行8583包的MAC运算)
 *					
 *=================================================================*/
unsigned char*  __stdcall smt_MulDesMac(unsigned char *Key,unsigned char *_data,unsigned char len ,unsigned char Result[9])
{
	return m_iso8583.GenMac2(Key,_data,len,Result);
}

/*=================================================================
 * Function ID :  smt_GenMac2
 * Input       :  
 * Output      :  
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  
 * Description :  
 * Notice	   :  计算MAC(银行8583包的MAC运算)
 *					
 *=================================================================*/
unsigned char*  __stdcall smt_GenMac(unsigned char *Key,unsigned char *_data,unsigned char len ,unsigned char Result[9])
{
	return m_iso8583.GenMac1(Key,_data,len,Result);
}

/*=================================================================
 * Function ID :  smt_EDES
 * Input       :  
 * Output      :  
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  success 0 fail -1
 * Description :  
 * Notice	   :  DES加密
 *				key:8字节的加密密钥 inData:8字节的数据 outData:8字节的加密数据结果
 *=================================================================*/
void __stdcall smt_EDES(unsigned char *key,unsigned char *inData,unsigned char *outData)
{
	DES(key,inData,outData);
}

/*=================================================================
 * Function ID :  smt_UDES
 * Input       :  
 * Output      :  
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  success 0 fail -1
 * Description :  
 * Notice	   :  DES解密
 *				key:8字节的加密密钥 inData:8字节的数据 outData:8字节的加密数据结果
 *=================================================================*/
void __stdcall smt_UDES(unsigned char *key,unsigned char *inData,unsigned char *outData)
{
	_DES(key,inData,outData);
}

/*=================================================================
 * Function ID :  smt_ETransKey
 * Input       :  
 * Output      :  
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  
 * Description :  
 * Notice	   :  得到传输密钥密文
 *				TransKey:8字节的传输密钥 ETransKey:8字节的传输密钥密文
 *=================================================================*/
void __stdcall smt_ETransKey(unsigned char *TransKey,unsigned char *ETransKey)
{
	unsigned char key[9];	
	memset(key,0x00,sizeof key);
	memcpy(key,"\xD6\xC7\xBB\xDB\xB5\xE7\xD7\xD3",8); //智慧电子
	DES(key,TransKey,ETransKey);
}

/*=================================================================
 * Function ID :  smt_UTransKey
 * Input       :  
 * Output      :  
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  
 * Description :  
 * Notice	   :  得到传输密钥的明文(该方法不向第三方提供)
 *				 ETransKey:8字节的传输密钥密文TransKey:8字节的传输密钥
 *=================================================================*/
void __stdcall smt_UTransKey(unsigned char *ETransKey,unsigned char *TransKey)
{
	unsigned char key[9];	

	memset(key,0x00,sizeof key);
	memcpy(key,"\xD6\xC7\xBB\xDB\xB5\xE7\xD7\xD3",8); //智慧电子
	_DES(key,ETransKey,TransKey);
}

/*=================================================================
 * Function ID :  smt_GetEWorkKey
 * Input       :  unsigned char *TransKey,unsigned char *WorkKey
 * Output      :  unsigned char *EWorkKey
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  
 * Description :  
 * Notice	   :  用传输密钥加密工作密钥
 *				  TransKey:8字节的传输密钥WorkKey:9字节的工作密钥
 *			   :  加密钥后的工作密钥密文为16字节 EWorkKey
 *=================================================================*/
void __stdcall smt_GetEWorkKey(unsigned char *TransKey,unsigned char *WorkKey,unsigned char *EWorkKey)
{
	unsigned char ucWorkKey[33];	
	unsigned char ucEWorkKey[33];

	memset(ucWorkKey, 0x00,sizeof ucWorkKey);
	memset(ucEWorkKey,0x00,sizeof ucEWorkKey);

	memcpy(ucWorkKey,WorkKey,9);
	memcpy(ucWorkKey+9,"\xAB\xCD\x12\x34\x56\x78\x90",7);
	DES(TransKey,ucWorkKey,ucEWorkKey);
	DES(TransKey,ucWorkKey+8,ucEWorkKey+8);
	memcpy(EWorkKey,ucEWorkKey,16);
}

/*=================================================================
 * Function ID :  smt_GetWorkKey
 * Input       :  unsigned char *TransKey,unsigned char *EWorkKey
 * Output      :  unsigned char *WorkKey
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  
 * Description :  
 * Notice	   :  用传输密钥加密工作密钥
 *				  TransKey:8字节的传输密钥EWorkKey:16字节的工作密钥密文
 *			   :  解密钥后的工作密钥为9字节 WorkKey
 *=================================================================*/
void __stdcall smt_GetWorkKey(unsigned char *TransKey,unsigned char *EWorkKey,unsigned char *WorkKey)
{	
	unsigned char ucWorkKey[33];	

	memset(ucWorkKey,0x00,sizeof ucWorkKey);
	_DES(TransKey,EWorkKey,ucWorkKey);
	_DES(TransKey,EWorkKey+8,ucWorkKey+8);
	memcpy(WorkKey,ucWorkKey,9);
}

/*=================================================================
 * Function ID :  smt_trim
 * Input       :  
 * Output      :  
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  
 * Description :  
 * Notice	   :  去掉str两头的空格
 *				 
 *=================================================================*/
void __stdcall smt_trim(char *str)
{
	CTool mtool;
	mtool.trim(str);
}

/*=================================================================
 * Function ID :  smt_AscToBcd
 * Input       :  BYTE* ucAsc,int ucAscLen
 * Output      :  BYTE* ucBcd
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  
 * Description :  
 * Notice	   :  将ASC码转换为BCD码
 *				 
 *=================================================================*/
BYTE* __stdcall smt_AscToBcd(BYTE* ucAsc,int ucAscLen,BYTE* ucBcd)
{
	CTool mtool;
	return mtool.AscToBcd(ucAsc,ucAscLen,ucBcd);
}

/*=================================================================
 * Function ID :  smt_BcdToAsc
 * Input       :  BYTE* ucBcd,int ucBcdLen
 * Output      :  BYTE* ucAsc
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  
 * Description :  
 * Notice	   :  将BCD码转换为ASC码
 *				 
 *=================================================================*/
BYTE* __stdcall smt_BcdToAsc(BYTE* ucBcd,int ucBcdLen,BYTE* ucAsc)
{
	CTool mtool;
	return mtool.BcdToAsc(ucBcd,ucBcdLen,ucAsc);
}

/*=================================================================
 * Function ID :  smt_IntToHex
 * Input       :  int ndata
 * Output      :  
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  
 * Description :  
 * Notice	   :  将整数转换为4字节的16进制数
 *				 
 *=================================================================*/
char* __stdcall smt_IntToHex(int nData)
{
	CTool mtool;
	return mtool.IntToHex(nData);
}

/*=================================================================
 * Function ID :  smt_HexToInt
 * Input       :  BYTE* HexData,int HexDataLen
 * Output      :  
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  
 * Description :  
 * Notice	   :  将16进制的数转换为十进制数
 *			   :  HexDataLen最长不能大于4
 *				 
 *=================================================================*/
int  __stdcall smt_HexToInt(BYTE* HexData,int HexDataLen)
{
	CTool mtool;
	return mtool.HexToInt(HexData,HexDataLen);	
}