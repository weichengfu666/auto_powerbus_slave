#include "main.h"		 

#define PAGE_SIZE 2     //flash缓存页，最多一次写入 4 缓存页到flash

u16 EEPROM_Write_n_i=0;
uchar EEPROM_Write_HuanCun[32];
uint addr2=0,EEPROM_Write_i=0,EEPROM_Write_j=0;
u8 Flash512_PageArr[PAGE_SIZE][512];                                                   //flash缓存页，最多一次写入 4 缓存页到flash

void IapIdle()
{
	IAP_CONTR = 0;                              
	IAP_CMD = 0;                               
	IAP_TRIG = 0;                        
	IAP_ADDRH = 0x80;                    
	IAP_ADDRL = 0;
}	  
/*----------------------------
从ISP/IAP/EEPROM区域读取一字节
----------------------------*/
u8 IapReadByte(u16 addr)
{
	addr += IAP_OFFSET; // 
	return *(char code *)(addr); // 
}
/*----------------------------
写一字节数据到ISP/IAP/EEPROM区域
----------------------------*/
void IapProgramByte(u16 addr, u8 dat)
{
	IAP_CONTR = 0x80;         			//使能IAP
	IAP_TPS = 24;
	IAP_CMD = 2;          					//设置IAP命令
	IAP_ADDRL = addr;               //设置IAP低地址
	IAP_ADDRH = addr >> 8;          //设置IAP高地址
	IAP_DATA = dat;                 //写ISP/IAP/EEPROM数据
	IAP_TRIG = 0x5a;                //写触发命令(0x5a)
	IAP_TRIG = 0xa5;                //写触发命令(0xa5)
	_nop_();                        //等待ISP/IAP/EEPROM操作完成
	IapIdle();
}
/*----------------------------
扇区擦除，擦除后为0xFF
----------------------------*/
void IapEraseSector(u16 addr)
{
	IAP_CONTR = 0x80;         //使能IAP
	IAP_TPS = 24;
	IAP_CMD = 3;            //设置IAP命令
	IAP_ADDRL = addr;               //设置IAP低地址
	IAP_ADDRH = addr >> 8;          //设置IAP高地址
	IAP_TRIG = 0x5a;                //写触发命令(0x5a)
	IAP_TRIG = 0xa5;                //写触发命令(0xa5)
	_nop_();                        //等待ISP/IAP/EEPROM操作完成
	IapIdle();
}
/*----------------------------
写入字符串到EEPROM
----------------------------*/
void EEPROM_Write_Str(u16 addr,u8 dat[],u16 dat_Len)
{
	if(addr%512==0)
		IapEraseSector(addr);
	for(EEPROM_Write_i=0;EEPROM_Write_i<dat_Len;EEPROM_Write_i++)
	{
		IapProgramByte(addr+EEPROM_Write_i,dat[EEPROM_Write_i]);		
	}
}
/*----------------------------
读EEPROM
----------------------------*/
void EEPROM_Read_Str(u16 addr,u8 dat[],u16 dat_Len)
{
    u16 i = 0;
    for(i = 0; i < dat_Len; i++)
    {
        dat[i] = IapReadByte(addr + i);
    }
}
/*----------------------------
写入字符串到EEPROM,不会覆盖掉以前的数据
----------------------------*/
u8 writeFlashStr ( u32 _ulFlashAddr, u8 *_ucpSrc, u32 _ulSize ) /* 读取页到缓存，修改内容，再写回flash  */
{
    u32 i;
    u8* flash512_PageArr_p;                 //指向flash缓存页的指针
    u8 page_index;                         //需要操作缓存页的索引
    u32 ulFlashAddr_pageStart;             //首页起始地址
    u32 ulFlashAddr_pageOffset;            //首页偏移地址
    u32 ulFlashAddr_pageNum;               //需要修改的页数
    u32 ulFlashAddr_pageNum_Bytes;     //需要修改的字数
        
	if(_ulFlashAddr >= 0x0000)
	{
        /* 计算需要操作的页起始地址，页偏移地址，页数 */
        ulFlashAddr_pageOffset = (u32) _ulFlashAddr % 512;           
        ulFlashAddr_pageStart = _ulFlashAddr - ulFlashAddr_pageOffset ;     
        if( ( _ulSize + ulFlashAddr_pageOffset ) % 512 == 0)               //计算要修改多少页
        {
            ulFlashAddr_pageNum = ( _ulSize + ulFlashAddr_pageOffset ) / 512;
        }
        else
        {
            ulFlashAddr_pageNum = ( ( _ulSize + ulFlashAddr_pageOffset) / 512 ) + 1;          
        }
        /* 超过单次最大写入页数，返回错误代码 */
        if( ulFlashAddr_pageNum > PAGE_SIZE )
        {
            return 1;   
        }  

        /* 读取flash要修改的页到缓存页 Flash512_PageArr */
        for( page_index = 0; page_index < ulFlashAddr_pageNum; page_index++ )
        {
            for( i = 0; i < 512; i++ )
            {
//                Flash512_PageArr[ page_index ][ i ] = *(u8 *) ( ulFlashAddr_pageStart + i + page_index * 512 ); 
                Flash512_PageArr[ page_index ][ i ] = IapReadByte( ulFlashAddr_pageStart + i + page_index * 512 ); 
            }
        }
        /* 将要修改的数据保存到缓存页 Flash512_PageArr */
        flash512_PageArr_p = & Flash512_PageArr[ 0 ][ ulFlashAddr_pageOffset ];
        for(i = 0; i < _ulSize; i++)
        {
            flash512_PageArr_p[i] = _ucpSrc[i];
        }
        /* 擦除要修改的页 */
        for( page_index = 0; page_index < ulFlashAddr_pageNum; page_index++ )
        {
            IapEraseSector(ulFlashAddr_pageStart + page_index * 512);
        }
        /* 将缓存写入flash，按字节模式编程（为提高效率，可以按字编程，一次写入4字节） */
        flash512_PageArr_p = &Flash512_PageArr[0][0];
        ulFlashAddr_pageNum_Bytes = ulFlashAddr_pageNum * 512;
        for(i=0;i<ulFlashAddr_pageNum_Bytes;i++)
        {
            IapProgramByte(ulFlashAddr_pageStart+i,flash512_PageArr_p[i]);		
        }
        return 0;
    }
    return 1;
}
/*----------------------------
读EEPROM
----------------------------*/
void readFlashStr(u16 addr,u8 dat[],u16 dat_Len)
{
    u16 i = 0;
    for(i = 0; i < dat_Len; i++)
    {
        dat[i] = IapReadByte(addr + i);
    }
}


////测试程序1
//    EEPROM_Read_Str( PACK1,(void*)LED_displayPackArr,PACKROW*PACKCOL);
//    for(i=0;i<PACKROW;i++)
//    {
//        for(j=0;j<PACKCOL;j++)
//        {
//            SendData(LED_displayPackArr[i][j]);
//        }
//    }
//    EEPROM_Write_Str(PACK1,(void*)LED_displayPack1,PACKROW*PACKCOL);
//    EEPROM_Read_Str( PACK1,(void*)LED_displayPackArr,PACKROW*PACKCOL);
//    for(i=0;i<PACKROW;i++)
//    {
//        for(j=0;j<PACKCOL;j++)
//        {
//            SendData(LED_displayPackArr[i][j]);
//        }
//    }


////测试程序2
//u8 test1[1024] ={0x00};
//u8 test2[1024] ={0x00};
//u8 test3[1024] ={0x0f,0x0e,0x03,0x04,0x05,0x06};
//    for(i=0;i<512;i++)
//    {
//        test1[i] = 0x0a;
//    }
//    for(i=512;i<1024;i++)
//    {
//        test1[i] = 0x0b;
//    }
//    EEPROM_Read_Str( PACK1,(void*)test2,1024);
//    for(i=0;i<512;i++)
//    {
//        SendData(test2[i]);
//    }
//    writeFlashStr(PACK1,(void*)test3,512);
//    EEPROM_Read_Str( PACK1,(void*)test2,512);
//    for(i=0;i<512;i++)
//    {
//        SendData(test2[i]);
//    }
//    writeFlashStr(PACK1+6,(void*)test1,506);
//    EEPROM_Read_Str( PACK1,(void*)test2,512);
//    for(i=0;i<512;i++)
//    {
//        SendData(test2[i]);
//    }
