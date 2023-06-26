#ifndef __EEPROM_H__
#define __EEPROM_H__
#include "main.h"

/*sfr IAP_DATA        = 0xC2;          //IAP���ݼĴ���
sfr IAP_ADDRH       = 0xC3;          //IAP��ַ�Ĵ������ֽ�
sfr IAP_ADDRL       = 0xC4;          //IAP��ַ�Ĵ������ֽ�
sfr IAP_CMD         = 0xC5;          //IAP����Ĵ���
sfr IAP_TRIG        = 0xC6;          //IAP������Ĵ��� 
sfr IAP_TRIG        = 0xC6;          //IAP������Ĵ���*/

#define  IAP_OFFSET 0x8000  //STC8H8K64U     ��32k

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
u8 IapReadByte(u16 addr); 		     //��ISP/IAP/EEPROM�����ȡһ���ֽ�
void IapProgramByte(u16 addr,u8 dat); //дһ���ֽ����ݵ�ISP/IAP/EEPROM����
void IapEraseSector(u16 addr);			 //��������
void EEPROM_Write_Str(u16 addr,u8 dat[],u16 dat_Len);
void EEPROM_Read_Str(u16 addr,u8 dat[],u16 dat_Len);
//����ʹ�����º�����дEEPROM
u8 writeFlashStr ( u32 _ulFlashAddr, u8 *_ucpSrc, u32 _ulSize ); /* ��ȡҳ�����棬�޸����ݣ���д��flash  */
void readFlashStr (u16 addr,u8 dat[],u16 dat_Len);

#endif
