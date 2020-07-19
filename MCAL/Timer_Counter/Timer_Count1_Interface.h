#ifndef _TIMER_COUNT1_INTERFACE_H_
#define _TIMER_COUNT1_INTERFACE_H_


//***************** Functions of Timer/Counter 0 *****************

void Tim1_VidInit(void);
void Tim1_VidIntEN(void);
void Tim1_VidOutCompare(void);
void Tim1_VidTCNT(u16 LOC_u16TCNT);
void Tim1_VidOCRA(u16 LOC_u16OCRA);
void Tim1_VidOCRB(u16 LOC_u16OCRB);
void Tim1_VidICR(u16 LOC_u16ICR);
void Tim1_VidEdgeSelect(u8 LOC_u16Edge);

void Timer1_VidSetCallBack(void (*Fptr)(void));


//*********************** Configuration of Timer Register **************************

//wave generation Initialization
#define Wavegen				Fast_PWM_ICR
#define Normal				0
#define	Phase_PWM_8bit		1
#define	Phase_PWM_9bit		2
#define	Phase_PWM_10bit		3
#define	CTC_OCR				4
#define	Fast_PWM_8bit		5
#define	Fast_PWM_9bit		6
#define	Fast_PWM_10bit		7
#define	Phase_PWM_Frq_ICR	8
#define	Phase_PWM_Frq_OCR	9
#define	Phase_PWM_ICR		10
#define	Phase_PWM_OCR		11
#define CTC_ICR				12
#define Fast_PWM_ICR		13
#define	Fast_PWM_OCR		14

//Prescaler Initialization
#define	Prescaler		256		//Choose from 1  8  64  256  1024 or below
#define	No_Pres			0			//No Prescaler
#define	EXT_Clk_Falling	6			//External clock source on T1 pin. Clock on falling edge.
#define	EXT_Clk_Rising	7			//External clock source on T1 pin. Clock on rising edge.

//Interrupt Enable
#define INT_EN			0
#define	INP_Capture		1
#define	Out_CompareA	2
#define	Out_CompareB	3
#define	Overflow		4

//Output Compare	Normal or CTC Mode
#define OutComp		Normal		
#define	Normal		0			//Normal port operation, OC1A/OC1B disconnected.
#define	Toggle		1			//Toggle OC1A/OC1B on compare match
#define	Clear		2			//Clear OC1A/OC1B on compare match (Set output to low level)
#define	Set			3			//Set OC1A/OC1B on compare match (Set output to high level)

//Output Compare 	Fast PWM
#define OutFast			Clear
#define	Normal			0			//Normal port operation, OC1A/OC1B disconnected.
#define	Toggle_OC1A		1			//WGM13:0 = 15: Toggle OC1A on Compare Match, OC1B disconnected (normal port operation)
#define	Clear			2			//Clear OC1A/OC1B on compare match, set OC1A/OC1B at TOP
#define	Set				3			//Set OC1A/OC1B on compare match, clear OC1A/OC1B at TOP

//Output Compare	Phase Correct and Phase and Frequency Correct
#define	OutPhase		Normal		
#define	Normal			0			//Normal port operation, OC1A/OC1B disconnected.
#define	Toggle_OC1A		1			//WGM13:0 = 9 or 14: Toggle OC1A on Compare Match, OC1B disconnected (normal port operation)
#define	Clear			2			//Clear OC1A/OC1B on compare match when up-counting. Set OC1A/OC1B on compare match when downcounting
#define	Set				3			//Set OC1A/OC1B on compare match when upcounting. Clear OC1A/OC1B on compare match when downcounting.


//Noise Canceler
#define Noise_Canceller_EN	0	//for Enable set 1




void __vector_6(void) __attribute__((signal));	//Timer 1 Capture event
void __vector_7(void) __attribute__((signal));	//Timer 1 Compare match A
void __vector_8(void) __attribute__((signal));	//Timer 1 Compare match B
void __vector_9(void) __attribute__((signal));	//Timer 1 Overflow



#endif
