#ifndef _LCD_INTERFACE_H_
#define _LCD_INTERFACE_H_

	
#define FOUR 	 0
#define EIGHT	 1
	
	#define LCD_Init 		PRTB
	#define LCD_PORT 		PRTC
	#define LCD_Port_Mask 	PORTC

	#define RS				PIN7
	#define RW				PIN6
	#define E				PIN5


	void LCD_VidInit8bit(void);
	void LCD_VidWriteData8bit(u8 LOC_u8data);
	void LCD_VidWriteCommand8bit(u8 LOC_u8command);

	
	

	void LCD_VidInit4bit(void);
	void LCD_VidWriteCommand4bit(u8 LOC_u8command);
	void LCD_VidWriteData4bit(u8 LOC_u8data);
	

	void LCD_VidWriteString(u8 *LOC_u8String,u8 LOC_u8Mode);
	void LCD_VidWriteNumber(u16 LOC_u16Number,u8 LOC_u8Mode);
	void LCD_VidSetPosition(u8 LOC_u8ROW,u8 LOC_u8COL,u8 LOC_u8Mode);
	void LCD_Custom_Char ( u8 LOC_u8Position, u8 *LOC_u8DataString,u8 LOC_u8Mode);



	//***************** Configuration for Command ******************
#define LCD_ClearDisplay 			0b00000001
#define LCD_ReturnHome 	 			0b00000010
#define LCD_EntryModeSet 			0b00000111
#define LCD_DisplayControl			0b00001100
#define LCD_CursorShift_Right		0b00010100 		// to shift right >> <<0b00010000 to shift cursor left
#define LCD_CursorShift_Left		0b00010000
#define LCD_DisplayShift			0b00011100
#define LCD_FunctionSet8bit			0b00111000
#define LCD_FunctionSet4bit			0b00101000

#endif
