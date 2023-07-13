#include "main.h"

void main()
{  
    u16 i = 0,j=0;
    u8 *ptr = 0;
	Timer0Init();
	InitUART();
	IO_Init();
	FenJi_Init();

	for(;;)
	{	
		FenJi_ShuJuChuLi2();
		ZongZhiXin();
        
	}
} 
