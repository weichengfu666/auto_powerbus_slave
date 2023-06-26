#ifndef _BSP_TETS_H
#define _BSP_TEST_H
#include "main.h"

#define LED1 LED1_PORT
#define LED2 LED2_PORT
#define LED3 LED3_PORT
#define LED4 LED4_PORT
#define LED5 LED5_PORT
#define LED6 LED6_PORT
#define LED7 LED7_PORT
#define LED8 LED8_PORT

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
#define PACKROW     39  //Ч�����������ж��ٸ�Ч��
#define PACKCOL      13  //Ч��������������Ч���Ĳ���

extern u32 LED_displayTime;
extern u16   LED_PACK_id;
extern u8 LED_displayPackArr[PACKROW][PACKCOL];  //��ȡЧ�������ڴ�
extern code u8 LED_displayPack1[PACKROW][PACKCOL];
extern code u8 LED_displayPack2[PACKROW][PACKCOL];
extern u8 StartDisplayPack_flag;

void LED_displayPackStore( u8 _PACK_id );
void LED_displayPackPlayer( u8 _PACK_id );

#endif