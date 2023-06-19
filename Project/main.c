#include "main.h"

void main()
{  
    u16 i = 0,j=0;
    u8 *ptr = 0;
	Timer0Init();
	InitUART();
	IO_Init();
	FenJi_Init();
    
    writeFlashStr(PACK1,(void*)LED_displayPack1,PACKROW*PACKCOL);
    writeFlashStr(PACK2,(void*)LED_displayPack2,PACKROW*PACKCOL);
//    LED_displayPackPlayer(1);

	SendData(0x61);
	SendData2(0x61);

	for(;;)
	{	
		FenJi_ShuJuChuLi2();
		ZongZhiXin();
        
	}
} 
