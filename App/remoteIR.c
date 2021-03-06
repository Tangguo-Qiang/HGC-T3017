#include "system.h"
#include "app.h"
#include "remoteIR.h"


void ParseRemoteIR(byte order)
{
	if(App.SysCtrlPara.Power == POWER_SLEEP)
	{
		System.Device.Beep.BeepOn(BEEP_SHORT);
		if(App.SysCtrlPara.MuteSet == MUTEMODE_ACT)
		{
			App.SysCtrlPara.MuteSet = MUTEMODE_OFF;
			PostMessage(MessageParaUpdate, PARA_MUTEMODE);
		}
		else
		{
			System.Device.Led.LedModeSet(LED_GREEN,TURN_OFF);
			App.SysCtrlPara.Power = POWER_ON;
		LCD_BL_ON;
		}
		return;
	}
	
	if((App.SysCtrlPara.Power == POWER_OFF)&&(order!=IR_REMOTE_POWER))
		return;
	
  if((App.SysCtrlPara.ChildLock==CHILD_LOCK)&&(order!=IR_REMOTE_LOCK)&&(order!=IR_REMOTE_MUTE))
	{
		System.Device.Led.LedModeSet(LED_GREEN,TEMP_TWINKLE);
		return;
	}
  
	App.SysState.WifiState |= WIFI_UPLOAD_SYSPARA;
	switch(order)
	{
		case IR_REMOTE_AIRFLOW_PLUS:
      App.SysCtrlPara.AirFlowSet++;
			if(App.SysCtrlPara.AirFlowSet>CtrlStepMax)
				App.SysCtrlPara.AirFlowSet = CtrlStepMax;
			App.SysCtrlPara.AirFlowRun=App.SysCtrlPara.AirFlowSet;
//			PostMessage(MessageParaUpdate, PARA_XFMOTODUTY);
//			CommTalk_Trans(COMM_BEEPONE);
			SeqOperDelay =SEQUENCEOPER_DELAY_100MS;
			
			break;
		case IR_REMOTE_AIRFLOW_MINUS:
        App.SysCtrlPara.AirFlowSet--;
	  		if(App.SysCtrlPara.AirFlowSet<CTRLFLOW_STEP_MIN)
					App.SysCtrlPara.AirFlowSet = CTRLFLOW_STEP_MIN;
				App.SysCtrlPara.AirFlowRun=App.SysCtrlPara.AirFlowSet;
//		PostMessage(MessageParaUpdate, PARA_XFMOTODUTY);
//		CommTalk_Trans(COMM_BEEPONE);
			SeqOperDelay =SEQUENCEOPER_DELAY_100MS;
				
			break;
		case IR_REMOTE_LOCK:
			if(App.SysCtrlPara.ChildLock == CHILD_UNLOCK)
				App.SysCtrlPara.ChildLock = CHILD_LOCK;
			else
				App.SysCtrlPara.ChildLock = CHILD_UNLOCK;
			PostMessage(MessageParaUpdate, PARA_CHILDLOCK);
			System.Device.Beep.BeepOn(BEEP_LONG);
			
			break;
		case IR_REMOTE_VENTIRATE_PLUS:
		  if(pDevData->ExchangeFlows)
			{
				App.SysCtrlPara.VentilateRate++;
				if(App.SysCtrlPara.VentilateRate>RATE10TO12)
					App.SysCtrlPara.VentilateRate=RATE10TO12;
				PostMessage(MessageParaUpdate, PARA_VENTILATE);
				System.Device.Beep.BeepOn(BEEP_LONG);
			}
			break;
		case IR_REMOTE_VENTIRATE_MINUS:
		  if(pDevData->ExchangeFlows)
			{
				App.SysCtrlPara.VentilateRate--;
				if(App.SysCtrlPara.VentilateRate<RATE10TO08)
					App.SysCtrlPara.VentilateRate=RATE10TO08;
				PostMessage(MessageParaUpdate, PARA_VENTILATE);
				System.Device.Beep.BeepOn(BEEP_LONG);
			}
			break;
		case IR_REMOTE_POWER:
			if(App.SysCtrlPara.Power == POWER_OFF)
			{
				App.SysCtrlPara.Power = POWER_ON;
				System.Device.Beep.BeepOn(BEEP_POWERON);
			}
			else
			{
				App.SysCtrlPara.Power = POWER_OFF;
				System.Device.Beep.BeepOn(BEEP_POWEROFF);
			}
			PostMessage(MessageParaUpdate, PARA_POWER_SET);
			
			break;
		case IR_REMOTE_MUTE:
			if(App.SysCtrlPara.MuteSet == MUTEMODE_OFF)
				App.SysCtrlPara.MuteSet = MUTEMODE_ACT;
			else
				App.SysCtrlPara.MuteSet = MUTEMODE_OFF;
			PostMessage(MessageParaUpdate, PARA_MUTEMODE);
			System.Device.Beep.BeepOn(BEEP_LONG);
			
			break;
		case IR_REMOTE_CIRCLEOUT:
			App.SysCtrlPara.CircleModeSet = CIRCLEMODE_OUT;
			PostMessage(MessageParaUpdate, PARA_CIRCLEMODE);
			System.Device.Beep.BeepOn(BEEP_LONG);
		
			break;
		case IR_REMOTE_CIRCLEIN:
			App.SysCtrlPara.CircleModeSet = CIRCLEMODE_IN;
			PostMessage(MessageParaUpdate, PARA_CIRCLEMODE);			
			System.Device.Beep.BeepOn(BEEP_LONG);
		
			break;
		case IR_REMOTE_CIRCLEAUTO:
			App.SysCtrlPara.CircleModeSet = CIRCLEMODE_AUTO;
			PostMessage(MessageParaUpdate, PARA_CIRCLEMODE);			
			System.Device.Beep.BeepOn(BEEP_LONG);
		
			break;
		
		case IR_REMOTE_THERMALMODE:
		  if(pDevData->ExchangeFlows)
			{
				App.SysCtrlPara.ThermalModeSet++;
				if(App.SysCtrlPara.ThermalModeSet>TEMPMODE_OFF)
					App.SysCtrlPara.ThermalModeSet=TEMPMODE_AUTO;
				PostMessage(MessageParaUpdate, PARA_THERMALMODE);
				System.Device.Beep.BeepOn(BEEP_LONG);
			}
			else if(pDevData->AuxiHeater)
			{
				if(pDevData->AuxiHeater>1)
				{
				App.SysCtrlPara.AuxiliaryHeatSet++;
				if(App.SysCtrlPara.AuxiliaryHeatSet>HEATER_FULL)
					App.SysCtrlPara.AuxiliaryHeatSet = HEATER_OFF;						
				}
				else
				{
					if(App.SysCtrlPara.AuxiliaryHeatSet==HEATER_OFF)
						App.SysCtrlPara.AuxiliaryHeatSet = HEATER_FULL;
					else
						App.SysCtrlPara.AuxiliaryHeatSet = HEATER_OFF;
				}
				PostMessage(MessageParaUpdate, PARA_HEATSET);
				System.Device.Beep.BeepOn(BEEP_LONG);
			}
 
			break;
		case IR_REMOTE_TIMERMODE:
			App.SysCtrlPara.ShutTimer++;
			if(App.SysCtrlPara.ShutTimer>9)
			{
				App.SysCtrlPara.ShutTimer = 0;
			}
			PostMessage(MessageParaUpdate, PARA_WORKMODE);			
			System.Device.Beep.BeepOn(BEEP_SHORT);		
			
			break;
		case IR_REMOTE_HEATER:
			App.SysCtrlPara.AuxiliaryHeatSet++;
			if(App.SysCtrlPara.AuxiliaryHeatSet>HEATER_FULL)
				App.SysCtrlPara.AuxiliaryHeatSet = HEATER_OFF;
			System.Device.Beep.BeepOn(BEEP_LONG);			
			PostMessage(MessageParaUpdate, PARA_HEATSET);
			break;
		case IR_REMOTE_CIRCLEMODE:
				App.SysCtrlPara.CircleModeSet++;
				if(App.SysCtrlPara.CircleModeSet>CIRCLEMODE_IN)
					App.SysCtrlPara.CircleModeSet = CIRCLEMODE_AUTO;
				System.Device.Beep.BeepOn(BEEP_LONG);
				PostMessage(MessageParaUpdate, PARA_CIRCLEMODE);
			break;
		default:
			break;
	}
}
