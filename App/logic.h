/*
********************************************************************************
*文件名     : logic.h
*作用       : 
*原理       : 
********************************************************************************
*版本     作者            日期            说明
*V1.0    tgq        2016/05/12       初始版本
********************************************************************************
*/



#ifndef __LOGIC_H
#define __LOGIC_H

#define 	SEQUENCEOPER_DELAY_100MS		5

#define CTRLFLOW_STEP_MIN 1

typedef struct 
{
	ushort DispMax;
	byte DispMin;
	byte Dispstep;
	
	ushort BypassAngle;
	byte DoubleMotos;
	byte ExchangeFlows;
	byte AuxiHeater;
	
	ushort RpmMin_Moto1;
	ushort RpmOutAct_Moto1;
	ushort RpmInAct_Moto1;
	ushort PwmMin_Moto1;
	ushort PwmOutAct_Moto1;
	ushort PwmInAct_Moto1;	
	
	ushort RpmMin_Moto2;
	ushort RpmStop_Moto2;
	ushort RpmAct06_Moto2;
	ushort RpmAct08_Moto2;
	ushort RpmAct10_Moto2;
	ushort RpmAct12_Moto2;
	ushort PwmMin_Moto2;
	ushort PwmStop_Moto2;
	ushort PwmAct06_Moto2;
	ushort PwmAct08_Moto2;
	ushort PwmAct10_Moto2;
	ushort PwmAct12_Moto2;
}DevDataType;

extern byte SeqOperDelay;
extern const DevDataType *pDevData;

extern void LogicTask(void);

#endif 

