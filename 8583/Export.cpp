
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
 * Description :  ����8583����ʽ�����ݴ�װ�ص�8583����
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
 * Description :  ��8583�������Ϊһ�����ݴ�str
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
 * Description :  ����n����ص�8583��(ISO_data)��.
 * Notice	   :  n->�ڼ����� str->��Ҫ������ַ��� len->�ַ����ĳ���
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
 * Description :  ��8583��(ISO_data)��ȡ��n���ֵ
 * Notice	   :  n->�ڼ����� str->ȡ�����ַ���
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
 * Notice	   :  ��8583�����
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
 * Notice	   :  ����MAC(����8583����MAC����)
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
 * Notice	   :  ����MAC(����8583����MAC����)
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
 * Notice	   :  DES����
 *				key:8�ֽڵļ�����Կ inData:8�ֽڵ����� outData:8�ֽڵļ������ݽ��
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
 * Notice	   :  DES����
 *				key:8�ֽڵļ�����Կ inData:8�ֽڵ����� outData:8�ֽڵļ������ݽ��
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
 * Notice	   :  �õ�������Կ����
 *				TransKey:8�ֽڵĴ�����Կ ETransKey:8�ֽڵĴ�����Կ����
 *=================================================================*/
void __stdcall smt_ETransKey(unsigned char *TransKey,unsigned char *ETransKey)
{
	unsigned char key[9];	
	memset(key,0x00,sizeof key);
	memcpy(key,"\xD6\xC7\xBB\xDB\xB5\xE7\xD7\xD3",8); //�ǻ۵���
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
 * Notice	   :  �õ�������Կ������(�÷�������������ṩ)
 *				 ETransKey:8�ֽڵĴ�����Կ����TransKey:8�ֽڵĴ�����Կ
 *=================================================================*/
void __stdcall smt_UTransKey(unsigned char *ETransKey,unsigned char *TransKey)
{
	unsigned char key[9];	

	memset(key,0x00,sizeof key);
	memcpy(key,"\xD6\xC7\xBB\xDB\xB5\xE7\xD7\xD3",8); //�ǻ۵���
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
 * Notice	   :  �ô�����Կ���ܹ�����Կ
 *				  TransKey:8�ֽڵĴ�����ԿWorkKey:9�ֽڵĹ�����Կ
 *			   :  ����Կ��Ĺ�����Կ����Ϊ16�ֽ� EWorkKey
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
 * Notice	   :  �ô�����Կ���ܹ�����Կ
 *				  TransKey:8�ֽڵĴ�����ԿEWorkKey:16�ֽڵĹ�����Կ����
 *			   :  ����Կ��Ĺ�����ԿΪ9�ֽ� WorkKey
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
 * Notice	   :  ȥ��str��ͷ�Ŀո�
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
 * Notice	   :  ��ASC��ת��ΪBCD��
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
 * Notice	   :  ��BCD��ת��ΪASC��
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
 * Notice	   :  ������ת��Ϊ4�ֽڵ�16������
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
 * Notice	   :  ��16���Ƶ���ת��Ϊʮ������
 *			   :  HexDataLen����ܴ���4
 *				 
 *=================================================================*/
int  __stdcall smt_HexToInt(BYTE* HexData,int HexDataLen)
{
	CTool mtool;
	return mtool.HexToInt(HexData,HexDataLen);	
}