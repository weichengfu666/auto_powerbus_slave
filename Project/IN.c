#include "main.h"		  
void IN_Init(void)
{
	//INT0 = 1;
    IT0 = 0;                    //����INT0���ж����� (1:���½��� 0:�����غ��½���)
    EX0 = 1;                    //ʹ��INT0�ж�
    EA = 1;
	INT_CLKO |= 0x70;               //(EX3 = 1)ʹ��INT3�ж�
}

//-----------------------------------------
//�жϷ������
void exint0() interrupt 0       //INT0�ж����
{
	if(IN_0==1)
	{
	
	}else{
	
	}
}

void exint1() interrupt 2       //INT1�ж����
{
	if(IN_0==1)
	{
	
	}else{
	
	}

}

void exint2() interrupt 10          //INT2�ж����
{
    
//  INT_CLKO &= 0xEF;               //����Ҫ�ֶ�����жϱ�־,���ȹر��ж�,��ʱϵͳ���Զ�����ڲ����жϱ�־
//  INT_CLKO |= 0x10;               //Ȼ���ٿ��жϼ���
}

void exint3() interrupt 11          //INT3�ж����
{
    
//  INT_CLKO &= 0xDF;               //����Ҫ�ֶ�����жϱ�־,���ȹر��ж�,��ʱϵͳ���Զ�����ڲ����жϱ�־
//  INT_CLKO |= 0x20;               //Ȼ���ٿ��жϼ���
}

void exint4() interrupt 16          //INT3�ж����
{
    
//  INT_CLKO &= 0xBF;               //����Ҫ�ֶ�����жϱ�־,���ȹر��ж�,��ʱϵͳ���Զ�����ڲ����жϱ�־
//  INT_CLKO |= 0x40;               //Ȼ���ٿ��жϼ���
}
