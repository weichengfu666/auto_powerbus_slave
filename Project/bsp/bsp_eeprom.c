#include "main.h"		 

#define PAGE_SIZE 2     //flash����ҳ�����һ��д�� 4 ����ҳ��flash

u16 EEPROM_Write_n_i=0;
uchar EEPROM_Write_HuanCun[32];
uint addr2=0,EEPROM_Write_i=0,EEPROM_Write_j=0;
u8 Flash512_PageArr[PAGE_SIZE][512];                                                   //flash����ҳ�����һ��д�� 4 ����ҳ��flash

void IapIdle()
{
	IAP_CONTR = 0;                              
	IAP_CMD = 0;                               
	IAP_TRIG = 0;                        
	IAP_ADDRH = 0x80;                    
	IAP_ADDRL = 0;
}	  
/*----------------------------
��ISP/IAP/EEPROM�����ȡһ�ֽ�
----------------------------*/
u8 IapReadByte(u16 addr)
{
	addr += IAP_OFFSET; // 
	return *(char code *)(addr); // 
}
/*----------------------------
дһ�ֽ����ݵ�ISP/IAP/EEPROM����
----------------------------*/
void IapProgramByte(u16 addr, u8 dat)
{
	IAP_CONTR = 0x80;         			//ʹ��IAP
	IAP_TPS = 24;
	IAP_CMD = 2;          					//����IAP����
	IAP_ADDRL = addr;               //����IAP�͵�ַ
	IAP_ADDRH = addr >> 8;          //����IAP�ߵ�ַ
	IAP_DATA = dat;                 //дISP/IAP/EEPROM����
	IAP_TRIG = 0x5a;                //д��������(0x5a)
	IAP_TRIG = 0xa5;                //д��������(0xa5)
	_nop_();                        //�ȴ�ISP/IAP/EEPROM�������
	IapIdle();
}
/*----------------------------
����������������Ϊ0xFF
----------------------------*/
void IapEraseSector(u16 addr)
{
	IAP_CONTR = 0x80;         //ʹ��IAP
	IAP_TPS = 24;
	IAP_CMD = 3;            //����IAP����
	IAP_ADDRL = addr;               //����IAP�͵�ַ
	IAP_ADDRH = addr >> 8;          //����IAP�ߵ�ַ
	IAP_TRIG = 0x5a;                //д��������(0x5a)
	IAP_TRIG = 0xa5;                //д��������(0xa5)
	_nop_();                        //�ȴ�ISP/IAP/EEPROM�������
	IapIdle();
}
/*----------------------------
д���ַ�����EEPROM
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
��EEPROM
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
д���ַ�����EEPROM,���Ḳ�ǵ���ǰ������
----------------------------*/
u8 writeFlashStr ( u32 _ulFlashAddr, u8 *_ucpSrc, u32 _ulSize ) /* ��ȡҳ�����棬�޸����ݣ���д��flash  */
{
    u32 i;
    u8* flash512_PageArr_p;                 //ָ��flash����ҳ��ָ��
    u8 page_index;                         //��Ҫ��������ҳ������
    u32 ulFlashAddr_pageStart;             //��ҳ��ʼ��ַ
    u32 ulFlashAddr_pageOffset;            //��ҳƫ�Ƶ�ַ
    u32 ulFlashAddr_pageNum;               //��Ҫ�޸ĵ�ҳ��
    u32 ulFlashAddr_pageNum_Bytes;     //��Ҫ�޸ĵ�����
        
	if(_ulFlashAddr >= 0x0000)
	{
        /* ������Ҫ������ҳ��ʼ��ַ��ҳƫ�Ƶ�ַ��ҳ�� */
        ulFlashAddr_pageOffset = (u32) _ulFlashAddr % 512;           
        ulFlashAddr_pageStart = _ulFlashAddr - ulFlashAddr_pageOffset ;     
        if( ( _ulSize + ulFlashAddr_pageOffset ) % 512 == 0)               //����Ҫ�޸Ķ���ҳ
        {
            ulFlashAddr_pageNum = ( _ulSize + ulFlashAddr_pageOffset ) / 512;
        }
        else
        {
            ulFlashAddr_pageNum = ( ( _ulSize + ulFlashAddr_pageOffset) / 512 ) + 1;          
        }
        /* �����������д��ҳ�������ش������ */
        if( ulFlashAddr_pageNum > PAGE_SIZE )
        {
            return 1;   
        }  

        /* ��ȡflashҪ�޸ĵ�ҳ������ҳ Flash512_PageArr */
        for( page_index = 0; page_index < ulFlashAddr_pageNum; page_index++ )
        {
            for( i = 0; i < 512; i++ )
            {
//                Flash512_PageArr[ page_index ][ i ] = *(u8 *) ( ulFlashAddr_pageStart + i + page_index * 512 ); 
                Flash512_PageArr[ page_index ][ i ] = IapReadByte( ulFlashAddr_pageStart + i + page_index * 512 ); 
            }
        }
        /* ��Ҫ�޸ĵ����ݱ��浽����ҳ Flash512_PageArr */
        flash512_PageArr_p = & Flash512_PageArr[ 0 ][ ulFlashAddr_pageOffset ];
        for(i = 0; i < _ulSize; i++)
        {
            flash512_PageArr_p[i] = _ucpSrc[i];
        }
        /* ����Ҫ�޸ĵ�ҳ */
        for( page_index = 0; page_index < ulFlashAddr_pageNum; page_index++ )
        {
            IapEraseSector(ulFlashAddr_pageStart + page_index * 512);
        }
        /* ������д��flash�����ֽ�ģʽ��̣�Ϊ���Ч�ʣ����԰��ֱ�̣�һ��д��4�ֽڣ� */
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
��EEPROM
----------------------------*/
void readFlashStr(u16 addr,u8 dat[],u16 dat_Len)
{
    u16 i = 0;
    for(i = 0; i < dat_Len; i++)
    {
        dat[i] = IapReadByte(addr + i);
    }
}


////���Գ���1
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


////���Գ���2
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
