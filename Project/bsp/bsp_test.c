#include "bsp_test.h"
#include "main.h"

typedef struct LED_Display{
    u32 displayTime;
    u8 PWMxx;
    u8 breath_state;
    u16 periodBreathFlash1_cntCmp;
    u16 periodChangeFlash2_cntCmp;
    u8 waveBreathChangeFlash_start;
    u8 waveBreathChangeFlash_end;
    u8 waveBreath_now;
}LED_DisplayTypedef;

u32 LED_displayTime = 0;
u16 LED_dispalyPackIndex = 0;
u16   LED_PACK_id = 0;
u16 LED_PACK_idArr[8] = {0x0000, PACK1, PACK2, PACK3, PACK4, PACK5, PACK6, PACK7};
u8 StartDisplayPack_flag = 0; //����Ч������1��������2���ر�


u8 LED_displayPackArr[PACKROW][PACKCOL] = { 0 };


code u8 LED_displayPack1[PACKROW][PACKCOL] = {    
                                                        {0x00,0x00,0x00,0x00,LED1,BREATH,0x0b,0xb8,0x0b,0xb8,10,100,30},//0��
                                                        {0x00,0x00,0x00,0x00,LED2,BREATH,0x0b,0xb8,0x0b,0xb8,10,100,30},
                                                        {0x00,0x00,0x00,0x00,LED3,BREATH,0x0b,0xb8,0x0b,0xb8,10,100,30},
                                                        {0x00,0x00,0x00,0x00,LED4,BREATH,0x0b,0xb8,0x0b,0xb8,10,100,30},
                                                        {0x00,0x00,0x00,0x00,LED5,BREATH,0x0b,0xb8,0x0b,0xb8,10,100,30},
                                                        {0x00,0x00,0x00,0x00,LED6,BREATH,0x0b,0xb8,0x0b,0xb8,10,100,30},
                                                        {0x00,0x00,0x00,0x00,LED7,BREATH,0x0b,0xb8,0x0b,0xb8,10,100,30},
                                                        {0x00,0x00,0x00,0x00,LED8,BREATH,0x0b,0xb8,0x0b,0xb8,10,100,30},
                                                        {0x00,0x00,0x0b,0xb8,LED1,GRADCHANGE_ONCE,0x0b,0xb8,0x0b,0xb8,100,0,30},//3��
                                                        {0x00,0x00,0x0b,0xb8,LED2,GRADCHANGE_ONCE,0x0b,0xb8,0x0b,0xb8,100,0,30},
                                                        {0x00,0x00,0x0b,0xb8,LED3,GRADCHANGE_ONCE,0x0b,0xb8,0x0b,0xb8,100,0,30},
                                                        {0x00,0x00,0x0b,0xb8,LED4,GRADCHANGE_ONCE,0x0b,0xb8,0x0b,0xb8,100,0,30},
                                                        {0x00,0x00,0x0b,0xb8,LED5,GRADCHANGE_ONCE,0x0b,0xb8,0x0b,0xb8,100,0,30},
                                                        {0x00,0x00,0x0b,0xb8,LED6,GRADCHANGE_ONCE,0x0b,0xb8,0x0b,0xb8,100,0,30},
                                                        {0x00,0x00,0x0b,0xb8,LED7,GRADCHANGE_ONCE,0x0b,0xb8,0x0b,0xb8,100,0,30},
                                                        {0x00,0x00,0x0b,0xb8,LED8,GRADCHANGE_ONCE,0x0b,0xb8,0x0b,0xb8,100,0,30},
                                                        {0x00,0x00,0x17,0x70,LED1,FLASH,0x00,0x1e,0x00,0x3c,10,100,10},//6��
                                                        {0x00,0x00,0x17,0x70,LED2,FLASH,0x00,0x1e,0x00,0x3c,10,100,10},
                                                        {0x00,0x00,0x17,0x70,LED3,FLASH,0x00,0x1e,0x00,0x3c,10,100,10},
                                                        {0x00,0x00,0x17,0x70,LED4,FLASH,0x00,0x1e,0x00,0x3c,10,100,10},
                                                        {0x00,0x00,0x17,0x70,LED5,FLASH,0x00,0x1e,0x00,0x3c,10,100,10},
                                                        {0x00,0x00,0x17,0x70,LED6,FLASH,0x00,0x1e,0x00,0x3c,10,100,10},
                                                        {0x00,0x00,0x17,0x70,LED7,FLASH,0x00,0x1e,0x00,0x3c,10,100,10},
                                                        {0x00,0x00,0x17,0x70,LED8,FLASH,0x00,0x1e,0x00,0x3c,10,100,10},
                                                        {0xff,0xff,0xff,0xff}};

code u8 LED_displayPack2[PACKROW][PACKCOL] = {    
                                                        {0x00,0x00,0x00,0x00,LED1,FLASH,0x03,0xe8,0x03,0xe8,10,40},//0��
                                                        {0x00,0x00,0x00,0x00,LED2,LOW,0x03,0xe8,0x03,0xe8,10,40},
                                                        {0x00,0x00,0x00,0x00,LED3,HIGH,0x03,0xe8,0x03,0xe8,10,40},
                                                        {0x00,0x00,0x00,0x00,LED4,FLASH,0x03,0xe8,0x03,0xe8,10,40},
                                                        {0x00,0x00,0x00,0x00,LED5,BREATH,0x03,0xe8,0x03,0xe8,10,40},
                                                        {0x00,0x00,0x00,0x00,LED6,GRADCHANGE_CYCLE,0x03,0xe8,0x03,0xe8,10,40},
                                                        {0x00,0x00,0x0b,0xb8,LED1,HIGH,0x03,0xe8,0x03,0xe8,10,40},//3��
                                                        {0x00,0x00,0x0b,0xb8,LED2,HIGH,0x03,0xe8,0x03,0xe8,10,40},
                                                        {0x00,0x00,0x0b,0xb8,LED3,HIGH,0x03,0xe8,0x03,0xe8,10,40},
                                                        {0x00,0x00,0x0b,0xb8,LED4,HIGH,0x03,0xe8,0x03,0xe8,10,40},
                                                        {0x00,0x00,0x0b,0xb8,LED5,HIGH,0x03,0xe8,0x03,0xe8,10,40},
                                                        {0x00,0x00,0x0b,0xb8,LED6,HIGH,0x03,0xe8,0x03,0xe8,10,40},
                                                        {0x00,0x00,0x0b,0xb8,LED7,HIGH,0x03,0xe8,0x03,0xe8,10,40},
                                                        {0x00,0x00,0x0b,0xb8,LED8,HIGH,0x03,0xe8,0x03,0xe8,10,40},
                                                        {0x00,0x00,0x17,0x70,LED1,LOW,0x03,0xe8,0x03,0xe8,10,40},//6��
                                                        {0x00,0x00,0x17,0x70,LED2,LOW,0x03,0xe8,0x03,0xe8,10,40},
                                                        {0x00,0x00,0x17,0x70,LED3,LOW,0x03,0xe8,0x03,0xe8,10,40},
                                                        {0x00,0x00,0x17,0x70,LED4,LOW,0x03,0xe8,0x03,0xe8,10,40},
                                                        {0x00,0x00,0x17,0x70,LED5,LOW,0x03,0xe8,0x03,0xe8,10,40},
                                                        {0x00,0x00,0x17,0x70,LED6,LOW,0x03,0xe8,0x03,0xe8,10,40},
                                                        {0x00,0x00,0x17,0x70,LED7,LOW,0x03,0xe8,0x03,0xe8,10,40},
                                                        {0x00,0x00,0x17,0x70,LED8,LOW,0x03,0xe8,0x03,0xe8,10,40},
                                                        {0x00,0x01,0x11,0x70,LED1,FLASH,0x03,0xe8,0x03,0xe8,10,40},//70��
                                                        {0x00,0x01,0x11,0x70,LED2,FLASH,0x03,0xe8,0x03,0xe8,10,40},
                                                        {0x00,0x01,0x11,0x70,LED3,FLASH,0x03,0xe8,0x03,0xe8,10,40},
                                                        {0x00,0x01,0x11,0x70,LED4,FLASH,0x03,0xe8,0x03,0xe8,10,40},
                                                        {0x00,0x01,0x11,0x70,LED5,FLASH,0x03,0xe8,0x03,0xe8,10,40},
                                                        {0x00,0x01,0x11,0x70,LED6,FLASH,0x03,0xe8,0x03,0xe8,10,40},
                                                        {0x00,0x01,0x11,0x70,LED7,FLASH,0x03,0xe8,0x03,0xe8,10,40},
                                                        {0x00,0x01,0x11,0x70,LED8,FLASH,0x03,0xe8,0x03,0xe8,10,40},
                                                        {0xff,0xff,0xff,0xff}};
                                                        
void LED_displayPackStore( u8 _PACK_id )
{
    EEPROM_Write_Str(_PACK_id,(void*)LED_displayPackArr,PACKROW*PACKCOL);
}
    
void LED_displayPackPlayer( u8 _PACK_id )
{
     u16 i = 0,j=0;
    LED_DisplayTypedef* LED_Display = 0;
    if( _PACK_id == 0 )
    {
        LED_Display = (LED_DisplayTypedef*)&LED_displayPackArr[0][0];
        LED_displayTime = 1;//����Ч��ʱ����
        if( LED_displayTime >= LED_Display->displayTime )
        {
            LED_breathInit( LED_Display->PWMxx, LED_Display->breath_state, LED_Display->periodBreathFlash1_cntCmp, LED_Display->periodChangeFlash2_cntCmp,
                                    LED_Display->waveBreathChangeFlash_start, LED_Display->waveBreathChangeFlash_end, LED_Display->waveBreath_now);
        }
        LED_displayTime = 0;//�ر�Ч��ʱ����
    }
    else if( _PACK_id >=1 && _PACK_id <= 7)
    {
        //��falsh��ȡָ��Ч�������ڴ�
        EEPROM_Read_Str( LED_PACK_idArr[ _PACK_id ],(void*)LED_displayPackArr,PACKROW*PACKCOL);
        
        LED_displayTime = 1;//����Ч��ʱ����
        while(1)
        {
            LED_Display = (LED_DisplayTypedef*)(&LED_displayPackArr[0][0] + LED_dispalyPackIndex * PACKCOL);
            if( LED_Display->displayTime >= 0xffffffff || LED_dispalyPackIndex >= PACKROW )
            {
                LED_displayTime = 0;//�ر�Ч��ʱ����
                LED_dispalyPackIndex = 0;//����Ч����ָ��
                break;
            }
            if( LED_displayTime >= LED_Display->displayTime )
            {
                LED_breathInit( LED_Display->PWMxx, LED_Display->breath_state, LED_Display->periodBreathFlash1_cntCmp, LED_Display->periodChangeFlash2_cntCmp,
                                        LED_Display->waveBreathChangeFlash_start, LED_Display->waveBreathChangeFlash_end, LED_Display->waveBreath_now);
                LED_dispalyPackIndex++;
            }
        }
    }
}



