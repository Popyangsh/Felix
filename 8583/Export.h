#ifndef EXPORT__H_
#define EXPORT__H_

#include "iso8583.h"
#include <string.h>
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
int __stdcall smt_strtoiso(unsigned char *dstr, ISO_data *iso);

/*=================================================================
 * Function ID :  isotostr
 * Input       :  ISO_data *iso
 * Output      :  unsigned char *str
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  fail -1
 * Description :  ��8583�������Ϊһ�����ݴ�str
 * Notice	   :  �ɹ�:���ظ����ݴ��ĳ���,ʧ��:����-1
 *					
 *=================================================================*/
int  __stdcall  smt_isotostr(unsigned char *dstr, ISO_data *iso);

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
int  __stdcall  smt_setbit(ISO_data * iso,int n,unsigned char *str,int len);

/*=================================================================
 * Function ID :  getbit
 * Input       :  ISO_data *iso, int n
 * Output      :  unsigned char *str
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  success str len  fail -1
 * Description :  ��8583��(ISO_data)��ȡ��n���ֵ
 * Notice	   :  n->�ڼ����� str->ȡ�����ַ���
 *					
 *=================================================================*/
int  __stdcall smt_getbit(ISO_data *iso, int n, unsigned char *str);
/*=================================================================
 * Function ID :  smt_clearbit
 * Input       :  ISO_data *iso
 * Output      :  
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  
 * Description :  
 * Notice	   :  
 *					
 *=================================================================*/
void __stdcall smt_clearbit(ISO_data *iso);

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
unsigned char*  __stdcall smt_MulDesMac(unsigned char *Key,unsigned char *_data,unsigned char len ,unsigned char Result[9]);

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
unsigned char*  __stdcall smt_GenMac(unsigned char *Key,unsigned char *_data,unsigned char len ,unsigned char Result[9]);

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
void __stdcall smt_UDES(unsigned char *key,unsigned char *inData,unsigned char *outData);
/*=================================================================
 * Function ID :  smt_EDES
 * Input       :  
 * Output      :  
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  success 0 fail -1
 * Description :  
 * Notice	   :  DES����
 *				  key:8�ֽڵļ�����Կ inData:8�ֽڵ����� outData:8�ֽڵļ������ݽ��
 *=================================================================*/
void __stdcall smt_EDES(unsigned char *key,unsigned char *inData,unsigned char *outData);

/*=================================================================
 * Function ID :  smt_UDES
 * Input       :  unsigned char *TransKey
 * Output      :  unsigned char *ETransKey
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  
 * Description :  
 * Notice	   :  �õ�������Կ����
 *				TransKey:8�ֽڵĴ�����Կ ETransKey:8�ֽڵĴ�����Կ����
 *=================================================================*/
void __stdcall smt_ETransKey(unsigned char *TransKey,unsigned char *ETransKey);

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
void __stdcall smt_GetEWorkKey(unsigned char *TransKey,unsigned char *WorkKey,unsigned char *EWorkKey);

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
void __stdcall smt_GetWorkKey(unsigned char *TransKey,unsigned char *EWorkKey,unsigned char *WorkKey);

void __stdcall SMT_Smart_UserDes(unsigned char* InputData,unsigned char* OutputData,char CodeFlag);
void _stdcall  SMT_GenerateWorkingKey(unsigned char *Plain,unsigned char *WorkingKey);
void _stdcall  SMT_Smart_CardDes(unsigned char *AccountNum,unsigned char *SourceKey,unsigned char *PlainPin,unsigned char *CipherData,unsigned char CodeFlag);
#endif


