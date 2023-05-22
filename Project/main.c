#include "main.h"

void main()
{  
    u16 i = 0,j=0;
    u8 *ptr = 0;
	Timer0Init();
	InitUART();
	IO_Init();
	FenJi_Init();

    EEPROM_Write_Str(PACK1,(void*)LED_displayPack1,PACKROW*PACKCOL);
    EEPROM_Write_Str(PACK2,(void*)LED_displayPack2,PACKROW*PACKCOL);
//    EEPROM_Read_Str(PACK1,(void*)LED_displayPack1,PACKROW*PACKCOL);
    
////    memset(EEPROM_ChuShi, 0x00, 2);
//    EEPROM_Write_Str(0x0000,EEPROM_ChuShi,2);
//   
//    EEPROM_Read_Str(0x0000,EEPROM_ChuShi,10);
//    for(i=0;i<PACKROW;i++)
//    {
//        for(j = 0; j < PACKCOL; j++)
//        {
//            SendData(LED_displayPackArr[i][j]);
//        }
//    }
    LED_displayPackPlayer(1);
//    LED_displayPackPlayer(PACK2);
	SendData(0x61);
	SendData2(0x61);

	for(;;)
	{	
		FenJi_ShuJuChuLi2();
		ZongZhiXin();
        
	}
} 
