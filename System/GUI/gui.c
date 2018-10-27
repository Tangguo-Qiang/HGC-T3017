#include "system.h"

#define		FLASHSPEED_100MS	((byte)5)
#define 	LEAFSGIF_100MS		((byte)10)

const LCD_DispTypeDef FigInSys[NUM_Full]={
{0,0x01},{0,0x02},{0,0x04},{0,0x08},{0,0x10},{0,0x20},{0,0x40},{0,0x80},
{1,0x01},{1,0x02},{1,0x04},{1,0x08},{1,0x10},{1,0x20},{1,0x40},{1,0x80},
{2,0x01},{2,0x02},{2,0x04},{2,0x08},{2,0x10},{2,0x20},{2,0x40},{2,0x80},
{3,0x01},{3,0x02},{3,0x04},{3,0x08},{3,0x10},{3,0x20},{3,0x40},{3,0x80},
{4,0x01},{4,0x02},{4,0x04},{4,0x08},{4,0x10},{4,0x20},{4,0x40},{4,0x80},
{5,0x01},{5,0x02},{5,0x04},{5,0x08},{5,0x10},{5,0x20},{5,0x40},{5,0x80},
{6,0x01},{6,0x02},{6,0x04},{6,0x08},{6,0x10},{6,0x20},{6,0x40},{6,0x80},
{7,0x01},{7,0x02},{7,0x04},{7,0x08},{7,0x10},{7,0x20},{7,0x40},{7,0x80},
{8,0x01},{8,0x02},{8,0x04},{8,0x08},{8,0x10},{8,0x20},{8,0x40},{8,0x80},
{9,0x01},{9,0x02},{9,0x04},{9,0x08},{9,0x10},{9,0x20},{9,0x40},{9,0x80},
{10,0x01},{10,0x02},{10,0x04},{10,0x08},{10,0x10},{10,0x20},{10,0x40},{10,0x80},
{11,0x01},{11,0x02},{11,0x04},{11,0x08},{11,0x10},{11,0x20},{11,0x40},{11,0x80},
{12,0x01},{12,0x02},{12,0x04},{12,0x08},{12,0x10},{12,0x20},{12,0x40},{12,0x80},
{13,0x01},{13,0x02},{13,0x04},{13,0x08},{13,0x10},{13,0x20},{13,0x40},{13,0x80},
{14,0x01},{14,0x02},{14,0x04},{14,0x08},{14,0x10},{14,0x20},{14,0x40},{14,0x80},
{15,0x01},{15,0x02},{15,0x04},{15,0x08},{15,0x10},{15,0x20},{15,0x40},{15,0x80},
{16,0x01},{16,0x02},{16,0x04},{16,0x08},{16,0x10},{16,0x20},{16,0x40},{16,0x80},
{17,0x01},{17,0x02},{17,0x04},{17,0x08},{17,0x10},{17,0x20},{17,0x40},{17,0x80},
{18,0x01},{18,0x02},{18,0x04},{18,0x08},{18,0x10},{18,0x20},{18,0x40},{18,0x80},
{19,0x01},{19,0x02},{19,0x04},{19,0x08},{19,0x10},{19,0x20},{19,0x40},{19,0x80},
};

/* bit7-0 G F E D C B A  */
const byte NumLed[12]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x00,0x79};
										/*  0,   1,   2,    3,   4,   5,   6,   7,   8,   9, none,  E,*/	
byte GuiTimer100ms=0;
byte GuiTimer10ms=0;

static byte 		GifLeafs100ms=0;
static byte 		FigFlash=0;
static byte 		FaultFlag=0;
static byte 		GifLeafNum=0;


static void DigitToDisp(byte val,byte LocNumD)
{
	byte num;
	
//	System.Device.Lcd.NonDispUnit(FigInSys[LocNumD]); //D
//	System.Device.Lcd.NonDispUnit(FigInSys[LocNumD+1]); //C
//	System.Device.Lcd.NonDispUnit(FigInSys[LocNumD+2]); //B
//	System.Device.Lcd.NonDispUnit(FigInSys[LocNumD+3]); //A
//	System.Device.Lcd.NonDispUnit(FigInSys[LocNumD+5]); //E
//	System.Device.Lcd.NonDispUnit(FigInSys[LocNumD+6]); //G
//	System.Device.Lcd.NonDispUnit(FigInSys[LocNumD+7]); //F
	
	if(val<12)
	{
		num = NumLed[val];
		if(num&0x01) //A
			System.Device.Lcd.DispUnit(FigInSys[LocNumD+3]);
		else
			System.Device.Lcd.NonDispUnit(FigInSys[LocNumD+3]);
			
		if(num&0x02) //B
			System.Device.Lcd.DispUnit(FigInSys[LocNumD+2]);
		else
			System.Device.Lcd.NonDispUnit(FigInSys[LocNumD+2]);
			
		if(num&0x04) //C
			System.Device.Lcd.DispUnit(FigInSys[LocNumD+1]);
		else
			System.Device.Lcd.NonDispUnit(FigInSys[LocNumD+1]);
			
		if(num&0x08) //D
			System.Device.Lcd.DispUnit(FigInSys[LocNumD]);
		else
			System.Device.Lcd.NonDispUnit(FigInSys[LocNumD]);
			
		if(num&0x10) //E
			System.Device.Lcd.DispUnit(FigInSys[LocNumD+5]);
		else
			System.Device.Lcd.NonDispUnit(FigInSys[LocNumD+5]);
			
		if(num&0x20) //F
			System.Device.Lcd.DispUnit(FigInSys[LocNumD+7]);
		else
			System.Device.Lcd.NonDispUnit(FigInSys[LocNumD+7]);
			
		if(num&0x40) //G
			System.Device.Lcd.DispUnit(FigInSys[LocNumD+6]);
		else
			System.Device.Lcd.NonDispUnit(FigInSys[LocNumD+6]);
			
	}
}

static void DigitToDispRev(byte val,byte LocNumD)
{
	byte num;
	
//	System.Device.Lcd.NonDispUnit(FigInSys[LocNumD]); //D
//	System.Device.Lcd.NonDispUnit(FigInSys[LocNumD-1]); //C
//	System.Device.Lcd.NonDispUnit(FigInSys[LocNumD-2]); //B
//	System.Device.Lcd.NonDispUnit(FigInSys[LocNumD-3]); //A
//	System.Device.Lcd.NonDispUnit(FigInSys[LocNumD-5]); //E
//	System.Device.Lcd.NonDispUnit(FigInSys[LocNumD-6]); //G
//	System.Device.Lcd.NonDispUnit(FigInSys[LocNumD-7]); //F
	
	if(val<12)
	{
		num = NumLed[val];
		if(num&0x01) //A
			System.Device.Lcd.DispUnit(FigInSys[LocNumD-3]);
		else
			System.Device.Lcd.NonDispUnit(FigInSys[LocNumD-3]);
		if(num&0x02) //B
			System.Device.Lcd.DispUnit(FigInSys[LocNumD-2]);
		else
			System.Device.Lcd.NonDispUnit(FigInSys[LocNumD-2]);
		if(num&0x04) //C
			System.Device.Lcd.DispUnit(FigInSys[LocNumD-1]);
		else
			System.Device.Lcd.NonDispUnit(FigInSys[LocNumD-1]);
		if(num&0x08) //D
			System.Device.Lcd.DispUnit(FigInSys[LocNumD]);
		else
			System.Device.Lcd.NonDispUnit(FigInSys[LocNumD]);
		if(num&0x10) //E
			System.Device.Lcd.DispUnit(FigInSys[LocNumD-5]);
		else
			System.Device.Lcd.NonDispUnit(FigInSys[LocNumD-5]);
		if(num&0x20) //F
			System.Device.Lcd.DispUnit(FigInSys[LocNumD-7]);
		else
			System.Device.Lcd.NonDispUnit(FigInSys[LocNumD-7]);
		if(num&0x40) //G
			System.Device.Lcd.DispUnit(FigInSys[LocNumD-6]);
		else
			System.Device.Lcd.NonDispUnit(FigInSys[LocNumD-6]);
	}
	else if(val>11)
	{		
			System.Device.Lcd.NonDispUnit(FigInSys[LocNumD]); //D
			System.Device.Lcd.NonDispUnit(FigInSys[LocNumD-1]); //C
			System.Device.Lcd.NonDispUnit(FigInSys[LocNumD-2]); //B
			System.Device.Lcd.NonDispUnit(FigInSys[LocNumD-3]); //A
			System.Device.Lcd.NonDispUnit(FigInSys[LocNumD-5]); //E
			System.Device.Lcd.NonDispUnit(FigInSys[LocNumD-7]); //F
			System.Device.Lcd.DispUnit(FigInSys[LocNumD-6]); //G
	}

}

static void AddDispObj(FormTypeDef * formPointer, DispObjType *objPointer)
{
	DispObjType *pointer;
	
	objPointer->ObjNum = FigObj_Null;        
	objPointer->Disp = NormalDisp;
	objPointer->UpdataFlag = TRUE;
	if (formPointer->DispObjPointer == null)
	{
			 formPointer->DispObjPointer = objPointer;
			 return;
	}
	pointer = formPointer->DispObjPointer;
	while (pointer->NextObjPointer != null)
			pointer = pointer->NextObjPointer;

	pointer->NextObjPointer = objPointer;	
	
}

static void ParseForm(FormTypeDef * formPointer)
{
	byte num=0,flag=0;
	ushort val;
	uint lval;
	signed char snum;
	DispObjType *objPointer= null;
	
	if(GuiTimer100ms)
	{
		GuiTimer100ms=0;
		GifLeafs100ms++;
		FigFlash++;
	
		if(FigFlash>(FLASHSPEED_100MS*2))
			FigFlash = 0;
	}
    
	objPointer = formPointer->DispObjPointer;
	while(objPointer != null)
	{
		if(objPointer->UpdataFlag!=TRUE)
		{
			objPointer = objPointer->NextObjPointer;
			continue;
		}
		objPointer->UpdataFlag =FALSE;
		switch(objPointer->ObjNum)
		{
			case FigObj_CircleMode:
				num = (*(byte*)objPointer->DataPointer);		
				switch(num)
				{
					case CIRCLEMODE_AUTO:
						System.Device.Lcd.DispUnit(FigInSys[LCD_T19]);
						System.Device.Lcd.NonDispUnit(FigInSys[LCD_T20]);
						System.Device.Lcd.NonDispUnit(FigInSys[LCD_T21]);	
						break;
					case CIRCLEMODE_OUT:
						System.Device.Lcd.DispUnit(FigInSys[LCD_T21]);
						System.Device.Lcd.NonDispUnit(FigInSys[LCD_T19]);
						System.Device.Lcd.NonDispUnit(FigInSys[LCD_T20]);
						break;
					case CIRCLEMODE_IN:
						System.Device.Lcd.DispUnit(FigInSys[LCD_T20]);
						System.Device.Lcd.NonDispUnit(FigInSys[LCD_T19]);
						System.Device.Lcd.NonDispUnit(FigInSys[LCD_T21]);	
						break;
					default:
						break;
				}				
				break;
			case FigObj_VentiRate:
				num = (*(byte*)objPointer->DataPointer);
				switch(num)
				{
					case RATE10TO08:
						System.Device.Lcd.DispUnit(FigInSys[LCD_T16]);
						System.Device.Lcd.NonDispUnit(FigInSys[LCD_T17]);
						System.Device.Lcd.NonDispUnit(FigInSys[LCD_T18]);	
						break;
					case RATE10TO10:
						System.Device.Lcd.DispUnit(FigInSys[LCD_T17]);
						System.Device.Lcd.NonDispUnit(FigInSys[LCD_T16]);
						System.Device.Lcd.NonDispUnit(FigInSys[LCD_T18]);	
						break;
					case RATE10TO12:
						System.Device.Lcd.DispUnit(FigInSys[LCD_T18]);
						System.Device.Lcd.NonDispUnit(FigInSys[LCD_T16]);
						System.Device.Lcd.NonDispUnit(FigInSys[LCD_T17]);
						break;
					default:
						break;
				}				
				break;
			case FigObj_FlowVol:
				val = (*(ushort*)objPointer->DataPointer);		
				
				num = val/100;
				val %= 100;
				if(!num)
					num=10;		
				DigitToDispRev(num,LCD_8D);
				num = val/10;
				DigitToDispRev(num,LCD_9D);
				num= val%10;
				DigitToDispRev(num,LCD_10D); 
				
				System.Device.Lcd.DispUnit(FigInSys[LCD_T5]);

				break;
			case FigObj_Wheel:
				System.Device.Lcd.DispUnit(FigInSys[LCD_T6]);
				System.Device.Lcd.DispUnit(FigInSys[LCD_T7]);
				System.Device.Lcd.DispUnit(FigInSys[LCD_T9]);
				break;
			case FigObj_Leafs:
				if(GifLeafs100ms==LEAFSGIF_100MS)
				{
					GifLeafs100ms =0;
					switch(GifLeafNum)
					{
						case 0:
							System.Device.Lcd.DispUnit(FigInSys[LCD_S1]);
							System.Device.Lcd.NonDispUnit(FigInSys[LCD_S2]);
							System.Device.Lcd.NonDispUnit(FigInSys[LCD_S3]);
							break;
						case 1:
							System.Device.Lcd.DispUnit(FigInSys[LCD_S2]);
							System.Device.Lcd.NonDispUnit(FigInSys[LCD_S1]);
							System.Device.Lcd.NonDispUnit(FigInSys[LCD_S3]);
							break;
						case 2:
							System.Device.Lcd.DispUnit(FigInSys[LCD_S3]);
							System.Device.Lcd.NonDispUnit(FigInSys[LCD_S2]);
							System.Device.Lcd.NonDispUnit(FigInSys[LCD_S1]);
							break;
					}
					if(++GifLeafNum>2)
						GifLeafNum=0;
				}
				objPointer->UpdataFlag =TRUE;
				break;
			case FigObj_Timer:
				num = (*(byte*)objPointer->DataPointer);		
				if(!num)
					num = 0xff;
				DigitToDispRev(num,LCD_17D);
					
				System.Device.Lcd.DispUnit(FigInSys[LCD_T22]);
				System.Device.Lcd.DispUnit(FigInSys[LCD_T23]);
				break;
			case FigObj_AuxiHeater:
				num = (*(byte*)objPointer->DataPointer);		
				if(num == (byte)HEATER_HALF)
				{
					if(FigFlash==(FLASHSPEED_100MS))
					{
						System.Device.Lcd.NonDispUnit(FigInSys[LCD_T28]);
					}
					else if(!FigFlash)
						System.Device.Lcd.DispUnit(FigInSys[LCD_T28]);
					objPointer->UpdataFlag = TRUE;
				}					
				else if(num==HEATER_FULL)
					System.Device.Lcd.DispUnit(FigInSys[LCD_T28]);
				else
					System.Device.Lcd.NonDispUnit(FigInSys[LCD_T28]);				
				
			break;
			case FigObj_TempBla:
				num = (*(byte*)objPointer->DataPointer);	
				if(num==TEMPMODE_AUTO)
				{
					if(FigFlash==(FLASHSPEED_100MS))
						System.Device.Lcd.NonDispUnit(FigInSys[LCD_T30]);
					else if(!FigFlash)
						System.Device.Lcd.DispUnit(FigInSys[LCD_T30]);
					objPointer->UpdataFlag =TRUE;
				}						
				else if(num==(byte)TEMPMODE_ON)
					System.Device.Lcd.DispUnit(FigInSys[LCD_T30]);
				else  // TEMPMODE_OFF:
					System.Device.Lcd.NonDispUnit(FigInSys[LCD_T30]);
				break;
			case FigObj_Lock:
				num = (*(byte*)objPointer->DataPointer);		
				if(num==(byte)CHILD_UNLOCK)
					System.Device.Lcd.NonDispUnit(FigInSys[LCD_T27]);							
				else
					System.Device.Lcd.DispUnit(FigInSys[LCD_T27]);
				break;
			case FigObj_Fault:
				lval= (*(uint*)objPointer->DataPointer);
			  if(lval&0xFFF0)
					System.Device.Lcd.DispUnit(FigInSys[LCD_T24]);

				break;
			case FigObj_Filter:
				lval= (*(uint*)objPointer->DataPointer);
			if(lval&0x0F)
				System.Device.Lcd.DispUnit(FigInSys[LCD_T29]);
			else
				System.Device.Lcd.NonDispUnit(FigInSys[LCD_T29]);
			
			if(lval&FIRSTFILTER_CHECK)
				System.Device.Lcd.DispUnit(FigInSys[LCD_W1]);
			else
				System.Device.Lcd.NonDispUnit(FigInSys[LCD_W1]);				
			if(lval&MIDFILTER_CHECK)
				System.Device.Lcd.DispUnit(FigInSys[LCD_W2]);
			else
				System.Device.Lcd.NonDispUnit(FigInSys[LCD_W2]);
			if(lval&ESPFILTER_CHECK)
				System.Device.Lcd.DispUnit(FigInSys[LCD_W3]);
			else
				System.Device.Lcd.NonDispUnit(FigInSys[LCD_W3]);
			if(lval&HPFILTER_CHECK)
				System.Device.Lcd.DispUnit(FigInSys[LCD_W4]);
			else
				System.Device.Lcd.NonDispUnit(FigInSys[LCD_W4]);
			
				break;
			case FigObj_WIFI:
				lval= (*(uint*)objPointer->DataPointer);
				if(lval & (WIFI_STATE_STA))
				{
					System.Device.Lcd.DispUnit(FigInSys[LCD_T26]);	
				}
				else if(lval & WIFI_STATE_CONFIG)
				{
						if(FigFlash==FLASHSPEED_100MS)
						{
							System.Device.Lcd.NonDispUnit(FigInSys[LCD_T26]);
						}
						else if(!FigFlash)
							System.Device.Lcd.DispUnit(FigInSys[LCD_T26]);	
						objPointer->UpdataFlag =TRUE;
				}
				else
					System.Device.Lcd.NonDispUnit(FigInSys[LCD_T26]);
					
				break;
			case FigObj_RF:
				break;
			case FigObj_CO2:
				val = (*(ushort*)objPointer->DataPointer);	
				num = val/1000;
				val %= 1000;
				if(!num)
					num=10;
				else
					flag =1;			
				DigitToDispRev(num,LCD_4D);
				
				num = val/100;
				val %= 100;
				if((!num)&&(!flag))
					num=10;		
				DigitToDispRev(num,LCD_5D);
				num = val/10;
				val %= 10;
				DigitToDispRev(num,LCD_6D);
				DigitToDispRev(val,LCD_7D); 
				
				System.Device.Lcd.DispUnit(FigInSys[LCD_T2]);
				System.Device.Lcd.DispUnit(FigInSys[LCD_T4]);					
				break;
			case FigObj_PM25:
				val = (*(ushort*)objPointer->DataPointer);	
				num = val/100;
				val %= 100;
				if(!num)
					num=10;
				else
					flag =1;			
				DigitToDispRev(num,LCD_1D);
				num = val/10;
				val %= 10;
				if((!num)&&(!flag))
					num=10;		
				DigitToDispRev(num,LCD_2D);
				DigitToDispRev(val,LCD_3D); 
				
				System.Device.Lcd.DispUnit(FigInSys[LCD_T1]);
				System.Device.Lcd.DispUnit(FigInSys[LCD_T3]);
				
				break;
			case FigObj_TempOut:
				snum = (*(signed char*)objPointer->DataPointer);		
				if(snum<0)
				{
					System.Device.Lcd.DispUnit(FigInSys[LCD_T13]);
					snum *= -1;
				}
				else
					System.Device.Lcd.NonDispUnit(FigInSys[LCD_T13]);
				System.Device.Lcd.DispUnit(FigInSys[LCD_T12]);
				System.Device.Lcd.DispUnit(FigInSys[LCD_T15]);
				num = snum/10;
				DigitToDisp(num,LCD_11D);
				num = snum%10;
				DigitToDisp(num,LCD_12D);
				System.Device.Lcd.DispUnit(FigInSys[LCD_T34]);					
				break;
			case FigObj_TempIn:
				snum = (*(signed char*)objPointer->DataPointer);		
				if(snum<0)
				{
					System.Device.Lcd.DispUnit(FigInSys[LCD_T32]);
					snum *= -1;
				}
				else
					System.Device.Lcd.NonDispUnit(FigInSys[LCD_T32]);
				System.Device.Lcd.DispUnit(FigInSys[LCD_T11]);
				System.Device.Lcd.DispUnit(FigInSys[LCD_T31]);
				num = snum/10;
				DigitToDisp(num,LCD_13D);
				num = snum%10;
				DigitToDisp(num,LCD_14D);
				System.Device.Lcd.DispUnit(FigInSys[LCD_T35]);					
				
				break;
			case FigObj_RHIn:
				num = (*(byte*)objPointer->DataPointer);		
				System.Device.Lcd.DispUnit(FigInSys[LCD_T10]);
				System.Device.Lcd.DispUnit(FigInSys[LCD_T14]);
				val = num/10;
				DigitToDisp(val,LCD_15D);
				num %= 10;
				DigitToDisp(num,LCD_16D);
				break;
			case FigObj_SFrame:
				System.Device.Lcd.DispUnit(FigInSys[LCD_SS]);
				break;
			case FigObj_FaultCode:			
				lval= (*(uint*)objPointer->DataPointer);
			  if(lval)
					System.Device.Lcd.DispUnit(FigInSys[LCD_T24]);
				
				DigitToDispRev(11,LCD_8D);			  
			  lval >>=4;
			  lval >>= FaultFlag;
			  while(lval)
				{
					if(lval&0x01)
					{
            FaultFlag++;	
						break;
					}
					else
					{
						FaultFlag++;
						lval >>=1;
					}
				}
				num = FaultFlag/10;
				DigitToDispRev(num,LCD_9D);
				num = FaultFlag%10;
				DigitToDispRev(num,LCD_10D);

				break;

			case FigObj_CtrlVersionCode:
				val = (*(ushort*)objPointer->DataPointer);	
				num = val>>8;
//				DigitToDispRev(10,LCD_4D);
				num %= 10;
				DigitToDispRev(num,LCD_5D);
				val &= 0xFF;
				num = val/10;
				DigitToDispRev(num,LCD_6D);
				num = val%10;
				DigitToDispRev(num,LCD_7D); 
				
				System.Device.Lcd.DispUnit(FigInSys[LCD_T34]);					
				break;
			case FigObj_PowerVersionCode:
				val = (*(ushort*)objPointer->DataPointer);	
				num = val>>8;
//				DigitToDispRev(10,LCD_4D);
				num %= 10;
				DigitToDispRev(num,LCD_1D);
				val &= 0xFF;
				num = val/10;
				DigitToDispRev(num,LCD_2D);
				num = val%10;
				DigitToDispRev(num,LCD_3D); 
				
				System.Device.Lcd.DispUnit(FigInSys[LCD_T35]);					
				break;
			
			case FigObj_DevTypeCode:			
				lval= (*(byte*)objPointer->DataPointer);


				num = lval/100;
				lval = lval%100;
				DigitToDispRev(num,LCD_8D);
				num = lval/10;
				DigitToDispRev(num,LCD_9D);
				num = lval%10;
				DigitToDispRev(num,LCD_10D);

				break;
			default:
				break;
			}
		objPointer = objPointer->NextObjPointer;
	}
	
}

static void LoadForm(FormTypeDef * formPointer)
{
	DispObjType *objPointer= null;
	
	objPointer = formPointer->DispObjPointer;
	while(objPointer != null)
	{
		objPointer->UpdataFlag = TRUE;
		objPointer = objPointer->NextObjPointer;
	}

	if(formPointer->ScreenClean)
		System.Device.Lcd.ScreenClear();
	
	formPointer->LoadFresh=0;
		
}
	
void InitGui(void)
{
	System.Gui.ParseForm = ParseForm;
  System.Gui.AddDispObj = AddDispObj;    
  System.Gui.LoadForm = LoadForm;    

}

