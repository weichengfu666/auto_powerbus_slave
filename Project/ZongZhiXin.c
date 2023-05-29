#include "main.h"
uint ZongXunHuan_i=0,GongNen_i=0,GongNen_j=0,ZongZhiXin_i=0,ZongZhiXin_j=0;
ulong Delay_Time[5],MuBiao_Time[5],JianBian_Time1=0,JianBian_Time2=0;
uint Delay_Addr[5];
uint GongNen_Addr_Shou[5],GongNen_Addr_Wei[5],XunHuan_Changdu=0,XunHuan_ZhiZhen=0,XunHuan_Addr=0;
char LiangDu_ChuShi=0,LiangDu_JieShu=0,LiangDu_DangQian=0;
long LiangDu_HuanCun=0;
uchar BianHao_QingChu[2],SouXunXuLie_Time=0,BiaoHaoFuZhi_Time=0;
uint Time=0,Time_i=0;
code uchar XuLieHao[5]={0x0A,0x0A,0x0A,0x0A,0x0A};
u8 EEPROM_ChuShi[2] = {0x00, 0x00}; //分机赋值号

//code uint LiangDuDuiZhao[101]={0,
//	1,2,2,2,2,3,3,3,3,3,
//	4,4,4,4,5,5,5,6,6,6,
//	7,7,8,8,9,9,10,10,11,11,
//	12,13,14,15,16,17,19,20,21,22,
//	24,26,27,29,31,33,35,37,40,42,
//	45,48,51,55,58,62,66,71,75,80,
//	86,91,97,104,110,118,125,134,142,152,
//	162,172,184,196,209,222,237,252,269,287,
//	306,326,347,370,394,420,448,477,508,542,
//	577,615,656,699,745,794,846,902,961,1024
//};
void FenJi_Init(void)
{	
	uchar ZhuJi_Init_i,ZhuJi_Init_j;
	for(ZhuJi_Init_i=0;ZhuJi_Init_i<3;ZhuJi_Init_i++)
	{
		for(ZhuJi_Init_j=0;ZhuJi_Init_j<20;ZhuJi_Init_j++)
		{
			ZhuJiJieShou_HuanCun[ZhuJi_Init_i][ZhuJi_Init_j]=0;
		}
	}	
	for(ZhuJi_Init_i=0;ZhuJi_Init_i<5;ZhuJi_Init_i++)
	{
		Delay_Time[ZhuJi_Init_i]=0;
		MuBiao_Time[ZhuJi_Init_i]=0;
		Delay_Addr[ZhuJi_Init_i]=0;
		GongNen_Addr_Shou[ZhuJi_Init_i]=0;
		GongNen_Addr_Wei[ZhuJi_Init_i]=0;
	}
    EEPROM_Write_Str(0x0000,EEPROM_ChuShi,2);
    ZhiLin_ChangDu[0x01-1] = 11;
    ZhiLin_ChangDu[0x02-1] = 13;
    ZhiLin_ChangDu[0x03-1] = 6;
    ZhiLin_ChangDu[0x04-1] = 6;
    ZhiLin_ChangDu[0x05-1] = 8;
    ZhiLin_ChangDu[0x06-1] = 8;
    ZhiLin_ChangDu[0x07-1] = 6;
    
    ZhiLin_ChangDu[0x20-1] = 8;
    ZhiLin_ChangDu[0x21-1] = 8;
    ZhiLin_ChangDu[0x22-1] = 13;
    ZhiLin_ChangDu[0x23-1] = 12;
    ZhiLin_ChangDu[0x24-1] = 12;
}
void ZhiLinZhiXing(uchar *GongNeng_HuanCun,uchar FanHui_Flag)
{	
    //LED控制参数初始化
    u8 PWMxx = PWM00;
    u8 breath_state = HIGH;
    u16 periodBreath_cntCmp = 0x03e8;
    u16 periodGradChange_cntCmp = 0x03e8;
    u16 periodFlash_cntCmp = 0x0032;
    u8 waveBreathChangeFlash_start = 0;
    u8 waveBreathChangeFlash_end = 49;
    u8 waveBreathChangeFlash_now = 0;

	switch(GongNeng_HuanCun[0])
	{
		case 1://按位搜寻模块序列号
			if((GongNeng_HuanCun[1]&XuLieHao[0])==0)
				if((GongNeng_HuanCun[2]&XuLieHao[1])==0)
					if((GongNeng_HuanCun[3]&XuLieHao[2])==0)
						if((GongNeng_HuanCun[4]&XuLieHao[3])==0)
							if((GongNeng_HuanCun[5]&XuLieHao[4])==0)
							{
								if((IapReadByte(0x0000)==0)&&(IapReadByte(0x0001)==0))
								{
                                    SendData2(0x02);
									SouXunXuLie_Time=1;
								}
							}
            break;	
		case 2://编号赋值 a5 ff ff 02 cc 00 00 00 00 00 02 14 0c
			if((GongNeng_HuanCun[1]==XuLieHao[0])&&(GongNeng_HuanCun[2]==XuLieHao[1])&&(GongNeng_HuanCun[3]==XuLieHao[2])&&(GongNeng_HuanCun[4]==XuLieHao[3])&&(GongNeng_HuanCun[5]==XuLieHao[4]))
			{
				uchar BianHao_HuanCun[2];
				BianHao_HuanCun[0]=GongNeng_HuanCun[6];
				BianHao_HuanCun[1]=GongNeng_HuanCun[7];
				EEPROM_Write_Str(0x0000,BianHao_HuanCun,2);
				BiaoHaoFuZhi_Time=1;
			}
            break;//a5 ff ff 02 52 61 01 02 03 52 61 96 8a
		case 3://输出开
            
			if(FanHui_Flag==0)
			{
				FaSong_HuanCun[0]=3;
				FaSong_HuanCun[1]=IapReadByte(0x0000);
				FaSong_HuanCun[2]=IapReadByte(0x0001);
				ZhiLingFaSong(3);
			}
            break;//a5 ff ff 03 01 40   a5 00 02 03 A1 30
		case 4://输出关
			if(FanHui_Flag==0)
			{
				FaSong_HuanCun[0]=4;
				FaSong_HuanCun[1]=IapReadByte(0x0000);
				FaSong_HuanCun[2]=IapReadByte(0x0001);
				ZhiLingFaSong(3);
			}
            break;//a5 ff ff 04 c3 01
		case 5://亮度调节
			if(FanHui_Flag==0)
			{
				FaSong_HuanCun[0]=5;
				FaSong_HuanCun[1]=IapReadByte(0x0000);
				FaSong_HuanCun[2]=IapReadByte(0x0001);
				FaSong_HuanCun[3]=GongNeng_HuanCun[1];
				FaSong_HuanCun[4]=GongNeng_HuanCun[2];
				ZhiLingFaSong(5);
			}
            break;//a5 ff ff 05 03 a0 89 10
		case 6://联动效果执行
            LED_PACK_id = GongNeng_HuanCun[1] * 256 + GongNeng_HuanCun[2];
            if( LED_PACK_id == 0 )
            {
                memcpy( &LED_displayPackArr[0][0], &GongNeng_HuanCun[2], PACKCOL );
            }
            LED_displayPackPlayer(LED_PACK_id);

			if(FanHui_Flag==0)
			{
				FaSong_HuanCun[0]=6;
				FaSong_HuanCun[1]=IapReadByte(0x0000);
				FaSong_HuanCun[2]=IapReadByte(0x0001);
				ZhiLingFaSong(3);
			}
            break;//a5 ff ff 06 00 01 
		case 7://编号清除
			BianHao_QingChu[0]=0x00;
			BianHao_QingChu[1]=0x00;
			EEPROM_Write_Str(0x0000,BianHao_QingChu,2);
			FaSong_HuanCun[0]=7;
			FaSong_HuanCun[1]=IapReadByte(0x0000);
			FaSong_HuanCun[2]=IapReadByte(0x0001);
			ZhiLingFaSong(3);
            break;//a5 ff ff 07 c2 41
        case 0x20://LED开关

            PWMxx = GongNeng_HuanCun[1];
            breath_state = GongNeng_HuanCun[2];
        SendData(breath_state);
            LED_breathInit(PWMxx, breath_state, periodBreath_cntCmp, periodGradChange_cntCmp, periodFlash_cntCmp, waveBreathChangeFlash_start, waveBreathChangeFlash_end,waveBreathChangeFlash_now);
            break;
		case 0x21://LED亮度设定

            PWMxx = GongNeng_HuanCun[1];
            breath_state = GongNeng_HuanCun[2];
        SendData(breath_state);
            LED_breathInit(PWMxx, breath_state, periodBreath_cntCmp, periodGradChange_cntCmp, periodFlash_cntCmp, waveBreathChangeFlash_start, waveBreathChangeFlash_end,waveBreathChangeFlash_now);
            break;
		case 0x22://LED循环呼吸
            
            PWMxx = GongNeng_HuanCun[1];
            breath_state = GongNeng_HuanCun[2];
        SendData(breath_state);
            periodBreath_cntCmp = GongNeng_HuanCun[3]*256 + GongNeng_HuanCun[4];
            waveBreathChangeFlash_start = GongNeng_HuanCun[5];
            waveBreathChangeFlash_end  = GongNeng_HuanCun[6];
            waveBreathChangeFlash_now = GongNeng_HuanCun[7];
            LED_breathInit(PWMxx, breath_state, periodBreath_cntCmp, periodGradChange_cntCmp, periodFlash_cntCmp, waveBreathChangeFlash_start, waveBreathChangeFlash_end,waveBreathChangeFlash_now);
            break;
		case 0x23://LED循环（单次）渐变
            
            PWMxx = GongNeng_HuanCun[1];
            breath_state = GongNeng_HuanCun[2];
        SendData(breath_state);
            periodGradChange_cntCmp    = GongNeng_HuanCun[3]*256 + GongNeng_HuanCun[4];
            waveBreathChangeFlash_start = GongNeng_HuanCun[5];
            waveBreathChangeFlash_end  = GongNeng_HuanCun[6];
            waveBreathChangeFlash_now = GongNeng_HuanCun[7];
            LED_breathInit(PWMxx, breath_state, periodBreath_cntCmp, periodGradChange_cntCmp, periodFlash_cntCmp, waveBreathChangeFlash_start, waveBreathChangeFlash_end,waveBreathChangeFlash_now);
            break;
		case 0x24://LED循环闪烁
            
            PWMxx = GongNeng_HuanCun[1];
            breath_state = GongNeng_HuanCun[2];
        SendData(breath_state);
            periodFlash_cntCmp = GongNeng_HuanCun[3]*256 + GongNeng_HuanCun[4];
            waveBreathChangeFlash_start = GongNeng_HuanCun[5];
            waveBreathChangeFlash_end  = GongNeng_HuanCun[6];
            waveBreathChangeFlash_now = waveBreathChangeFlash_start;
            LED_breathInit(PWMxx, breath_state, periodBreath_cntCmp, periodGradChange_cntCmp, periodFlash_cntCmp, waveBreathChangeFlash_start, waveBreathChangeFlash_end,waveBreathChangeFlash_now);
            break;
	}
}

void ZongZhiXin(void)
{	
	if(SouXunXuLie_Time>0)
	{
		SouXunXuLie_Time=0;
		FaSong_HuanCun[0]=1;
		ZhiLingFaSong(1);
	}
	if(BiaoHaoFuZhi_Time>5)
	{
		BiaoHaoFuZhi_Time=0;
		FaSong_HuanCun[0]=2;
		FaSong_HuanCun[1]=IapReadByte(0x0000);
		FaSong_HuanCun[2]=IapReadByte(0x0001);
		FaSong_HuanCun[3]=XuLieHao[0];
		FaSong_HuanCun[4]=XuLieHao[1];
		FaSong_HuanCun[5]=XuLieHao[2];
		FaSong_HuanCun[6]=XuLieHao[3];
		FaSong_HuanCun[7]=XuLieHao[4];
		ZhiLingFaSong(8);
	}
}



