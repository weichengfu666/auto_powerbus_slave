#include "main.h"
void Delay10us()		//@30.000MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 72;
	while (--i);
}
/*******************************
    向SPI器件写入一个字节数据
*******************************/
void SPI_Write(unsigned char SPI_Dat)  
{  
 	unsigned  char  i;  
 	SPI_CS=0;  
 	for(i=0;i<8;i++)  
 	{  
  		SPI_SCK=0;    
  		if((SPI_Dat&0x80)==0x80)
			SPI_MISO=1;  
  		else 
			SPI_MISO=0; 
		Delay10us(); 
        SPI_SCK=1;   
  		SPI_Dat=(SPI_Dat<<1); 
		Delay10us(); 
 	}  
 	SPI_CS=1;
}  
/********************************
  从SPI器件读出一个字节数据
********************************/
unsigned char SPI_Read()  
{  
 	unsigned char i,SPI_Dat;  
 	SPI_CS=0;  
   	for (i=0;i<8;i++)  
 	{                                  
  		SPI_SCK=0;  
     	SPI_Dat=(SPI_Dat<<1);  
     	SPI_SCK=1;  
  		if(SPI_MOSI==1)
			SPI_Dat|=0x01;  
  		else 
			SPI_Dat&=~0x01;  
 	}  
 	SPI_CS=1;
 	return SPI_Dat;  
}