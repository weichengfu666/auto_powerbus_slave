#include "main.h"
int led_ms=0,mimajishu=0,liangdenjishu=0,dangqiansheji=0,fuzhu9=0; 
uchar Ledmima1=1,Ledmima2=6,Ledmima3=11,Ledmima4=16; 
uchar tongguocishu=0,mimashezhizhuzu=0;
uchar mimashuzu[4][4][4]={{{2,6,3,13},{8,13,6,9},{12,15,5,8},{4,1,13,6}},
						  {{13,3,9,1},{16,3,8,7},{5,11,6,9},{5,7,9,10}},
						  {{2,16,3,4},{6,3,4,14},{3,5,9,1},{12,16,2,5}},
						  {{9,8,13,4},{2,14,11,6},{2,11,6,14},{6,8,2,13}}};
void mimashezhi(char mimazuhao,char mimaxuhao)
{
 	Ledmima1=mimashuzu[mimazuhao][mimaxuhao][0];
	Ledmima2=mimashuzu[mimazuhao][mimaxuhao][1];
	Ledmima3=mimashuzu[mimazuhao][mimaxuhao][2];
	Ledmima4=mimashuzu[mimazuhao][mimaxuhao][3]; 	
}
void led_init(void)
{
	Led1=Led1R;
	Led2=Led2R;
	Led3=Led3R;
	Led4=Led4R;
	Led5=Led5R;
	Led6=Led6R;
	Led7=Led7R;
	Led8=Led8R;
	Led9=Led9R;
	Led10=Led10R;
	Led11=Led11R;
	Led12=Led12R;
	Led13=Led13R;
	Led14=Led14R;
	Led15=Led15R;
	Led16=Led16R;
	mimajishu=0;
	fuzhu9=0;
	led_ms=0;
	dangqiansheji=0;
	liangdenjishu=0;
	delay_ms(1000);
}
void ledkey_on1(void)
{
   	Led1=Led1G;
	Led2=Led2G;
	Led3=Led3G;
	Led4=Led4G;
	Led5=Led5G;
	Led6=Led6G;
	Led7=Led7G;
	Led8=Led8G;
	Led9=Led9G;
	Led10=Led10G;
	Led11=Led11G;
	Led12=Led12G;
	Led13=Led13G;
	Led14=Led14G;
	Led15=Led15G;
	Led16=Led16G;
	delay_ms(1000);
}
void ledkey_on(void)
{
   	Led1=Led1G;
	Led2=Led2G;
	Led3=Led3G;
	Led4=Led4G;
	Led5=Led5G;
	Led6=Led6G;
	Led7=Led7G;
	Led8=Led8G;
	Led9=Led9G;
	Led10=Led10G;
	Led11=Led11G;
	Led12=Led12G;
	Led13=Led13G;
	Led14=Led14G;
	Led15=Led15G;
	Led16=Led16G;
	delay_ms(300);	
	Led1=Led1R;
	Led2=Led2R;
	Led3=Led3R;
	Led4=Led4R;
	Led5=Led5R;
	Led6=Led6R;
	Led7=Led7R;
	Led8=Led8R;
	Led9=Led9R;
	Led10=Led10R;
	Led11=Led11R;
	Led12=Led12R;
	Led13=Led13R;
	Led14=Led14R;
	Led15=Led15R;
	Led16=Led16R;
	delay_ms(300);
   	Led1=Led1G;
	Led2=Led2G;
	Led3=Led3G;
	Led4=Led4G;
	Led5=Led5G;
	Led6=Led6G;
	Led7=Led7G;
	Led8=Led8G;
	Led9=Led9G;
	Led10=Led10G;
	Led11=Led11G;
	Led12=Led12G;
	Led13=Led13G;
	Led14=Led14G;
	Led15=Led15G;
	Led16=Led16G;
	delay_ms(300);
	Led1=Led1R;
	Led2=Led2R;
	Led3=Led3R;
	Led4=Led4R;
	Led5=Led5R;
	Led6=Led6R;
	Led7=Led7R;
	Led8=Led8R;
	Led9=Led9R;
	Led10=Led10R;
	Led11=Led11R;
	Led12=Led12R;
	Led13=Led13R;
	Led14=Led14R;
	Led15=Led15R;
	Led16=Led16R;
	delay_ms(300);
   	Led1=Led1G;
	Led2=Led2G;
	Led3=Led3G;
	Led4=Led4G;
	Led5=Led5G;
	Led6=Led6G;
	Led7=Led7G;
	Led8=Led8G;
	Led9=Led9G;
	Led10=Led10G;
	Led11=Led11G;
	Led12=Led12G;
	Led13=Led13G;
	Led14=Led14G;
	Led15=Led15G;
	Led16=Led16G;
	delay_ms(10000);
}
int shejijiance(void)
{
  	if(Led_Key1==Led1key_on)
	{
		delay_ms(20);	
		if(Led_Key1==Led1key_on)
		{
			led_ms=0;
			return 1;
		}
	}
	if(Led_Key2==Led2key_on)
	{
		delay_ms(20);	
		if(Led_Key2==Led2key_on)
		{
			led_ms=0;
			return 2;
		}
	}
	if(Led_Key3==Led3key_on)
	{
		delay_ms(20);	
		if(Led_Key3==Led3key_on)
		{
			led_ms=0;
			return 3;
		}
	}
	if(Led_Key4==Led4key_on)
	{
		delay_ms(20);	
		if(Led_Key4==Led4key_on)
		{
			led_ms=0;
			return 4;
		}
	}
	if(Led_Key5==Led5key_on)
	{
		delay_ms(20);	
		if(Led_Key5==Led5key_on)
		{
			led_ms=0;
			return 5;
		}
	}
	if(Led_Key6==Led6key_on)
	{
		delay_ms(20);	
		if(Led_Key6==Led6key_on)
		{
			led_ms=0;
			return 6;
		}
	}
	if(Led_Key7==Led7key_on)
	{
		delay_ms(20);	
		if(Led_Key7==Led7key_on)
		{
			led_ms=0;
			return 7;
		}
	}
	if(Led_Key8==Led8key_on)
	{
		delay_ms(20);	
		if(Led_Key8==Led8key_on)
		{
			led_ms=0;
			return 8;
		}
	}
	if(Led_Key9==Led9key_on)
	{
		delay_ms(20);	
		if(Led_Key9==Led9key_on)
		{
			led_ms=0;
			return 9;
		}
	}
	if(Led_Key10==Led10key_on)
	{
		delay_ms(20);	
		if(Led_Key10==Led10key_on)
		{
			led_ms=0;
			return 10;
		}
	}
	if(Led_Key11==Led11key_on)
	{
		delay_ms(20);	
		if(Led_Key11==Led11key_on)
		{
			led_ms=0;
			return 11;
		}
	}
	if(Led_Key12==Led12key_on)
	{
		delay_ms(20);	
		if(Led_Key12==Led12key_on)
		{
			led_ms=0;
			return 12;
		}
	}
	if(Led_Key13==Led13key_on)
	{
		delay_ms(20);	
		if(Led_Key13==Led13key_on)
		{
			led_ms=0;
			return 13;
		}
	}
	if(Led_Key14==Led14key_on)
	{
		delay_ms(20);	
		if(Led_Key14==Led14key_on)
		{
			led_ms=0;
			return 14;
		}
	}
	if(Led_Key15==Led15key_on)
	{
		delay_ms(20);	
		if(Led_Key15==Led15key_on)
		{
			led_ms=0;
			return 15;
		}
	}
	if(Led_Key16==Led16key_on)
	{
		delay_ms(20);	
		if(Led_Key16==Led16key_on)
		{
			led_ms=0;
			return 16;
		}
	}
	return 0;
}
void led_mima(void)
{	
	dangqiansheji=shejijiance();
	switch(dangqiansheji)
	{
		case 0:break;
		case 1:if(Led1==Led1G){dangqiansheji=0;};Led1=Led1G;break;
		case 2:if(Led2==Led2G){dangqiansheji=0;};Led2=Led2G;break;
		case 3:if(Led3==Led3G){dangqiansheji=0;};Led3=Led3G;break;
		case 4:if(Led4==Led4G){dangqiansheji=0;};Led4=Led4G;break;
		case 5:if(Led5==Led5G){dangqiansheji=0;};Led5=Led5G;break;
		case 6:if(Led6==Led6G){dangqiansheji=0;};Led6=Led6G;break;
		case 7:if(Led7==Led7G){dangqiansheji=0;};Led7=Led7G;break;
		case 8:if(Led8==Led8G){dangqiansheji=0;};Led8=Led8G;break;
		case 9:if(fuzhu9==1){dangqiansheji=0;};Led9=Led9G;fuzhu9=1;break;
		case 10:if(Led10==Led10G){dangqiansheji=0;};Led10=Led10G;break;
		case 11:if(Led11==Led11G){dangqiansheji=0;};Led11=Led11G;break;
		case 12:if(Led12==Led12G){dangqiansheji=0;};Led12=Led12G;break;
		case 13:if(Led13==Led13G){dangqiansheji=0;};Led13=Led13G;break;
		case 14:if(Led14==Led14G){dangqiansheji=0;};Led14=Led14G;break;
		case 15:if(Led15==Led15G){dangqiansheji=0;};Led15=Led15G;break;
		case 16:if(Led16==Led16G){dangqiansheji=0;};Led16=Led16G;break;
	}
	if(dangqiansheji==0)
	{
		if(led_ms>=5)
		{
			led_init();
		}
	}else if(mimajishu==0)
	{	
		liangdenjishu++;
		if(dangqiansheji==Ledmima1)
		{
		 	mimajishu=1;
			
		}else{
			mimajishu=0;
		}
	}else if(mimajishu==1)
	{
		liangdenjishu++;
	    if(dangqiansheji==Ledmima2)
		{
		 	mimajishu=2;
		}else{
			mimajishu=0;
		}
	}else if(mimajishu==2)
	{
		liangdenjishu++;
	    if(dangqiansheji==Ledmima3)
		{
		 	mimajishu=3;
		}else{
			mimajishu=0;
		}
	}else if(mimajishu==3)
	{
		liangdenjishu++;
	    if(dangqiansheji==Ledmima4)
		{
		 	mimajishu=4;
		}else{
			mimajishu=0;
		}
	}
	if(liangdenjishu==4)
	{
	 	if(mimajishu==4)
		{
			tongguocishu++;
			if(tongguocishu>=4)
			{
			 	ledkey_on();
				tongguocishu=0;
			}else{
				ledkey_on1();
			}
			mimashezhi(mimashezhizhuzu,tongguocishu);
			led_init();
		}else{
			delay_ms(500);
		   	led_init();
		}
		liangdenjishu=0;
		mimajishu=0;
	} 
}