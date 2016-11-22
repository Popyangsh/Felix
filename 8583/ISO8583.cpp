#include "iso8583.h"
#include "def8583.h"
#include <string.h>
#include <ctype.h>
#include "stdlib.h"
#include <iostream>
#include "quickdes.h"
#include "tool.h"

#define		NCONTRL		"\x01\x32\x8F\xB1"
CISO8583::CISO8583()
{
	CTool mTool;
	memset(m_CurDate,0,sizeof m_CurDate);
	memcpy(m_CurDate,mTool.GetSysTime(),8);
	m_nCtronl=atol(m_CurDate);
}

CISO8583::~CISO8583()
{
	
}
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
int CISO8583::strtoiso(unsigned char *dstr, ISO_data *iso)
{
	unsigned char	*rpt=NULL, bitmask=0;
	unsigned char	i=0,j=0,n=0,bitnum=0;
	int				off=0, len=0, k=0;
	unsigned char   ucLen[10];

	memset(ucLen,0x00,sizeof ucLen);

	/* Initialize the iso->f[].bitf */
	clearbit(iso);		
	/* Get Message ID */
	bcd_to_asc( (unsigned char*)iso->message_id,dstr,4,0 );
	iso->message_id[4]=0x00;
	bitnum=8;
	/* initialize <rpt> point to data elements */
	rpt = dstr+2+bitnum;

	/* copy dstr elements to iso */
	for(i = 0; i<bitnum; i++) 
	{
		bitmask = 0x80;
		for(j = 0; j < 8; j++, bitmask>>=1) 
		{
			if (i==0 && bitmask==0x80)
			{
				continue;
			}
			if ((dstr[i+2] & bitmask)==0)
			{
				continue;
			}
			n = (i<<3) +j;

			/*1.计算相应域的数据的长度 */
			if( iso8583[n].flag == LLVAR_LEN) /*1位可变长*/
			{
				memset(ucLen,0x00,sizeof ucLen);
				bcd_to_asc( ucLen,rpt,2,0 );
				len = atol((char*)ucLen);
				rpt++;
			}
			else if( iso8583[n].flag == LLLVAR_LEN) 
			{
				memset(ucLen,0x00,sizeof ucLen);
				bcd_to_asc( ucLen,rpt,4,0 );
				len = atol((char*)ucLen);
				rpt+=2;
			}
			else if( iso8583[n].flag == FIX_LEN) 
			{
				len = iso8583[n].len;
			}
			iso->f[n].len		= len;
			iso->f[n].dbuf_addr = off;
			if( len+off >= 1024 )
			{
				return-1;
			}
			/*1 将相应域的值放入到8583包 */
			if( iso8583[n].type ==L_BCD ) 
			{
				len = (len+1)/2;
				memcpy(&iso->dbuf[off],rpt,len);
			}
			else if( iso8583[n].type ==L_ASC ) 
			{
				memcpy(&iso->dbuf[off],rpt,len);
			}
			else if( iso8583[n].type ==R_BCD ) 
			{
				len = (len+1)/2;
				memcpy(&iso->dbuf[off],rpt,len);
			}
			else if( iso8583[n].type ==R_ASC ) 
			{
				memcpy(&iso->dbuf[off],rpt,len);
			}
			iso->f[n].bitf=1;
			off+=len;
			rpt+=len;
		}
	}
	iso->off = off;
	return 0;
}

/*=================================================================
 * Function ID :  isotostr
 * Input       :  ISO_data *iso
 * Output      :  unsigned char *str
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  
 * Description :  将8583包解包成为一个数据串str
 * Notice	   :  成功:返回该数据串的长度,失败:返回-1
 *					
 *=================================================================*/
int  CISO8583::isotostr(unsigned char *dstr, ISO_data *iso)
{
	unsigned char   *wpt=NULL, bitmask=0, bitmap=0,str[10],tmp[10];
	int				k=0, lc=0;
	unsigned char	i=0,j=0,n=0,bitnum=0;

	memset(tmp, 0x00, sizeof tmp );
	asc_to_bcd(dstr,(unsigned char*)iso->message_id,4,0);
	bitnum = 8;
	
	//检查8583包是64域还是128域
	if( bitnum != 16)
	{
		bitnum = 8;  
	}
	/* wpt是指向bitmap后具体内容的指针 */
	wpt = dstr+2+bitnum;    

	/* copy iso elements to dstr */
	for(i=0; i<bitnum; i++) 
	{
		/*变量bitmap表示8个位图域*/
		bitmap  = 0; 
		bitmask = 0x80; 
		for( j=0; j<8; j++, bitmask>>=1 ) 
		{
			n = (i<<3) + j;
			if (iso->f[n].bitf==0)
			{
				continue; /*表示该域没有值*/
			}
			bitmap |= bitmask;

			lc = iso->f[n].len;                         
			if( iso8583[n].flag==LLVAR_LEN ) /*存放VARII型长度*/
			{			
				memset(str, 0x00, sizeof str );
				sprintf((char*)str,"%02ld",lc);
				asc_to_bcd(wpt,str,2,0);
				wpt++;				
			} 
			else if(iso8583[n].flag==LLLVAR_LEN) /*存放VARIII型长度*/
			{
				memset(str, 0x00, sizeof str );
				sprintf((char*)str,"%04ld",lc);
				asc_to_bcd(wpt,str,4,0);
				wpt+=2;
			}       
			
			k=0;
			if( iso8583[n].type == 0 )	/*左对齐BCD码*/
			{
				lc=(lc+1)/2;
			}
			else if( iso8583[n].type == 1 )  /*左对齐ASC*/
			{
				lc = lc;
			}
			else if( iso8583[n].type == 2 )	/*右对齐BCD码*/
			{
				lc=(lc+1)/2;
			}
			else if( iso8583[n].type == 3 )	/*右对齐ASC码*/
			{
				lc = lc;
			}
			else							/*目前不支持*/
			{
				dstr=NULL;
				return -1;
			}
			memcpy(wpt,&(iso->dbuf[iso->f[n].dbuf_addr]),lc);				
			wpt+=lc;
		}
		dstr[i+2]=bitmap;
	}

	if( iso->f[127].bitf&&bitnum == 8 )  /* 存放 MAC */
	{  
		dstr[bitnum+1]|=0x01;
		memcpy(wpt, &iso->dbuf[iso->f[127].dbuf_addr], 8);
		wpt+=8;
	}
	if (bitnum==16) dstr[2] |= 0x80;        /* 置MAC的bitmap */
	return wpt-dstr;
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
int  CISO8583::setbit(ISO_data * iso,int n,unsigned char *str,int len)
{
	int  i=0, l=0;
	unsigned char *pt=NULL, tmp[MAXBUFFERLEN];
	
	memset(tmp,0x00, sizeof tmp );
	
	if( len==0 )
	{
		return 0; //str为空,不需要打包
	}
	if( n==0   ) 
	{
		memcpy( iso->message_id, str, 4);
		iso->message_id[4]=0x00;
		return 0;
	}
	//第1域为位图域,不能用
	if (n<=1 || n>128)
	{
		return -1;	
	}
	n--;
	//最大长度不能超过8583包规定的长度
	if( len > iso8583[n].len )	
	{
		len = iso8583[n].len;
	}
	l=len;
	if( iso8583[n].flag==FIX_LEN ) //该域为固定长度
	{
		len=iso8583[n].len;
	}	
	iso->f[n].len		= len;		/*保存该域的长度*/
	iso->f[n].bitf		= 1;		/*置该域为有值*/
	iso->f[n].dbuf_addr	= iso->off;	/*该域值在dbuf中的起始位置*/

	pt=(unsigned char*)&(iso->dbuf[iso->off]);
	//dbuf的空间已经满
	if( (iso->off+len) >= MAXBUFFERLEN )
	{
		return -1;
	}	
	if( iso8583[n].type==0 ) //左对齐  BCD码
	{   
		memcpy(tmp,str,l);
		memset(tmp+l,' ',len-l);		
		asc_to_bcd(pt, tmp, len, 0);
		iso->off+=(len+1)/2;
	}
	else if( iso8583[n].type==1 ) //左对齐  ASC码
	{
		memcpy(tmp,str,l);
		memset(tmp+l,' ',len-l);		
		memcpy(pt,tmp,len);
		iso->off+=len;
	}
	else if( iso8583[n].type==2 ) //右对齐  BCD码
	{
		memset(tmp,'0',len-l);		
		memcpy(tmp+len-l,str,l);
		asc_to_bcd(pt, tmp, len, 0);		
		iso->off+=(len+1)/2;
	}
	else if( iso8583[n].type==3 ) //右对齐  ASC码
	{		
		memset(tmp,' ',len-l);
		memcpy(tmp+len-l,str,l);
		memcpy(pt,tmp,len);
		iso->off+=len;
	}
	return 0;
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
int  CISO8583::getbit(ISO_data *iso, int n, unsigned char *str)
{
	int			  len=0;
	unsigned char *pt=NULL;

	if( n==0 ) 
	{
		memcpy(str, iso->message_id,4);
		str[4]='\0';
		len = 4;
		return len;
	}
	if( n<=1 || n>128 )	return -1;	
	n--;
	if( iso->f[n].bitf==0 ) 
	{
		if( n==127 )
		{
			if (iso->f[63].bitf==0)	return -1;
		}
		str[0] = 0x00;
		return -1;
	}
	pt  = (unsigned char*) &iso->dbuf[iso->f[n].dbuf_addr];
	len = iso->f[n].len;

	if( iso8583[n].type==0 ) //左对齐  BCD码
	{   
		bcd_to_asc(str,pt,len,0);		
	}
	else if( iso8583[n].type==1 ) //左对齐  ASC码
	{
		memcpy(str,pt,len);				
	}
	else if( iso8583[n].type==2 ) //右对齐  BCD码
	{
		bcd_to_asc(str,pt,len,0);			
	}
	else if( iso8583[n].type==3 ) //右对齐  ASC码
	{
		memcpy(str,pt,len);		
	}
	else
	{
		str = NULL;	//目前还不支持这种类型
		return -1;
	}
	trim((char*)str);
	str[len]=0x00;;
	return len;
}


/*=================================================================
 * Function ID :  clearbit
 * Input       :  ISO_data *iso
 * Output      :  void
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  
 * Description :  清空8583包
 * Notice	   :  
 *					
 *=================================================================*/
void  CISO8583::clearbit(ISO_data *iso)
{
	int i;
	for (i=0; i<128; i++)
	{
		iso->f[i].bitf=0;
	}
	iso->off=0;
}

/*=================================================================
 * Function ID :  asc_to_bcd
 * Input       :  unsigned char *ascii_buf, int conv_len, unsigned char type
 * Output      :  unsigned char *bcd_buf
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  void
 * Description :  
 * Notice	   :  将ASC码压缩为BCD码
 *					
 *=================================================================*/
void CISO8583::asc_to_bcd(unsigned char *bcd_buf, unsigned char *ascii_buf, int conv_len, unsigned char type)
{
	int    cnt;
	char   ch, ch1;

	if (conv_len&0x01 && type ) ch1=0;
	else ch1=0x55;
	for (cnt=0; cnt<conv_len; ascii_buf++, cnt++) 
	{
		if (*ascii_buf >= 'a' ) ch = *ascii_buf-'a' + 10;
		else if ( *ascii_buf >= 'A' ) ch =*ascii_buf- 'A' + 10;
		     else if ( *ascii_buf >= '0' ) ch =*ascii_buf-'0';
			  else ch = 0;
		if (ch1==0x55) ch1=ch;
		else {
			*bcd_buf++=( ch1<<4 )| ch;
			ch1=0x55;
		}
	}
	if (ch1!=0x55) *bcd_buf=ch1<<4;
}


/*=================================================================
 * Function ID :  bcd_to_asc
 * Input       :  unsigned char * bcd_buf, int conv_len, unsigned char type
 * Output      :  unsigned char *ascii_buf
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  void
 * Description :  
 * Notice	   :  将BCD码扩展为ASC码
 *					
 *=================================================================*/
void CISO8583::bcd_to_asc(unsigned char *ascii_buf,unsigned char * bcd_buf, int conv_len, unsigned char type)
{
    int cnt=0;

    if (conv_len&0x01 && type) {cnt=1; conv_len++;}
    else cnt=0;
    for (; cnt<conv_len; cnt++, ascii_buf++){
	*ascii_buf = ((cnt&0x01) ? (*bcd_buf++&0x0f) : (*bcd_buf>>4));
	*ascii_buf += ((*ascii_buf>9) ? ('A'-10) : '0');
    }
}

/*=================================================================
 * Function ID :  l_trim
 * Input       :  char* str
 * Output      :  char* str
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  str
 * Description :  
 * Notice	   :  去掉字符串左边的空格
 *					
 *=================================================================*/
char* CISO8583::l_trim(char* str)
{
	char buf[2048];
	int  i=0,len=0;	

	memset(buf, 0x00, sizeof buf );
	strcpy(buf, str);	
	memset(str, 0x00, strlen(str) );
	len = strlen(buf);
	for(i=0; i<len; i++)
	{
		if( buf[i] !=' ')
			break;		
	}
	memcpy(str,buf+i,len-i);
	return str;
}

/*=================================================================
 * Function ID :  r_trim
 * Input       :  char* str
 * Output      :  char* str
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  str
 * Description :  
 * Notice	   :  去掉字符串右边的空格
 *					
 *=================================================================*/
char* CISO8583::r_trim(char* str)
{
	char buf[2048];
	int	 len;	

	memset(buf,0x00,sizeof buf);
	strcpy(buf,str);
	len = strlen(str);
	while(len)
	{
		if( buf[len] != ' ' )
		{
			break;
		}
		len--;
	}
	memset(str,0x00, strlen(str));
	memcpy(str,buf,len);
	return str;
}

/*=================================================================
 * Function ID :  trim
 * Input       :  char* str
 * Output      :  char* str
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  str
 * Description :  
 * Notice	   :  去掉字符串左右两边的空格
 *					
 *=================================================================*/
char* CISO8583::trim(char* str)
{
	r_trim(str);
	l_trim(str);
	return str;
}

/*=================================================================
 * Function ID :  GenMac2
 * Input       :  
 * Output      :  
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  
 * Description :  
 * Notice	   :  银行报文MAC2算法
 *					
 *=================================================================*/
unsigned char* CISO8583::GenMac2(unsigned char *Key,unsigned char *_data,unsigned char len ,unsigned char Result[9])
{
	int i,j;
	unsigned char tmp[9],data[512];
	
	memset(tmp,  0x00,sizeof tmp);
	memset(data, 0x00, sizeof data);

	memcpy(data,_data,len);
	if( (i=len%8) )
	{
		i=8-i;
		memcpy(data+len,tmp,i);
		len=len+i;
	}		
	memcpy(tmp,_data,8);
	DES(Key,tmp,tmp);
	len=len-8;	
	for(i=0;i<len;i+=8)
	{
		for(j=0;j<8;j++)
		{
			if((i+j)<len)
			{
				tmp[j]^=data[i+j];
			}
		}
		DES(Key,tmp,tmp);
	}
	memcpy(Result,tmp,8);
	return Result;
}

/*=================================================================
 * Function ID :  GenMac2
 * Input       :  
 * Output      :  
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  
 * Description :  
 * Notice	   :  银行报文MAC1算法
 *					
 *=================================================================*/
unsigned char* CISO8583::GenMac1(unsigned char *Key,unsigned char *_data,unsigned char len ,unsigned char Result[9])
{
	int i,j;
	unsigned char tmp[9],data[512];	
	unsigned char tmpH[17] ={0};
	memset(tmp,  0x00,sizeof tmp);
	memset(data, 0x00, sizeof data);

	memcpy(data,_data,len);
	if( (i=len%8) )
	{
		i=8-i;
		memcpy(data+len,tmp,i);
		len=len+i;
	}	
	memcpy(tmp,data,8);	
	len=len-8;	
	for(i=0;i<len;i+=8)
	{
		for(j=0;j<8;j++)
		{
			if((i+j)<len)
			{
				tmp[j]^=data[i+j];
			}
		}		
	}
	sprintf((char *)tmpH,"%02X%02X%02X%02X%02X%02X%02X%02X",tmp[0],tmp[1],tmp[2],tmp[3],tmp[4],tmp[5],tmp[6],tmp[7]);
	memcpy(tmp,tmpH,8);
	DES(Key,tmp,tmp);
	memcpy(Result,tmp,8);
	return Result;
}
