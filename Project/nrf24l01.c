#include "main.h"

/***************************************************/
uchar code TX_ADDRESS[TX_ADR_WIDTH] = {0x00,0x22,0x22,0x22,0x22};  // ����һ����̬���͵�ַ 
uchar code RX_ADDRESS[RX_ADR_WIDTH] = {0x00,0x22,0x22,0x22,0x22};
//uchar code RX_ADDRESS1[RX_ADR_WIDTH] = {0x01,0x11,0x11,0x11,0x11};
//uchar code RX_ADDRESS2[1] = {0x02};
//uchar code RX_ADDRESS3[1] = {0x03};
//uchar code RX_ADDRESS4[1] = {0x04};
//uchar code RX_ADDRESS5[1] = {0x05};

uchar bdata sta;
sbit  RX_DR	 = sta^6;
sbit  TX_DS	 = sta^5;
sbit  MAX_RT = sta^4;
/**************************************************/

//****************************************************************************************
/*NRF24L01��ʼ��
//***************************************************************************************/
void init_NRF24L01(void)
{
//    inerDelay_us(100);
 	CE=0;    // chip enable
 	CSN=1;   // Spi disable 
 	SCK=0;   // Spi clock line init high
	SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);    // д���ص�ַ	
	SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH); // д���ն˵�ַ
//	SPI_Write_Buf(WRITE_REG + RX_ADDR_P1, RX_ADDRESS1, RX_ADR_WIDTH); // д���ն˵�ַ
//	SPI_Write_Buf(WRITE_REG + RX_ADDR_P2, RX_ADDRESS2, 1); // д���ն˵�ַ
//	SPI_Write_Buf(WRITE_REG + RX_ADDR_P3, RX_ADDRESS3, 1); // д���ն˵�ַ
//	SPI_Write_Buf(WRITE_REG + RX_ADDR_P4, RX_ADDRESS4, 1); // д���ն˵�ַ
//	SPI_Write_Buf(WRITE_REG + RX_ADDR_P5, RX_ADDRESS5, 1); // д���ն˵�ַ
	SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);      //  Ƶ��0�Զ�	ACKӦ������	
	SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);  //  ������յ�ַֻ��Ƶ��0�������Ҫ��Ƶ�����Բο�Page21  
	SPI_RW_Reg(WRITE_REG + RF_CH, 0);        //   �����ŵ�����Ϊ2.4GHZ���շ�����һ��
	SPI_RW_Reg(WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH); //���ý������ݳ��ȣ���������Ϊ4�ֽ�
//	SPI_RW_Reg(WRITE_REG + RX_PW_P1, RX_PLOAD_WIDTH); //���ý������ݳ��ȣ���������Ϊ4�ֽ�
//	SPI_RW_Reg(WRITE_REG + RX_PW_P2, RX_PLOAD_WIDTH); //���ý������ݳ��ȣ���������Ϊ4�ֽ�
//	SPI_RW_Reg(WRITE_REG + RX_PW_P3, RX_PLOAD_WIDTH); //���ý������ݳ��ȣ���������Ϊ4�ֽ�
//	SPI_RW_Reg(WRITE_REG + RX_PW_P4, RX_PLOAD_WIDTH); //���ý������ݳ��ȣ���������Ϊ4�ֽ�
//	SPI_RW_Reg(WRITE_REG + RX_PW_P5, RX_PLOAD_WIDTH); //���ý������ݳ��ȣ���������Ϊ4�ֽ�
	SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);   		//���÷�������Ϊ1MHZ�����书��Ϊ���ֵ0dB	
	SPI_RW_Reg(WRITE_REG + CONFIG, 0x0e);   		 // IRQ�շ�����ж���Ӧ��16λCRC��������

}
/**************************************************/


/**************************************************
������SPI_RW()

������
    ����SPIЭ�飬дһ�ֽ����ݵ�nRF24L01��ͬʱ��nRF24L01
	����һ�ֽ�
/**************************************************/
uchar SPI_RW(uchar byte)
{
	uchar i;
   	for(i=0; i<8; i++)          // ѭ��8��
   	{
   		MOSI = (byte & 0x80);   // byte���λ�����MOSI
   		byte <<= 1;             // ��һλ��λ�����λ
   		SCK = 1;                // ����SCK��nRF24L01��MOSI����1λ���ݣ�ͬʱ��MISO���1λ����
   		byte |= MISO;       	// ��MISO��byte���λ
   		SCK = 0;            	// SCK�õ�
   	}
    return(byte);           	// ���ض�����һ�ֽ�
}
/**************************************************/

/**************************************************
������SPI_RW_Reg()

������
    д����value��reg�Ĵ���
/**************************************************/
uchar SPI_RW_Reg(uchar reg, uchar value)
{
	uchar status;
  	CSN = 0;                   // CSN�õͣ���ʼ��������
  	status = SPI_RW(reg);      // ѡ��Ĵ�����ͬʱ����״̬��
  	SPI_RW(value);             // Ȼ��д���ݵ��üĴ���
  	CSN = 1;                   // CSN���ߣ��������ݴ���
  	return(status);            // ����״̬�Ĵ���
}
/**************************************************/

/**************************************************
������SPI_Read()

������
    ��reg�Ĵ�����һ�ֽ�
/**************************************************/
uchar SPI_Read(uchar reg)
{
	uchar reg_val;
  	CSN = 0;                    // CSN�õͣ���ʼ��������
  	SPI_RW(reg);                // ѡ��Ĵ���
  	reg_val = SPI_RW(0);        // Ȼ��ӸüĴ���������
  	CSN = 1;                    // CSN���ߣ��������ݴ���
  	return(reg_val);            // ���ؼĴ�������
}
/**************************************************/

/**************************************************
������SPI_Read_Buf()

������
    ��reg�Ĵ�������bytes���ֽڣ�ͨ��������ȡ����ͨ��
	���ݻ����/���͵�ַ
/**************************************************/
uchar SPI_Read_Buf(uchar reg, uchar * pBuf, uchar bytes)
{
	uchar status, i;
  	CSN = 0;                    // CSN�õͣ���ʼ��������
  	status = SPI_RW(reg);       // ѡ��Ĵ�����ͬʱ����״̬��
  	for(i=0; i<bytes; i++)
    	pBuf[i] = SPI_RW(0);    // ����ֽڴ�nRF24L01����
  	CSN = 1;                    // CSN���ߣ��������ݴ���
  	return(status);             // ����״̬�Ĵ���
}
/**************************************************/

/**************************************************
������SPI_Write_Buf()

������
    ��pBuf�����е�����д�뵽nRF24L01��ͨ������д�뷢
	��ͨ�����ݻ����/���͵�ַ
/**************************************************/
uchar SPI_Write_Buf(uchar reg, uchar * pBuf, uchar bytes)
{
	uchar status, i;
  	CSN = 0;                    // CSN�õͣ���ʼ��������
  	status = SPI_RW(reg);       // ѡ��Ĵ�����ͬʱ����״̬��
  	for(i=0; i<bytes; i++)
    	SPI_RW(pBuf[i]);        // ����ֽ�д��nRF24L01
  	CSN = 1;                    // CSN���ߣ��������ݴ���
  	return(status);             // ����״̬�Ĵ���
}
/**************************************************/

/**************************************************
������setRX_Mode()

������
    �����������nRF24L01Ϊ����ģʽ���ȴ����շ����豸�����ݰ�
/**************************************************/
void setRX_Mode(void)
{
	CE = 0;
  	SPI_RW_Reg(WRITE_REG + CONFIG, 0x0f);   		// IRQ�շ�����ж���Ӧ��16λCRC	��������	
	CE = 1;                                            // ����CE���������豸
//	inerDelay_us(130);
}
/**************************************************/

/******************************************************************************************************/
/*������unsigned char nRF24L01_RxPacket(unsigned char* rx_buf)
/*���ܣ����ݶ�ȡ�����rx_buf���ջ�������
/******************************************************************************************************/
unsigned char nRF24L01_RxPacket(unsigned char* rx_buf)
{
    unsigned char revale=0;
	sta=SPI_Read(STATUS);	// ��ȡ״̬�Ĵ������ж����ݽ���״��
	if(RX_DR)				// �ж��Ƿ���յ�����
	{
	    CE = 0; 			//SPIʹ��
		SPI_Read_Buf(RD_RX_PLOAD,rx_buf,TX_PLOAD_WIDTH);// read receive payload from RX_FIFO buffer
		revale =1;			//��ȡ������ɱ�־
	}
	SPI_RW_Reg(WRITE_REG+STATUS,sta);   //���յ����ݺ�RX_DR,TX_DS,MAX_PT���ø�Ϊ1��ͨ��д1������жϱ�־
	return revale;
}
/***********************************************************************************************************
/*������void nRF24L01_TxPacket(unsigned char * tx_buf)
/*���ܣ����� tx_buf������
/**********************************************************************************************************/
void nRF24L01_TxPacket(unsigned char * tx_buf)
{
	CE=0;			//StandBy Iģʽ	
	SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, RX_ADDRESS, TX_ADR_WIDTH); // װ�ؽ��ն˵�ַ
	SPI_Write_Buf(WR_TX_PLOAD, tx_buf, TX_PLOAD_WIDTH); 			 // װ������	
//	SPI_RW_Reg(WRITE_REG + CONFIG, 0x0e);   		 // IRQ�շ�����ж���Ӧ��16λCRC��������
	CE=1;		 //�ø�CE���������ݷ���
//	inerDelay_us(10);
}

/**************************************************
������Check_ACK()

������
    �������豸���޽��յ����ݰ����趨û���յ�Ӧ����
	���Ƿ��ط�
/**************************************************/
uchar Check_ACK(bit clear)
{
	while(IRQ);
	sta = SPI_RW(NOP);                    // ����״̬�Ĵ���
	if(MAX_RT)
		if(clear)                         // �Ƿ����TX FIFO��û������ڸ�λMAX_RT�жϱ�־���ط�
			SPI_RW(FLUSH_TX);
	SPI_RW_Reg(WRITE_REG + STATUS, sta);  // ���TX_DS��MAX_RT�жϱ�־
	IRQ = 1;
	if(TX_DS)
		return(0x00);
	else
		return(0xff);
}
/**************************************************/
