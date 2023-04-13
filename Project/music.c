#include "main.h"
uchar bofangyinxiaohao=0;		  
extern uchar JiGuanQiDong,jiguanzhuangtai_flag,DanCiFaSong_ZhuJi;
void yingxiaokongzhi(uchar gequhao,uchar moshihao)
{
	if(moshihao==0)
	{
		switch(gequhao)
		{
			case 1:music_A1=0;music_A2=1;music_A3=1;music_A4=1;music_A5=1;break;
			case 2:music_A1=1;music_A2=0;music_A3=1;music_A4=1;music_A5=1;break;
			case 3:music_A1=0;music_A2=0;music_A3=1;music_A4=1;music_A5=1;break;
			case 4:music_A1=1;music_A2=1;music_A3=0;music_A4=1;music_A5=1;break;
			case 5:music_A1=0;music_A2=1;music_A3=0;music_A4=1;music_A5=1;break;
			case 6:music_A1=1;music_A2=0;music_A3=0;music_A4=1;music_A5=1;break;
			case 7:music_A1=0;music_A2=0;music_A3=0;music_A4=1;music_A5=1;break;
			case 8:music_A1=1;music_A2=1;music_A3=1;music_A4=0;music_A5=1;break;
			case 9:music_A1=0;music_A2=1;music_A3=1;music_A4=0;music_A5=1;break;
			case 10:music_A1=1;music_A2=0;music_A3=1;music_A4=0;music_A5=1;break;
			case 11:music_A1=0;music_A2=0;music_A3=1;music_A4=0;music_A5=1;break;
			case 12:music_A1=1;music_A2=1;music_A3=0;music_A4=0;music_A5=1;break;
			case 13:music_A1=0;music_A2=1;music_A3=0;music_A4=0;music_A5=1;break;
			case 14:music_A1=1;music_A2=0;music_A3=0;music_A4=0;music_A5=1;break;
			case 15:music_A1=0;music_A2=0;music_A3=0;music_A4=0;music_A5=1;break;
			case 16:music_A1=1;music_A2=1;music_A3=1;music_A4=1;music_A5=0;break;
			case 17:music_A1=0;music_A2=1;music_A3=1;music_A4=1;music_A5=0;break;
			case 18:music_A1=1;music_A2=0;music_A3=1;music_A4=1;music_A5=0;break;
			case 19:music_A1=0;music_A2=0;music_A3=1;music_A4=1;music_A5=0;break;
			case 20:music_A1=1;music_A2=1;music_A3=0;music_A4=1;music_A5=0;break;
			case 21:music_A1=0;music_A2=1;music_A3=0;music_A4=1;music_A5=0;break;
			case 22:music_A1=1;music_A2=0;music_A3=0;music_A4=1;music_A5=0;break;
			case 23:music_A1=0;music_A2=0;music_A3=0;music_A4=1;music_A5=0;break;
			case 24:music_A1=1;music_A2=1;music_A3=1;music_A4=0;music_A5=0;break;
			case 25:music_A1=0;music_A2=1;music_A3=1;music_A4=0;music_A5=0;break;
			case 26:music_A1=1;music_A2=0;music_A3=1;music_A4=0;music_A5=0;break;
			case 27:music_A1=0;music_A2=0;music_A3=1;music_A4=0;music_A5=0;break;
			case 28:music_A1=1;music_A2=1;music_A3=0;music_A4=0;music_A5=0;break;
			case 29:music_A1=0;music_A2=1;music_A3=0;music_A4=0;music_A5=0;break;
			case 30:music_A1=1;music_A2=0;music_A3=0;music_A4=0;music_A5=0;break;
			case 31:music_A1=0;music_A2=0;music_A3=0;music_A4=0;music_A5=0;break;
		}
		Delay400ms();
		music_A1=1;music_A2=1;music_A3=1;music_A4=1;music_A5=1;
 	}else if(moshihao==1){
//		switch(gequhao)
//		{
//			case 1:music_A1=0;music_A2=1;music_A3=1;music_A4=1;music_A5=1;music_A6=1;music_A7=1;music_A8=1;music_A9=1;break;
//			case 2:music_A1=1;music_A2=0;music_A3=1;music_A4=1;music_A5=1;music_A6=1;music_A7=1;music_A8=1;music_A9=1;break;
//			case 3:music_A1=1;music_A2=1;music_A3=0;music_A4=1;music_A5=1;music_A6=1;music_A7=1;music_A8=1;music_A9=1;break;
//			case 4:music_A1=1;music_A2=1;music_A3=1;music_A4=0;music_A5=1;music_A6=1;music_A7=1;music_A8=1;music_A9=1;break;
//			case 5:music_A1=1;music_A2=1;music_A3=1;music_A4=1;music_A5=0;music_A6=1;music_A7=1;music_A8=1;music_A9=1;break;
//			case 6:music_A1=1;music_A2=1;music_A3=1;music_A4=1;music_A5=1;music_A6=0;music_A7=1;music_A8=1;music_A9=1;break;
//			case 7:music_A1=1;music_A2=1;music_A3=1;music_A4=1;music_A5=1;music_A6=1;music_A7=0;music_A8=1;music_A9=1;break;
//			case 8:music_A1=1;music_A2=1;music_A3=1;music_A4=1;music_A5=1;music_A6=1;music_A7=1;music_A8=0;music_A9=1;break;
//			case 9:music_A1=1;music_A2=1;music_A3=1;music_A4=1;music_A5=1;music_A6=1;music_A7=1;music_A8=1;music_A9=0;break;
//		}
//		Delay_ms(500);
//		music_A1=1;music_A2=1;music_A3=1;music_A4=1;music_A5=1;music_A6=1;music_A7=1;music_A8=1;music_A9=1;	
	}
}
void Delay400ms() 	 		//@20.000MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 31;
	j = 102;
	k = 247;
	do
	{
		do
		{
			WDT_CONTR=0x3d;
			while (--k);
		} while (--j);
	} while (--i);
}
