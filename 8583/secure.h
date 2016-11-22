/*=================================================================
 * Function ID :  GenMacData
 * Input       :  char *_data,char len
 * Output      :  char *_data
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  ����_data�ĳ���
 * Description :  ����Ҫ����MAC�����ݽ��д���
 * Notice	   :  
 *					
 *=================================================================*/
int	GenMacData(char *_data, char len);
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
 *					
 *=================================================================*/
unsigned char* genmac(unsigned char *key,unsigned char *random,unsigned int len,unsigned char *input_data,unsigned char *out_data);
/*=================================================================
 * Function ID :  GenMac
 * Input       :  unsigned char *s_key,unsigned int len,
 *				  unsigned char *input_data
 * Output      :  unsigned char *mac
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  void
 * Description :  �ù�����Կ�����MAC1��MAC2(�õ�DES)
 * Notice	   :  
 *					
 *=================================================================*/
unsigned char* GenMac(unsigned char *Key,unsigned char *_data,unsigned char len ,unsigned char Result[8]);
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
 *					
 *=================================================================*/
unsigned char* genmac_3des(unsigned char *key,unsigned char *random,unsigned int len,unsigned char *input_data,unsigned char *out_data);
/*=================================================================
 * Function ID :  triple_des
 * Input       :  unsigned char key[17],unsigned char in_data[9]
 * Output      :  unsigned char out_data[9]
 * Author      :  Felix
 * Date        :  Dec  12  2015
 * Return	   :  void
 * Description :  ��in_data���ݽ���3DES����
 * Notice	   :  
 *					
 *=================================================================*/
unsigned char* triple_des(unsigned char key[17],unsigned char in_data[9],unsigned char out_data[9]);
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
unsigned char* _triple_des(unsigned char key[17],unsigned char in_data[9],unsigned char out_data[9]);

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
unsigned char* pboc_diver_key ( unsigned char cardno[9], unsigned char key_in[17], unsigned char key_out[17] );
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
unsigned char* pboc_session_key(unsigned char cardno[9],unsigned char M_key[17],unsigned char in_data[9],unsigned char session_key[9]);
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
unsigned char* SingleMACVB(unsigned char *s_key,unsigned char *random,unsigned int len,unsigned char *input_data,unsigned char *mac);
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
unsigned char* TripleMACVB(unsigned char *s_key,unsigned char *random,unsigned int len,unsigned char *input_data,unsigned char *mac);

