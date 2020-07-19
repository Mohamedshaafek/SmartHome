/*
 * LCD_4BIT.c
 *
 *  Created on: Jun 11, 2020
 *      Author: shafek
 */
#include "../../LIB/STD_TYPE.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_TYPE.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "avr/delay.h"
#include "../../MCAL/DIO/DIO_Regster.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "LCD_4BIT_Interface.h"

static u8 InitStepFinishid= 0;

void LCD_Vid4Initialization(void)
{
	DIO_VidSitPortDirection(LCD_PORT, 0xff);
	DIO_VidSitPintDirection(LCD_INIT,LCD_RS,HIGH);   //RS
	DIO_VidSitPintDirection(LCD_INIT,LCD_RW,HIGH);   //RW
	DIO_VidSitPintDirection(LCD_INIT,LCD_EN,HIGH);   //EN
	_delay_ms(50); // wait for LCD to initialize

	LCD_VidWrite4Cmd(0x20);
	LCD_VidWrite4Cmd(0x20);
	LCD_VidWrite4Cmd(0x80);
	_delay_ms(2);
	LCD_VidWrite4Cmd(0x00);
	LCD_VidWrite4Cmd(0xC0);
	_delay_ms(1);
	LCD_VidWrite4Cmd(0x00);
	LCD_VidWrite4Cmd(0x10);
	_delay_ms(2);
	InitStepFinishid=1;
}


void LCD_VidWrite4Cmd(u8 LOC_Cmd)
{
	DIO_VidSitPintValue(LCD_INIT,LCD_RS,LOW);
	DIO_VidSitPintValue(LCD_INIT,LCD_RW,LOW);

	DIO_VidSitPintValue(LCD_PORT,PIN4,GET_BIT(LOC_Cmd,4));
	DIO_VidSitPintValue(LCD_PORT,PIN5,GET_BIT(LOC_Cmd,5));
	DIO_VidSitPintValue(LCD_PORT,PIN6,GET_BIT(LOC_Cmd,6));
	DIO_VidSitPintValue(LCD_PORT,PIN7,GET_BIT(LOC_Cmd,7));

	DIO_VidSitPintValue(LCD_INIT,LCD_EN,HIGH);
	_delay_ms(1);
	DIO_VidSitPintValue(LCD_INIT,LCD_EN,LOW);
	_delay_ms(1);

	if(InitStepFinishid)
	{
		DIO_VidSitPintValue(LCD_PORT,PIN4,GET_BIT(LOC_Cmd,0));
		DIO_VidSitPintValue(LCD_PORT,PIN5,GET_BIT(LOC_Cmd,1));
		DIO_VidSitPintValue(LCD_PORT,PIN6,GET_BIT(LOC_Cmd,2));
		DIO_VidSitPintValue(LCD_PORT,PIN7,GET_BIT(LOC_Cmd,3));

		DIO_VidSitPintValue(LCD_INIT,LCD_EN,HIGH);
		_delay_ms(1);
		DIO_VidSitPintValue(LCD_INIT,LCD_EN,LOW);
		_delay_ms(1);
	}
	_delay_ms(2);
}


void LCD_VidWrite4Data(u8 LOC_Data)
{
	DIO_VidSitPintValue(LCD_INIT,LCD_RS,HIGH);
	DIO_VidSitPintValue(LCD_INIT,LCD_RW,LOW);

	DIO_VidSitPintValue(LCD_PORT,PIN4,GET_BIT(LOC_Data,4));
	DIO_VidSitPintValue(LCD_PORT,PIN5,GET_BIT(LOC_Data,5));
	DIO_VidSitPintValue(LCD_PORT,PIN6,GET_BIT(LOC_Data,6));
	DIO_VidSitPintValue(LCD_PORT,PIN7,GET_BIT(LOC_Data,7));

	DIO_VidSitPintValue(LCD_INIT,LCD_EN,HIGH);
	_delay_ms(1);
	DIO_VidSitPintValue(LCD_INIT,LCD_EN,LOW);

	DIO_VidSitPintValue(LCD_PORT,PIN4,GET_BIT(LOC_Data,0));
	DIO_VidSitPintValue(LCD_PORT,PIN5,GET_BIT(LOC_Data,1));
	DIO_VidSitPintValue(LCD_PORT,PIN6,GET_BIT(LOC_Data,2));
	DIO_VidSitPintValue(LCD_PORT,PIN7,GET_BIT(LOC_Data,3));

	DIO_VidSitPintValue(LCD_INIT,LCD_EN,HIGH);
	_delay_ms(1);
	DIO_VidSitPintValue(LCD_INIT,LCD_EN,LOW);

	_delay_ms(2);

}

void LCD_Write4String(u8* str,u8 row,u8 col)
{
	LCD_GoToPosition(row,col);
	u8 index=0;
	u8 line0=0;
	while (str[index] !='\0' && ((row*16)+(col+index))<32)
	{
		if (((row*16)+(col+index))<16&&(line0==0))
		{
			LCD_VidWrite4Data(str[index]);
			index++;
		}
		else if (((row*16)+(col+index))>=16&& ((row*16)+(col+index))<32 &&(line0==0))
		{
			LCD_GoToPosition(1,col);
			line0++;
		}
		else if (((row*16)+(col+index))<32&&(line0==1))
		{
			LCD_VidWrite4Data(str[index]);
			index++;
		}
	}

}

void LCD_GoToPosition(u8 row,u8 col)
{
	u8 adress;
	adress= (row*0x40)+col;
	adress =SET_BIT(adress,7);
	LCD_VidWrite4Cmd(adress);
}

void LCD_VidDisp4Number(u32 number)
{

	u32 digit=0;
	u16 i=0;
	u32 f=0;
	u8 number_holder[10];

	while(number>0)
	{
		f=number%10;
		number_holder[i]=f;
		number=number/10;
		i++;
		digit++;
		if(number==0)
		{break;}
	}
	for(i=digit;i>0;i--)
	{
		LCD_VidWrite4Data(number_holder[i-1]+48);
	}

}


void LCD_StoreCustomChr(u8* LOC_pattern, u8 LOC_CGRAM_Index)
{
	u8 LOC_Adress;
	u8 LOC_Adress_Index;
	if(LOC_CGRAM_Index < 8)
	{
		LOC_Adress = LOC_CGRAM_Index *8;
		LOC_Adress = SET_BIT(LOC_Adress,6);
		LCD_VidWrite4Cmd(LOC_Adress);
		for(LOC_Adress_Index=0;LOC_Adress_Index<8;LOC_Adress_Index++)
		{
			LCD_VidWrite4Data(LOC_pattern[LOC_Adress_Index]);
		}
	}

	LCD_VidWrite4Cmd(RETURN_HOME);

}

void LCD_Disply(u8 LOC_CGRAM_Index,u8 LOC_row,u8 LOC_col)
{
	LCD_GoToPosition(LOC_row,LOC_col);

	LCD_VidWrite4Data(LOC_CGRAM_Index);


}
