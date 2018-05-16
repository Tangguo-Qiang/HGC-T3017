/*

********************************************************************************
*文件名     : menu.c
*作用       : 界面设计
*原理       : 例子程序中包含五个窗体Form，每一个窗体可以加载BackText背景文字、
*           : Chart表、Label标签、TextBox文本四类控件，采用Add方法加载之后，
*           : 需要初始化值。
********************************************************************************
*版本     作者            日期            说明
*V0.1    Wangsw        2013/07/21       初始版本
********************************************************************************
*/

#include "system.h"
#include "app.h"
#include "menu.h"
#include "hmi.h"


static DispObjType DispCircleMode;
static DispObjType DispVentiRate;
static DispObjType DispFlowVol;
static DispObjType DispWheel;
static DispObjType DispLeafs;
static DispObjType DispTimer;
static DispObjType DispAuxiHeater;
static DispObjType DispTempBla;
static DispObjType DispLock;
static DispObjType DispFault;
static DispObjType DispFilter;
static DispObjType DispWIFI;
static DispObjType DispRF;
static DispObjType DispCO2;
static DispObjType DispPM25;
static DispObjType DispTempOut;
static DispObjType DispTempIn;
static DispObjType DispRHIn;
static DispObjType DispSFrame;
static DispObjType DispFaultCode;
static DispObjType DispCtrlVersion;
static DispObjType DispPowerVersion;

//DispObjType *pMairFormObj[]={&DispCircleMode,&DispVentiRate,&DispFlowVol,&DispWheel,&DispLeafs,
//&DispTimer,&DispAuxiHeater,&DispTempBla,&DispLock,&DispFault,&DispFilter,&DispWIFI,&DispRF,
//&DispCO2,&DispPM25,&DispTempOut,&DispTempIn,&DispSFrame};
static SensorDataTypedef DispSensorData;
static SysCtrlParaTypedef DispSysCtrlPara;
static SysStateTypedef DispSysState;

void InitMenu(void)
{
	App.Menu.MainForm.DispObjPointer= null;
	App.Menu.MainForm.ScreenClean = 1;
	App.Menu.MainForm.KeyProcess= KeyProcessMainForm;

	System.Gui.AddDispObj(&App.Menu.MainForm,&DispCircleMode);
	DispCircleMode.ObjNum = FigObj_CircleMode;
	DispCircleMode.Disp = NormalDisp;
	DispCircleMode.DataPointer = (void*)&App.SysCtrlPara.CircleModeSet;
	
	System.Gui.AddDispObj(&App.Menu.MainForm,&DispVentiRate);
	DispVentiRate.ObjNum = FigObj_VentiRate;
	DispVentiRate.Disp = NormalDisp;
	DispVentiRate.DataPointer = (void*)&App.SysCtrlPara.VentilateRate;
	
	System.Gui.AddDispObj(&App.Menu.MainForm,&DispFlowVol);
	DispFlowVol.ObjNum = FigObj_FlowVol;
	DispFlowVol.Disp = NormalDisp;
	DispFlowVol.DataPointer = (void*)&App.SysCtrlPara.AirFlowRun;
	
	System.Gui.AddDispObj(&App.Menu.MainForm,&DispWheel);
	DispWheel.ObjNum = FigObj_Wheel;
	DispWheel.Disp = NormalDisp;
//	DispWheel.DataPointer = (void*)&App.SysCtrlPara.AirFlowSet;
	
	System.Gui.AddDispObj(&App.Menu.MainForm,&DispLeafs);
	DispLeafs.ObjNum = FigObj_Leafs;
	DispLeafs.Disp = NormalDisp;
//	DispLeafs.DataPointer = (void*)&App.SysCtrlPara.AirFlowSet;
	
	System.Gui.AddDispObj(&App.Menu.MainForm,&DispTimer);
	DispTimer.ObjNum = FigObj_Timer;
	DispTimer.Disp = NormalDisp;
	DispTimer.DataPointer = (void*)&App.SysCtrlPara.ShutTimer;
	
	System.Gui.AddDispObj(&App.Menu.MainForm,&DispAuxiHeater);
	DispAuxiHeater.ObjNum = FigObj_AuxiHeater;
	DispAuxiHeater.Disp = NormalDisp;
	DispAuxiHeater.DataPointer = (void*)&App.SysCtrlPara.AuxiliaryHeatSet;
	
	System.Gui.AddDispObj(&App.Menu.MainForm,&DispTempBla);
	DispTempBla.ObjNum = FigObj_TempBla;
	DispTempBla.Disp = NormalDisp;
	DispTempBla.DataPointer = (void*)&App.SysCtrlPara.ThermalModeSet;
	
	System.Gui.AddDispObj(&App.Menu.MainForm,&DispLock);
	DispLock.ObjNum = FigObj_Lock;
	DispLock.Disp = NormalDisp;
	DispLock.DataPointer = (void*)&App.SysCtrlPara.ChildLock;
	
	System.Gui.AddDispObj(&App.Menu.MainForm,&DispFault);
	DispFault.ObjNum = FigObj_Fault;
	DispFault.Disp = NormalDisp;
	DispFault.DataPointer = (void*)&App.SysState.FaultFlag;
	
	System.Gui.AddDispObj(&App.Menu.MainForm,&DispFilter);
	DispFilter.ObjNum = FigObj_Filter;
	DispFilter.Disp = NormalDisp;
	DispFilter.DataPointer = (void*)&App.SysState.FilterWarning;
	
	System.Gui.AddDispObj(&App.Menu.MainForm,&DispWIFI);
	DispWIFI.ObjNum = FigObj_WIFI;
	DispWIFI.Disp = NormalDisp;
	DispWIFI.DataPointer = (void*)&App.SysState.WifiState;
	
	System.Gui.AddDispObj(&App.Menu.MainForm,&DispRF);
	DispRF.ObjNum = FigObj_RF;
	DispRF.Disp = NormalDisp;
	DispRF.DataPointer = (void*)&App.SysState.RFState;
	
	System.Gui.AddDispObj(&App.Menu.MainForm,&DispCO2);
	DispCO2.ObjNum = FigObj_CO2;
	DispCO2.Disp = NormalDisp;
	DispCO2.DataPointer = (void*)&App.SensorData.CO2Inside;
	
	System.Gui.AddDispObj(&App.Menu.MainForm,&DispPM25);
	DispPM25.ObjNum = FigObj_PM25;
	DispPM25.Disp = NormalDisp;
	DispPM25.DataPointer = (void*)&App.SensorData.PMInside;
	
	System.Gui.AddDispObj(&App.Menu.MainForm,&DispTempOut);
	DispTempOut.ObjNum = FigObj_TempOut;
	DispTempOut.Disp = NormalDisp;
	DispTempOut.DataPointer = (void*)&App.SensorData.TempOutside;
	
	System.Gui.AddDispObj(&App.Menu.MainForm,&DispTempIn);
	DispTempIn.ObjNum = FigObj_TempIn;
	DispTempIn.Disp = NormalDisp;
	DispTempIn.DataPointer = (void*)&App.SensorData.TempInside;
	
	System.Gui.AddDispObj(&App.Menu.MainForm,&DispRHIn);
	DispRHIn.ObjNum = FigObj_RHIn;
	DispRHIn.Disp = NormalDisp;
	DispRHIn.DataPointer = (void*)&App.SensorData.RHInside;
	
	System.Gui.AddDispObj(&App.Menu.MainForm,&DispSFrame);
	DispSFrame.ObjNum = FigObj_SFrame;
	DispSFrame.Disp = NormalDisp;
	DispSFrame.DataPointer = (void*)&App.SysCtrlPara.Power;
	
	App.Menu.FaultForm.DispObjPointer= null;
	App.Menu.FaultForm.KeyProcess=KeyProcessFaultForm;
	App.Menu.FaultForm.ScreenClean = 1;
	
	System.Gui.AddDispObj(&App.Menu.FaultForm,&DispFaultCode);
	DispFaultCode.ObjNum = FigObj_FaultCode;
	DispFaultCode.Disp = NormalDisp;
	DispFaultCode.DataPointer = (void*)&App.SysState.FaultFlag;
	
	System.Gui.AddDispObj(&App.Menu.FaultForm,&DispCtrlVersion);
	DispCtrlVersion.ObjNum = FigObj_CtrlVersionCode;
	DispCtrlVersion.Disp = NormalDisp;
	DispCtrlVersion.DataPointer = (void*)&App.SysVersion.CtrlVersion;
	
	System.Gui.AddDispObj(&App.Menu.FaultForm,&DispPowerVersion);
	DispPowerVersion.ObjNum = FigObj_PowerVersionCode;
	DispPowerVersion.Disp = NormalDisp;
	DispPowerVersion.DataPointer = (void*)&App.SysVersion.PowerVersion;
	
	
	

//	FormDispPoint=&(App.Menu);
//	SysStatusPoint =&(App.SysState);
//	SensorDataPoint =&(App.SensorData);
//	SysCtrlParaPoint =&(App.SysCtrlPara);
}

static void RefreshMenu(void)
{
	if(App.Menu.FocusFormPointer->LoadFresh)
	{
		System.Gui.LoadForm(App.Menu.FocusFormPointer);
	}
		
	if(DispSensorData.CO2Inside != App.SensorData.CO2Inside)
	{
		DispSensorData.CO2Inside = App.SensorData.CO2Inside;
		DispCO2.UpdataFlag = TRUE;
	}
	if(DispSensorData.PMInside != App.SensorData.PMInside)
	{
		DispSensorData.PMInside = App.SensorData.PMInside;
		DispPM25.UpdataFlag = TRUE;
	}
	if(DispSensorData.TempInside != App.SensorData.TempInside)
	{
		DispSensorData.TempInside = App.SensorData.TempInside;
		DispTempIn.UpdataFlag = TRUE;
		DispSensorData.RHInside = App.SensorData.RHInside;
		DispRHIn.UpdataFlag = TRUE;
	}
	if(DispSensorData.TempOutside != App.SensorData.TempOutside)
	{
		DispSensorData.TempOutside = App.SensorData.TempOutside;
		DispTempOut.UpdataFlag = TRUE;
	}

	if(DispSysCtrlPara.AirFlowRun != App.SysCtrlPara.AirFlowRun)
	{
		DispSysCtrlPara.AirFlowRun = App.SysCtrlPara.AirFlowRun;
		DispFlowVol.UpdataFlag = TRUE;
	}
	if(DispSysCtrlPara.CircleModeSet != App.SysCtrlPara.CircleModeSet)
	{
		DispSysCtrlPara.CircleModeSet = App.SysCtrlPara.CircleModeSet;
		DispCircleMode.UpdataFlag = TRUE;
	}
	if(DispSysCtrlPara.VentilateRate != App.SysCtrlPara.VentilateRate)
	{
		DispSysCtrlPara.VentilateRate = App.SysCtrlPara.VentilateRate;
		DispVentiRate.UpdataFlag = TRUE;
	}
	if(DispSysCtrlPara.AuxiliaryHeatSet != App.SysCtrlPara.AuxiliaryHeatSet)
	{
		DispSysCtrlPara.AuxiliaryHeatSet = App.SysCtrlPara.AuxiliaryHeatSet;
		DispAuxiHeater.UpdataFlag = TRUE;
	}
	if(DispSysCtrlPara.ThermalModeSet != App.SysCtrlPara.ThermalModeSet)
	{
		DispSysCtrlPara.ThermalModeSet = App.SysCtrlPara.ThermalModeSet;
		DispTempBla.UpdataFlag = TRUE;
	}
	if(DispSysCtrlPara.ShutTimer != App.SysCtrlPara.ShutTimer)
	{
		DispSysCtrlPara.ShutTimer = App.SysCtrlPara.ShutTimer;
		DispTimer.UpdataFlag = TRUE;
	}
	if(DispSysCtrlPara.ChildLock != App.SysCtrlPara.ChildLock)
	{
		DispSysCtrlPara.ChildLock = App.SysCtrlPara.ChildLock;
		DispLock.UpdataFlag = TRUE;
	}
	if(DispSysState.FilterWarning != App.SysState.FilterWarning)
	{
		DispSysState.FilterWarning = App.SysState.FilterWarning;
		DispFilter.UpdataFlag = TRUE;
	}
	if(DispSysState.WifiState != App.SysState.WifiState)
	{
		DispSysState.WifiState = App.SysState.WifiState;
		DispWIFI.UpdataFlag = TRUE;
	}
	if(DispSysState.RFState != App.SysState.RFState)
	{
		DispSysState.RFState = App.SysState.RFState;
		DispRF.UpdataFlag = TRUE;
	}
	if(DispSysState.FaultFlag != App.SysState.FaultFlag)
	{
		DispSysState.FaultFlag = App.SysState.FaultFlag;
		DispFault.UpdataFlag = TRUE;
	}
}

void MenuTask(void)
{
	RefreshMenu();
	System.Gui.ParseForm(App.Menu.FocusFormPointer);
}


