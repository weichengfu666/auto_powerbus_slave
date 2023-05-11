#include "main.h"		 

WORD EEPROM_Write_n_i=0;
uchar EEPROM_Write_HuanCun[32];
uint addr2=0,EEPROM_Write_i=0,EEPROM_Write_j=0;

void IapIdle()
{
	IAP_CONTR = 0;                              
	IAP_CMD = 0;                               
	IAP_TRIG = 0;                        
	IAP_ADDRH = 0x80;                    
	IAP_ADDRL = 0;
}	  
/*----------------------------
��ISP/IAP/EEPROM�����ȡһ�ֽ�
----------------------------*/
BYTE IapReadByte(WORD addr)
{
	addr += IAP_OFFSET; // 
	return *(char code *)(addr); // 
}
/*----------------------------
дһ�ֽ����ݵ�ISP/IAP/EEPROM����
----------------------------*/
void IapProgramByte(WORD addr, BYTE dat)
{
	IAP_CONTR = 0x80;         			//ʹ��IAP
	IAP_TPS = 24;
	IAP_CMD = 2;          					//����IAP����
	IAP_ADDRL = addr;               //����IAP�͵�ַ
	IAP_ADDRH = addr >> 8;          //����IAP�ߵ�ַ
	IAP_DATA = dat;                 //дISP/IAP/EEPROM����
	IAP_TRIG = 0x5a;                //д��������(0x5a)
	IAP_TRIG = 0xa5;                //д��������(0xa5)
	_nop_();                        //�ȴ�ISP/IAP/EEPROM�������
	IapIdle();
}
/*----------------------------
��������
----------------------------*/
void IapEraseSector(WORD addr)
{
	IAP_CONTR = 0x80;         //ʹ��IAP
	IAP_TPS = 24;
	IAP_CMD = 3;            //����IAP����
	IAP_ADDRL = addr;               //����IAP�͵�ַ
	IAP_ADDRH = addr >> 8;          //����IAP�ߵ�ַ
	IAP_TRIG = 0x5a;                //д��������(0x5a)
	IAP_TRIG = 0xa5;                //д��������(0xa5)
	_nop_();                        //�ȴ�ISP/IAP/EEPROM�������
	IapIdle();
}
/*----------------------------
д���ַ�����EEPROM
----------------------------*/
void EEPROM_Write_Str(WORD addr,BYTE dat[],WORD dat_Len)
{
	if(addr%512==0)
		IapEraseSector(addr);
	for(EEPROM_Write_i=0;EEPROM_Write_i<dat_Len;EEPROM_Write_i++)
	{
//	  WDT_CONTR=0x3d;//���Ź�
		IapProgramByte(addr+EEPROM_Write_i,dat[EEPROM_Write_i]);		
	}
}

//void EEPROM_Read_Str(WORD addr)
//{
//	for(EEPROM_Write_i=0;EEPROM_Write_i<32;EEPROM_Write_i++)
//	{
//		Sendnum(EEPROM_Write_i+1);
//		SendData(':');
//		for(EEPROM_Write_j=0;EEPROM_Write_j<16;EEPROM_Write_j++)
//		{
//			WDT_CONTR=0x3d;
//			SendData(' ');
//			Sendnum(IapReadByte(addr+EEPROM_Write_i*16+EEPROM_Write_j));
//		}
//		SendData(13);
//		SendData(10);
//	}
//}
