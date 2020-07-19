#ifndef _ACD_INTERFACE_H_
#define _ACD_INTERFACE_H_


void ADC_VidInit(void);
void ADC_VidEnable(void);
void ADC_VidAutoTriggerSource(void);
void ADC_VidSingleEnded(void);
u16  ADC_u16GetDataSingleEnded(void);
void ADC_VidDifferential(void);
u16  ADC_u16GetDataDifferential(u8 LOC_u8Gain);
															/*  Gain=10:
																	for channel: 8,9,12,13
																Gain=200:
																	for channel: 10,11,14,15
																Gain=1:
																	for channl: 16 to 29
															*/


#define InternVCC		1 	//config num for voltage reference( 0 turned off , 1 AVCC external , 3 internal 2.56V)
#define ADC_LeftAdj		0	//config num for Adjust left or Right ( 0 for Right , 1 for left)
#define SingleEndedCh	0	//config num for choose channel ( 0>>7 mean for ADC0 to ADC7)
#define Prescaler		64	//config num for prescaler ( 2,4,8,16,32,64,128)
#define DifferentialCh	9	//config num for choose channels (9>>28)
#define ADC_INT_En		1	// To Enable ISR of ADC Interrupt

//**************** configuration of Auto Trigger Source*****************
#define AutoTrigEn		0	// to enable auto trigger set 1
#define Trigger_Mode	2	// to choose mode of Auto trigger

#define FreeRunning		0
#define AnalogComp		1
#define EXT_I0Req		2
#define Timer0CompMatch	3
#define	Timer0OvFlow	4
#define Timer1ComMatch	5
#define Timer1OvFlow	6
#define Timer1CapEvent	7

#endif
