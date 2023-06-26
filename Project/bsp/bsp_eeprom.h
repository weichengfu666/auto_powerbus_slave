#ifndef __EEPROM_H__
#define __EEPROM_H__
#include "main.h"

/*sfr IAP_DATA        = 0xC2;          //IAP数据寄存器
sfr IAP_ADDRH       = 0xC3;          //IAP地址寄存器高字节
sfr IAP_ADDRL       = 0xC4;          //IAP地址寄存器低字节
sfr IAP_CMD         = 0xC5;          //IAP命令寄存器
sfr IAP_TRIG        = 0xC6;          //IAP命令触发寄存器 
sfr IAP_TRIG        = 0xC6;          //IAP命令触发寄存器*/

#define  IAP_OFFSET 0x8000  //STC8H8K64U     留32k

#define CMD_IDLE    0                //空闲模式  
#define CMD_READ    1                //IAP字节读命令  
#define CMD_PROGRAM 2                //IAP字节编程命令
#define CMD_ERASE   3                //IAP扇区擦除命令

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
void IapIdle(void);                      //关闭IAP
u8 IapReadByte(u16 addr); 		     //从ISP/IAP/EEPROM区域读取一个字节
void IapProgramByte(u16 addr,u8 dat); //写一个字节数据到ISP/IAP/EEPROM区域
void IapEraseSector(u16 addr);			 //扇区擦除
void EEPROM_Write_Str(u16 addr,u8 dat[],u16 dat_Len);
void EEPROM_Read_Str(u16 addr,u8 dat[],u16 dat_Len);
//建议使用以下函数读写EEPROM
u8 writeFlashStr ( u32 _ulFlashAddr, u8 *_ucpSrc, u32 _ulSize ); /* 读取页到缓存，修改内容，再写回flash  */
void readFlashStr (u16 addr,u8 dat[],u16 dat_Len);

#endif
