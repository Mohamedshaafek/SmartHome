#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"
#include "DIO_Register.h"


void KeyPad_VidInit(u8 LOC_u8Port)
{
	DIO_VidSetPortDircection(LOC_u8Port,0x0f);
	DIO_VidSetPortValue(LOC_u8Port,0xff);
}

u8 GetPressedKey(u8 LOC_u8Port)
{
	u8 KeyOut=-1;
	u8 ROW;
	u8 COL;
	u8 KEY_NUM[4][4]={			{1 ,2 ,3 ,11 },
								{4 ,5 ,6 ,12 },
								{7 ,8 ,9 ,13 },
								{16,0 ,15,14 }
					 };
	
	
	for (COL=0;COL<4;COL++)
	{
		DIO_VidSetPinValue(LOC_u8Port,COL,LOW);
		for (ROW=4;ROW<8;ROW++)
		{
			if (DIO_u8GitPinValue(LOC_u8Port,ROW)==0)
			{
				KeyOut=KEY_NUM[ROW-4][COL];
				while (DIO_u8GitPinValue(LOC_u8Port,ROW)==0){}
				_delay_ms(50);
			}
		}
		DIO_VidSetPinValue(LOC_u8Port,COL,HIGH);
	}
	return KeyOut;}
