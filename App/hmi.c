#include "app.h"

#define TYPESET_DELAY_S 10

byte TypeSetState=0;
byte TypeSetDelay=0;
/*******************************************************************************
* 描述	    : 按键消息处理函数
* 输入参数  : key，任意按键值
*******************************************************************************/
void KeyProcessMainForm(KeyActEnum key)
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
		LCD_BL_ON;
			System.Device.Led.LedModeSet(LED_GREEN,TURN_OFF);
			System.Device.Led.LedModeSet(LED_RED,TURN_OFF);
			App.SysCtrlPara.Power = POWER_ON;
		}
		System.Device.Key.KeyLedSet(5);
		return;
	}

	if((App.SysCtrlPara.Power == POWER_OFF)&&(key!=KeyPower))
		return;
	
  if(App.SysCtrlPara.ChildLock==CHILD_LOCK)
	{
		System.Device.Led.LedModeSet(LED_GREEN,TEMP_TWINKLE);
		
		return;
	}
	
			
		switch(key)
    {
        case KeyPower:                
					if(App.SysCtrlPara.Power == POWER_OFF)
					{
						App.SysCtrlPara.Power = POWER_ON;
							System.Device.Beep.BeepOn(BEEP_POWERON);

						System.Device.Key.KeyLedSet(5);
					}
					else
					{
						App.SysCtrlPara.Power = POWER_OFF;
							System.Device.Beep.BeepOn(BEEP_POWEROFF);
						System.Device.Key.KeyLedSet(1);
					}
					PostMessage(MessageParaUpdate, PARA_POWER_SET);
            break;
        case KeyMode:
					System.Device.Key.KeyLedSet(5);
					System.Device.Beep.BeepOn(BEEP_LONG);
					App.SysCtrlPara.CircleModeSet++;
				if(App.SysCtrlPara.CircleModeSet>CIRCLEMODE_IN)
					App.SysCtrlPara.CircleModeSet = CIRCLEMODE_AUTO;
				PostMessage(MessageParaUpdate, PARA_CIRCLEMODE);
            break;
        case KeyHeater :
					System.Device.Key.KeyLedSet(5);
					System.Device.Beep.BeepOn(BEEP_LONG);
				if(pDevData->ExchangeFlows)
				{
					App.SysCtrlPara.VentilateRate++;
					if(App.SysCtrlPara.VentilateRate>RATE10TO12)
						App.SysCtrlPara.VentilateRate=RATE10TO08;
					PostMessage(MessageParaUpdate, PARA_VENTILATE);
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

            
            
        case KeyPlus:
					System.Device.Key.KeyLedSet(5);
            App.SysCtrlPara.AirFlowSet++;
						if(App.SysCtrlPara.AirFlowSet>CtrlStepMax)
							App.SysCtrlPara.AirFlowSet = CtrlStepMax;
						App.SysCtrlPara.AirFlowRun=App.SysCtrlPara.AirFlowSet;
//						PostMessage(MessageParaUpdate, PARA_XFMOTODUTY);
						SeqOperDelay =SEQUENCEOPER_DELAY_100MS;
            break;
        case KeyMinus:
					System.Device.Key.KeyLedSet(5);
             App.SysCtrlPara.AirFlowSet--;
						if(App.SysCtrlPara.AirFlowSet<CTRLFLOW_STEP_MIN)
							App.SysCtrlPara.AirFlowSet = CTRLFLOW_STEP_MIN;
						App.SysCtrlPara.AirFlowRun=App.SysCtrlPara.AirFlowSet;
//						PostMessage(MessageParaUpdate, PARA_XFMOTODUTY);
						SeqOperDelay =SEQUENCEOPER_DELAY_100MS;
            break;
				case KeyLongPlus:
					break;
				case KeyLongPlusMinus:
#ifdef __WIFI_VALIDE
						PostMessage(MessageWifiCtrl, HekrConfig);
				System.Device.Beep.BeepOn(BEEP_3SHORT);
				System.Device.Key.KeyLedSet(5);
#endif
					break;
				case KeyLongPower:	
					System.Device.Key.KeyLedSet(5);
					if(App.SysCtrlPara.Power == POWER_ON)
					{
							System.Device.Beep.BeepOn(BEEP_3SHORT);
							App.Menu.FaultForm.LoadFresh =TRUE;
							App.Menu.FocusFormPointer= &App.Menu.FaultForm;
					}
					break;
				default:
					break;
         
    }
}

void KeyProcessFaultForm(KeyActEnum key)
{
		switch(key)
		{
			case KeyMode:
			case KeyHeater:
			case KeyPlus:
			case KeyMinus:
			case KeyPower:
			case KeyLongMode:
			case KeyLongPlus:
			case KeyLongMinus:
							System.Device.Beep.BeepOn(BEEP_LONG);
							App.Menu.MainForm.LoadFresh = TRUE;
							App.Menu.FocusFormPointer= &App.Menu.MainForm;
				
				break;
			case KeyLongPower:
					App.SysCtrlPara.Power = POWER_OFF;
					System.Device.Beep.BeepOn(BEEP_POWEROFF);
					System.Device.Key.KeyLedSet(1);
					App.Menu.MainForm.LoadFresh =TRUE;
					App.Menu.FocusFormPointer= &App.Menu.MainForm;
					PostMessage(MessageParaUpdate, PARA_POWER_SET);
				break;
				default:
					break;
		}
	
}


void KeyProcessDevTypeForm(KeyActEnum key)
{
		switch(key)
		{
			case KeyMode:
			case KeyHeater:
				break;
			case KeyPlus:
				if(TypeSetState==2)
				{
					App.DevType++;
					if(App.DevType >200)
						App.DevType =1;
				}
				TypeSetDelay= TYPESET_DELAY_S;
				break;
			case KeyMinus:
				if(TypeSetState==2)
				{
					App.DevType--;
					if(App.DevType <1)
						App.DevType =2;
				}
				TypeSetDelay= TYPESET_DELAY_S;
				break;
			case KeyPower:
					App.SysCtrlPara.Power = POWER_ON;
					System.Device.Beep.BeepOn(BEEP_POWEROFF);
					System.Device.Key.KeyLedSet(1);
					PostMessage(MessageParaUpdate, PARA_POWER_SET);
					TypeSetState=0;
					TypeSetDelay= 0;
				break;
			case KeyLongMode:
			case KeyLongPlus:
				break;
			case KeyLongPlusMinus:			
				TypeSetState++;
			  if(TypeSetState==2)
				{
					System.Device.Led.LedModeSet(LED_RED,TURN_OFF);
					System.Device.Led.LedModeSet(LED_GREEN,LED_TWINKLE);
				}
				else
				{
					if((App.DevType==HD_360C_CODE)||(App.DevType==HD_180C_CODE))
						DevParaOpt(WRITETOSTORE);
					App.SysCtrlPara.Power = POWER_OFF;
					System.Device.Led.LedModeSet(LED_RED,TURN_ON);
					System.Device.Led.LedModeSet(LED_GREEN,TURN_OFF);
					System.Device.Led.LedModeSet(LED_RED,TEMP_TWINKLE);
					
					TypeSetState=0;
					TypeSetDelay= 0;
					LCD_BL_OFF;
				}
				
				TypeSetDelay= TYPESET_DELAY_S;
				break;
			case KeyLongPowerPlus:
				System.Device.Led.LedModeSet(LED_RED,TURN_OFF);
				System.Device.Led.LedModeSet(LED_GREEN,TURN_OFF);
				App.Menu.DevTypeForm.LoadFresh =TRUE;
				LCD_BL_ON;
				TypeSetState = 1;
			
				TypeSetDelay= TYPESET_DELAY_S;
				break;
			case KeyLongPower:
					App.SysCtrlPara.Power = POWER_ON;
					System.Device.Beep.BeepOn(BEEP_POWEROFF);
					System.Device.Key.KeyLedSet(1);
					PostMessage(MessageParaUpdate, PARA_POWER_SET);
					TypeSetState=0;
					TypeSetDelay= 0;
				break;
				default:
					TypeSetState=0;
					TypeSetDelay= 0;
					LCD_BL_OFF;
					break;
		}
	
}
