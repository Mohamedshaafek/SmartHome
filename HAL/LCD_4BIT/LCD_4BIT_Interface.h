/*
 * LCD_4BIT.h
 *
 *  Created on: Jun 11, 2020
 *      Author: shafek
 */

#ifndef COTS_HAL_LCD_4BIT_LCD_4BIT_INTERFACE_H_
#define COTS_HAL_LCD_4BIT_LCD_4BIT_INTERFACE_H_

//LCD PORT CONNECTION
#define LCD_PORT PORTD
//LCD RS AND RW AND EN HARDWER CONNECTION
#define LCD_INIT PORTB
#define LCD_RS PIN3
#define LCD_RW PIN4
#define LCD_EN PIN5
//COMEND CODES
#define SET_CGRAM_ADDRESS         0b01000000
#define function_set_8_bit_lcd    0b00111000
#define Display_On_Cursor_OFF     0b00001100
#define Display_On_Cursor_ON      0b00001110
#define Clear_Display             0b00000001
#define DDRAM_address_row_one_lcd 0b10000000
#define DDRAM_address_row_two_lcd 0b11000000
#define RETURN_HOME               0x02

void LCD_Vid4Initialization(void);

void LCD_VidWrite4Cmd(u8 LOC_Cmd);

void LCD_VidWrite4Data(u8 LOC_Data);

void LCD_Write4String(u8* str,u8 row,u8 col);

void LCD_GoToPosition(u8 row,u8 clo);

void LCD_VidDisp4Number(u32 number);

void LCD_VidGoto4CGRAM(void);

void LCD_StoreCustomChr(u8* LOC_pattern, u8 LOC_CGRAM_Index);

void LCD_Disply(u8 LOC_CGRAM_Index,u8 LOC_row,u8 LOC_col);


#endif /* COTS_HAL_LCD_4BIT_LCD_4BIT_INTERFACE_H_ */
