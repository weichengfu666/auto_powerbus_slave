#include "main.h"
uchar dengzhuangtai[42]={0,0,0,0,0,0,0,
						0,0,0,0,0,0,0,
						0,0,0,0,0,0,0,
						0,0,0,0,0,0,0,
						0,0,0,0,0,0,0,
						0,0,0,0,0,0,0,};
uchar liangdeng_i=0,liangdeng_j=0;
void liangdengsaomiao(void)
{
	switch(liangdeng_i)
	{
		case 0:ZHU_1=1;ZHU_2=0;ZHU_3=0;ZHU_4=0;ZHU_5=0;ZHU_6=0;break;
		case 1:ZHU_1=0;ZHU_2=1;ZHU_3=0;ZHU_4=0;ZHU_5=0;ZHU_6=0;break;
		case 2:ZHU_1=0;ZHU_2=0;ZHU_3=1;ZHU_4=0;ZHU_5=0;ZHU_6=0;break;
		case 3:ZHU_1=0;ZHU_2=0;ZHU_3=0;ZHU_4=1;ZHU_5=0;ZHU_6=0;break;
		case 4:ZHU_1=0;ZHU_2=0;ZHU_3=0;ZHU_4=0;ZHU_5=1;ZHU_6=0;break;
		case 5:ZHU_1=0;ZHU_2=0;ZHU_3=0;ZHU_4=0;ZHU_5=0;ZHU_6=1;break;
	}
	for(liangdeng_j=0;liangdeng_j<7;liangdeng_j++)
	{
		switch(liangdeng_j)
		{
			case 0:if(dengzhuangtai[liangdeng_i*7+liangdeng_j]==0){HAO_1=0;}else{HAO_1=1;}break;
			case 1:if(dengzhuangtai[liangdeng_i*7+liangdeng_j]==0){HAO_2=0;}else{HAO_2=1;}break;
			case 2:if(dengzhuangtai[liangdeng_i*7+liangdeng_j]==0){HAO_3=0;}else{HAO_3=1;}break;
			case 3:if(dengzhuangtai[liangdeng_i*7+liangdeng_j]==0){HAO_4=0;}else{HAO_4=1;}break;
			case 4:if(dengzhuangtai[liangdeng_i*7+liangdeng_j]==0){HAO_5=0;}else{HAO_5=1;}break;
			case 5:if(dengzhuangtai[liangdeng_i*7+liangdeng_j]==0){HAO_6=0;}else{HAO_6=1;}break;
			case 6:if(dengzhuangtai[liangdeng_i*7+liangdeng_j]==0){HAO_7=0;}else{HAO_7=1;}break;
		}
		
	}
}