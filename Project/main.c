#include "main.h"
u8 test1[2] ={0x00};
u8 test2[2] ={0x01,0x01};
void main()
{  
    u16 i = 0,j=0;
    u8 *ptr = 0;
	Timer0Init();
	InitUART();
	IO_Init();
	FenJi_Init();
    
//    EEPROM_Read_Str( PACK1,(void*)test1,2);
//    for(j=0;j<2;j++)
//    {
//        SendData(test1[j]);
//    }

//    EEPROM_Write_Str( PACK1,(void*)test2,2);
//    EEPROM_Read_Str( PACK1,(void*)test1,2);
//    for(j=0;j<2;j++)
//    {
//        SendData(test1[j]);
//    }

//    EEPROM_Read_Str( PACK1,(void*)LED_displayPackArr,PACKROW*PACKCOL);
//    for(i=0;i<PACKROW;i++)
//    {
//        for(j=0;j<PACKCOL;j++)
//        {
//            SendData(LED_displayPackArr[i][j]);
//        }
//    }
//    EEPROM_Write_Str(PACK1,(void*)LED_displayPack1,PACKROW*PACKCOL);
//    EEPROM_Read_Str( PACK1,(void*)LED_displayPackArr,PACKROW*PACKCOL);
//    for(i=0;i<PACKROW;i++)
//    {
//        for(j=0;j<PACKCOL;j++)
//        {
//            SendData(LED_displayPackArr[i][j]);
//        }
//    }

    
//    EEPROM_Write_Str(PACK1,(void*)LED_displayPack1,PACKROW*PACKCOL);
//    EEPROM_Write_Str(PACK2,(void*)LED_displayPack2,PACKROW*PACKCOL);
//    LED_displayPackPlayer(1);

	SendData(0x61);
	SendData2(0x61);

	for(;;)
	{	
		FenJi_ShuJuChuLi2();
		ZongZhiXin();
        
	}
} 
