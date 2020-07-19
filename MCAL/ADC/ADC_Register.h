#ifndef _ACD_REGISTER_H_
#define _ACD_REGISTER_H_

//********** configuration of register ***************
#define  SFIOR		*((volatile u8*)0x50)
#define  ADMUX		*((volatile u8*)0x27)
#define  ADCSRA		*((volatile u8*)0x26)
#define  ADCH		*((volatile u8*)0x25)
#define  ADCL		*((volatile u8*)0x24)
#define  ADC		*((volatile u16*)0x24)

void __vector_16(void) __attribute__((signal));


#endif
