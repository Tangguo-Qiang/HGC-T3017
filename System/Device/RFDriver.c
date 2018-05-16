#include "system.h"
#include "si446x_defs.h"
//#include "si446x_patch.h"
#include "radio_config_Si4438.h"


#define		RF_PORT_SDI		GPIOC
#define		RF_PIN_SDI		GPIO_Pin_4
#define		RF_PORT_SDO		GPIOC
#define		RF_PIN_SDO		GPIO_Pin_5
#define		RF_PORT_SCK		GPIOA
#define		RF_PIN_SCK		GPIO_Pin_7
#define		RF_PORT_SEL		GPIOA
#define		RF_PIN_SEL		GPIO_Pin_6
#define		RF_PORT_IRQ		GPIOA
#define		RF_PIN_IRQ		GPIO_Pin_5
#define		RF_PORT_SDN		GPIOA
#define		RF_PIN_SDN		GPIO_Pin_4
#define		RF_PORT_GPIO1		GPIOA
#define		RF_PIN_GPIO1		GPIO_Pin_4

#define SET_SDI_LOW 			GPIO_ResetBits(RF_PORT_SDI, RF_PIN_SDI)
#define SET_SDI_HIGH 			GPIO_SetBits(RF_PORT_SDI, RF_PIN_SDI)
#define SET_SCK_LOW 			GPIO_ResetBits(RF_PORT_SCK, RF_PIN_SCK)
#define SET_SCK_HIGH 			GPIO_SetBits(RF_PORT_SCK, RF_PIN_SCK)
#define SET_SEL_LOW 			GPIO_ResetBits(RF_PORT_SEL, RF_PIN_SEL)
#define SET_SEL_HIGH 			GPIO_SetBits(RF_PORT_SEL, RF_PIN_SEL)
#define GET_SDO_STATE()		GPIO_ReadInputDataBit(RF_PORT_SDO, RF_PIN_SDO)
#define GET_IRQ_STATE()		GPIO_ReadInputDataBit(RF_PORT_IRQ, RF_PIN_IRQ)
#define SET_SDN_LOW 			GPIO_ResetBits(RF_PORT_SDN, RF_PIN_SDN)
#define SET_SDN_HIGH 			GPIO_SetBits(RF_PORT_SDN, RF_PIN_SDN)


/*****************************************************************************
 *  Global Typedefs & Enums
 *****************************************************************************/
#define SI466X_FIFO_SIZE 64
#define RADIO_MAX_PACKET_LENGTH     32u
#define RADIO_CTS_TIMEOUT 300

typedef enum{
	NOBYTE	= (byte)0x00,
	YESBYTE = !(byte)0x01,
}bool_typ; 

enum
{
    SI446X_SUCCESS,
    SI446X_NO_PATCH,
    SI446X_CTS_TIMEOUT,
    SI446X_PATCH_FAIL,
    SI446X_COMMAND_ERROR
};

typedef struct
{
    const uint8_t   *Radio_ConfigurationArray;

    uint8_t   Radio_ChannelNumber;
    uint8_t   Radio_PacketLength;
    uint8_t   Radio_State_After_Power_Up;

    uint16_t  Radio_Delay_Cnt_After_Reset;
    uint8_t   Radio_CustomPayload[RADIO_MAX_PACKET_LENGTH];
} tRadioConfiguration;

/*****************************************************************************
 *  Global Variables
 *****************************************************************************/
const uint8_t Radio_Configuration_Data_Array[] =  RADIO_CONFIGURATION_DATA_ARRAY;

const tRadioConfiguration RadioConfiguration = RADIO_CONFIGURATION_DATA;

const tRadioConfiguration *pRadioConfiguration = &RadioConfiguration;


uint8_t customRadioPacket[RADIO_MAX_PACKET_LENGTH];


static union si446x_cmd_reply_union Si446xCmd;
byte ctsWentHigh = 0;
static byte s_ucPro2Cmd[16];

#if 0 //不使用补丁
#ifdef SI446X_PATCH_CMDS
const byte Si446xPatchCommands[][8] = { SI446X_PATCH_CMDS };
#endif
#endif

/*******************************************************************************
* 文件名	: Spi_ReadWriteSpi
* 描述    	: SPI读写位操作
* 输入		: biDataIn
* 输出		: 无
* 返回值	: 无
*******************************************************************************/
byte Spi_ReadWriteSpi(byte biDataIn)//PR008B1：实测时钟周期=100K 2014.7.8
{
	volatile byte rl = 0, i;

	SET_SCK_LOW;
	for(i = 0; i < 8; i ++)
	{
		if((biDataIn & 0x80) > 0) //先发送高位
			SET_SDI_HIGH;
		else
			SET_SDI_LOW;

		SET_SCK_HIGH;
		biDataIn <<= 1;

		rl <<= 1;
		if(GET_SDO_STATE())
			rl += 1;

		SET_SCK_LOW;
	}SET_SCK_LOW;

	return rl;
}
/*******************************************************************************
* 文件名	: Spi_WriteDataSpi
* 描述    	: SPI写数据
* 输入		: biDataInLength，pabiDataIn
* 输出		: 无
* 返回值	: 无
*******************************************************************************/
void Spi_WriteDataSpi(byte biDataInLength, byte *pabiDataIn)
{
  while (biDataInLength--) 
  {
    Spi_ReadWriteSpi(*pabiDataIn++);

  }
}


/*******************************************************************************
* 文件名	: Spi_ReadDataSpi
* 描述    	: SPI读数据
* 输入		: biDataOutLength，paboDataOut
* 输出		: 无
* 返回值	: 无
*******************************************************************************/
void Spi_ReadDataSpi(byte biDataOutLength, byte *paboDataOut)
{
 
  while (biDataOutLength--) 
  {
    *paboDataOut++ = Spi_ReadWriteSpi(0xFF);

  }
}
/*******************************************************************************
* 文件名	: radio_comm_GetResp
* 描述    	: 获取命令返回值
* 输入		: 无
* 输出		: 无
* 返回值	: CTS value
*******************************************************************************/
byte radio_comm_GetResp(byte byteCount, byte* pData)
{
  byte ctsVal = 0u;
  ushort errCnt = RADIO_CTS_TIMEOUT;

  //实测循环RADIO_CTS_TIMEOUT次花费时间, RP008B1实测最长循环时间~50ms 2014.7.9	
  //POWER UP命令等待时间最长约14ms  It takes approximately 14ms to complete the command (boot time)
  while (errCnt != 0)      //wait until radio IC is ready with the data
  {
		DelayMsNull(1);
    SET_SEL_LOW;
//    radio_hal_SpiWriteByte(0x44);    //read CMD buffer
    Spi_ReadWriteSpi(0x44);    //read CMD buffer
//    ctsVal = radio_hal_SpiReadByte();
    ctsVal = Spi_ReadWriteSpi(0xFF);;
    if (ctsVal == 0xFF)
    {
      if(byteCount)
      {
//        radio_hal_SpiReadData(byteCount, pData);
        Spi_ReadDataSpi(byteCount, pData);
      }
//      radio_hal_SetNsel();
        SET_SEL_HIGH;
      break;
    }
//    radio_hal_SetNsel();
    SET_SEL_HIGH;
    errCnt--;
  }
  if (ctsVal == 0xFF)
  {
    ctsWentHigh = 1;
  }

  return ctsVal;
}

/*******************************************************************************
* 文件名	: radio_comm_PollCTS
* 描述    	: Waits for CTS to be high
* 输入		: 无
* 输出		: 无
* 返回值	: CTS value
*******************************************************************************/
byte radio_comm_PollCTS(void)
{
#ifdef RADIO_USER_CFG_USE_GPIO1_FOR_CTS  //使用GPIO口来判断
    while(!radio_hal_Gpio1Level())
    {
        /* Wait...*/
    }
    ctsWentHigh = 1;
    return 0xFF;
#else
    return radio_comm_GetResp(0, 0);
#endif
} 
/*******************************************************************************
* 文件名	: radio_comm_SendCmd
* 描述    	: 发送命令
* 输入		: 无
* 输出		: 无
* 返回值	: 无
*******************************************************************************/
void radio_comm_SendCmd(byte byteCount, byte* pData)
{
    while (!ctsWentHigh)
    {
        radio_comm_PollCTS();
    }
//    radio_hal_ClearNsel();
		SET_SEL_LOW;
//    radio_hal_SpiWriteData(byteCount, pData);
		Spi_WriteDataSpi(byteCount, pData);
//    radio_hal_SetNsel();
		SET_SEL_HIGH;
    ctsWentHigh = 0;
}

/*******************************************************************************
* 文件名	: radio_comm_SendCmdGetResp
* 描述    	: 发送命令并返回命令响应值
* 输入		: 无
* 输出		: 无
* 返回值	: 无
*******************************************************************************/
byte radio_comm_SendCmdGetResp(byte cmdByteCount, byte* pCmdData, byte respByteCount, byte* pRespData)
{
    radio_comm_SendCmd(cmdByteCount, pCmdData);
    return radio_comm_GetResp(respByteCount, pRespData);
}

 
/*******************************************************************************
* 文件名	: radio_comm_ReadData
* 描述    	: 读数据 Gets a command response from the radio chip
* 输入		:
			* @param cmd           Command ID
			* @param pollCts       Set to poll CTS
			* @param byteCount     Number of bytes to get from the radio chip.
			* @param pData         Pointer to where to put the data.
* 输出		: 无
* 返回值	: 无
*******************************************************************************/
void radio_comm_ReadData(byte cmd, bool_typ pollCts, byte byteCount, byte* pData)
{
    if(pollCts)
    {
        while(!ctsWentHigh)
        {
            radio_comm_PollCTS();
        }
    }
//    radio_hal_ClearNsel();
		SET_SEL_LOW;
//    radio_hal_SpiWriteByte(cmd);    //read CMD buffer
    Spi_ReadWriteSpi(cmd);    //read CMD buffer
//        radio_hal_SpiReadData(byteCount, pData);
        Spi_ReadDataSpi(byteCount, pData);
//    radio_hal_SetNsel();
		SET_SEL_HIGH;
    ctsWentHigh = 0;
}


 
/*******************************************************************************
* 文件名	: radio_comm_WriteData
* 描述    	: 读数据 Gets a command response from the radio chip
* 输入		:
			* @param cmd           Command ID
			* @param pollCts       Set to poll CTS
			* @param byteCount     Number of bytes to get from the radio chip
			* @param pData         Pointer to where to put the data
* 返回值	: 无
*******************************************************************************/
void radio_comm_WriteData(byte cmd, bool_typ pollCts, byte byteCount, byte* pData)
{
    if(pollCts)
    {
        while(!ctsWentHigh)
        {
            radio_comm_PollCTS();
        }
    }
//    radio_hal_ClearNsel();
		SET_SEL_LOW;
//    radio_hal_SpiWriteByte(cmd);    //read CMD buffer
    Spi_ReadWriteSpi(cmd);    //read CMD buffer
//    radio_hal_SpiReadData(byteCount, pData);
    Spi_ReadDataSpi(byteCount, pData);
//    radio_hal_SetNsel();
		SET_SEL_HIGH;
    ctsWentHigh = 0;
}

/*!
 * This functions is used to reset the si446x radio by applying shutdown and
 * releasing it.  After this function @ref si446x_boot should be called.  You
 * can check if POR has completed by waiting 4 ms or by polling GPIO 0, 2, or 3.
 * When these GPIOs are high, it is safe to call @ref si446x_boot.
 */
void si446x_reset(void) //延时时间需要实测
{
    //u16 loopCount;

    /* Put radio in shutdown, wait then release 
    radio_hal_AssertShutdown();*/
	SET_SDN_HIGH;

    //! @todo this needs to be a better delay function.
    //for (loopCount = 1000; loopCount != 0; loopCount--); // Wait ~300us (SDN pulse width)  		实测PR008B1:2ms 2014.7.9
	DelayMsNull(2);
//    radio_hal_DeassertShutdown();
	SET_SDN_LOW;
    //for (loopCount = 3500; loopCount != 0; loopCount--); //Wait for POR (power on reset); ~5ms  实测PR008B1:7ms 2014.7.9
	DelayMsNull(7);
//    radio_comm_ClearCTS();
	ctsWentHigh = 0;

}

/*!
 * This function is used to initialize after power-up the radio chip.
 * Before this function @si446x_reset should be called.
 */
void si446x_power_up(byte BOOT_OPTIONS, byte XTAL_OPTIONS, uint XO_FREQ)
{
    s_ucPro2Cmd[0] = SI446X_CMD_ID_POWER_UP;
    s_ucPro2Cmd[1] = BOOT_OPTIONS;
    s_ucPro2Cmd[2] = XTAL_OPTIONS;
    s_ucPro2Cmd[3] = (byte)(XO_FREQ >> 24);
    s_ucPro2Cmd[4] = (byte)(XO_FREQ >> 16);
    s_ucPro2Cmd[5] = (byte)(XO_FREQ >> 8);
    s_ucPro2Cmd[6] = (byte)(XO_FREQ);

    radio_comm_SendCmd( SI446X_CMD_ARG_COUNT_POWER_UP, s_ucPro2Cmd );
}
/*! Sends START_TX command to the radio.
 *
 * @param CHANNEL   Channel number.
 * @param CONDITION Start TX condition.
 * @param TX_LEN    Payload length (exclude the PH generated CRC).
 */
void si446x_start_tx(byte CHANNEL, byte CONDITION, ushort TX_LEN)
{
    s_ucPro2Cmd[0] = SI446X_CMD_ID_START_TX;
    s_ucPro2Cmd[1] = CHANNEL;
    s_ucPro2Cmd[2] = CONDITION;
    s_ucPro2Cmd[3] = (byte)(TX_LEN >> 8);
    s_ucPro2Cmd[4] = (byte)(TX_LEN);
    s_ucPro2Cmd[5] = 0x00;

    radio_comm_SendCmd( SI446X_CMD_ARG_COUNT_START_TX, s_ucPro2Cmd );
}

/*!
 * Sends START_RX command to the radio.
 *
 * @param CHANNEL     Channel number.
 * @param CONDITION   Start RX condition.
 * @param RX_LEN      Payload length (exclude the PH generated CRC).
 * @param NEXT_STATE1 Next state when Preamble Timeout occurs.
 * @param NEXT_STATE2 Next state when a valid packet received.
 * @param NEXT_STATE3 Next state when invalid packet received (e.g. CRC error).
 */
void si446x_start_rx(byte CHANNEL, byte CONDITION, ushort RX_LEN, byte NEXT_STATE1, byte NEXT_STATE2, byte NEXT_STATE3)
{
    s_ucPro2Cmd[0] = SI446X_CMD_ID_START_RX;
    s_ucPro2Cmd[1] = CHANNEL;
    s_ucPro2Cmd[2] = CONDITION;
    s_ucPro2Cmd[3] = (byte)(RX_LEN >> 8);
    s_ucPro2Cmd[4] = (byte)(RX_LEN);
    s_ucPro2Cmd[5] = NEXT_STATE1;
    s_ucPro2Cmd[6] = NEXT_STATE2;
    s_ucPro2Cmd[7] = NEXT_STATE3;

    radio_comm_SendCmd( SI446X_CMD_ARG_COUNT_START_RX, s_ucPro2Cmd );
}

/*!
 * Get the Interrupt status/pending flags form the radio and clear flags if requested.
 *
 * @param PH_CLR_PEND     Packet Handler pending flags clear.
 * @param MODEM_CLR_PEND  Modem Status pending flags clear.
 * @param CHIP_CLR_PEND   Chip State pending flags clear.
 */
void si446x_get_int_status(byte PH_CLR_PEND, byte MODEM_CLR_PEND, byte CHIP_CLR_PEND)
{
    s_ucPro2Cmd[0] = SI446X_CMD_ID_GET_INT_STATUS;
    s_ucPro2Cmd[1] = PH_CLR_PEND;
    s_ucPro2Cmd[2] = MODEM_CLR_PEND;
    s_ucPro2Cmd[3] = CHIP_CLR_PEND;

    radio_comm_SendCmdGetResp( SI446X_CMD_ARG_COUNT_GET_INT_STATUS,
                              s_ucPro2Cmd,
                              SI446X_CMD_REPLY_COUNT_GET_INT_STATUS,
                              s_ucPro2Cmd );

    Si446xCmd.GET_INT_STATUS.INT_PEND       = s_ucPro2Cmd[0];
    Si446xCmd.GET_INT_STATUS.INT_STATUS     = s_ucPro2Cmd[1];
    Si446xCmd.GET_INT_STATUS.PH_PEND        = s_ucPro2Cmd[2];
    Si446xCmd.GET_INT_STATUS.PH_STATUS      = s_ucPro2Cmd[3];
    Si446xCmd.GET_INT_STATUS.MODEM_PEND     = s_ucPro2Cmd[4];
    Si446xCmd.GET_INT_STATUS.MODEM_STATUS   = s_ucPro2Cmd[5];
    Si446xCmd.GET_INT_STATUS.CHIP_PEND      = s_ucPro2Cmd[6];
    Si446xCmd.GET_INT_STATUS.CHIP_STATUS    = s_ucPro2Cmd[7];
}

/*!
 * Issue a change state command to the radio.
 *
 * @param NEXT_STATE1 Next state.
 */
void si446x_change_state(byte NEXT_STATE1)
{
    s_ucPro2Cmd[0] = SI446X_CMD_ID_CHANGE_STATE;
    s_ucPro2Cmd[1] = NEXT_STATE1;

    radio_comm_SendCmd( SI446X_CMD_ARG_COUNT_CHANGE_STATE, s_ucPro2Cmd );
}

/*!
 * Send the FIFO_INFO command to the radio. Optionally resets the TX/RX FIFO. Reads the radio response back
 * into @Si446xCmd.
 *
 * @param FIFO  RX/TX FIFO reset flags.
 */
void si446x_fifo_info(byte FIFO)
{
    s_ucPro2Cmd[0] = SI446X_CMD_ID_FIFO_INFO;
    s_ucPro2Cmd[1] = FIFO;

    radio_comm_SendCmdGetResp( SI446X_CMD_ARG_COUNT_FIFO_INFO,
                              s_ucPro2Cmd,
                              SI446X_CMD_REPLY_COUNT_FIFO_INFO,
                              s_ucPro2Cmd );

    Si446xCmd.FIFO_INFO.RX_FIFO_COUNT   = s_ucPro2Cmd[0];
    Si446xCmd.FIFO_INFO.TX_FIFO_SPACE   = s_ucPro2Cmd[1];
}


/*!
 * The function can be used to load data into TX FIFO.
 *
 * @param numBytes  Data length to be load.
 * @param pTxData   Pointer to the data (byte*).
 */
void si446x_write_tx_fifo(byte numBytes, byte* pTxData)
{
  radio_comm_WriteData( SI446X_CMD_ID_WRITE_TX_FIFO, (bool_typ)0, numBytes, pTxData );
}

/*!
 * Reads the RX FIFO content from the radio.
 *
 * @param numBytes  Data length to be read.
 * @param pRxData   Pointer to the buffer location.
 */
void si446x_read_rx_fifo(byte numBytes, byte* pRxData)
{
  radio_comm_ReadData( SI446X_CMD_ID_READ_RX_FIFO, (bool_typ)0, numBytes, pRxData );
}

/*!
 * This function is used to load all properties and commands with a list of NULL terminated commands.
 * Before this function @si446x_reset should be called.
 */
byte si446x_configuration_init(const byte* pSetPropCmd)
{

	byte col;
	byte numOfBytes;

  /* While cycle as far as the pointer points to a command */
  while (*pSetPropCmd != 0x00)
  {
    /* Commands structure in the array:
     * --------------------------------
     * LEN | <LEN length of data>
     */

    numOfBytes = *pSetPropCmd++;

    if (numOfBytes > 16u)
    {
      /* Number of command bytes exceeds maximal allowable length */
      return SI446X_COMMAND_ERROR;
    }

    for (col = 0u; col < numOfBytes; col++)
    {
      s_ucPro2Cmd[col] = *pSetPropCmd;
      pSetPropCmd++;
    }

    if (radio_comm_SendCmdGetResp(numOfBytes, s_ucPro2Cmd, 0, 0) != 0xFF)
    {
      /* Timeout occured */
      return SI446X_CTS_TIMEOUT;
    }

    if (GET_SDO_STATE() == 0)
    {
      /* Get and clear all interrupts.  An error has occured... */
      si446x_get_int_status(0, 0, 0);
      if (Si446xCmd.GET_INT_STATUS.CHIP_PEND & SI446X_CMD_GET_CHIP_STATUS_REP_CMD_ERROR_PEND_MASK)
      {
        return SI446X_COMMAND_ERROR;
      }
    }
  }

  return SI446X_SUCCESS;
}



/*!
 *  Check if Packet sent IT flag or Packet Received IT is pending.
 *
 *  @return   SI4455_CMD_GET_INT_STATUS_REP_PACKET_SENT_PEND_BIT / SI4455_CMD_GET_INT_STATUS_REP_PACKET_RX_PEND_BIT
 *
 *  @note
 *
 */
uint8_t bRadio_Check_Tx_RX(void)
{
//  if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2) == FALSE)
//  {
      /* Read ITs, clear pending ones */
      si446x_get_int_status(0u, 0u, 0u);

	  if (Si446xCmd.GET_INT_STATUS.CHIP_PEND & SI446X_CMD_GET_CHIP_STATUS_REP_CMD_ERROR_PEND_BIT)
		{
      	/* State change to */
      	si446x_change_state(SI446X_CMD_CHANGE_STATE_ARG_NEW_STATE_ENUM_SLEEP);
	
	  	/* Reset FIFO */
      	si446x_fifo_info(SI446X_CMD_FIFO_INFO_ARG_RX_BIT);
      
	  	/* State change to */
        si446x_change_state(SI446X_CMD_CHANGE_STATE_ARG_NEW_STATE_ENUM_RX);
    }

    if(Si446xCmd.GET_INT_STATUS.PH_PEND & SI446X_CMD_GET_INT_STATUS_REP_PACKET_SENT_PEND_BIT)
    {
       return SI446X_CMD_GET_INT_STATUS_REP_PACKET_SENT_PEND_BIT;
    }

    if(Si446xCmd.GET_INT_STATUS.PH_PEND & SI446X_CMD_GET_INT_STATUS_REP_PACKET_RX_PEND_BIT)
    {
      /* Packet RX */

			/* Get payload length */
      si446x_fifo_info(0x00);

			si446x_read_rx_fifo(Si446xCmd.FIFO_INFO.RX_FIFO_COUNT, &customRadioPacket[0]);

      return SI446X_CMD_GET_INT_STATUS_REP_PACKET_RX_PEND_BIT;
    }
      
	  if (Si446xCmd.GET_INT_STATUS.PH_PEND & SI446X_CMD_GET_INT_STATUS_REP_CRC_ERROR_BIT)
    {
     	/* Reset FIFO */
     	si446x_fifo_info(SI446X_CMD_FIFO_INFO_ARG_RX_BIT);
    }


//  }

  return 0;
}

/*!
 *  Set Radio to RX mode. .
 *
 *  @param channel Freq. Channel,  packetLength : 0 Packet handler fields are used , nonzero: only Field1 is used
 *
 *  @note
 *
 */
void vRadio_StartRX(uint8_t channel, uint8_t packetLenght )
{
  // Read ITs, clear pending ones
  si446x_get_int_status(0u, 0u, 0u);

   // Reset the Rx Fifo
   si446x_fifo_info(SI446X_CMD_FIFO_INFO_ARG_RX_BIT);

  /* Start Receiving packet, channel 0, START immediately, Packet length used or not according to packetLength */
  si446x_start_rx(channel, 0u, packetLenght,
                  SI446X_CMD_START_RX_ARG_RXTIMEOUT_STATE_ENUM_NOCHANGE,
                  SI446X_CMD_START_RX_ARG_RXVALID_STATE_ENUM_READY,
                  SI446X_CMD_START_RX_ARG_RXINVALID_STATE_ENUM_RX );
}

/*!
 *  Set Radio to TX mode, variable packet length.
 *
 *  @param channel Freq. Channel, Packet to be sent length of of the packet sent to TXFIFO
 *
 *  @note
 *
 */
void vRadio_StartTx_Variable_Packet(uint8_t channel, uint8_t *pioRadioPacket, uint8_t length)
{
  /* Leave RX state */
  si446x_change_state(SI446X_CMD_CHANGE_STATE_ARG_NEW_STATE_ENUM_READY);

  /* Read ITs, clear pending ones */
  si446x_get_int_status(0u, 0u, 0u);

  /* Reset the Tx Fifo */
  si446x_fifo_info(SI446X_CMD_FIFO_INFO_ARG_TX_BIT);

  /* Fill the TX fifo with datas */
  si446x_write_tx_fifo(length, pioRadioPacket);

  /* Start sending packet, channel 0, START immediately */
   si446x_start_tx(channel, 0x80, length);
 
}
void vRadio_PowerUp(void)
{
  uint16_t wDelay = 0u;

  /* Hardware reset the chip */
  si446x_reset();

  /* Wait until reset timeout or Reset IT signal */
  for (; wDelay < pRadioConfiguration->Radio_Delay_Cnt_After_Reset; wDelay++);
}
void vRadio_Init(void)
{
  uint16_t wDelay;

  /* Power Up the radio chip */
  vRadio_PowerUp();

  /* Load radio configuration */
  while (SI446X_SUCCESS != si446x_configuration_init(pRadioConfiguration->Radio_ConfigurationArray))
  {
    for (wDelay = 0x7FFF; wDelay--; ) ;
    /* Power Up the radio chip */
    vRadio_PowerUp();
  }

  // Read ITs, clear pending ones
  si446x_get_int_status(0u, 0u, 0u);
}


void Si4463_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	
  GPIO_InitStruct.GPIO_Pin =  RF_PIN_SDI ;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Speed =GPIO_Speed_2MHz;
  GPIO_Init(RF_PORT_SDI, &GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin = RF_PIN_SEL ;
  GPIO_Init(RF_PORT_SEL, &GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin = RF_PIN_SCK ;
  GPIO_Init(RF_PORT_SCK, &GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin = RF_PIN_SDN ;
  GPIO_Init(RF_PORT_SDN, &GPIO_InitStruct);
	SET_SEL_HIGH;
	SET_SCK_HIGH;
	SET_SDN_HIGH;
	SET_SDI_HIGH;
	
	GPIO_InitStruct.GPIO_Pin = RF_PIN_IRQ ; 
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP; // 上拉输入
	GPIO_Init(RF_PORT_IRQ, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = RF_PIN_SDO; 
	GPIO_Init(RF_PORT_SDO, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = RF_PIN_GPIO1; 
	GPIO_Init(RF_PORT_GPIO1, &GPIO_InitStruct);
	GPIO_SetBits( RF_PORT_GPIO1	, RF_PIN_GPIO1 );
}
