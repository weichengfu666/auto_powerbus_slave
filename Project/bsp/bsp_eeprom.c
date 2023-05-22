#include "main.h"		 

u16 EEPROM_Write_n_i=0;
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
u8 IapReadByte(u16 addr)
{
	addr += IAP_OFFSET; // 
	return *(char code *)(addr); // 
}
/*----------------------------
дһ�ֽ����ݵ�ISP/IAP/EEPROM����
----------------------------*/
void IapProgramByte(u16 addr, u8 dat)
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
����������������Ϊ0xFF
----------------------------*/
void IapEraseSector(u16 addr)
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
void EEPROM_Write_Str(u16 addr,u8 dat[],u16 dat_Len)
{
	if(addr%512==0)
		IapEraseSector(addr);
	for(EEPROM_Write_i=0;EEPROM_Write_i<dat_Len;EEPROM_Write_i++)
	{
		IapProgramByte(addr+EEPROM_Write_i,dat[EEPROM_Write_i]);		
	}
}

void EEPROM_Read_Str(u16 addr,u8 dat[],u16 dat_Len)
{
    u16 i = 0;
    for(i = 0; i < dat_Len; i++)
    {
        dat[i] = IapReadByte(addr + i);
    }
}
