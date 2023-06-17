#ifndef _BSP_TETS_H
#define _BSP_TEST_H
#include "main.h"

#define LED2 PWM1_PORT
#define LED3 PWM2_PORT
#define LED4 PWM3_PORT
#define LED5 PWM4_PORT
#define LED6 PWM5_PORT
#define LED7 PWM6_PORT
#define LED8 PWM7_PORT
#define LED1 PWM8_PORT

#define FLASHADDR_START       0x000       //flash起始地址的512字节留作他用
#define FLASHADDR_DISPLAY1  0x200       //每个效果包512字节
#define FLASHADDR_DISPLAY2  0x400
#define FLASHADDR_DISPLAY3  0x600
#define FLASHADDR_DISPLAY4  0x800
#define FLASHADDR_DISPLAY5  0xa00
#define FLASHADDR_DISPLAY6  0xc00
#define FLASHADDR_DISPLAY7  0xe00

//_PACK_id
#define	PACK1				FLASHADDR_DISPLAY1
#define	PACK2				FLASHADDR_DISPLAY2
#define	PACK3				FLASHADDR_DISPLAY3
#define	PACK4				FLASHADDR_DISPLAY4
#define	PACK5				FLASHADDR_DISPLAY5
#define	PACK6				FLASHADDR_DISPLAY6
#define	PACK7				FLASHADDR_DISPLAY7

//504字节
#define PACKROW     39  //效果包行数：有多少个效果
#define PACKCOL      13  //效果包列数：单个效果的参数

extern u32 LED_displayTime;
extern u16   LED_PACK_id;
extern u8 LED_displayPackArr[PACKROW][PACKCOL];  //读取效果包到内存
extern code u8 LED_displayPack1[PACKROW][PACKCOL];
extern code u8 LED_displayPack2[PACKROW][PACKCOL];
extern u8 StartDisplayPack_flag;

void LED_displayPackStore( u8 _PACK_id );
void LED_displayPackPlayer( u8 _PACK_id );

#endif