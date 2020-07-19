#ifndef _UART_INTERFACE_H_
#define _UART_INTERFACE_H_


void UART_VidInit(u16 LOC_u16BuadRate);
void UART_VidINT_En(void);
u8 	 UART_U8Checker(u8 LOC_u8FlagStatus);
void UART_VidSendData(u8 data);
u8 UART_u8ReadData(void);



#define DoubleSpeed  	0	//to Enable Set	1
#define	MutiProcessor	0	//to Enable Set 1
#define CharSize		8	// Choose from 5 6 7 8 9
#define ModeSelect		0	//Asynchronous=0 and Synchronous=1
#define ParityMode		0	// Disable 0 OR 0Even 1 OR Odd 2
#define StopMode		0	// for 1 bit set 0 for 2bit set 1
#define ClkPolarity		0	//0 for rising in transimition and falling for reciving, OR 1 for falling for transimition and rising for reciving 
#define TxEnable 		1
#define	RxEnable		1

#endif
