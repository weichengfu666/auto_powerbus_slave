#ifndef __EEPROM_H__
#define __EEPROM_H__
#include "main.h"

/*sfr IAP_DATA        = 0xC2;          //IAP���ݼĴ���
sfr IAP_ADDRH       = 0xC3;          //IAP��ַ�Ĵ������ֽ�
sfr IAP_ADDRL       = 0xC4;          //IAP��ַ�Ĵ������ֽ�
sfr IAP_CMD         = 0xC5;          //IAP����Ĵ���
sfr IAP_TRIG        = 0xC6;          //IAP������Ĵ��� 
sfr IAP_TRIG        = 0xC6;          //IAP������Ĵ���*/

typedef unsigned int WORD;
typedef unsigned char BYTE;

#define  IAP_OFFSET 0x2000  //STC8G1K08

#define CMD_IDLE    0                //����ģʽ  
#define CMD_READ    1                //IAP�ֽڶ�����  
#define CMD_PROGRAM 2                //IAP�ֽڱ������
#define CMD_ERASE   3                //IAP������������

#define ENABLE_IAP  0x80             //if SYSXLK<30MHZ   
//#define ENABLE_IAP  0x81             //if SYSXLK<24MHZ   
//#define ENABLE_IAP  0x82             //if SYSXLK<20MHZ   
//#define ENABLE_IAP  0x83             //if SYSXLK<12MHZ   
//#define ENABLE_IAP  0x84             //if SYSXLK<6MHZ   
//#define ENABLE_IAP  0x85             //if SYSXLK<3MHZ   
//#define ENABLE_IAP  0x86             //if SYSXLK<2MHZ   
//#define ENABLE_IAP  0x87             //if SYSXLK<1MHZ   	

void EEPROM_init(void);
void EEPROM_kongzhi(void);									   
void IapIdle(void);                      //�ر�IAP
BYTE IapReadByte(WORD addr); 		     //��ISP/IAP/EEPROM�����ȡһ���ֽ�
void IapProgramByte(WORD addr,BYTE dat); //дһ���ֽ����ݵ�ISP/IAP/EEPROM����
void IapEraseSector(WORD addr);			 //��������
void EEPROM_Write_Str(WORD addr,BYTE dat[],WORD dat_Len);
void EEPROM_Read_Str(WORD addr);

#endif
