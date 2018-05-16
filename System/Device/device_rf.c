#include "system.h"
#include "radio_config_Si4438.h"                  // Device header
//#include "si44xx.h"                  // Device header

#define Tx_LENTH 64
#define Rx_LENTH 64

extern unsigned char  abApi_Write[16],abApi_Read[16];
extern unsigned char  transmit_arry[Tx_LENTH];

#define     RF4463_SDI		  GPIO_Pin_4
#define     RF4463_SDO	    GPIO_Pin_5 	   //输出
#define     RF4463_SCLK     GPIO_Pin_7
#define     RF4463_SEL      GPIO_Pin_6
#define     RF4463_IRQ      GPIO_Pin_5   //输入
#define     RF4463_SDN		  GPIO_Pin_4
#define     RF4463_GIPO1	    GPIO_Pin_0  

unsigned char const PaSettings[][5] = {
    /*[0] - PA_MODE, [1] - PA_PWR_LVL, [2] - PA_BIAS_CLKDUTY, [3] - PA_TC_FSK, [4] - PA_TC_OOK */
    {/*4463_TSQ20B169*/0x08,0x7F,0x00,0x5D,0x14},
    {/*4463_TSQ20D169*/0x08,0x7F,0x00,0x5D,0x14},
    {/*4463_TSQ27F169*/0x08,0x7F,0x00,0x5D,0x14},
    {/*4461_TCE14D434*/0x20,0x21,0x00,0x5D,0x14},
    {/*4460_TCE10D434*/0x18,0x1A,0xC0,0x5D,0x14},
    {/*4463_TCE20B460*/0x08,0x7F,0x00,0x5D,0x14},
    {/*4463_TCE20C460*/0x08,0x7F,0x00,0x5D,0x14},
    {/*4460_TSC10D868*/0x19,0x40,0xE8,0x5D,0x14},
    {/*4460_TCE10D868*/0x18,0x18,0xC0,0x5D,0x14},
    {/*4461_TSC14D868*/0x21,0x64,0x2C,0x5D,0x14},
    {/*4461_TCE16D868*/0x20,0x41,0x00,0x5D,0x14},
    {/*4463_TCE20B868*/0x08,0x7F,0x00,0x5D,0x14},
    {/*4463_TCE20C868*/0x08,0x7F,0x00,0x5D,0x14},
    {/*4463_TCE27F868*/0x08,0x7F,0x00,0x5D,0x14},
    {/*4463_TCE20B915*/0x08,0x7F,0x00,0x5D,0x14},
    {/*4463_TCE20C915*/0x08,0x7F,0x00,0x5D,0x14},
    {/*4463_TCE30E915*/0x08,0x7F,0x00,0x5D,0x14},
    {/*4464_TCE20B420*/0x08,0x7F,0x00,0x5D,0x14}
};

unsigned char const ModemTrx1[] = {0x07,RF_POWER_UP };
unsigned char const ModemTrx2[] = {0x08,RF_GPIO_PIN_CFG };
unsigned char const ModemTrx3[] = {0x05,RF_GLOBAL_XO_TUNE_2};
unsigned char const ModemTrx4[] = {0x05, RF_GLOBAL_CONFIG_6};
unsigned char const ModemTx1[] = {0x06,RF_INT_CTL_ENABLE_2 };
unsigned char const ModemTx2[] = {0x05,RF_INT_CTL_CHIP_ENABLE_1 };
unsigned char const ModemRx1[] = {0x08,RF_FRR_CTL_A_MODE_4 };
unsigned char const ModemRx2[] = {0x05,RF_PREAMBLE_CONFIG_1 };
unsigned char const ModemRx3[] = {0x07, RF_SYNC_CONFIG_3};
unsigned char const ModemRx4[] = {0x05,RF_PKT_CONFIG1_1 };
unsigned char const ModemRx4_1[] = {0x05,RF_PKT_FIELD_1_CONFIG_1 };
unsigned char const ModemRx5[] = {0x10,RF_MODEM_MOD_TYPE_12 };
unsigned char const ModemRx6[] = {0x05,RF_MODEM_FREQ_DEV_0_1 };
unsigned char const ModemRx7[] = {0x0C,RF_MODEM_TX_RAMP_DELAY_8 };
unsigned char const ModemRx8[] = {0x0D, RF_MODEM_BCR_OSR_1_9};
unsigned char const ModemRx9[] = {0x0B,RF_MODEM_AFC_GEAR_7 };
unsigned char const ModemRx10[] = {0x05, RF_MODEM_AGC_CONTROL_1};
unsigned char const ModemRx11[] = {0x0D,RF_MODEM_AGC_WINDOW_SIZE_9 };
unsigned char const ModemRx12[] = {0x0D,RF_MODEM_OOK_CNT1_9 };
unsigned char const ModemRx13[] = {0x05,RF_MODEM_RSSI_CONTROL_1 };
unsigned char const ModemRx14[] = {0x05,RF_MODEM_RSSI_COMP_1 };
unsigned char const ModemRx15[] = {0x05,RF_MODEM_CLKGEN_BAND_1 };
unsigned char const ModemRx16[] = {0x10,RF_MODEM_CHFLT_RX1_CHFLT_COE13_7_0_12 };
unsigned char const ModemRx17[] = {0x10,RF_MODEM_CHFLT_RX1_CHFLT_COE1_7_0_12 };
unsigned char const ModemRx18[] = {0x10,RF_MODEM_CHFLT_RX2_CHFLT_COE7_7_0_12 };
unsigned char const ModemRx19[] = {0x05, RF_PA_TC_1};

unsigned char const ModemRx20[] = {0x0B,RF_SYNTH_PFDCP_CPFF_7 };
unsigned char const ModemRx21[] = {0x0C,RF_FREQ_CONTROL_INTE_8 };

unsigned char  abApi_Write[16],abApi_Read[16];
//unsigned char  transmit_arry[Tx_LENTH];

unsigned char Spi1ReadWrite(unsigned char uchar)
{  	 
	unsigned char bit_ctr;

//   	for(bit_ctr=0;bit_ctr<8;bit_ctr++) // output 8-bit
//   	{
//		MCU_MOSI = (uchar & 0x80);         // output 'uchar', MSB to MOSI
//		uchar = (uchar << 1);           // shift next bit into MSB..
//		MCU_SCK = 1;                      // Set SCK high..
//		uchar |= MCU_MISO;       		  // capture current MISO bit
//		MCU_SCK = 0;            		  // ..then set SCK low again
//   	}
//    return(uchar);           		  // return read uchar
	
		for(bit_ctr=0;bit_ctr<8;bit_ctr++) // output 8-bit
		{
				if (uchar&0x80)	//总是发送最高位
				{
//					RF4432_SDI=1;
					 GPIO_SetBits(GPIOA,RF4463_SDI ); 
				}
				else
				{
// 	  	    RF4432_SDI=0;
						GPIO_ResetBits(GPIOA,RF4463_SDI ); 
				}
				
				uchar = (uchar << 1);           // shift next bit into MSB..
				
				GPIO_SetBits(GPIOA,RF4463_SCLK );

				if ( GPIO_ReadInputDataBit(GPIOA, RF4463_SDO)!=0)			//读取最高位，保存至最末尾，通过左移位完成整个字节
				{
					uchar |= 0x01;
				}
				else
				{
					uchar &= ~0x01;
				}
				
				GPIO_ResetBits(GPIOA,RF4463_SCLK ); 
		}

    return(uchar);           		  // return read uchar		
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  U8 bSpi_SendDataNoResp(U8 bDataInLength, U8 *pbDataIn)
  +
  + DESCRIPTION:    send data over SPI no response expected
  +
  + INPUT:          bDataInLength - length of data
  +                 *pbDataIn     - pointer to the data
  +
  + RETURN:         None
  +
  + NOTES:          None
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
unsigned char bSpi_SendDataNoResp(unsigned char bDataInLength, unsigned char *pbDataIn)
{
//  SEGMENT_VARIABLE(bCnt, U8, SEG_XDATA);
	unsigned char  bCnt;
	for (bCnt=0; bCnt<bDataInLength; bCnt++)    // Send input data array via SPI
	{
		Spi1ReadWrite(pbDataIn[bCnt]);
	}
  return 0;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  U8 bSpi_SendDataGetResp(U8 bDataOutLength, U8 *pbDataOut)
  +
  + DESCRIPTION:    send dummy data over SPI and get the response
  +
  + INPUT:          bDataOutLength  - length of data to be read
  +                 *pbDataOut      - response
  +
  + RETURN:         None
  +
  + NOTES:          None
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
unsigned char bSpi_SendDataGetResp(unsigned char bDataOutLength, unsigned char *pbDataOut)   // Send data, get the response
{
//  SEGMENT_VARIABLE(bCnt, U8, SEG_XDATA);
	unsigned char  bCnt;
  // send command and get response from the radio IC
	for (bCnt=0; bCnt<bDataOutLength; bCnt++)
	{
		pbDataOut[bCnt] = Spi1ReadWrite(0xFF);            // Store data byte that came from the radio IC
	}
  return 0;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  U8 bSpi_SendDataByte(U8 bDataIn)
  +
  + DESCRIPTION:    send one byte via SPI
  +
  + INPUT:          bDataIn - data to be sent
  +
  + RETURN:         None
  +
  + NOTES:          None
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
unsigned char bSpi_SendDataByte(unsigned char bDataIn)      // Send a single byte via SPI
{
  Spi1ReadWrite(bDataIn);
  return 0;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  U8 bApi_SendCommand(U8 bCmdLength, U8 *pbCmdData)
  +
  + DESCRIPTION:    send API command, no response expected
  +
  + INPUT:          bCmdLength - nmbr of bytes to be sent
  +                 *pbCmdData - pointer to the commands
  +
  + RETURN:         None
  +
  + NOTES:          None
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
unsigned char bApi_SendCommand(unsigned char bCmdLength, unsigned char *pbCmdData)   // Send a command + data to the chip
{
//	MCU_NSEL = 0;
	GPIO_ResetBits(GPIOA,RF4463_SEL ); 	
	bSpi_SendDataNoResp(bCmdLength, pbCmdData);   // Send data array to the radio IC via SPI
	
//	MCU_NSEL = 1;
	GPIO_SetBits(GPIOA,RF4463_SEL ); 
	
	return 0;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  U8 vApi_WaitforCTS(void)
  +
  + DESCRIPTION:    wait for CTS
  +
  + INPUT:          None
  +
  + RETURN:         0 - CTS arrived
  +                 1 - CTS didn't arrive within MAX_CTS_RETRY
  +
  + NOTES:          None
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
unsigned char vApi_WaitforCTS(void)
{
//	SEGMENT_VARIABLE(bCtsValue, U8, SEG_XDATA);
//	SEGMENT_VARIABLE(bErrCnt, U16, SEG_XDATA);
	unsigned char  bCtsValue; 
	unsigned int  bErrCnt; 
	bCtsValue = 0;
	bErrCnt = 0;
	
	while (bCtsValue!=0xFF)                   // Wait until radio IC is ready with the data
	{
//		MCU_NSEL = 0;                        // Select radio IC by pulling its nSEL pin low
		GPIO_ResetBits(GPIOA,RF4463_SEL );
		bSpi_SendDataByte(CMD_READ_CMD_BUFF);        // Read command buffer; send command byte
		bSpi_SendDataGetResp(1, &bCtsValue);    // Read command buffer; get CTS value
//		MCU_NSEL = 1;                          // If CTS is not 0xFF, put NSS high and stay in waiting loop
		GPIO_SetBits(GPIOA,RF4463_SEL ); 
		if (++bErrCnt > MAX_CTS_RETRY)
		{
			return 1;     // Error handling; if wrong CTS reads exceeds a limit
		}
	}
	return 0;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  U8 bApi_GetFastResponseRegister(U8 bStartReg, U8 bNmbrOfRegs, U8 * pbRegValues)
  +
  + DESCRIPTION:    get fast response registers
  +
  + INPUT:          bStartReg - one of the fast response registers
  +                 bNmbrOfRegs - number of registers (1 ... 4)
  +                 pbRegValues - value of the registers
  +
  + RETURN:         0 - operation successful
  +                 1 - error
  +
  + NOTES:          None
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
unsigned char bApi_GetFastResponseRegister(unsigned char bStartReg, unsigned char bNmbrOfRegs, unsigned char * pbRegValues)
{
  if((bNmbrOfRegs == 0) || (bNmbrOfRegs > 4))
  {
    return 1;
  }

//  MCU_NSEL = 0;
	GPIO_ResetBits(GPIOA,RF4463_SEL );
	
  bSpi_SendDataByte(bStartReg);
  bSpi_SendDataGetResp(bNmbrOfRegs, pbRegValues);
	
//  MCU_NSEL = 1;
	GPIO_SetBits(GPIOA,RF4463_SEL ); 	
  return 0;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  U8 bApi_GetResponse(U8 bRespLength, U8 *pbRespData)
  +
  + DESCRIPTION:    wait for CTS and get the read bytes from the chip
  +
  + INPUT:          bRespLength - nmbr of bytes to be read
  +                 *pbRespData - pointer to the read data
  +
  + RETURN:         0 - operation successful
  +                 1 - no CTS within MAX_CTS_RETRY
  +
  + NOTES:          None
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
unsigned char bApi_GetResponse(unsigned char bRespLength, unsigned char *pbRespData) // Get response from the chip (used after a command)
{
//  SEGMENT_VARIABLE(bCtsValue, U8, SEG_XDATA);
//  SEGMENT_VARIABLE(bErrCnt, U16, SEG_XDATA);
  unsigned char  bCtsValue; 
  unsigned int  bErrCnt; 
  bErrCnt = 0;

  while (bCtsValue!=0xFF)                   // Wait until radio IC is ready with the data
  {
//  MCU_NSEL = 0;
		GPIO_ResetBits(GPIOA,RF4463_SEL );
		
		// Select radio IC by pulling its nSEL pin low
    bSpi_SendDataByte(CMD_READ_CMD_BUFF);        // Read command buffer; send command byte
    bSpi_SendDataGetResp(1, &bCtsValue);
    if(bCtsValue != 0xFF)
    {
	//  MCU_NSEL = 1;
			GPIO_SetBits(GPIOA,RF4463_SEL ); 	
			
    }
    if(++bErrCnt > MAX_CTS_RETRY)
    {
      return 1;
    }
  }
  bSpi_SendDataGetResp(bRespLength, pbRespData);  // CTS value ok, get the response data from the radio IC
//  MCU_NSEL = 1;
	GPIO_SetBits(GPIOA,RF4463_SEL ); 	
	

  return 0;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  U8 bApi_ReadRxDataBuffer(U8 bRxFifoLength, U8 *pbRxFifoData)
  +
  + DESCRIPTION:    Read RX FIFO content from the chip
  +
  + INPUT:          bRxFifoLength - nmbr of bytes to be read
  +
  + RETURN:         *pbRxFifoData - pointer to the read data
  +                 0             - operation successful
  +
  + NOTES:          None
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
unsigned char bApi_ReadRxDataBuffer(unsigned char bRxFifoLength, unsigned char *pbRxFifoData)
{
//  MCU_NSEL = 0;
		GPIO_ResetBits(GPIOA,RF4463_SEL );
	
  bSpi_SendDataByte(CMD_READ_RX_FIFO);                // Send Rx read command
  bSpi_SendDataGetResp(bRxFifoLength, pbRxFifoData);  // Write Tx FIFO
	
//  MCU_NSEL = 1;
	GPIO_SetBits(GPIOA,RF4463_SEL ); 	
  return 0;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  U8 bApi_WriteTxDataBuffer(U8 bTxFifoLength, U8 *pbTxFifoData)
  +
  + DESCRIPTION:    wait for CTS and get the read bytes from the chip
  +
  + INPUT:      bTxFifoLength - nmbr of bytes to be sent
  +         *pbTxFifoData - pointer to the transmit data
  +
  + RETURN:         0 - operation successful
  +         1 - no CTS within MAX_CTS_RETRY
  +
  + NOTES:          None
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
unsigned char bApi_WriteTxDataBuffer(unsigned char bTxFifoLength, unsigned char *pbTxFifoData)   // Write Tx FIFO
{
//  MCU_NSEL = 0;
	GPIO_ResetBits(GPIOA,RF4463_SEL );
	
  bSpi_SendDataByte(CMD_WRITE_TX_FIFO);                 // Send Tx write command
  bSpi_SendDataNoResp(bTxFifoLength, pbTxFifoData); // Write Tx FIFO
	
//  MCU_NSEL = 1;
	GPIO_SetBits(GPIOA,RF4463_SEL ); 		
  return 0;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  +
  + FUNCTION NAME:  void vSetPAMode(PA_OPTIONS PaMode)
  +
  + DESCRIPTION:    Set the PA operating mode
  +
  + INPUT:      PaMode:
  +                     TestCard_4463_TSQ20B169
  +                     TestCard_4463_TSQ20D169
  +                     TestCard_4463_TSQ27F169
  +                     TestCard_4461_TCE14D434
  +                     TestCard_4460_TCE10D434
  +                     TestCard_4463_TCE20B460
  +                     TestCard_4463_TCE20C460
  +                     TestCard_4460_TSC10D868
  +                     TestCard_4460_TCE10D868
  +                     TestCard_4461_TSC14D868
  +                     TestCard_4461_TCE16D868
  +                     TestCard_4463_TCE20B868
  +                     TestCard_4463_TCE20C868
  +                     TestCard_4463_TCE27F868
  +                     TestCard_4463_TCE20B915
  +                     TestCard_4463_TCE20C915
  +                     TestCard_4463_TCE30E915
  +                     TestCard_4464_TCE20B420
  +
  + RETURN:         None
  +
  + NOTES:          None
  +
  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void vSetPAMode(unsigned char bPaMode, unsigned char bModType)
{

  abApi_Write[0] = CMD_SET_PROPERTY;
  abApi_Write[1] = PROP_PA_GROUP;
  abApi_Write[2] = 4;
  abApi_Write[3] = PROP_PA_MODE;
  abApi_Write[4] = PaSettings[bPaMode][0];
  abApi_Write[5] = PaSettings[bPaMode][1];
  abApi_Write[6] = PaSettings[bPaMode][2];
  if (bModType == MOD_OOK)
  {
    abApi_Write[7] = PaSettings[bPaMode][4];
  }
  else
  {
    abApi_Write[7] = PaSettings[bPaMode][3];
  }
  bApi_SendCommand(8,abApi_Write);
  vApi_WaitforCTS();
}

void Si4463_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	
  GPIO_InitStruct.GPIO_Pin = RF4463_SEL | RF4463_SCLK | RF4463_SDI | RF4463_SDN ;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Speed =GPIO_Speed_2MHz;
  GPIO_Init( GPIOA	, &GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin = RF4463_SDI ;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Speed =GPIO_Speed_2MHz;
  GPIO_Init( GPIOC	, &GPIO_InitStruct);
	GPIO_SetBits( GPIOA	, RF4463_SEL | RF4463_SCLK | RF4463_SDN );
	GPIO_SetBits( GPIOC	,  RF4463_SDI );
	
	
	GPIO_InitStruct.GPIO_Pin = RF4463_IRQ ; 
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP; // 上拉输入
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = RF4463_SDO; 
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP; // 上拉输入
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = RF4463_GIPO1; 
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP; // 上拉输入
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_SetBits( GPIOB	, RF4463_GIPO1 );

	  // RF4432_SEL=1;  
			GPIO_SetBits(GPIOA,RF4463_SEL ); 
	      // RF4432_SCLK=0;
		  GPIO_ResetBits(GPIOA,RF4463_SCLK ); 
         //  RF4432_SDN = 0;
		  GPIO_ResetBits(GPIOA,RF4463_SDN ); 						 

	GPIO_SetBits(GPIOA,RF4463_SDN ); 
	delay_ms(1);
	GPIO_ResetBits(GPIOA,RF4463_SDN ); 
	delay_ms(5);
	
	abApi_Write[0] = CMD_POWER_UP;          // Use API command to power up the radio IC
	abApi_Write[1] = 0x01;              // Write global control registers
	abApi_Write[2] = 0x00;              // Write global control registers
	bApi_SendCommand(3,abApi_Write);        // Send command to the radio IC
	// Wait for boot
	if (vApi_WaitforCTS())                // Wait for CTS
	{
		while (1) {}    // Stop if radio power-up error
	}
	
	  // Read ITs, clear pending ones
	abApi_Write[0] = CMD_GET_INT_STATUS;      // Use interrupt status command
	abApi_Write[1] = 0;               // Clear PH_CLR_PEND
	abApi_Write[2] = 0;               // Clear MODEM_CLR_PEND
	abApi_Write[3] = 0;               // Clear CHIP_CLR_PEND
	bApi_SendCommand(4,abApi_Write);        // Send command to the radio IC
	bApi_GetResponse(8, abApi_Read );         // Make sure that CTS is ready then get the response
	
	// Set TRX parameters of the radio IC; data retrieved from the WDS-generated modem_params.h header file	
	GPIO_ResetBits(GPIOA,RF4463_SEL ); 		
	for(api_num=0;api_num<ModemTrx1[0];api_num++)Spi1ReadWrite(ModemTrx1[1+api_num]);	
	GPIO_SetBits(GPIOA,RF4463_SEL ); 
	vApi_WaitforCTS();// Wait for CTS
	
//	bApi_SendCommand(ModemTrx2[0],&ModemTrx2[1]);
	GPIO_ResetBits(GPIOA,RF4463_SEL ); 		
	for(api_num=0;api_num<ModemTrx2[0];api_num++)Spi1ReadWrite(ModemTrx2[1+api_num]);	
	GPIO_SetBits(GPIOA,RF4463_SEL ); 
	vApi_WaitforCTS();// Wait for CTS
	
//	bApi_SendCommand(ModemTrx3[0],&ModemTrx3[1]);
	GPIO_ResetBits(GPIOA,RF4463_SEL ); 		
	for(api_num=0;api_num<ModemTrx3[0];api_num++)Spi1ReadWrite(ModemTrx3[1+api_num]);	
	GPIO_SetBits(GPIOA,RF4463_SEL ); 
	vApi_WaitforCTS();// Wait for CTS

//bApi_SendCommand(ModemTrx4[0],&ModemTrx4[1]);
	GPIO_ResetBits(GPIOA,RF4463_SEL ); 		
	for(api_num=0;api_num<ModemTrx4[0];api_num++)Spi1ReadWrite(ModemTrx4[1+api_num]);	
	GPIO_SetBits(GPIOA,RF4463_SEL ); 
	vApi_WaitforCTS();// Wait for CTS
	
	// Set TX parameters of the radio IC
//	bApi_SendCommand(ModemTx1[0],&ModemTx1[1]);       // Send API command to the radio IC
	GPIO_ResetBits(GPIOA,RF4463_SEL ); 		
	for(api_num=0;api_num<ModemTx1[0];api_num++)Spi1ReadWrite(ModemTx1[1+api_num]);	
	GPIO_SetBits(GPIOA,RF4463_SEL ); 
	vApi_WaitforCTS();// Wait for CTS
	// Wait for CTS
	
//	bApi_SendCommand(ModemTx2[0],&ModemTx2[1]);
	GPIO_ResetBits(GPIOA,RF4463_SEL ); 		
	for(api_num=0;api_num<ModemTx2[0];api_num++)Spi1ReadWrite(ModemTx2[1+api_num]);	
	GPIO_SetBits(GPIOA,RF4463_SEL ); 
	vApi_WaitforCTS();// Wait for CTS

////////
	// Set Rx parameters of the radio IC
//	bApi_SendCommand(ModemRx1[0],&ModemRx1[1]);       // Send API command to the radio IC
	GPIO_ResetBits(GPIOA,RF4463_SEL ); 		
	for(api_num=0;api_num<ModemRx1[0];api_num++)Spi1ReadWrite(ModemRx1[1+api_num]);	
	GPIO_SetBits(GPIOA,RF4463_SEL );// Wait for CTS 
	vApi_WaitforCTS();

//	bApi_SendCommand(ModemRx2[0],&ModemRx2[1]);
	GPIO_ResetBits(GPIOA,RF4463_SEL ); 		
	for(api_num=0;api_num<ModemRx2[0];api_num++)Spi1ReadWrite(ModemRx2[1+api_num]);	
	GPIO_SetBits(GPIOA,RF4463_SEL );
	vApi_WaitforCTS();// Wait for CTS 
	
//	bApi_SendCommand(ModemRx3[0],&ModemRx3[1]);
	GPIO_ResetBits(GPIOA,RF4463_SEL ); 		
	for(api_num=0;api_num<ModemRx3[0];api_num++)Spi1ReadWrite(ModemRx3[1+api_num]);	
	GPIO_SetBits(GPIOA,RF4463_SEL );
	vApi_WaitforCTS();// Wait for CTS 
	
//	bApi_SendCommand(ModemRx4[0],&ModemRx4[1]);
	GPIO_ResetBits(GPIOA,RF4463_SEL ); 		
	for(api_num=0;api_num<ModemRx4[0];api_num++)Spi1ReadWrite(ModemRx4[1+api_num]);	
	GPIO_SetBits(GPIOA,RF4463_SEL );
	vApi_WaitforCTS();// Wait for CTS 
	
//	bApi_SendCommand(ModemRx4_1[0],&ModemRx4_1[1]);
	GPIO_ResetBits(GPIOA,RF4463_SEL ); 		
	for(api_num=0;api_num<ModemRx4_1[0];api_num++)Spi1ReadWrite(ModemRx4_1[1+api_num]);	
	GPIO_SetBits(GPIOA,RF4463_SEL );
	vApi_WaitforCTS();// Wait for CTS 
	
//	bApi_SendCommand(ModemRx5[0],&ModemRx5[1]);
	GPIO_ResetBits(GPIOA,RF4463_SEL ); 		
	for(api_num=0;api_num<ModemRx5[0];api_num++)Spi1ReadWrite(ModemRx5[1+api_num]);	
	GPIO_SetBits(GPIOA,RF4463_SEL );
	vApi_WaitforCTS();// Wait for CTS 
	
//	bApi_SendCommand(ModemRx6[0],&ModemRx6[1]);
	GPIO_ResetBits(GPIOA,RF4463_SEL ); 		
	for(api_num=0;api_num<ModemRx6[0];api_num++)Spi1ReadWrite(ModemRx6[1+api_num]);	
	GPIO_SetBits(GPIOA,RF4463_SEL );
	vApi_WaitforCTS();// Wait for CTS 
	
//	bApi_SendCommand(ModemRx7[0],&ModemRx7[1]);
	GPIO_ResetBits(GPIOA,RF4463_SEL ); 		
	for(api_num=0;api_num<ModemRx7[0];api_num++)Spi1ReadWrite(ModemRx7[1+api_num]);	
	GPIO_SetBits(GPIOA,RF4463_SEL );
	vApi_WaitforCTS();// Wait for CTS 
	
//	bApi_SendCommand(ModemRx8[0],&ModemRx8[1]);
	GPIO_ResetBits(GPIOA,RF4463_SEL ); 		
	for(api_num=0;api_num<ModemRx8[0];api_num++)Spi1ReadWrite(ModemRx8[1+api_num]);	
	GPIO_SetBits(GPIOA,RF4463_SEL );
	vApi_WaitforCTS();// Wait for CTS 
	
//	bApi_SendCommand(ModemRx9[0],&ModemRx9[1]);
	GPIO_ResetBits(GPIOA,RF4463_SEL ); 		
	for(api_num=0;api_num<ModemRx9[0];api_num++)Spi1ReadWrite(ModemRx9[1+api_num]);	
	GPIO_SetBits(GPIOA,RF4463_SEL );
	vApi_WaitforCTS();// Wait for CTS 
	
//	bApi_SendCommand(ModemRx10[0],&ModemRx10[1]);
	GPIO_ResetBits(GPIOA,RF4463_SEL ); 		
	for(api_num=0;api_num<ModemRx10[0];api_num++)Spi1ReadWrite(ModemRx10[1+api_num]);	
	GPIO_SetBits(GPIOA,RF4463_SEL );
	vApi_WaitforCTS();// Wait for CTS 
	
//	bApi_SendCommand(ModemRx11[0],&ModemRx11[1]);
	GPIO_ResetBits(GPIOA,RF4463_SEL ); 		
	for(api_num=0;api_num<ModemRx11[0];api_num++)Spi1ReadWrite(ModemRx11[1+api_num]);	
	GPIO_SetBits(GPIOA,RF4463_SEL );
	vApi_WaitforCTS();// Wait for CTS 
	
//	bApi_SendCommand(ModemRx12[0],&ModemRx12[1]);
	GPIO_ResetBits(GPIOA,RF4463_SEL ); 		
	for(api_num=0;api_num<ModemRx12[0];api_num++)Spi1ReadWrite(ModemRx12[1+api_num]);	
	GPIO_SetBits(GPIOA,RF4463_SEL );
	vApi_WaitforCTS();// Wait for CTS 
	
//	bApi_SendCommand(ModemRx13[0],&ModemRx13[1]);
	GPIO_ResetBits(GPIOA,RF4463_SEL ); 		
	for(api_num=0;api_num<ModemRx13[0];api_num++)Spi1ReadWrite(ModemRx13[1+api_num]);	
	GPIO_SetBits(GPIOA,RF4463_SEL );
	vApi_WaitforCTS();// Wait for CTS 

//	bApi_SendCommand(ModemRx13[0],&ModemRx13[1]);
	GPIO_ResetBits(GPIOA,RF4463_SEL ); 		
	for(api_num=0;api_num<ModemRx14[0];api_num++)Spi1ReadWrite(ModemRx14[1+api_num]);	
	GPIO_SetBits(GPIOA,RF4463_SEL );
	vApi_WaitforCTS();// Wait for CTS 
	//	bApi_SendCommand(ModemRx13[0],&ModemRx13[1]);
	GPIO_ResetBits(GPIOA,RF4463_SEL ); 		
	for(api_num=0;api_num<ModemRx15[0];api_num++)Spi1ReadWrite(ModemRx15[1+api_num]);	
	GPIO_SetBits(GPIOA,RF4463_SEL );
	vApi_WaitforCTS();// Wait for CTS 
	//	bApi_SendCommand(ModemRx13[0],&ModemRx13[1]);
	GPIO_ResetBits(GPIOA,RF4463_SEL ); 		
	for(api_num=0;api_num<ModemRx16[0];api_num++)Spi1ReadWrite(ModemRx16[1+api_num]);	
	GPIO_SetBits(GPIOA,RF4463_SEL );
	vApi_WaitforCTS();// Wait for CTS 
	//	bApi_SendCommand(ModemRx13[0],&ModemRx13[1]);
	GPIO_ResetBits(GPIOA,RF4463_SEL ); 		
	for(api_num=0;api_num<ModemRx17[0];api_num++)Spi1ReadWrite(ModemRx17[1+api_num]);	
	GPIO_SetBits(GPIOA,RF4463_SEL );
	vApi_WaitforCTS();// Wait for CTS 
	//	bApi_SendCommand(ModemRx13[0],&ModemRx13[1]);
	GPIO_ResetBits(GPIOA,RF4463_SEL ); 		
	for(api_num=0;api_num<ModemRx18[0];api_num++)Spi1ReadWrite(ModemRx18[1+api_num]);	
	GPIO_SetBits(GPIOA,RF4463_SEL );
	vApi_WaitforCTS();// Wait for CTS 
	//	bApi_SendCommand(ModemRx13[0],&ModemRx13[1]);
	GPIO_ResetBits(GPIOA,RF4463_SEL ); 		
	for(api_num=0;api_num<ModemRx19[0];api_num++)Spi1ReadWrite(ModemRx19[1+api_num]);	
	GPIO_SetBits(GPIOA,RF4463_SEL );
	vApi_WaitforCTS();// Wait for CTS 
		//	bApi_SendCommand(ModemRx13[0],&ModemRx13[1]);
	GPIO_ResetBits(GPIOA,RF4463_SEL ); 		
	for(api_num=0;api_num<ModemRx20[0];api_num++)Spi1ReadWrite(ModemRx20[1+api_num]);	
	GPIO_SetBits(GPIOA,RF4463_SEL );
	vApi_WaitforCTS();// Wait for CTS 
		//	bApi_SendCommand(ModemRx13[0],&ModemRx13[1]);
	GPIO_ResetBits(GPIOA,RF4463_SEL ); 		
	for(api_num=0;api_num<ModemRx21[0];api_num++)Spi1ReadWrite(ModemRx21[1+api_num]);	
	GPIO_SetBits(GPIOA,RF4463_SEL );
	vApi_WaitforCTS();// Wait for CTS 
  // Configuring PA mode
	vSetPAMode(0x0e,0x02);          // Select proper testcard and modulation
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Enable the proper interrupts
  abApi_Write[0] = CMD_SET_PROPERTY;        // Use property command
  abApi_Write[1] = PROP_INT_CTL_GROUP;      // Select property group
  abApi_Write[2] = 4;               // Number of properties to be written
  abApi_Write[3] = PROP_INT_CTL_ENABLE;     // Specify property
  abApi_Write[4] = 0x01;              // INT_CTL: PH interrupt enable
  abApi_Write[5] = 0x38;              // INT_CTL_PH: PH PACKET_SENT, PACKET_RX, CRC2_ERR enabled
  abApi_Write[6] = 0x00;              // INT_CTL_MODEM: -
  abApi_Write[7] = 0x00;              // INT_CTL_CHIP_EN: -
  bApi_SendCommand(8,abApi_Write);        // Send API command to the radio IC
  vApi_WaitforCTS();                // Wait for CTS

  // Configure Fast response registers
  abApi_Write[0] = CMD_SET_PROPERTY;        // Use property command
  abApi_Write[1] = PROP_FRR_CTL_GROUP;      // Select property group
  abApi_Write[2] = 4;               // Number of properties to be written
  abApi_Write[3] = PROP_FRR_CTL_A_MODE;     // Specify fast response registers
  abApi_Write[4] = 0x04;              // FRR A: PH IT pending
  abApi_Write[5] = 0x06;              // FRR B: Modem IT pending
  abApi_Write[6] = 0x0A;              // FRR C: Latched RSSI
  abApi_Write[7] = 0x00;              // FRR D: disabled
  bApi_SendCommand(8,abApi_Write);        // Send API command to the radio IC
  vApi_WaitforCTS();                // Wait for CTS

	// Set packet content
// Set preamble length - Tx
  abApi_Write[0] = CMD_SET_PROPERTY;        // Use property command
  abApi_Write[1] = PROP_PREAMBLE_GROUP;     // Select property group
  abApi_Write[2] = 1;               // Number of properties to be written
  abApi_Write[3] = PROP_PREAMBLE_TX_LENGTH;   // Specify property
  abApi_Write[4] = 0x05;              // 5 bytes Tx preamble
  bApi_SendCommand(5,abApi_Write);        // Send command to the radio IC
  vApi_WaitforCTS();                // Wait for CTS

 // Set preamble length - Rx
  abApi_Write[0] = CMD_SET_PROPERTY;        // Use property command
  abApi_Write[1] = PROP_PREAMBLE_GROUP;     // Select property group
  abApi_Write[2] = 1;               // Number of properties to be written
  abApi_Write[3] = PROP_PREAMBLE_CONFIG_STD_1;  // Specify property
  abApi_Write[4] = 20;              // 20 bits preamble detection threshold
  bApi_SendCommand(5,abApi_Write);        // Send API command to the radio IC
  vApi_WaitforCTS();                // Wait for CTS


	// Set preamble pattern
	abApi_Write[0] = CMD_SET_PROPERTY;        // Use property command
	abApi_Write[1] = PROP_PREAMBLE_GROUP;     // Select property group
	abApi_Write[3] = PROP_PREAMBLE_CONFIG;      // Specify property
	abApi_Write[2] = 1;               // Number of properties to be written
	abApi_Write[4] = 0x31;              // Use `1010` pattern, length defined in bytes
	bApi_SendCommand(5,abApi_Write);        // Send command to the radio IC
	vApi_WaitforCTS();                // Wait for CTS

	// Set sync word
	abApi_Write[0] = CMD_SET_PROPERTY;        // Use property command
	abApi_Write[1] = PROP_SYNC_GROUP;       // Select property group
	abApi_Write[3] = PROP_SYNC_CONFIG;        // Specify property
	abApi_Write[2] = 3;               // Number of properties to be written
	abApi_Write[4] = 0x01;              // SYNC_CONFIG: 2 bytes sync word
	abApi_Write[5] = 0xB4;              // SYNC_BITS_31_24: 1st sync byte: 0x2D; NOTE: LSB transmitted first!
	abApi_Write[6] = 0x2B;              // SYNC_BITS_23_16: 2nd sync byte: 0xD4; NOTE: LSB transmitted first!
	bApi_SendCommand(7,abApi_Write);        // Send command to the radio IC
	vApi_WaitforCTS();                // Wait for CTS

  // General packet config (set bit order)
  abApi_Write[0] = CMD_SET_PROPERTY;        // Use property command
  abApi_Write[1] = PROP_PKT_GROUP;        // Select property group
  abApi_Write[2] = 1;               // Number of properties to be written
  abApi_Write[3] = PROP_PKT_CONFIG1;        // Specify property
  abApi_Write[4] = 0x80;              // Separate RX and TX FIELD properties are used, payload data goes MSB first
  bApi_SendCommand(5,abApi_Write);        // Send command to the radio IC
  vApi_WaitforCTS(); 


  // Set variable packet length
  abApi_Write[0] = CMD_SET_PROPERTY;        // Use property command
  abApi_Write[1] = PROP_PKT_GROUP;        // Select property group
  abApi_Write[2] = 3;               // Number of properties to be written
  abApi_Write[3] = PROP_PKT_LEN;          // Specify property
  abApi_Write[4] = 0x0A;              // PKT_LEN: length is put in the Rx FIFO, FIELD 2 is used for the payload (with variable length)
  abApi_Write[5] = 0x01;              // PKT_LEN_FIELD_SOURCE: FIELD 1 is used for the length information
  abApi_Write[6] = 0x00;              // PKT_LEN_ADJUST: no adjustment (FIELD 1 determines the actual payload length)
  bApi_SendCommand(7,abApi_Write);        // Send command to the radio IC
  vApi_WaitforCTS();                // Wait for CTS

  // Set packet fields for Tx (one field is used)
  abApi_Write[0] = CMD_SET_PROPERTY;        // Use property command
  abApi_Write[1] = PROP_PKT_GROUP;        // Select property group
  abApi_Write[2] = 4;               // Number of properties to be written
  abApi_Write[3] = PROP_PKT_FIELD_1_LENGTH_12_8;  // Specify first property
  abApi_Write[4] = 0x00;              // PKT_FIELD_1_LENGTH_12_8: defined later (under bSendPacket() )
  abApi_Write[5] = 0x00;              // PKT_FIELD_1_LENGTH_7_0: defined later (under bSendPacket() )
  abApi_Write[6] = 0x00;              // PKT_FIELD_1_CONFIG : No 4(G)FSK/Whitening/Manchester coding for this field
  abApi_Write[7] = 0xA2;              // PKT_FIELD_1_CRC_CONFIG: Start CRC calc. from this field, send CRC at the end of the field
  bApi_SendCommand(8,abApi_Write);        // Send command to the radio IC
  vApi_WaitforCTS();                // Wait for CTS

  // Set packet fields for Rx (two fields are used)
  // FIELD1 is fixed, 1byte length, used for PKT_LEN
  abApi_Write[0] = CMD_SET_PROPERTY;        // Use property command
  abApi_Write[1] = PROP_PKT_GROUP;        // Select property group
  abApi_Write[2] = 4;               // Number of properties to be written
  abApi_Write[3] = PROP_PKT_RX_FIELD_1_LENGTH_12_8; // Specify first property
  abApi_Write[4] = 0x00;              // PKT_RX_FIELD_1_LENGTH_12_8: 1 byte (containing variable packet length info)
  abApi_Write[5] = 0x01;              // PKT_RX_FIELD_1_LENGTH_7_0: 1 byte (containing variable packet length info)
  abApi_Write[6] = 0x00;              // PKT_RX_FIELD_1_CONFIG: No 4(G)FSK/Whitening/Manchester coding for this field
  abApi_Write[7] = 0x82;              // PKT_RX_FIELD_1_CRC_CONFIG: Start CRC calc. from this field, enable CRC calc.
  bApi_SendCommand(8,abApi_Write);        // Send command to the radio IC
  // FIELD2 is variable length, contains the actual payload
  vApi_WaitforCTS();                // Wait for CTS
  abApi_Write[0] = CMD_SET_PROPERTY;        // Use property command
  abApi_Write[1] = PROP_PKT_GROUP;        // Select property group
  abApi_Write[2] = 4;               // Number of properties to be written
  abApi_Write[3] = PROP_PKT_RX_FIELD_2_LENGTH_12_8; // Specify first property
  abApi_Write[4] = 0x00;              // PKT_RX_FIELD_2_LENGTH_12_8: max. field length (variable packet length)
  abApi_Write[5] = MAX_RX_LENGTH;     // PKT_RX_FIELD_2_LENGTH_7_0: max. field length (variable packet length)
  abApi_Write[6] = 0x00;              // PKT_RX_FIELD_2_CONFIG: No 4(G)FSK/Whitening/Manchester coding for this field
  abApi_Write[7] = 0x0A;              // PKT_RX_FIELD_2_CRC_CONFIG: check CRC at the end, enable CRC calc.
  bApi_SendCommand(8,abApi_Write);        // Send command to the radio IC
  vApi_WaitforCTS(); 

	// Configure CRC polynomial and seed
	abApi_Write[0] = CMD_SET_PROPERTY;        // Use property command
	abApi_Write[1] = PROP_PKT_GROUP;        // Select property group
	abApi_Write[3] = PROP_PKT_CRC_CONFIG;     // Specify property
	abApi_Write[2] = 1;               // Number of properties to be written
	abApi_Write[4] = 0x05;              // CRC seed: all `0`s, poly: No. 5, 16bit; CCIT-16
	bApi_SendCommand(5,abApi_Write);        // Send command to the radio IC
	vApi_WaitforCTS();                // Wait for CTS

// Set RSSI latch to sync word
  abApi_Write[0] = CMD_SET_PROPERTY;        // Use property command
  abApi_Write[1] = PROP_MODEM_GROUP;        // Select property group
  abApi_Write[2] = 1;               // Number of properties to be written
  abApi_Write[3] = PROP_MODEM_RSSI_CONTROL;   // Specify property
  abApi_Write[4] = 0x12;              // RSSI average over 4 bits, latches at sync word detect
  bApi_SendCommand(5,abApi_Write);        // Send API command to the radio IC
  vApi_WaitforCTS();                // Wait for CTS

	// Select Tx_Clock to GPIO0, Tx_Data to GPIO1
	abApi_Write[0] = CMD_GPIO_PIN_CFG;        // Use GPIO pin configuration command
#ifdef ONE_SMA_WITH_RF_SWITCH
  // If RF switch is used
  // Select Tx state to GPIO2, Rx state to GPIO0
	abApi_Write[1] = 0x21;              // Configure GPIO0 as Rx state
	abApi_Write[2] = 0x13;              // Configure GPIO1 as Tx data
	abApi_Write[3] = 0x20;              // Configure GPIO2 as Tx state
	abApi_Write[4] = 0x10;              // Configure GPIO3 as Tx data CLK
#else
	abApi_Write[1] = 0x10;              // Configure GPIO0 as Tx data CLK
	abApi_Write[2] = 0x13;              // Configure GPIO1 as Tx data
	abApi_Write[3] = 0x20;              // Configure GPIO2 as Tx state
	abApi_Write[4] = 0x21;              // Configure GPIO3 as Rx state
#endif
	bApi_SendCommand(5,abApi_Write);        // Send command to the radio IC
	vApi_WaitforCTS();
	
	// Adjust XTAL clock frequency
	abApi_Write[0] = CMD_SET_PROPERTY;        // Use property command
	abApi_Write[1] = PROP_GLOBAL_GROUP;       // Select property group
	abApi_Write[2] = 1;               // Number of properties to be written
	abApi_Write[3] = PROP_GLOBAL_XO_TUNE;     // Specify property
	abApi_Write[4] = CAP_BANK_VALUE;        // Set cap bank value to adjust XTAL clock frequency
	bApi_SendCommand(5,abApi_Write);        // Send command to the radio IC
	vApi_WaitforCTS();                // Wait for CTS
/////////////////////////////////////////////////////////////////////
// Start Rx
  abApi_Write[0] = CMD_START_RX;      // Use start Rx command
  abApi_Write[1] = 0;           // Set channel number
  abApi_Write[2] = 0x00;          // Start Rx immediately
  abApi_Write[3] = 0x00;          // Packet fields used, do not enter packet length here
  abApi_Write[4] = 0x00;          // Packet fields used, do not enter packet length here
  abApi_Write[5] = 0x00;          // No change if Rx timeout
  abApi_Write[6] = 0x00;          // Ready state after Rx valid state
  abApi_Write[7] = 0x03;          // Ready state after Rx invalid state
  bApi_SendCommand(8,abApi_Write);    // Send API command to the radio IC
  vApi_WaitforCTS();            // Wait for CTS//	for(api_num=0;api_num<Tx_LENTH;api_num++) transmit_arry[api_num]=api_num;

}
