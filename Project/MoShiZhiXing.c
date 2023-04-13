#include "main.h"
extern uchar JiGuanZhuangTai,LaiYuanHao,Menu_Key1,Menu_Key2,Menu_Key3,Menu_Key4;
uchar BaoShan_flag=0,BaoShanMoShi=1;
uint YanShiChuFa_Time=0,BaoShan_Time=0,BaoShan_Delay=0;
void GongNeng1(void)				          	//
{
	XieYiFaSong(LaiYuanHao,0x19);
	delay_ms(10);
	XieYiFaSong(0x00,0x18);	  
	JiGuanZhuangTai=1;
}
void GongNeng2(void)
{
	XieYiFaSong(LaiYuanHao,0x29);
	delay_ms(10);
	XieYiFaSong(0x00,0x28);	  
	JiGuanZhuangTai=2;
}
void GongNeng3(void)
{
	XieYiFaSong(LaiYuanHao,0x39); 
	JiGuanZhuangTai=3;	 
	delay_ms(10);
	XieYiFaSong(0x00,0x38);	
}  
void GongNeng4(void)
{
	XieYiFaSong(LaiYuanHao,0x49);
	delay_ms(10);
	JiGuanZhuangTai=4;	
	XieYiFaSong(0x00,0x48);	 
}  
void GongNeng5(void)
{
	XieYiFaSong(LaiYuanHao,0x59);
	delay_ms(10);
	JiGuanZhuangTai=5;	
	XieYiFaSong(0x00,0x58);
}  
void GongNeng6(void)
{
	XieYiFaSong(LaiYuanHao,0x69);
	delay_ms(10);
	JiGuanZhuangTai=6;	
	XieYiFaSong(0x00,0x68);
}  
void GongNeng7(void)
{
	XieYiFaSong(LaiYuanHao,0x79);
	delay_ms(10);
	JiGuanZhuangTai=7;	
	XieYiFaSong(0x00,0x78);
}
void ZongJiZhuangTaiHuiFu(void)
{
	XieYiFaSong(0x00,JiGuanZhuangTai*16+0x08);	
}
void ZongZhiXing(void)
{		
	Key();
	if(JiGuanZhuangTai==1)
	{	
	}
	if(JiGuanZhuangTai==2)
	{
		JiDianQi=0;	
	}
	if(JiGuanZhuangTai==3)
	{	
	}
}
void ZiFuWei(void)
{

}
void IOMoShi_Init(void)
{		
	P3M1=0x01;
	P3M0=0x02;
	if(CeIO1_MoShi==0)
	{
		P0M1=P0M1|0x10;
		P0M0=P0M0&0xef;	
	}else if(CeIO1_MoShi==1){
		P0M1=P0M1&0xef;
		P0M0=P0M0|0x10;
	}else if(CeIO1_MoShi==2){
		P0M1=P0M1&0xef;
		P0M0=P0M0&0xef;
	}else if(CeIO1_MoShi==3){
		P0M1=P0M1|0x10;
		P0M0=P0M0|0x10;
	}
	if(CeIO2_MoShi==0)
	{
		P0M1=P0M1|0x20;
		P0M0=P0M0&0xdf;	
	}else if(CeIO2_MoShi==1){
		P0M1=P0M1&0xdf;
		P0M0=P0M0|0x20;
	}else if(CeIO2_MoShi==2){
		P0M1=P0M1&0xdf;
		P0M0=P0M0&0xdf;
	}else if(CeIO2_MoShi==3){
		P0M1=P0M1|0x20;
		P0M0=P0M0|0x20;
	}
	if(CeIO3_MoShi==0)
	{
		P1M1=P1M1|0x10;
		P1M0=P1M0&0xef;	
	}else if(CeIO3_MoShi==1){
		P1M1=P1M1&0xef;
		P1M0=P1M0|0x10;
	}else if(CeIO3_MoShi==2){
		P1M1=P1M1&0xef;
		P1M0=P1M0&0xef;
	}else if(CeIO3_MoShi==3){
		P1M1=P1M1|0x10;
		P1M0=P1M0|0x10;
	}
	if(CeIO4_MoShi==0)
	{
		P1M1=P1M1|0x20;
		P1M0=P1M0&0xdf;	
	}else if(CeIO4_MoShi==1){
		P1M1=P1M1&0xdf;
		P1M0=P1M0|0x20;
	}else if(CeIO4_MoShi==2){
		P1M1=P1M1&0xdf;
		P1M0=P1M0&0xdf;
	}else if(CeIO4_MoShi==3){
		P1M1=P1M1|0x20;
		P1M0=P1M0|0x20;
	}
	if(CeIO5_MoShi==0)
	{
		P1M1=P1M1|0x40;
		P1M0=P1M0&0xbf;	
	}else if(CeIO5_MoShi==1){
		P1M1=P1M1&0xbf;
		P1M0=P1M0|0x40;
	}else if(CeIO5_MoShi==2){
		P1M1=P1M1&0xbf;
		P1M0=P1M0&0xbf;
	}else if(CeIO5_MoShi==3){
		P1M1=P1M1|0x40;
		P1M0=P1M0|0x40;
	}
	if(CeIO6_MoShi==0)
	{
		P1M1=P1M1|0x80;
		P1M0=P1M0&0x7f;	
	}else if(CeIO6_MoShi==1){
		P1M1=P1M1&0x7f;
		P1M0=P1M0|0x80;
	}else if(CeIO6_MoShi==2){
		P1M1=P1M1&0x7f;
		P1M0=P1M0&0x7f;
	}else if(CeIO6_MoShi==3){
		P1M1=P1M1|0x80;
		P1M0=P1M0|0x80;
	}
	if(LED_R1_MoShi==0)
	{
		P4M1=P4M1|0x20;
		P4M0=P4M0&0xdf;	
	}else if(LED_R1_MoShi==1){
		P4M1=P4M1&0xdf;
		P4M0=P4M0|0x20;
	}else if(LED_R1_MoShi==2){
		P4M1=P4M1&0xdf;
		P4M0=P4M0&0xdf;
	}else if(LED_R1_MoShi==3){
		P4M1=P4M1|0x20;
		P4M0=P4M0|0x20;
	}
	if(LED_G1_MoShi==0)
	{
		P2M1=P2M1|0x80;
		P2M0=P2M0&0x7f;	
	}else if(LED_G1_MoShi==1){
		P2M1=P2M1&0x7f;
		P2M0=P2M0|0x80;
	}else if(LED_G1_MoShi==2){
		P2M1=P2M1&0x7f;
		P2M0=P2M0&0x7f;
	}else if(LED_G1_MoShi==3){
		P2M1=P2M1|0x80;
		P2M0=P2M0|0x80;
	}
	if(LED_B1_MoShi==0)
	{
		P2M1=P2M1|0x40;
		P2M0=P2M0&0xbf;	
	}else if(LED_B1_MoShi==1){
		P2M1=P2M1&0xbf;
		P2M0=P2M0|0x40;
	}else if(LED_B1_MoShi==2){
		P2M1=P2M1&0xbf;
		P2M0=P2M0&0xbf;
	}else if(LED_B1_MoShi==3){
		P2M1=P2M1|0x40;
		P2M0=P2M0|0x40;
	}
	if(OUT1_MoShi==0)
	{
		P2M1=P2M1|0x20;
		P2M0=P2M0&0xdf;	
	}else if(OUT1_MoShi==1){
		P2M1=P2M1&0xdf;
		P2M0=P2M0|0x20;
	}else if(OUT1_MoShi==2){
		P2M1=P2M1&0xdf;
		P2M0=P2M0&0xdf;
	}else if(OUT1_MoShi==3){
		P2M1=P2M1|0x20;
		P2M0=P2M0|0x20;
	}
	if(LED_R2_MoShi==0)
	{
		P2M1=P2M1|0x10;
		P2M0=P2M0&0xef;	
	}else if(LED_R2_MoShi==1){
		P2M1=P2M1&0xef;
		P2M0=P2M0|0x10;
	}else if(LED_R2_MoShi==2){
		P2M1=P2M1&0xef;
		P2M0=P2M0&0xef;
	}else if(LED_R2_MoShi==3){
		P2M1=P2M1|0x10;
		P2M0=P2M0|0x10;
	}
	if(LED_G2_MoShi==0)
	{
		P2M1=P2M1|0x08;
		P2M0=P2M0&0xf7;	
	}else if(LED_G2_MoShi==1){
		P2M1=P2M1&0xf7;
		P2M0=P2M0|0x08;
	}else if(LED_G2_MoShi==2){
		P2M1=P2M1&0xf7;
		P2M0=P2M0&0xf7;
	}else if(LED_G2_MoShi==3){
		P2M1=P2M1|0x08;
		P2M0=P2M0|0x08;
	}
	if(LED_B2_MoShi==0)
	{
		P2M1=P2M1|0x04;
		P2M0=P2M0&0xfb;	
	}else if(LED_B2_MoShi==1){
		P2M1=P2M1&0xfb;
		P2M0=P2M0|0x04;
	}else if(LED_B2_MoShi==2){
		P2M1=P2M1&0xfb;
		P2M0=P2M0&0xfb;
	}else if(LED_B2_MoShi==3){
		P2M1=P2M1|0x04;
		P2M0=P2M0|0x04;
	}
	if(OUT2_MoShi==0)
	{
		P2M1=P2M1|0x02;
		P2M0=P2M0&0xfd;	
	}else if(OUT2_MoShi==1){
		P2M1=P2M1&0xfd;
		P2M0=P2M0|0x02;
	}else if(OUT2_MoShi==2){
		P2M1=P2M1&0xfd;
		P2M0=P2M0&0xfd;
	}else if(OUT2_MoShi==3){
		P2M1=P2M1|0x02;
		P2M0=P2M0|0x02;
	}
	if(LED_R3_MoShi==0)
	{
		P2M1=P2M1|0x01;
		P2M0=P2M0&0xfe;	
	}else if(LED_R3_MoShi==1){
		P2M1=P2M1&0xfe;
		P2M0=P2M0|0x01;
	}else if(LED_R3_MoShi==2){
		P2M1=P2M1&0xfe;
		P2M0=P2M0&0xfe;
	}else if(LED_R3_MoShi==3){
		P2M1=P2M1|0x01;
		P2M0=P2M0|0x01;
	}
	if(LED_G3_MoShi==0)
	{
		P4M1=P4M1|0x10;
		P4M0=P4M0&0xef;	
	}else if(LED_G3_MoShi==1){
		P4M1=P4M1&0xef;
		P4M0=P4M0|0x10;
	}else if(LED_G3_MoShi==2){
		P4M1=P4M1&0xef;
		P4M0=P4M0&0xef;
	}else if(LED_G3_MoShi==3){
		P4M1=P4M1|0x10;
		P4M0=P4M0|0x10;
	}
	if(LED_B3_MoShi==0)
	{
		P4M1=P4M1|0x04;
		P4M0=P4M0&0xfb;	
	}else if(LED_B3_MoShi==1){
		P4M1=P4M1&0xfb;
		P4M0=P4M0|0x04;
	}else if(LED_B3_MoShi==2){
		P4M1=P4M1&0xfb;
		P4M0=P4M0&0xfb;
	}else if(LED_B3_MoShi==3){
		P4M1=P4M1|0x04;
		P4M0=P4M0|0x04;
	}
	if(OUT3_MoShi==0)
	{
		P4M1=P4M1|0x02;
		P4M0=P4M0&0xfd;	
	}else if(OUT3_MoShi==1){
		P4M1=P4M1&0xfd;
		P4M0=P4M0|0x02;
	}else if(OUT3_MoShi==2){
		P4M1=P4M1&0xfd;
		P4M0=P4M0&0xfd;
	}else if(OUT3_MoShi==3){
		P4M1=P4M1|0x02;
		P4M0=P4M0|0x02;
	}
	if(LED_R4_MoShi==0)
	{
		P3M1=P3M1|0x80;
		P3M0=P3M0&0x7f;	
	}else if(LED_R4_MoShi==1){
		P3M1=P3M1&0x7f;
		P3M0=P3M0|0x80;
	}else if(LED_R4_MoShi==2){
		P3M1=P3M1&0x7f;
		P3M0=P3M0&0x7f;
	}else if(LED_R4_MoShi==3){
		P3M1=P3M1|0x80;
		P3M0=P3M0|0x80;
	}
	if(LED_G4_MoShi==0)
	{
		P3M1=P3M1|0x40;
		P3M0=P3M0&0xbf;	
	}else if(LED_G4_MoShi==1){
		P3M1=P3M1&0xbf;
		P3M0=P3M0|0x40;
	}else if(LED_G4_MoShi==2){
		P3M1=P3M1&0xbf;
		P3M0=P3M0&0xbf;
	}else if(LED_G4_MoShi==3){
		P4M1=P4M1|0x40;
		P4M0=P4M0|0x40;
	}
	if(LED_B4_MoShi==0)
	{
		P3M1=P3M1|0x20;
		P3M0=P3M0&0xdf;	
	}else if(LED_B4_MoShi==1){
		P3M1=P3M1&0xdf;
		P3M0=P3M0|0x20;
	}else if(LED_B4_MoShi==2){
		P3M1=P3M1&0xdf;
		P3M0=P3M0&0xdf;
	}else if(LED_B4_MoShi==3){
		P3M1=P3M1|0x20;
		P3M0=P3M0|0x20;
	}
	if(OUT4_MoShi==0)
	{
		P3M1=P3M1|0x10;
		P3M0=P3M0&0xef;	
	}else if(OUT4_MoShi==1){
		P3M1=P3M1&0xef;
		P3M0=P3M0|0x10;
	}else if(OUT4_MoShi==2){
		P3M1=P3M1&0xef;
		P3M0=P3M0&0xef;
	}else if(OUT4_MoShi==3){
		P3M1=P3M1|0x10;
		P3M0=P3M0|0x10;
	}  
	if(JiDianQi_MoShi==0)
	{
		P5M1=P5M1|0x10;
		P5M0=P5M0&0xef;	
	}else if(JiDianQi_MoShi==1){
		P5M1=P5M1&0xef;
		P5M0=P5M0|0x10;
	}else if(JiDianQi_MoShi==2){
		P5M1=P5M1&0xef;
		P5M0=P5M0&0xef;
	}else if(JiDianQi_MoShi==3){
		P5M1=P5M1|0x10;
		P5M0=P5M0|0x10;
	}
} 
void IO_Init(void)
{ 
	JiDianQi=0;			  	//
	CeIO1=0;			  	//
	CeIO2=0;			  	//
	CeIO3=0;			  	//
	CeIO4=0;			  	//
	CeIO5=0;			  	//
	CeIO6=0;			  	//
	LED_R1=0;			  	//
	LED_G1=0;			  	//
	LED_B1=0;			  	//
	OUT1=0;			  		//
	LED_R2=0;			  	//
	LED_G2=0;			  	//
	LED_B2=0;			  	//
	OUT2=0;			  		//
	LED_R3=0;			  	//
	LED_G3=0;			  	//
	LED_B3=0;			  	//
	OUT3=0;			  		//
	LED_R4=0;			  	//
	LED_G4=0;			  	//
	LED_B4=0;			  	//
	OUT4=0;			  		//
}
void BaoShanXiaoGuo()
{
	BaoShan_Time++;
	if(BaoShanMoShi==1)
	{
		BaoShanDeng=0;
		BaoShan_Time=0;
	}else if(BaoShanMoShi==2){
		BaoShanDeng=1;
		BaoShan_Time=0;
	}else if(BaoShanMoShi==3){
		if(BaoShan_Time==1)
			BaoShanDeng=1;
		if(BaoShan_Time==1000)
			BaoShanDeng=0;
		if(BaoShan_Time==1200)
			BaoShanDeng=1;
		if(BaoShan_Time==3500)
			BaoShanDeng=0;
		if(BaoShan_Time==3800)
			BaoShanDeng=1;
		if(BaoShan_Time==4000)
			BaoShanDeng=0;
		if(BaoShan_Time==4200)
			BaoShanDeng=1;
		if(BaoShan_Time==4500)
			BaoShanDeng=0;
		if(BaoShan_Time==4600)
			BaoShanDeng=1;
		if(BaoShan_Time==5500)
			BaoShanDeng=0;
		if(BaoShan_Time==5600)
			BaoShanDeng=1;
		if(BaoShan_Time==6000)
			BaoShanDeng=0;
		if(BaoShan_Time==6200)
			BaoShanDeng=1;
		if(BaoShan_Time==7200)
			BaoShan_Time=0;
	}else if(BaoShanMoShi==4){
		if(BaoShan_Time==1)
			BaoShanDeng=1;
		if(BaoShan_Time==1000)
			BaoShanDeng=0;
		if(BaoShan_Time==2500)
			BaoShan_Time=0;
	}
}