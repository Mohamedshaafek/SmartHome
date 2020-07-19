#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"
#include "DIO_Register.h"
#include "LCD_Interface.h"


void LCD_VidInit8bit(void)
{
	_delay_ms(31);
	DIO_VidSetPortDirection(LCD_PORT,0xff);
	DIO_VidSetPinDirection(LCD_Init,RS,OUTPUT);
	DIO_VidSetPinDirection(LCD_Init,RW,OUTPUT);
	DIO_VidSetPinDirection(LCD_Init,E,OUTPUT);
	 LCD_VidWriteCommand8bit(0b00111000);	//function set
	_delay_us(500);
	LCD_VidWriteCommand8bit (0b00001110);	//Display on
	_delay_us(500);
	LCD_VidWriteCommand8bit(0b00000001);	//Clear Display
	_delay_ms(1.6);
	
}
void LCD_VidInit4bit(void)
{
	_delay_ms(32);
	DIO_VidSetPortDirection(LCD_PORT,0xff);
	DIO_VidSetPortDirection(LCD_Init,0b00000111);
	LCD_VidWriteCommand4bit(0x02);		/* send for 4 bit initialization of LCD  */
	LCD_VidWriteCommand4bit(0x28);              /* 2 line, 5*7 matrix in 4-bit mode */
	LCD_VidWriteCommand4bit(0x0c);              /* Display on cursor off*/
	LCD_VidWriteCommand4bit(0x06);              /* Increment cursor (shift cursor to right)*/
	LCD_VidWriteCommand4bit(0x83);
	LCD_VidWriteCommand4bit(0x01);              /* Clear display screen*/
	_delay_ms(2);
	
	
}
	
	void LCD_VidWriteCommand8bit(u8 LOC_u8command)
	{
		DIO_VidSetPinValue(LCD_Init,RS,LOW); //RS=0
		DIO_VidSetPinValue(LCD_Init,RW,LOW);	//RW=0
		DIO_VidSetPortValue(LCD_PORT,LOC_u8command);
		
		DIO_VidSetPinValue(LCD_Init,E,HIGH);	//E=High
		_delay_ms(1);
		DIO_VidSetPinValue(LCD_Init,E,LOW);		//E=Low
		_delay_ms(1);
		
		
	}
	
	void LCD_VidWriteData8bit(u8 LOC_u8data)
	{
		DIO_VidSetPinValue(LCD_Init,RS,HIGH); //RS=0
		DIO_VidSetPinValue(LCD_Init,RW,LOW);	//RW=0
		DIO_VidSetPortValue(LCD_PORT,LOC_u8data);
		
		DIO_VidSetPinValue(LCD_Init,E,HIGH);	//E=High
		_delay_ms(1);
		DIO_VidSetPinValue(LCD_Init,E,LOW);		//E=Low
		_delay_ms(1);
	}
	
	void LCD_VidWriteData4bit(u8 LOC_u8data)
	{
		DIO_VidSetPinValue(LCD_Init,RS,HIGH); //RS=0
		DIO_VidSetPinValue(LCD_Init,RW,LOW);	//RW=0
		LCD_Port_Mask = (LCD_Port_Mask & 0x0F) | (LOC_u8data & 0xF0); //send higher 4-bit data
		DIO_VidSetPinValue(LCD_Init,E,HIGH);	//E=HIGH
		_delay_ms(1);
		DIO_VidSetPinValue(LCD_Init,E,LOW);		//E=Low
		_delay_ms(1);
		LCD_Port_Mask = (LCD_Port_Mask & 0x0F) | (LOC_u8data << 4); 	//send lower 4-bit data
		DIO_VidSetPinValue(LCD_Init,E,HIGH);	//E=HIGH
		_delay_ms(1);
		DIO_VidSetPinValue(LCD_Init,E,LOW);		//E=Low
		_delay_ms(2);
		
	}
	
	void LCD_VidWriteCommand4bit(u8 LOC_u8command)
	{
		DIO_VidSetPinValue(LCD_Init,RS,HIGH); //RS=0
		DIO_VidSetPinValue(LCD_Init,RW,LOW);	//RW=0
		LCD_Port_Mask = (LCD_Port_Mask & 0x0F) | (LOC_u8command & 0xF0);	//send higher 4-bit command
		DIO_VidSetPinValue(LCD_Init,E,HIGH);	//E=HIGH
		_delay_ms(1);
		DIO_VidSetPinValue(LCD_Init,E,LOW);		//E=Low
		_delay_ms(1);
		LCD_Port_Mask = (LCD_Port_Mask & 0x0F) | (LOC_u8command << 4); 	//send lower 4-bit command
		DIO_VidSetPinValue(LCD_Init,E,HIGH);	//E=HIGH
		_delay_ms(1);
		DIO_VidSetPinValue(LCD_Init,E,LOW);		//E=Low
		_delay_ms(1);
	}
	
	
	void LCD_VidWriteString(u8 *LOC_u8String,u8 LOC_u8Mode)
	{
		if (LOC_u8Mode==0)	//Mode 4-bit
		{
			for (u8 i=0;LOC_u8String[i]!='\0';i++)
			{
				LCD_VidWriteData4bit(LOC_u8String[i]);
			}
		}
		else if (LOC_u8Mode==1)
		{
			for (u8 i=0;LOC_u8String[i]!='\0';i++)
			{
			LCD_VidWriteData8bit(LOC_u8String[i]);
			}
		}
	}


	void LCD_Custom_Char ( u8 LOC_u8Position, u8 *LOC_u8DataString,u8 LOC_u8Mode)
{
			u8 i;
			if (LOC_u8Mode==0)
			{
				LCD_VidWriteCommand4bit(0x40 +(LOC_u8Position)*8 );
				for(i=0;i<8;i++)
					{
						LCD_VidWriteData4bit(LOC_u8DataString[i]);
					}
			}

			else if (LOC_u8Mode==1)
			{
				LCD_VidWriteCommand8bit(0x40 +(LOC_u8Position)*8 );
				for(i=0;i<8;i++)
					{
						LCD_VidWriteData8bit(LOC_u8DataString[i]);
					}
			}

}


	void LCD_VidSetPosition(u8 LOC_u8ROW,u8 LOC_u8COL,u8 LOC_u8Mode)
	{

		if (LOC_u8Mode==0)
		{
			if(LOC_u8ROW==0)
			{
				LCD_VidWriteCommand4bit(0x80 + LOC_u8COL);  //DDRAM address row one lcd
				_delay_ms(1);
			}
			else if(LOC_u8ROW==1)
				{
				LCD_VidWriteCommand4bit(0xC0 + LOC_u8COL); //DDRAM address row two lcd
					_delay_ms(1);
				}
		}
		else if (LOC_u8Mode==1)
		{
			if(LOC_u8ROW==0)
				{
					LCD_VidWriteCommand8bit(0x80+LOC_u8COL);  //DDRAM address row one lcd
					_delay_ms(1);
				}
			else if(LOC_u8ROW==1)
				{
					LCD_VidWriteCommand8bit(0xC0+LOC_u8COL); //DDRAM address row two lcd
					_delay_ms(1);
				}
		}
	}

	void LCD_VidWriteNumber(u16 LOC_u16Number,u8 LOC_u8Mode)
		{
			u8 Num[5]={0};

			u8 j=0;
			if (LOC_u8Mode==0)
			{
				for (u8 i=4;i>=0;i--)
								{
									Num[i]=LOC_u16Number%10;
									LOC_u16Number=LOC_u16Number/10;
									if (LOC_u16Number==0)
										break;
								}
								if(Num[0]==0)
									j++;
								if (Num[0]==0 && Num[1]==0)
									j++;
								if (Num[0]==0 && Num[1]==0 && Num[2]==0)
									j++;
								if (Num[0]==0 && Num[1]==0 && Num[2]==0 && Num[3]==0)
										j++;

								for (u8 k=j;k<5;k++)
								{
									LCD_VidWriteData4bit(Num[k]+'0');
								}

			}
			else if (LOC_u8Mode==1)
			{
				for (u8 i=4;i>=0;i--)
				{
					Num[i]=LOC_u16Number%10;
					LOC_u16Number=LOC_u16Number/10;
					if (LOC_u16Number==0)
						break;
				}
				if(Num[0]==0)
					j++;
				if (Num[0]==0 && Num[1]==0)
					j++;
				if (Num[0]==0 && Num[1]==0 && Num[2]==0)
					j++;
				if (Num[0]==0 && Num[1]==0 && Num[2]==0 && Num[3]==0)
						j++;

				for (u8 k=j;k<5;k++)
				{
					LCD_VidWriteData8bit(Num[k]+'0');
				}
			}


		}









