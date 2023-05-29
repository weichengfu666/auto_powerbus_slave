#ifndef _BSP_TETS_H
#define _BSP_TEST_H
#include "main.h"

#define LED1 PWM00
#define LED2 PWM01
#define LED3 PWM02
#define LED4 PWM03
#define LED5 PWM04
#define LED6 PWM05
#define LED7 PWM06
#define LED8 PWM07

#define FLASHADDR_START       0x000       //flash��ʼ��ַ��512�ֽ���������
#define FLASHADDR_DISPLAY1  0x200       //ÿ��Ч����512�ֽ�
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

//504�ֽ�
#define PACKROW     34  //Ч�����������ж��ٸ�Ч��
#define PACKCOL      15  //Ч��������������Ч���Ĳ���

extern u32 LED_displayTime;
extern u16   LED_PACK_id;
extern u8 LED_displayPackArr[PACKROW][PACKCOL];  //��ȡЧ�������ڴ�
extern code u8 LED_displayPack1[PACKROW][PACKCOL];
extern code u8 LED_displayPack2[PACKROW][PACKCOL];

void LED_displayPackStore( u8 _PACK_id );
void LED_displayPackPlayer( u8 _PACK_id );

#endif