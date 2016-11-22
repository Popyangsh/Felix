#include <string.h>
#include "quickdes.h"
#include "secure.h"



/*=================================================================
 * Function ID :  GenMacData
 * Input       :  char *_data,char len
 * Output      :  char *_data
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  ����_data�ĳ���
 * Description :  ����Ҫ����MAC�����ݽ��д���
 * Notice	   :  �����8�ı������ں����0x80���������,�ټ����ʵ���0x00;
 *				  �����8�ı������ں����\x80\x00\x00\x00\x00\x00\x00\x00
 *=================================================================*/
int	GenMacData(char *_data, char len)
{
	if(len%8 == 0)
	{
	    memcpy(_data+len,"\x80\0\0\0\0\0\0\0",8);
	    len+=8;
	}
	else
	{
	    _data[len]=(char)0x80;
		len++;
	    if(len%8)
		{
			memset(_data+len,'\0',8-len%8);
			len=len+8-len%8;
	    }
	}
	return len;
}

/*=================================================================
 * Function ID :  genmac
 * Input       :  unsigned char *s_key,unsigned char *random,unsigned int len,
 *				  unsigned char *input_data
 * Output      :  unsigned char *mac
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  void
 * Description :  �ù�����Կ������������MAC1��MAC2(�õ�DES)
 * Notice	   :  һ������³�ʼrandomΪ8���ֽڵ�0x00
 *				  input_data���Ѿ�����PBOC�ļ���Ҫ��������ݵĴ���
 *=================================================================*/
unsigned char* genmac(unsigned char *key,unsigned char *random,unsigned int len,unsigned char *input_data,unsigned char *out_data)
{
    unsigned char tmp[16];
    int i,j;

	memset(tmp, 0x00, sizeof tmp );
    memcpy(tmp,random,8);

    for(i=0;i<(int)len;i+=8)
	{
		for(j=0;j<8;j++)
			if((i+j)<(int)len)
				tmp[j]^=input_data[i+j];	
		DES(key,tmp,tmp);
    }
	
    memcpy(out_data,tmp,8);
    return out_data;
}


/*=================================================================
 * Function ID :  GenMac
 * Input       :  unsigned char *s_key,unsigned int len,
 *				  unsigned char *input_data
 * Output      :  unsigned char *mac
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  void
 * Description :  �ù�����Կ�����MAC1��MAC2(�õ�DES)
 * Notice	   :  input_data���Ѿ�����PBOC�ļ���Ҫ��������ݵĴ���
 *				  	
 *=================================================================*/
unsigned char* GenMac(unsigned char *Key,unsigned char *_data,unsigned char len ,unsigned char Result[8])
{
	int i,j;
	unsigned char tmp[8];

	memset(tmp,0,8);
	for(i=0;i<len;i+=8)
	{
		for(j=0;j<8;j++)
			if((i+j)<len) tmp[j]^=_data[i+j];
		DES(Key,tmp,tmp);
	}
	memcpy(Result,tmp,8);
	return Result;
}

/*=================================================================
 * Function ID :  genmac_3des
 * Input       :  unsigned char *s_key,unsigned char *random,unsigned int len,
 *				  unsigned char *input_data
 * Output      :  unsigned char *mac
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  void
 * Description :  �ù�����Կ������������MAC1��MAC2(��3DES)
 * Notice	   :  һ������³�ʼrandomΪ8���ֽڵ�0x00
 *				  input_data���Ѿ�����PBOC�ļ���Ҫ��������ݵĴ���
 *=================================================================*/
unsigned char* genmac_3des(unsigned char *key,unsigned char *random,unsigned int len,unsigned char *input_data,unsigned char *out_data)
{
	genmac( key, random,len,input_data,out_data);
	_DES( key+8,out_data, out_data);
	DES ( key,  out_data, out_data);	
	return out_data;
}

/*=================================================================
 * Function ID :  triple_des
 * Input       :  unsigned char key[17],unsigned char in_data[9]
 * Output      :  unsigned char out_data[9]
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  void
 * Description :  ��in_data���ݽ���3DES��������
 * Notice	   :  
 *					
 *=================================================================*/
unsigned char* triple_des(unsigned char key[17],unsigned char in_data[9],unsigned char out_data[9])
{
	unsigned char left_name[9];
	unsigned char right_name[9];
	unsigned char tmp_data[9];

	memset(left_name,  0x00, sizeof left_name );
	memset(right_name, 0x00, sizeof right_name);
	memset(tmp_data,   0x00, sizeof tmp_data  );

	memcpy(left_name, key,  8);	
	memcpy(right_name,key+8,8);	
	
	DES(left_name,in_data,out_data   );
	_DES(right_name,out_data,tmp_data);
	DES(left_name,tmp_data,out_data  );

	return out_data;
}

/*=================================================================
 * Function ID :  _triple_des
 * Input       :  unsigned char key[17],unsigned char in_data[9]
 * Output      :  unsigned char out_data[9]
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  void
 * Description :  ��in_data���ݽ���3DES��������
 * Notice	   :  
 *					
 *=================================================================*/
unsigned char* _triple_des(unsigned char key[17],unsigned char in_data[9],unsigned char out_data[9])
{
	unsigned char left_name[9];
	unsigned char right_name[9];
	unsigned char tmp_data[9];

	memset(left_name,  0x00, sizeof left_name );
	memset(right_name, 0x00, sizeof right_name);
	memset(tmp_data,   0x00, sizeof tmp_data  );

	memcpy(left_name, key,  8);	
	memcpy(right_name,key+8,8);	
	
	_DES(left_name,in_data,out_data);
	DES(right_name,out_data,tmp_data);
	_DES(left_name,tmp_data,out_data);

	return out_data;
}

/*=================================================================
 * Function ID :  pboc_diver_key
 * Input       :  unsigned char cardno[9], unsigned char key_in[17]
 * Output      :  unsigned char key_out[17] 
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  void
 * Description :  ����Կ���з�ɢ������Կ
 * Notice	   :  
 *					
 *=================================================================*/
unsigned char* pboc_diver_key ( unsigned char cardno[9], unsigned char key_in[17], unsigned char key_out[17] )
{
	int i;
	unsigned char tmp1[20], tmp2[20];	
	unsigned char ret1[20], ret2[20];	

	memset(tmp1, 0x00, sizeof tmp1 );
	memset(tmp2, 0x00, sizeof tmp2 );
	memset(ret1, 0x00, sizeof ret1 );
	memset(ret2, 0x00, sizeof ret2 );

	memcpy ( tmp1, cardno, 8 );
	for( i=0; i<8; i++) 
	{
		tmp2[i]=~tmp1[i];
	}

	triple_des ( key_in, tmp1, ret1 );
	triple_des ( key_in, tmp2, ret2 );
	memcpy ( key_out,   ret1, 8 );
	memcpy ( key_out+8, ret2, 8 );
	return key_out;
}

/*=================================================================
 * Function ID :  pboc_session_key
 * Input       :  uchar cardno[9],uchar M_key[17],uchar in_data[9]
 * Output      :  uchar session_key[9](�õ�������Կ)
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  
 * Description :  ���������Կ
 * Notice	   :  
 *					
 *=================================================================*/
unsigned char* pboc_session_key(unsigned char cardno[9],unsigned char M_key[17],unsigned char in_data[9],unsigned char session_key[9])
{
	unsigned char s_key[17];
	unsigned char *p=NULL;

	memset(s_key, 0x00, sizeof s_key );
	if( strlen((char*)cardno) < 8 || strlen((char*)M_key) <16  || strlen((char*)in_data)<8 )
	{
		return p;
	}
	pboc_diver_key ( cardno, M_key, s_key );
	triple_des( s_key, in_data, session_key );
	return session_key;
}

/*=================================================================
 * Function ID :  SingleMACVB
 * Input       :  unsigned char *s_key,unsigned char *random,unsigned int len
 *				  unsigned char *input_data
 * Output      :  unsigned char *mac
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  void
 * Description :  ��������MAC�����ݰ�8�ı������д���
 *				  ���ù�����Կ�����MAC1��MAC2(�õ�DES)
 * Notice	   :  һ������³�ʼrandomΪ8���ֽڵ�0x00
 *					
 *=================================================================*/
unsigned char* SingleMACVB(unsigned char *s_key,unsigned char *random,unsigned int len,unsigned char *input_data,unsigned char *mac)
{
	int			  s_len=0;
	unsigned char MacData[2048];

	memset( MacData, 0x00, sizeof MacData);
	memcpy( MacData, input_data,  len    );

	s_len = GenMacData((char*)MacData,len);
	genmac(s_key,random,s_len,MacData,mac);
	if( strlen((char*)mac) > 4 )
	{
		memset(mac+4,0x00, strlen((char*)mac)-4);
	}
	return mac;
}


/*=================================================================
 * Function ID :  TripleMACVB
 * Input       :  unsigned char *s_key,unsigned char *random,unsigned int len
 *				  unsigned char *input_data
 * Output      :  unsigned char *mac
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  void
 * Description :  ��������MAC�����ݰ�8�ı������д���
 *				  ���ù�����Կ�����MAC1��MAC2(��3DES)
 * Notice	   :  һ������³�ʼrandomΪ8���ֽڵ�0x00
 *					
 *=================================================================*/
unsigned char* TripleMACVB(unsigned char *s_key,unsigned char *random,unsigned int len,unsigned char *input_data,unsigned char *mac)
{
	int			  s_len=0;
	unsigned char MacData[2048];

	memset( MacData, 0x00, sizeof MacData);
	memcpy( MacData, input_data,  len    );

	s_len = GenMacData((char*)MacData,len);
	genmac_3des(s_key,random,s_len,MacData,mac);
	if( strlen((char*)mac) > 4 )
	{
		memset(mac+4,0x00, strlen((char*)mac)-4);
	}
	return mac;
}

int HexToInt(char* HexData, int len)
{
	static int data;
	data = 0;
	
	if( len > 4 || len == 0  ) return data;
	if( len ==1 )
	{
		data = *HexData&0xF0+*HexData&0x0F;
	}
	else if( len == 2 )
	{
		data+= ((*HexData>>4)*16+(*HexData&0x0F))*16*16;
		HexData++;
		data+= (*HexData>>4)*16+(*HexData&0x0F);
	}
	else if( len == 3 )
	{
		data+= ((*HexData>>4)*16+(*HexData&0x0F))*16*16*16*16;
		HexData++;
		data+= ((*HexData>>4)*16+(*HexData&0x0F))*16*16;
		HexData++;
		data+= (*HexData>>4)*16+(*HexData&0x0F);
	}
	else if( len == 4 )
	{
		data+= ((*HexData>>4)*16+(*HexData&0x0F))*16*16*16*16*16*16;
		HexData++;
		data+= ((*HexData>>4)*16+(*HexData&0x0F))*16*16*16*16;
		HexData++;
		data+= ((*HexData>>4)*16+(*HexData&0x0F))*16*16;
		HexData++;
		data+= (*HexData>>4)*16+(*HexData&0x0F);
	}
	return data;
}





