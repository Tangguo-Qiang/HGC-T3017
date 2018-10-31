#ifndef __LOGICCTRL_H
	#define __LOGICCTRL_H

/*	ushort DispMax;
	byte DispMin;
	byte Dispstep;
	
	ushort BypassAngle; greater than 180 for inverse set
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
	ushort PwmAct12_Moto2;*/

const DevDataType DevDataArray[]={
	/*HD_360C*/
  {360,80,20, 210,1,1,0, 370,980,840,7400,1500,1500, 360,350,560,560,700,840,7600,7500,600,900,1000,1200},
	/*HD_180C*/
	{180,60,10, 30,1,1,0, 440,960,720,7400,1500,1500, 370,350,480,600,720,840,7600,7500,600,900,1000,1200},
};


#ifdef HD_GJ_360C		/*2016.03.11, BypassInverse,300A-former*/

//	#define		DISPFLOW_MIN   		80
//	#define		DISPFLOW_MAX			360
//	#define		DISPFLOW_ONESTEP	20
//	#define		DISPFLOW_RANGE		(DISPFLOW_MAX-DISPFLOW_MIN)
//	#define		CTRLFLOW_STEPS	 (DISPFLOW_RANGE/DISPFLOW_ONESTEP)  //15
//	#define		CTRLFLOW_STEP	 		1
//	#define		CTRLFLOW_STOP	 		0
//	#define		CTRLFLOW_STEP_MUTE	 		(CTRLFLOW_STEPS/2)

////	#define __BYPASS_INVERSE
//	#define BYPASS_ANGLE						30
//	#define  __DOUBLE_MOTOS
//	#define  __EXCHANGE_FLOWS
////	#define __AUXI_HEATER

//	#define RPM_MOTO1_MIN							(uint16_t)370
//	#define RPM_MOTO1_OUT_ACT					(uint16_t)980		//1500
//	#define RPM_MOTO1_IN_ACT					(uint16_t)840		//1500
//	#define RPM_MOTO1_MAX							(RPM_MOTO1_OUT_ACT+RPM_MOTO1_MIN)
//	#define RPM_MOTO1_OUT_STEP				(uint16_t)(RPM_MOTO1_OUT_ACT/CTRLFLOW_STEPS)
//	#define RPM_MOTO1_IN_STEP					(uint16_t)(RPM_MOTO1_IN_ACT/CTRLFLOW_STEPS)

//	#define RPM_MOTO2_MIN								(uint16_t)360
//	#define RPM_MOTO2_ACT12							(uint16_t)840		//1350
//	#define RPM_MOTO2_ACT10							(uint16_t)700		//1350
//	#define RPM_MOTO2_ACT08							(uint16_t)560		//1350
//	#define RPM_MOTO2_ACT06							(uint16_t)560		//1350
//	#define RPM_MOTO2_STOP							(uint16_t)350
//	
//	#define RPM_MOTO1_TOP									(uint16_t)(RPM_MOTO1_MAX+50)
//	#define RPM_MOTO2_TOP									(uint16_t)(RPM_MOTO2_MAX+50)
//	#define RPM_MOTO1_BOTTOM							(uint16_t)(RPM_MOTO1_MIN-50)
//	#define RPM_MOTO2_BOTTOM							(uint16_t)(RPM_MOTO2_MIN-50)

//	
//	#define PWM_MOTO1_OUT_ACT				(uint16_t)1500    //100-70
//	#define PWM_MOTO1_IN_ACT				(uint16_t)1500    //100-70
//	#define PWM_MOTO1_MIN						(uint16_t)7400    //70%
//	#define PWM_MOTO1_MAX						(PWM_MOTO1_MIN+PWM_OUT_MOTO1_ACT)
//	#define PWM_MOTO1_OUT_STEP 			(PWM_MOTO1_OUT_ACT/CTRLFLOW_STEPS)    //70%
//	#define PWM_MOTO1_IN_STEP 			(PWM_MOTO1_IN_ACT/CTRLFLOW_STEPS)    //70%
	
//	#define PWM_MOTO2_MIN							(uint16_t)7600    //70%
//	#define PWM_MOTO2_STOP						(uint16_t)7500    //70%
//	#define PWM_MOTO2_ACT06						(uint16_t)600  //83-82
//	#define PWM_MOTO2_ACT08						(uint16_t)900  //85-82
//	#define PWM_MOTO2_ACT10						(uint16_t)1000  //87-82
//	#define PWM_MOTO2_ACT12						(uint16_t)1200  //89-78
//	#define PWM_MOTO2_MAX							(PWM_MOTO2_MIN+PWM_MOTO2_ACT12)

#endif


//#ifdef HD_GJ_180C		/*2016.03.11, BypassInverse,300A-former*/

//	#define		DISPFLOW_MIN   		60
//	#define		DISPFLOW_MAX			180
//	#define		DISPFLOW_ONESTEP	10
//	#define		DISPFLOW_RANGE		(DISPFLOW_MAX-DISPFLOW_MIN)
//	#define		CTRLFLOW_STEPS	 (DISPFLOW_RANGE/DISPFLOW_ONESTEP)  //12
//	#define		CTRLFLOW_STEP	 		1
//	#define		CTRLFLOW_STOP	 		0
//	#define		CTRLFLOW_STEP_MUTE	 		(CTRLFLOW_STEPS/2)

////	#define __BYPASS_INVERSE
//	#define BYPASS_ANGLE						30
//	#define  __DOUBLE_MOTOS
//	#define  __EXCHANGE_FLOWS
////	#define __AUXI_HEATER

//	#define RPM_MOTO1_MIN							(uint16_t)440
//	#define RPM_MOTO1_OUT_ACT					(uint16_t)960		//1450
//	#define RPM_MOTO1_IN_ACT					(uint16_t)720		//1010
//	#define RPM_MOTO1_MAX							(RPM_MOTO1_OUT_ACT+RPM_MOTO1_MIN)
//	#define RPM_MOTO1_OUT_STEP				(uint16_t)(RPM_MOTO1_OUT_ACT/CTRLFLOW_STEPS)
//	#define RPM_MOTO1_IN_STEP					(uint16_t)(RPM_MOTO1_IN_ACT/CTRLFLOW_STEPS)

//	#define RPM_MOTO2_MIN								(uint16_t)370
//	#define RPM_MOTO2_ACT12							(uint16_t)840		//1350
//	#define RPM_MOTO2_ACT10							(uint16_t)720		//1350
//	#define RPM_MOTO2_ACT08							(uint16_t)600		//1350
//	#define RPM_MOTO2_ACT06							(uint16_t)480		//1350
//	#define RPM_MOTO2_STOP							(uint16_t)350
//	
//	#define RPM_MOTO1_TOP									(uint16_t)(RPM_MOTO1_MAX+50)
//	#define RPM_MOTO2_TOP									(uint16_t)(RPM_MOTO2_MAX+50)
//	#define RPM_MOTO1_BOTTOM							(uint16_t)(RPM_MOTO1_MIN-50)
//	#define RPM_MOTO2_BOTTOM							(uint16_t)(RPM_MOTO2_MIN-50)

//	
//	#define PWM_MOTO1_OUT_ACT				(uint16_t)1500    //100-70
//	#define PWM_MOTO1_IN_ACT				(uint16_t)1500    //100-70
//	#define PWM_MOTO1_MIN						(uint16_t)7400    //70%
//	#define PWM_MOTO1_MAX						(PWM_MOTO1_MIN+PWM_OUT_MOTO1_ACT)
//	#define PWM_MOTO1_OUT_STEP 			(PWM_MOTO1_OUT_ACT/CTRLFLOW_STEPS)    //70%
//	#define PWM_MOTO1_IN_STEP 			(PWM_MOTO1_IN_ACT/CTRLFLOW_STEPS)    //70%
//	
//	#define PWM_MOTO2_MIN							(uint16_t)7600    //70%
//	#define PWM_MOTO2_STOP						(uint16_t)7500    //70%
//	#define PWM_MOTO2_ACT06						(uint16_t)600  //83-82
//	#define PWM_MOTO2_ACT08						(uint16_t)900  //85-82
//	#define PWM_MOTO2_ACT10						(uint16_t)1000  //87-82
//	#define PWM_MOTO2_ACT12						(uint16_t)1200  //89-78
//	#define PWM_MOTO2_MAX							(PWM_MOTO2_MIN+PWM_MOTO2_ACT12)

//#endif

#endif
