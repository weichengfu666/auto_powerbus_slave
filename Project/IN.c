#include "main.h"		  
void IN_Init(void)
{
	//INT0 = 1;
    IT0 = 0;                    //设置INT0的中断类型 (1:仅下降沿 0:上升沿和下降沿)
    EX0 = 1;                    //使能INT0中断
    EA = 1;
	INT_CLKO |= 0x70;               //(EX3 = 1)使能INT3中断
}

//-----------------------------------------
//中断服务程序
void exint0() interrupt 0       //INT0中断入口
{
	if(IN_0==1)
	{
	
	}else{
	
	}
}

void exint1() interrupt 2       //INT1中断入口
{
	if(IN_0==1)
	{
	
	}else{
	
	}

}

void exint2() interrupt 10          //INT2中断入口
{
    
//  INT_CLKO &= 0xEF;               //若需要手动清除中断标志,可先关闭中断,此时系统会自动清除内部的中断标志
//  INT_CLKO |= 0x10;               //然后再开中断即可
}

void exint3() interrupt 11          //INT3中断入口
{
    
//  INT_CLKO &= 0xDF;               //若需要手动清除中断标志,可先关闭中断,此时系统会自动清除内部的中断标志
//  INT_CLKO |= 0x20;               //然后再开中断即可
}

void exint4() interrupt 16          //INT3中断入口
{
    
//  INT_CLKO &= 0xBF;               //若需要手动清除中断标志,可先关闭中断,此时系统会自动清除内部的中断标志
//  INT_CLKO |= 0x40;               //然后再开中断即可
}
