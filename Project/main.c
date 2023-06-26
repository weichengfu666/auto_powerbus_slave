#include "main.h"

void main()
{  
    u16 i = 0,j=0;
    u8 *ptr = 0;
	Timer0Init();
	InitUART();
	IO_Init();
	FenJi_Init();

//LED_breathInit(LED1_PORT, LIGHT,0,0,0,0,0,0);
//LED_breathInit(LED2_PORT, LIGHT,20,0,0,0,0,0);
//LED_breathInit(LED3_PORT, LIGHT,40,0,0,0,0,0);
//LED_breathInit(LED4_PORT, LIGHT,60,0,0,0,0,0);
//LED_breathInit(LED5_PORT, LIGHT,80,0,0,0,0,0);
//LED_breathInit(LED6_PORT, LIGHT,100,0,0,0,0,0);
//LED_breathInit(LED7_PORT, LIGHT,100,0,0,0,0,0);
//LED_breathInit(LED8_PORT, LIGHT,100,0,0,0,0,0);

    
//    EEPROM_Write_Str(PACK1,(void*)LED_displayPack1,PACKROW*PACKCOL);
//    EEPROM_Write_Str(PACK2,(void*)LED_displayPack2,PACKROW*PACKCOL);
//    LED_displayPackPlayer(1);

////	SendData(0x61);
////	SendData2(0x61);


	for(;;)
	{	
		FenJi_ShuJuChuLi2();
		ZongZhiXin();
        
	}
} 
