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
 * Description :  将按8583包格式的数据串装载到8583包中
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
 * Description :  将8583包解包成为一个数据串str
 * Notice	   :  成功:返回该数据串的长度,失败:返回-1
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
 * Description :  将第n域加载到8583包(ISO_data)中.
 * Notice	   :  n->第几个域 str->需要打包的字符串 len->字符串的长度
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
 * Description :  从8583包(ISO_data)中取第n域的值
 * Notice	   :  n->第几个域 str->取出的字符串
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
 * Notice	   :  计算MAC(银行8583包的MAC运算)
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
 * Notice	   :  计算MAC(银行8583包的MAC运算)
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
 * Notice	   :  DES解密
 *				key:8字节的加密密钥 inData:8字节的数据 outData:8字节的加密数据结果
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
 * Notice	   :  DES加密
 *				  key:8字节的加密密钥 inData:8字节的数据 outData:8字节的加密数据结果
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
 * Notice	   :  得到传输密钥密文
 *				TransKey:8字节的传输密钥 ETransKey:8字节的传输密钥密文
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
 * Notice	   :  用传输密钥加密工作密钥
 *				  TransKey:8字节的传输密钥WorkKey:9字节的工作密钥
 *			   :  加密钥后的工作密钥密文为16字节 EWorkKey
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
 * Notice	   :  用传输密钥加密工作密钥
 *				  TransKey:8字节的传输密钥EWorkKey:16字节的工作密钥密文
 *			   :  解密钥后的工作密钥为9字节 WorkKey
 *=================================================================*/
void __stdcall smt_GetWorkKey(unsigned char *TransKey,unsigned char *EWorkKey,unsigned char *WorkKey);

void __stdcall SMT_Smart_UserDes(unsigned char* InputData,unsigned char* OutputData,char CodeFlag);
void _stdcall  SMT_GenerateWorkingKey(unsigned char *Plain,unsigned char *WorkingKey);
void _stdcall  SMT_Smart_CardDes(unsigned char *AccountNum,unsigned char *SourceKey,unsigned char *PlainPin,unsigned char *CipherData,unsigned char CodeFlag);
#endif


