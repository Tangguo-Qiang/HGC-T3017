#include "system.h"


#define CO2_PORT	GPIOB
#define CO2_PIN	GPIO_Pin_1
#define CO2V_PORT	GPIOA
#define CO2V_PIN	GPIO_Pin_11
#define CO2V_OFF  GPIO_ResetBits(CO2V_PORT,CO2V_PIN)
#define CO2V_ON  GPIO_SetBits(CO2V_PORT,CO2V_PIN)

#define CO2_COUNTCYCLE_1MS   1000

static uint16_t CO2timer1ms=0;
static uint16_t CO2Count=0;
static uint16_t CO2ppm=0;

function PMSensorSystick1000Routine=Dummy;
function CO2SensorSystick1000Routine=Dummy;

static void CO2SensorHighCountPer1ms(void)
{
	CO2timer1ms++;
  if(GPIO_ReadInputDataBit(CO2_PORT,CO2_PIN)==SET)
		CO2Count++;	
	
		if(CO2timer1ms==1004)
		{
		if(CO2Count>2)
			CO2ppm	= (CO2Count-2)*2;
		else
			CO2ppm=0;
//		if(CO2Count>102)
//			CO2ppm	= (CO2Count-102)*4;
//		else
//			CO2ppm=0;
//		CO2ppm	+= 400;
			CO2timer1ms =0;
			CO2Count =0;
		}
}

static void CO2Sensor_Start(void)
{
	CO2V_ON;
	CO2SensorSystick1000Routine=CO2SensorHighCountPer1ms;
}

static void CO2Sensor_Stop(void)
{
	CO2V_OFF;
	CO2SensorSystick1000Routine=Dummy;
}
static uint16_t CO2ppm_Get(void)
{
	return CO2ppm;
}



void Init_PwmCount(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	
	/* CO2-PA5*/
  GPIO_InitStruct.GPIO_Pin = CO2_PIN;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(CO2_PORT, &GPIO_InitStruct);
	
	
  GPIO_InitStruct.GPIO_Pin = CO2V_PIN;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(CO2V_PORT, &GPIO_InitStruct);
	CO2V_OFF;
	
	
	System.Device.Pwm.CO2Sensor_Start=CO2Sensor_Start;
	System.Device.Pwm.CO2Sensor_Stop=CO2Sensor_Stop;	
	System.Device.Pwm.CO2ppm_Get=CO2ppm_Get;

}
