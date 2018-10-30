#ifndef __SYSDEFS_H
#define __SYSDEFS_H

#define __SENSOR_RH
#define __SENSOR_CO2
#define __SENSOR_PM25

#define MAIN_VERSION  3
#define SUB_VERSION		01



#define __SELF_ADJUSTMOTO
#define __WIFI_VALIDE

#define HD_GJ_180C   
//#define HD_GJ_360C  

#define HD_180C_CODE   132
#define HD_360C_CODE  69
typedef	enum
{
	HB_80 = 0x01,
	HG_150 = 0x02,
	HG_250 = 0x03,
	HG_350 = 0x04,
	HG_500 = 0x05,
	HG_800 = 0x06,
	
	HG_360C = 0x10,
	HG_180C = 0x11,
	HG_360Z= 0x20,
	HG_180Z= 0x21,
}MachineType;

#endif
