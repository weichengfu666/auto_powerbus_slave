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
从ISP/IAP/EEPROM区域读取一字节
----------------------------*/
u8 IapReadByte(u16 addr)
{
	addr += IAP_OFFSET; // 
	return *(char code *)(addr); // 
}
/*----------------------------
写一字节数据到ISP/IAP/EEPROM区域
----------------------------*/
void IapProgramByte(u16 addr, u8 dat)
{
	IAP_CONTR = 0x80;         			//使能IAP
	IAP_TPS = 24;
	IAP_CMD = 2;          					//设置IAP命令
	IAP_ADDRL = addr;               //设置IAP低地址
	IAP_ADDRH = addr >> 8;          //设置IAP高地址
	IAP_DATA = dat;                 //写ISP/IAP/EEPROM数据
	IAP_TRIG = 0x5a;                //写触发命令(0x5a)
	IAP_TRIG = 0xa5;                //写触发命令(0xa5)
	_nop_();                        //等待ISP/IAP/EEPROM操作完成
	IapIdle();
}
/*----------------------------
扇区擦除，擦除后为0xFF
----------------------------*/
void IapEraseSector(u16 addr)
{
	IAP_CONTR = 0x80;         //使能IAP
	IAP_TPS = 24;
	IAP_CMD = 3;            //设置IAP命令
	IAP_ADDRL = addr;               //设置IAP低地址
	IAP_ADDRH = addr >> 8;          //设置IAP高地址
	IAP_TRIG = 0x5a;                //写触发命令(0x5a)
	IAP_TRIG = 0xa5;                //写触发命令(0xa5)
	_nop_();                        //等待ISP/IAP/EEPROM操作完成
	IapIdle();
}
/*----------------------------
写入字符串到EEPROM
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
