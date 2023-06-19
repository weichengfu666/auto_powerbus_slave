#include "main.h"

uchar busy_flag,busy2_flag;

uchar JiHuo[2]={0,0},ZhuJiJieShou_HuanCun[3][20];
uchar ZhuJiJieShou_HuanCun_i[3]={0,0,0};
uchar FaSong_HuanCun[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},GuangBo_Flag[3]={0,0,0};
bit busy,busy2;	 
uchar ZhiLin_ChangDu[0x30]={11,13,6,6,8,8,6,0,0,0};

/*----------------------------
    UART1初始化
-----------------------------*/
void InitUART(void)	//9600 24MHZ
{
  SCON = 0x50;
  TMOD = 0x00;
  AUXR = 0x40;			//0100 0001
//  P_SW1 = 0x40; //RXD_2/P3.6, TXD_2/P3.7
	TL1 = 0x8F;				//
	TH1 = 0xFD;				//
  busy = 0;
	RI = 0;
	TI = 0;
	ET1 = 0;					//
	
	S2CON = 0x18;			//8位数据,可变波特率	
	AUXR |= 0x04;			//定时器时钟1T模式 0000 0100
	T2L = 0x8f;				//设定定时初值
	T2H = 0xFD;				//设定定时初值
	AUXR |= 0x10;			//定时器2开始计时 0001 0000
	
  ES = 1;             //使能串口中断
  IE2 = 0x01;         //使能串口2中断 0000 
  TR1 = 1;            //使能串口中断 
  EA = 1;
}

/*----------------------------
UART 中断服务程序
-----------------------------*/
void Uart() interrupt 4 using 1
{ 
	if (RI)
	{	                
        RI = 0;     //清除RI位
	}
    if (TI)
	{	             
        TI = 0;    //清除TI位
        busy = 0; 
	}
}

void FenJi_ShuJuChuLi(uchar FenJi_Data)
{
    uchar FenJi_ShuJuChuLi_i;
	for(FenJi_ShuJuChuLi_i=0;FenJi_ShuJuChuLi_i<3;FenJi_ShuJuChuLi_i++)
	{
		if(ZhuJiJieShou_HuanCun_i[FenJi_ShuJuChuLi_i]>=1)
		{
			ZhuJiJieShou_HuanCun[FenJi_ShuJuChuLi_i][ZhuJiJieShou_HuanCun_i[FenJi_ShuJuChuLi_i]-1]=FenJi_Data;
			ZhuJiJieShou_HuanCun_i[FenJi_ShuJuChuLi_i]++;
		}
	}
}

void FenJi_ShuJuChuLi2(void)
{
    uchar FenJi_ShuJuChuLi2_i,FenJi_ShuJuChuLi2_j;
	for(FenJi_ShuJuChuLi2_i=0;FenJi_ShuJuChuLi2_i<3;FenJi_ShuJuChuLi2_i++)
	{
		if((ZhuJiJieShou_HuanCun[FenJi_ShuJuChuLi2_i][0]==0)&&(ZhuJiJieShou_HuanCun_i[FenJi_ShuJuChuLi2_i]>1))
		{
			for(FenJi_ShuJuChuLi2_j=0;FenJi_ShuJuChuLi2_j<20;FenJi_ShuJuChuLi2_j++)
			{
				ZhuJiJieShou_HuanCun[FenJi_ShuJuChuLi2_i][FenJi_ShuJuChuLi2_j]=0;
			}
			ZhuJiJieShou_HuanCun_i[FenJi_ShuJuChuLi2_i]=0;
		}
		if(ZhuJiJieShou_HuanCun_i[FenJi_ShuJuChuLi2_i]>ZhiLin_ChangDu[ZhuJiJieShou_HuanCun[FenJi_ShuJuChuLi2_i][0]-1]-3)
		{
			crc16(ZhuJiJieShou_HuanCun[FenJi_ShuJuChuLi2_i],ZhiLin_ChangDu[ZhuJiJieShou_HuanCun[FenJi_ShuJuChuLi2_i][0]-1]-5,GuangBo_Flag[FenJi_ShuJuChuLi2_i]);			
			if(ZhuJiJieShou_HuanCun[FenJi_ShuJuChuLi2_i][ZhiLin_ChangDu[ZhuJiJieShou_HuanCun[FenJi_ShuJuChuLi2_i][0]-1]-5]==CRC_H)
			{
				if(ZhuJiJieShou_HuanCun[FenJi_ShuJuChuLi2_i][ZhiLin_ChangDu[ZhuJiJieShou_HuanCun[FenJi_ShuJuChuLi2_i][0]-1]-4]==CRC_L)
				{
					ZhiLinZhiXing(ZhuJiJieShou_HuanCun[FenJi_ShuJuChuLi2_i],GuangBo_Flag[FenJi_ShuJuChuLi2_i]);
				}
			}
			for(FenJi_ShuJuChuLi2_j=0;FenJi_ShuJuChuLi2_j<20;FenJi_ShuJuChuLi2_j++)
			{
				ZhuJiJieShou_HuanCun[FenJi_ShuJuChuLi2_i][FenJi_ShuJuChuLi2_j]=0;
			}
			ZhuJiJieShou_HuanCun_i[FenJi_ShuJuChuLi2_i]=0;
			GuangBo_Flag[FenJi_ShuJuChuLi2_i]=0;
		}
	}
}
void ZhiLingFaSong(uchar ChangDu)
{
    uchar ZhiLingFaSong_i;
	SendData2(0xa5);
	for(ZhiLingFaSong_i=0;ZhiLingFaSong_i<ChangDu;ZhiLingFaSong_i++)
	{
		SendData2(FaSong_HuanCun[ZhiLingFaSong_i]);
	}
	crc16(FaSong_HuanCun,ChangDu,2);
	SendData2(CRC_H);
	SendData2(CRC_L);
}
void SendData(uchar dat)
{
    while (busy) ;             //等待前面的数据发送完成
    SBUF = dat;                 //写数据到UART数据寄存器
    busy = 1;
}		 

/*----------------------------
UART2 中断服务程序
-----------------------------*/
void Uart2() interrupt 8 using 1
{
    uchar RX_i;
	if (S2CON&S2RI)
	{
		S2CON=S2CON&0xfe;        //清除S2RI位 
		FenJi_ShuJuChuLi(S2BUF); 
		if((JiHuo[1]==0xa5)&&(((JiHuo[0]==Slave.assignArr[0])&&(S2BUF==Slave.assignArr[1]))||((JiHuo[0]==0xff)&&(S2BUF==0xff))))
		{
			for(RX_i=0;RX_i<3;RX_i++)
			{
				if(ZhuJiJieShou_HuanCun_i[RX_i]==0)
				{
					if(JiHuo[0]==0xff)
						GuangBo_Flag[RX_i]=1;
					ZhuJiJieShou_HuanCun_i[RX_i]=1;
					RX_i=3;
				}
			}
		}
		JiHuo[1]=JiHuo[0];
		JiHuo[0]=S2BUF;
		//S2BUF;
	}
	if (S2CON&S2TI)
	{
		S2CON=S2CON&0xfd;         //清除S2TI位
		busy2 = 0;               			//清忙标志
	}	
}
/*----------------------------
发送串口2数据
----------------------------*/
void SendData2(uchar dat2)
{
  while (busy2)               //等待前面的数据发送完成
	{
		if(busy2_flag==0)
			busy2_flag=1;
	}  
	busy2_flag=0;
	busy2 = 1;
	S2BUF = dat2;                //写数据到UART2数据寄存器
}
////发送变量
//void Sendnum(long num)
//{
//  unsigned char i=0,j=0;
//  long n=0,num1=0,c=0,js=1,js1;
//  if(num<0)
//  {
//    num=-num;
//    num1=num;    
//  	SendData(45); 
//  }else{
//    num1=num;
//  }
//  
//  if(num==0) 
//  {       
//  	SendData(48);        
//  }
//  while(num1!=0) 
//  {
//    num1 = num1/10;
//    n++;
//  }
//  for(js1=n-1;js1>0;js1--) 
//  {
//    js=js*10;
//  }
//  while (n!=0)
//  { 
//    c =num/js;
//  	num=num-c*js;
//  	c=c+48;       
//  	SendData(c); 
//  	js=js/10;	
//  	n--;
//  }
//}