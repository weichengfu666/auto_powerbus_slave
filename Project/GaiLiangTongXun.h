#ifndef __GAILIANGTONGXUN_H__
#define __GAILIANGTONGXUN_H__
					 
#define GaiLiang_D_TongXun P7
#define GaiLiang_I_TongXun P7M1=0xff;P7M0=0x00;
#define GaiLiang_O_TongXun P7M1=0x00;P7M0=0x00;

#define XiaoGuoDen 

sbit ShuRu1=P4^2;
sbit ShuRu2=P4^5;
sbit ShuRu3=P1^4;
sbit ShuRu4=P1^7;
sbit ShuRu5=P4^1;
sbit ShuRu6=P4^4;
sbit ShuRu7=P4^7;
sbit ShuRu8=P1^6;
sbit ShuRu9=P4^0;
sbit ShuRu10=P4^3;
sbit ShuRu11=P4^6;
sbit ShuRu12=P1^5;

void ShuJuJiaoHuan_TongXunMOKuai(void);
void ShuJu_init(void);
void FaSongZhunBei_TongXun(uchar FaSong_JiGuanHao,uchar FaSong_NongNengMa);
void ShuJuJiaoHuan_ShuChuMoKuai1(void);

#endif 