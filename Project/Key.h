#ifndef _Key_h_
#define _Key_h_

#include "main.h"
#define Key1 OUT1
#define Key2 OUT2
//#define Key3 OUT3
//#define Key4 OUT4
#define Key_Open 1
#define Key_Delay 10     //消抖时间
#define Key_Tim 100     //长按连续Key_Tim后开始递增
#define Key_Tim1 10	//递增速率

void Key(void);
void Key_Time(void); 
 
#endif