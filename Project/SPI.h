#ifndef __SPI_H__
#define __SPI_H__

sbit SPI_MOSI=P0^0;
sbit SPI_MISO=P0^1;
sbit SPI_SCK=P0^2;
sbit SPI_CS=P0^3;

void Delay10us();
void SPI_Write(unsigned char SPI_Dat);
unsigned char SPI_Read();

#endif 