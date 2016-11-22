#ifndef ISO8583__H_
#define ISO8583__H_

#define MAXBUFFERLEN     2048 /*定义ISO_data结构中最长的缓冲区*/
struct  ISO_8583 /* ISO 8583 Message Structure Definitions */
{              
    int				len;   /* data element max length */
    unsigned char   type;  /* bit0,bit1暂留 */
						   /*bit2:为0时左对齐,为1时右对齐*/
						   /* bit3:为0时BCD码,为1时ASC码*/
							/*type:0,1,2,3三种*/
    unsigned char   flag;  /* length field length: 0--FIX_LEN型 1--LLVAR_LEN型 2--LLLVAR_LEN型*/
};

struct data_element_flag 
{
	short bitf;			/*field map if 1 true  0 false*/
    short len;			/*field length*/
    int   dbuf_addr;	/*field data's start address*/
};


typedef struct  
{
    struct  data_element_flag f[128];
    short   off;
    char    dbuf[MAXBUFFERLEN];
    char    message_id[10];
} ISO_data;

class CISO8583
{
public:
	 char  m_CurDate[30];
	 unsigned long  m_nCtronl;
public:
	CISO8583();
	~CISO8583();

	/********************************************************************
		created:	2016/03/22
		file base:	iso8583
		file ext:	h
		author:		Felix		
		purpose:	将字符串data压入到8583包iso中 [打包]
	*********************************************************************/
	int   strtoiso(unsigned char *data, ISO_data *iso);
	
	/********************************************************************
		created:	2016/03/22
		file base:	iso8583
		file ext:	h
		author:		Felix
		purpose:	将8583包iso解开到data中
	*********************************************************************/
	int   isotostr(unsigned char *data, ISO_data *iso);

	/********************************************************************
		created:	2016/03/22
		file base:	iso8583
		file ext:	h
		author:		Felix
		purpose:    获取某个域的值
	*********************************************************************/
	int   getbit(ISO_data *iso, int, unsigned char *data);

	/********************************************************************
		created:	2016/03/22
		file base:	iso8583
		file ext:	h
		author:		Felix
		purpose:    设置某个域的值
	*********************************************************************/
	int   setbit(ISO_data *iso, int, unsigned char *data, int);
	
	/********************************************************************
		created:	2016/03/22
		file base:	iso8583
		file ext:	h
		author:		Felix
		purpose:    清空iso包
	*********************************************************************/
	void  clearbit(ISO_data *iso);
	/********************************************************************
		created:	2016/03/22
		file base:	iso8583
		file ext:	h
		author:		Felix
		purpose:    Mac
	*********************************************************************/
	unsigned char* GenMac2(unsigned char *Key,unsigned char *_data,unsigned char len ,unsigned char Result[9]);
	unsigned char* GenMac1(unsigned char *Key,unsigned char *_data,unsigned char len ,unsigned char Result[9]);
	void asc_to_bcd(unsigned char *,unsigned  char *, int, unsigned char);
	void bcd_to_asc(unsigned char *,unsigned  char *, int, unsigned char);		
	char* l_trim(char* str);
	char* r_trim(char* str);
	char* trim(char* str);
};
void  DES(unsigned char *key,unsigned char *s_text,unsigned char *d_text);
void _DES(unsigned char *key,unsigned char *s_text,unsigned char *d_text);

#endif

