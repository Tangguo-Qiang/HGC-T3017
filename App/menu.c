/*

********************************************************************************
*�ļ���     : menu.c
*����       : �������
*ԭ��       : ���ӳ����а����������Form��ÿһ��������Լ���BackText�������֡�
*           : Chart��Label��ǩ��TextBox�ı�����ؼ�������Add��������֮��
*           : ��Ҫ��ʼ��ֵ��
********************************************************************************
*�汾     ����            ����            ˵��
*V0.1    Wangsw        2013/07/21       ��ʼ�汾
********************************************************************************
*/

#include "system.h"
#include "app.h"
#include "menu.h"
#include "hmi.h"

void InitMenu(void)
{
  App.Menu.AnionGifSpeed100ms=6;
	App.Menu.FigFlashSpeed100ms=5;
//	App.Menu.TempRHStay100ms=20;
//	App.Menu.WheelGifSpeed10ms=0;
	
	System.Gui.InitDispSensorData((SensorDataTypedef*)&(App.SensorData));
	System.Gui.InitDispSysCtrlPara((SysCtrlParaTypedef*)&(App.SysCtrlPara));
	System.Gui.InitDispSysStatus((SysStateTypedef*)&(App.SysState));
	System.Gui.LoadForm((FormDispTypeDef*)&(App.Menu));

//	FormDispPoint=&(App.Menu);
//	SysStatusPoint =&(App.SysState);
//	SensorDataPoint =&(App.SensorData);
//	SysCtrlParaPoint =&(App.SysCtrlPara);
}

void MenuTask(void)
{
	System.Gui.ParseForm();
}


