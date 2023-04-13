#ifndef __SHUNXUKEY_H__
#define __SHUNXUKEY_H__

sbit Key1 = P2^4;      	//0
sbit Key2 = P2^0;		//0
sbit Key3 = P3^7;		//0
sbit Key4 = P3^3;		//0
sbit Key5 = P3^3;		//0
sbit Key6 = P3^3;		//0
sbit Key7 = P3^3;		//0
sbit Key8 = P3^3;		//0

#define changfang 1

void ShunXu_Tium(void);
void ShunXu_PanDuan(void);

#endif 