#ifndef __COM_H__
#define __COM_H__

#define S2RI  0x01              //S2CON.0
#define S2TI  0x02              //S2CON.1
#define S2RB8 0x04              //S2CON.2
#define S2TB8 0x08              //S2CON.3

void InitUART(void);
void SendData(uchar dat);
void SendData2(uchar dat2);
void Sendnum(long num);
void FenJi_ShuJuChuLi(uchar FenJi_Data);
void FenJi_ShuJuChuLi2(void);
void ZhiLingFaSong(uchar ChangDu);
#endif 
