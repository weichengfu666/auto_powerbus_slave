#include "main.h"
uchar TongXunFaSong_HuanCun[50],TongXunFaSong_i=0,TongXunXunHuan_i=0,ChengXu_ShuZu[205][10];
uchar TongXunJieShou_HuanCun[50],TongXunJieShou_i=0,ChngXuJieShou_i=0,ShuJuinit_i=0,ShuJuinit_j=0;
uchar DaiZhiXinHuanCun[50][2],DaiZhiXinHuanCun_i=0,ChengXuShuZu_i=0,ChengXuShuZu_j=0,ChengXu_ShanQu=0,ChengXu_LingShi[15]=0;
uint ChengXu_Num=0,ChengXu_Num2=0,ChengXuShuZu_III=0,dsfsd=0;
extern uchar FaSongJiGuanZhuangTai[12],JiGuangZhuangTai[12],GongNengYanShi_Flag[64],GongNeng_JiShu[64],GongNeng_Delay[64][3];
extern uint shujuceshi_i,shujuceshi_j;

void ShuJu_init(void)
{		
	for(ShuJuinit_i=0;ShuJuinit_i<50;ShuJuinit_i++)
	{	
		TongXunFaSong_HuanCun[ShuJuinit_i]=0;	
		TongXunJieShou_HuanCun[ShuJuinit_i]=0;	
		DaiZhiXinHuanCun[ShuJuinit_i][0]=0;
		DaiZhiXinHuanCun[ShuJuinit_i][1]=0;
	}
	for(ChengXuShuZu_i=0;ChengXuShuZu_i<205;ChengXuShuZu_i++)
	{
		for(ChengXuShuZu_j=0;ChengXuShuZu_j<10;ChengXuShuZu_j++)
		{
			ChengXu_ShuZu[ChengXuShuZu_i][ChengXuShuZu_j]=0;
		}
	}	
	for(ChengXuShuZu_i=0;ChengXuShuZu_i<64;ChengXuShuZu_i++)
	{
		GongNeng_JiShu[ChengXuShuZu_i]=0;
		GongNengYanShi_Flag[ChengXuShuZu_i]=0;
		for(ChengXuShuZu_j=0;ChengXuShuZu_j<3;ChengXuShuZu_j++)
		{
			GongNeng_Delay[ChengXuShuZu_i][ChengXuShuZu_j]=0;
		}
	}	
	for(ChengXuShuZu_i=0;ChengXuShuZu_i<12;ChengXuShuZu_i++)
	{
		JiGuangZhuangTai[ChengXuShuZu_i]=2;
		FaSongJiGuanZhuangTai[ChengXuShuZu_i]=2;
	}	
}

void FaSongZhunBei_TongXun(uchar FaSong_JiGuanHao,uchar FaSong_NongNengMa)
{
 	TongXunFaSong_HuanCun[TongXunFaSong_i]=0x5A;
 	TongXunFaSong_HuanCun[TongXunFaSong_i+1]=FaSong_JiGuanHao;
 	TongXunFaSong_HuanCun[TongXunFaSong_i+2]=FaSong_NongNengMa;
 	TongXunFaSong_HuanCun[TongXunFaSong_i+3]=0xA5;		
	if(TongXunFaSong_i<46)
		TongXunFaSong_i+=4;
}
void ShuJuJiaoHuan_TongXunMOKuai(void)											
{
	if((TongXunFaSong_i>0)&&(FaSongShiNen_TongXun==0)&&(JieShouQinQiu_TongXun==0)&&(JieShouWanChen_TongXun==0))
	{
		GaiLiang_O_TongXun
		GaiLiang_D_TongXun=TongXunFaSong_HuanCun[0];	
		TongXunFaSong_i--;	
		for(TongXunXunHuan_i=0;TongXunXunHuan_i<TongXunFaSong_i;TongXunXunHuan_i++)
		{
			TongXunFaSong_HuanCun[TongXunXunHuan_i]=TongXunFaSong_HuanCun[TongXunXunHuan_i+1];	
		}
		JieShouQinQiu_TongXun=1;
	}
	if(JieShouWanChen_TongXun==1)
	{
		GaiLiang_D_TongXun=0x00;
		GaiLiang_I_TongXun
		JieShouQinQiu_TongXun=0;
	}
	if(FaSongQinQiu_TongXun==1)
	{
		if((JieShouQinQiu_TongXun==0)&&(JieShouWanChen_TongXun==0))
		{
		 	FaSongShiNen_TongXun=1;
		}
	}
	if((FaSongQinQiu_TongXun==0)&&(FaSongShiNen_TongXun==1))
	{
		if((GaiLiang_D_TongXun==0x5a)||(TongXunJieShou_i>0))			   //功能通讯
		{
			TongXunJieShou_HuanCun[TongXunJieShou_i]=GaiLiang_D_TongXun;
			TongXunJieShou_i++;	 
			if(TongXunJieShou_i>=4)
			{
				if((TongXunJieShou_HuanCun[0]==0x5a)&&(TongXunJieShou_HuanCun[3]==0xa5))
				{
					DaiZhiXinHuanCun[DaiZhiXinHuanCun_i][0]=TongXunJieShou_HuanCun[1];
					DaiZhiXinHuanCun[DaiZhiXinHuanCun_i][1]=TongXunJieShou_HuanCun[2];
					if(DaiZhiXinHuanCun_i==49)
					{
					 	DaiZhiXinHuanCun_i=48;
					}
					DaiZhiXinHuanCun_i++;
				}  
				TongXunJieShou_HuanCun[0]=0;
				TongXunJieShou_HuanCun[1]=0;
				TongXunJieShou_HuanCun[2]=0;
				TongXunJieShou_HuanCun[3]=0;
				TongXunJieShou_i=0;
			}
		}		   
		FaSongShiNen_TongXun=0;
	}
}