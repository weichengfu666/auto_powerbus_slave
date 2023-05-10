#include "main.h"

uchar CRC_L=0,CRC_H=0;

void crc16(unsigned char *ptr,unsigned int len,uchar CRC_GuangBo) 
{ 
    int CRC_i=0,CRC_j=0;								//������� 
    unsigned long CRC_wcrc=0XFFFF;	//Ԥ��16λcrc�Ĵ�������ֵȫ��Ϊ1 
    unsigned char CRC_temp;					//�����м���� 
    uchar CRC_HuanCun[2];
    
	CRC_wcrc=0XFFFF;
	CRC_i=0;
	if(CRC_GuangBo==0)
	{
		CRC_HuanCun[0]=IapReadByte(0x0000);
		CRC_HuanCun[1]=IapReadByte(0x0001);
	}else if(CRC_GuangBo==1)
	{
		CRC_HuanCun[0]=0xff;
		CRC_HuanCun[1]=0xff;
	}else{
		CRC_i=2;
	}	
	for(;CRC_i<len+2;CRC_i++)					//ѭ������ÿ������ 
	{ 
		if(CRC_i<2)
		{
			CRC_temp=CRC_HuanCun[CRC_i]&0X00FF;
		}else{
			CRC_temp=*ptr&0X00FF;					//����λ������crc�Ĵ������ 
			ptr++;												//ָ���ַ���ӣ�ָ���¸����� 
		}
		CRC_wcrc^=CRC_temp;						//�����ݴ���crc�Ĵ��� 
		for(CRC_j=0;CRC_j<8;CRC_j++)	//ѭ���������ݵ� 
		{ 
			if(CRC_wcrc&0X0001)					//�ж����Ƴ����ǲ���1�������1�������ʽ������� 
			{ 
				CRC_wcrc>>=1;							//�Ƚ���������һλ 
				CRC_wcrc^=0XA001;					//������Ķ���ʽ������� 
			}else{											//�������1����ֱ���Ƴ� 
			 	CRC_wcrc>>=1;							//ֱ���Ƴ� 
			} 
		} 
	} 
	CRC_temp=CRC_wcrc;							//crc��ֵ 
	CRC_L=CRC_wcrc;									//crc�ĵͰ�λ 		 
	CRC_H=CRC_wcrc>>8;							//crc�ĸ߰�λ 
}		
