#include "main.h"
uint ZongXunHuan_i=0,GongNen_i=0,GongNen_j=0,ZongZhiXin_i=0,ZongZhiXin_j=0;
ulong Delay_Time[5],MuBiao_Time[5],JianBian_Time1=0,JianBian_Time2=0;
uint Delay_Addr[5];
uint GongNen_Addr_Shou[5],GongNen_Addr_Wei[5],XunHuan_Changdu=0,XunHuan_ZhiZhen=0,XunHuan_Addr=0;
char LiangDu_ChuShi=0,LiangDu_JieShu=0,LiangDu_DangQian=0;
long LiangDu_HuanCun=0;
uchar BianHao_QingChu[2],SouXunXuLie_Time=0,BiaoHaoFuZhi_Time=0;
uint Time=0,Time_i=0;


SlaveTypeDef Slave = { 0 };

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
    //初始化从机结构体
    {
        //读取从机结构体到缓存
        EEPROM_Read_Str(0x0000,(u8*)&Slave,sizeof(Slave));
        //初始化序列号
        Slave.serialArr[0] = 0x01;
        Slave.serialArr[1] = 0x00;
        Slave.serialArr[2] = 0x0a;
        Slave.serialArr[3] = 0x0a;
        Slave.serialArr[4] = 0x0a;
        //未被赋值编号，则清除编号
        if( Slave.assignArr[0] == 0xff && Slave.assignArr[1] == 0xff )
        {
            Slave.assignArr[0] = 0x00;
            Slave.assignArr[1] = 0x00;
        }
        //写从机结构体到flash
        EEPROM_Write_Str(0x0000,(u8*)&Slave,sizeof(Slave));   
    }

    ZhiLin_ChangDu[0x01-1] = 11; //按位搜寻模块序列号
    ZhiLin_ChangDu[0x02-1] = 13; //编号赋值
    ZhiLin_ChangDu[0x06-1] = 8; //联动效果执行
    ZhiLin_ChangDu[0x07-1] = 6; //编号清除
    ZhiLin_ChangDu[0x0b-1] = 6; //检测从机在线状态
    
    ZhiLin_ChangDu[0x20-1] = 8;//LED通电
    ZhiLin_ChangDu[0x21-1] = 8;//LED断电
    ZhiLin_ChangDu[0x22-1] = 9;//LED亮度设定
    ZhiLin_ChangDu[0x23-1] = 13;//LED单次渐变
    ZhiLin_ChangDu[0x24-1] = 16;//LED循环呼吸
    ZhiLin_ChangDu[0x25-1] = 16;//LED循环闪烁
    
    ZhiLin_ChangDu[0x30-1] = 8;//LOCK通电
    ZhiLin_ChangDu[0x31-1] = 8;//LOCK断电
    ZhiLin_ChangDu[0x32-1] = 11;//LOCK断后通
    ZhiLin_ChangDu[0x33-1] = 11;//LOCK通后断
    
#ifdef LED
    LED_breathInit(LED1_PORT, CLOSE, 0x00, 0x001e, 0x003c, 10, 100, 10);
    LED_breathInit(LED2_PORT, CLOSE, 0x00, 0x001e, 0x003c, 10, 100, 10);
    LED_breathInit(LED3_PORT, CLOSE, 0x00, 0x001e, 0x003c, 10, 100, 10);  
    LED_breathInit(LED4_PORT, CLOSE, 0x00, 0x001e, 0x003c, 10, 100, 10);
    LED_breathInit(LED5_PORT, CLOSE, 0x00, 0x001e, 0x003c, 10, 100, 10);
    LED_breathInit(LED6_PORT, CLOSE, 0x00, 0x001e, 0x003c, 10, 100, 10);
    LED_breathInit(LED7_PORT, CLOSE, 0x00, 0x001e, 0x003c, 10, 100, 10);  
    LED_breathInit(LED8_PORT, CLOSE, 0x00, 0x001e, 0x003c, 10, 100, 10);
#endif
#ifdef LOCK
    LOCK_Init( LOCK1_PORT, CLOSE, 0 );
    LOCK_Init( LOCK2_PORT, CLOSE, 0 );
    LOCK_Init( LOCK3_PORT, CLOSE, 0 );
    LOCK_Init( LOCK4_PORT, CLOSE, 0 );
    LOCK_Init( LOCK5_PORT, CLOSE, 0 );
    LOCK_Init( LOCK6_PORT, CLOSE, 0 );
    LOCK_Init( LOCK7_PORT, CLOSE, 0 );
    LOCK_Init( LOCK8_PORT, CLOSE, 0 );
#endif
}
void ZhiLinZhiXing(uchar *GongNeng_HuanCun,uchar FanHui_Flag)
{	
    //LED控制参数初始化
    u8 LEDx_PORT = LED1_PORT;
    u8 led_state = CLOSE;
    u8 light = 0x00;
    u16 periodBreathFlash1_cntCmp = 0x03e8;
    u16 periodChangeFlash2_cntCmp = 0x03e8;
    u8 waveBreathChangeFlash_low = 0;
    u8 waveBreathChangeFlash_high = 100;
    u8 waveBreathChangeFlash_start = 0;
    //电磁锁控制参数初始化
    u8 LOCKx_PORT = LED1_PORT;
    u8 lock_state = OPEN;
    u32 lock_delayTime = 0;
    //如果是广播指令，则FanHui_Flag == 1, 不返回
    if( FanHui_Flag );
	switch(GongNeng_HuanCun[0])
	{
/*通用控制*/
		case 1: //按位搜寻模块序列号
			if((GongNeng_HuanCun[1]&Slave.serialArr[0])==0)
				if((GongNeng_HuanCun[2]&Slave.serialArr[1])==0)
					if((GongNeng_HuanCun[3]&Slave.serialArr[2])==0)
						if((GongNeng_HuanCun[4]&Slave.serialArr[3])==0)
							if((GongNeng_HuanCun[5]&Slave.serialArr[4])==0)
							{
								if((Slave.assignArr[0]==0)&&(Slave.assignArr[1]==0))
								{
									SouXunXuLie_Time=1;
								}
							}
        break;
		case 2: //编号赋值 a5 ff ff 02 cc 00 00 00 00 00 02 14 0c
			if((GongNeng_HuanCun[1]==Slave.serialArr[0])&&(GongNeng_HuanCun[2]==Slave.serialArr[1])&&(GongNeng_HuanCun[3]==Slave.serialArr[2])&&(GongNeng_HuanCun[4]==Slave.serialArr[3])&&(GongNeng_HuanCun[5]==Slave.serialArr[4]))
			{
				Slave.assignArr[0]=GongNeng_HuanCun[6];
				Slave.assignArr[1]=GongNeng_HuanCun[7];
                EEPROM_Write_Str(0x0000,(u8*)&Slave,sizeof(Slave));                   //写从机结构体到flash
				BiaoHaoFuZhi_Time=1;
			}
        break;
		case 6: //联动效果执行
            //从机执行
            {
                LED_PACK_id = GongNeng_HuanCun[1] * 256 + GongNeng_HuanCun[2];
                if( LED_PACK_id == 0 )
                {
                    memcpy( &LED_displayPackArr[0][0], &GongNeng_HuanCun[2], PACKCOL );
                }
                LED_displayPackPlayer(LED_PACK_id);
            }
			//返回主机
			{
				FaSong_HuanCun[0]=6;
				FaSong_HuanCun[1]=Slave.assignArr[0];
				FaSong_HuanCun[2]=Slave.assignArr[1];
				ZhiLingFaSong(3);
			}
        break;//a5 ff ff 06 00 01 
		case 7: //编号清除
            //从机执行
            {
				Slave.assignArr[0]=0x00;
				Slave.assignArr[1]=0x00;
                EEPROM_Write_Str(0x0000,(u8*)&Slave,sizeof(Slave));                   //写从机结构体到flash
            }
            //返回主机
            {
                FaSong_HuanCun[0]=7;
                FaSong_HuanCun[1]=Slave.assignArr[0];
                FaSong_HuanCun[2]=Slave.assignArr[1];
                ZhiLingFaSong(3);
            }
        break;//a5 ff ff 07 c2 41
        case 0x0b: //检测从机在线状态
            //返回主机
            {
                FaSong_HuanCun[0]=0x0b;
                FaSong_HuanCun[1]=Slave.assignArr[0];
                FaSong_HuanCun[2]=Slave.assignArr[1];
                ZhiLingFaSong(3);
            }
        break;
/*LED模块控制*/
        case 0x20://LED通电
            //从机执行
            {
                LEDx_PORT = GongNeng_HuanCun[1];
                led_state = GongNeng_HuanCun[2];
                LED_breathInit(LEDx_PORT, led_state, light, periodBreathFlash1_cntCmp, periodChangeFlash2_cntCmp, waveBreathChangeFlash_low, waveBreathChangeFlash_high,waveBreathChangeFlash_start);
            }
			//返回主机
            {
				FaSong_HuanCun[0]=GongNeng_HuanCun[0];//功能帧
				FaSong_HuanCun[1]=Slave.assignArr[0];//编号H
				FaSong_HuanCun[2]=Slave.assignArr[1];//编号L
                FaSong_HuanCun[3]=GongNeng_HuanCun[1];//输出端口
                FaSong_HuanCun[4]=GongNeng_HuanCun[2];//LED执行状态
				ZhiLingFaSong(5);
			}
        break;
        case 0x21://LED断电
            //从机执行
            {
                LEDx_PORT = GongNeng_HuanCun[1];//输出端口
                led_state = GongNeng_HuanCun[2];//LED执行状态
                LED_breathInit(LEDx_PORT, led_state, light, periodBreathFlash1_cntCmp, periodChangeFlash2_cntCmp, waveBreathChangeFlash_low, waveBreathChangeFlash_high,waveBreathChangeFlash_start);
            }
			//返回主机
            {
				FaSong_HuanCun[0]=GongNeng_HuanCun[0];//功能帧
				FaSong_HuanCun[1]=Slave.assignArr[0];//编号H
				FaSong_HuanCun[2]=Slave.assignArr[1];//编号L
                FaSong_HuanCun[3]=GongNeng_HuanCun[1];//输出端口
                FaSong_HuanCun[4]=GongNeng_HuanCun[2];//LED执行状态
				ZhiLingFaSong(5);
			}
        break;
		case 0x22://LED亮度设定
            //从机执行
            {
                LEDx_PORT = GongNeng_HuanCun[1];//输出端口
                led_state = GongNeng_HuanCun[2];//LED执行状态
                light = GongNeng_HuanCun[3];//LED亮度值
                LED_breathInit(LEDx_PORT, led_state, light, periodBreathFlash1_cntCmp, periodChangeFlash2_cntCmp, waveBreathChangeFlash_low, waveBreathChangeFlash_high,waveBreathChangeFlash_start);
            }
			//返回主机
            {
				FaSong_HuanCun[0]=GongNeng_HuanCun[0];//功能帧
				FaSong_HuanCun[1]=Slave.assignArr[0];//编号H
				FaSong_HuanCun[2]=Slave.assignArr[1];//编号L
                FaSong_HuanCun[3]=GongNeng_HuanCun[1];//输出端口
                FaSong_HuanCun[4]=GongNeng_HuanCun[2];//LED执行状态
                FaSong_HuanCun[5]=GongNeng_HuanCun[3];//LED亮度值
				ZhiLingFaSong(6);
			}
        break;
		case 0x23://LED单次渐变
            //从机执行
            {
                LEDx_PORT = GongNeng_HuanCun[1];//输出端口
                led_state = GongNeng_HuanCun[2];//LED执行状态
                waveBreathChangeFlash_low = GongNeng_HuanCun[3];//LED初始亮度值
                periodChangeFlash2_cntCmp    = GongNeng_HuanCun[4]*0x10000 + GongNeng_HuanCun[5]*0x100 + GongNeng_HuanCun[6]*0x1;//LED渐变时间
                waveBreathChangeFlash_high  = GongNeng_HuanCun[7];//LED结束亮度值
                LED_breathInit(LEDx_PORT, led_state, light, periodBreathFlash1_cntCmp, periodChangeFlash2_cntCmp, waveBreathChangeFlash_low, waveBreathChangeFlash_high,waveBreathChangeFlash_start);
            }
			//返回主机
            {
				FaSong_HuanCun[0]=GongNeng_HuanCun[0];//功能帧
				FaSong_HuanCun[1]=Slave.assignArr[0];//编号H
				FaSong_HuanCun[2]=Slave.assignArr[1];//编号L
                FaSong_HuanCun[3]=GongNeng_HuanCun[1];//输出端口
                FaSong_HuanCun[4]=GongNeng_HuanCun[2];//LED执行状态
                FaSong_HuanCun[5]=GongNeng_HuanCun[3];//LED初始亮度值
                FaSong_HuanCun[6]=GongNeng_HuanCun[4];//LED渐变时间
                FaSong_HuanCun[7]=GongNeng_HuanCun[5];
                FaSong_HuanCun[8]=GongNeng_HuanCun[6];
                FaSong_HuanCun[9]=GongNeng_HuanCun[7];//LED结束亮度值
				ZhiLingFaSong(10);
			} 
        break;
		case 0x24://LED循环呼吸
            //从机执行
            {
                LEDx_PORT = GongNeng_HuanCun[1];//输出端口
                led_state = GongNeng_HuanCun[2];//LED执行状态
                waveBreathChangeFlash_high = GongNeng_HuanCun[3];//LED最高亮度值
                waveBreathChangeFlash_low = GongNeng_HuanCun[4];//  LED最低亮度值
                periodBreathFlash1_cntCmp  = GongNeng_HuanCun[5]*0x10000 + GongNeng_HuanCun[6]*0x100 + GongNeng_HuanCun[7]*0x1;//LED呼吸周期
                waveBreathChangeFlash_start = ( ( GongNeng_HuanCun[8]*0x10000 + GongNeng_HuanCun[9]*0x100 + GongNeng_HuanCun[10]*0x1 ) * 200 ) / periodBreathFlash1_cntCmp;//LED起始时间
                LED_breathInit(LEDx_PORT, led_state, light, periodBreathFlash1_cntCmp, periodChangeFlash2_cntCmp, waveBreathChangeFlash_low, waveBreathChangeFlash_high,waveBreathChangeFlash_start);
            }
			//返回主机
            {
				FaSong_HuanCun[0]=GongNeng_HuanCun[0];//功能帧
				FaSong_HuanCun[1]=Slave.assignArr[0];//编号H
				FaSong_HuanCun[2]=Slave.assignArr[1];//编号L
                FaSong_HuanCun[3]=GongNeng_HuanCun[1];//输出端口
                FaSong_HuanCun[4]=GongNeng_HuanCun[2];//LED执行状态
                FaSong_HuanCun[5]=GongNeng_HuanCun[3];//LED最高亮度值
                FaSong_HuanCun[6]=GongNeng_HuanCun[4];//LED最低亮度值
                FaSong_HuanCun[7]=GongNeng_HuanCun[5];//LED呼吸周期
                FaSong_HuanCun[8]=GongNeng_HuanCun[6];
                FaSong_HuanCun[9]=GongNeng_HuanCun[7];
                FaSong_HuanCun[10]=GongNeng_HuanCun[8];//LED起始时间
                FaSong_HuanCun[11]=GongNeng_HuanCun[9];
                FaSong_HuanCun[12]=GongNeng_HuanCun[10];
				ZhiLingFaSong(13);
			}
        break;
		case 0x25://LED循环闪烁
            //从机执行
            {
                LEDx_PORT = GongNeng_HuanCun[1];//输出端口
                led_state = GongNeng_HuanCun[2];//LED执行状态
                periodBreathFlash1_cntCmp = GongNeng_HuanCun[3]*0x10000 + GongNeng_HuanCun[4]*0x100 + GongNeng_HuanCun[5]*0x1;//LED亮时间
                periodChangeFlash2_cntCmp  = GongNeng_HuanCun[6]*0x10000 + GongNeng_HuanCun[7]*0x100 + GongNeng_HuanCun[8]*0x1;//LED灭时间
                waveBreathChangeFlash_high  = GongNeng_HuanCun[9];//LED最高亮度
                waveBreathChangeFlash_low = GongNeng_HuanCun[10];//LED最低亮度
                LED_breathInit(LEDx_PORT, led_state, light, periodBreathFlash1_cntCmp, periodChangeFlash2_cntCmp, waveBreathChangeFlash_low, waveBreathChangeFlash_high,waveBreathChangeFlash_start);
            }
			//返回主机
            {
				FaSong_HuanCun[0]=GongNeng_HuanCun[0];//功能帧
				FaSong_HuanCun[1]=Slave.assignArr[0];//编号H
				FaSong_HuanCun[2]=Slave.assignArr[1];//编号L
                FaSong_HuanCun[3]=GongNeng_HuanCun[1];//输出端口
                FaSong_HuanCun[4]=GongNeng_HuanCun[2];//LED执行状态
                FaSong_HuanCun[5]=GongNeng_HuanCun[3];//LED亮时间
                FaSong_HuanCun[6]=GongNeng_HuanCun[4];
                FaSong_HuanCun[7]=GongNeng_HuanCun[5];
                FaSong_HuanCun[8]=GongNeng_HuanCun[6];//LED灭时间
                FaSong_HuanCun[9]=GongNeng_HuanCun[7];
                FaSong_HuanCun[10]=GongNeng_HuanCun[8];
                FaSong_HuanCun[11]=GongNeng_HuanCun[9];//LED最高亮度
                FaSong_HuanCun[12]=GongNeng_HuanCun[10];//LED最低亮度
				ZhiLingFaSong(13);
			} 
        break;
/*电磁锁模块控制*/
		case 0x30://电磁锁通电
            //从机执行
            {
                LOCKx_PORT = GongNeng_HuanCun[1];
                lock_state = GongNeng_HuanCun[2];
                LOCK_Init(LOCKx_PORT, lock_state, lock_delayTime);
            }
			//返回主机
            {
				FaSong_HuanCun[0]=GongNeng_HuanCun[0];//功能帧
				FaSong_HuanCun[1]=Slave.assignArr[0];//编号H
				FaSong_HuanCun[2]=Slave.assignArr[1];//编号L
                FaSong_HuanCun[3]=GongNeng_HuanCun[1];//输出端口
                FaSong_HuanCun[4]=GongNeng_HuanCun[2];//LOCK执行状态
				ZhiLingFaSong(5);
			} 
        break;
		case 0x31://电磁锁断电
            //从机执行
            {
                LOCKx_PORT = GongNeng_HuanCun[1];
                lock_state = GongNeng_HuanCun[2];
                LOCK_Init(LOCKx_PORT, lock_state, lock_delayTime);
            }
			//返回主机
            {
				FaSong_HuanCun[0]=GongNeng_HuanCun[0];//功能帧
				FaSong_HuanCun[1]=Slave.assignArr[0];//编号H
				FaSong_HuanCun[2]=Slave.assignArr[1];//编号L
                FaSong_HuanCun[3]=GongNeng_HuanCun[1];//输出端口
                FaSong_HuanCun[4]=GongNeng_HuanCun[2];//LOCK执行状态
				ZhiLingFaSong(5);
			} 
        break;
		case 0x32://电磁锁断后通
            //从机执行
            {
                LOCKx_PORT = GongNeng_HuanCun[1];
                lock_state = GongNeng_HuanCun[2];
                lock_delayTime = GongNeng_HuanCun[3] * 0xffff + GongNeng_HuanCun[4] * 0xff + GongNeng_HuanCun[5] ;
                LOCK_Init(LOCKx_PORT, lock_state, lock_delayTime);
            }
			//返回主机
            {
				FaSong_HuanCun[0]=GongNeng_HuanCun[0];//功能帧
				FaSong_HuanCun[1]=Slave.assignArr[0];//编号H
				FaSong_HuanCun[2]=Slave.assignArr[1];//编号L
                FaSong_HuanCun[3]=GongNeng_HuanCun[1];//输出端口
                FaSong_HuanCun[4]=GongNeng_HuanCun[2];//LOCK执行状态
                FaSong_HuanCun[5]=GongNeng_HuanCun[3];//延时时间
                FaSong_HuanCun[6]=GongNeng_HuanCun[4];
                FaSong_HuanCun[7]=GongNeng_HuanCun[5];
				ZhiLingFaSong(8);
			} 
        break;
		case 0x33://电磁锁通后断
            //从机执行
            {
                LOCKx_PORT = GongNeng_HuanCun[1];
                lock_state = GongNeng_HuanCun[2];
                lock_delayTime = GongNeng_HuanCun[3] * 0xffff + GongNeng_HuanCun[4] * 0xff + GongNeng_HuanCun[5] ;
                LOCK_Init(LOCKx_PORT, lock_state, lock_delayTime);
            }
			//返回主机
            {
				FaSong_HuanCun[0]=GongNeng_HuanCun[0];//功能帧
				FaSong_HuanCun[1]=Slave.assignArr[0];//编号H
				FaSong_HuanCun[2]=Slave.assignArr[1];//编号L
                FaSong_HuanCun[3]=GongNeng_HuanCun[1];//输出端口
                FaSong_HuanCun[4]=GongNeng_HuanCun[2];//LOCK执行状态
                FaSong_HuanCun[5]=GongNeng_HuanCun[3];//延时时间
                FaSong_HuanCun[6]=GongNeng_HuanCun[4];
                FaSong_HuanCun[7]=GongNeng_HuanCun[5];
				ZhiLingFaSong(8);
			} 
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
		FaSong_HuanCun[1]=Slave.assignArr[0];
		FaSong_HuanCun[2]=Slave.assignArr[1];
		FaSong_HuanCun[3]=Slave.serialArr[0];
		FaSong_HuanCun[4]=Slave.serialArr[1];
		FaSong_HuanCun[5]=Slave.serialArr[2];
		FaSong_HuanCun[6]=Slave.serialArr[3];
		FaSong_HuanCun[7]=Slave.serialArr[4];
		ZhiLingFaSong(8);
	}
}



