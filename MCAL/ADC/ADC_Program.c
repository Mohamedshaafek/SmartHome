#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"
#include "DIO_Register.h"
#include "ADC_Interface.h"
#include "ADC_Register.h"


void ADC_VidInit(void)
{
	//Set Interrupt Enable
#if ADC_INT_En==1
	SET_BIT(ADCSRA,3);
#elif ADC_INT_En==0
	CLR_BIT(ADCSRA,3);
#endif

		//Set Voltage Referance
#if InternVCC==0
		CLR_BIT(ADMUX,7);
		CLR_BIT(ADMUX,6);
#elif InternVCC==1
		CLR_BIT(ADMUX,7);
		SET_BIT(ADMUX,6);
#elif InternVCC==3
		SET_BIT(ADMUX,7);
		SET_BIT(ADMUX,6);
#else
		#error "Wrong Choose Voltage Referance ! "
#endif
	
	// Set Left adjustment 
	#if ADC_LeftAdj==0
		CLR_BIT(ADMUX,5);
	#else
		SET_BIT(ADMUX,5);
	#endif
	//Set prescaler
	#if Prescaler==2
		CLR_BIT(ADCSRA,2);
		CLR_BIT(ADCSRA,1);
		SET_BIT(ADCSRA,0);
	#elif Prescaler==4
		CLR_BIT(ADCSRA,2);
		SET_BIT(ADCSRA,1);
		CLR_BIT(ADCSRA,0);
	#elif Prescaler==8
		CLR_BIT(ADCSRA,2);
		SET_BIT(ADCSRA,1);
		SET_BIT(ADCSRA,0);
	#elif Prescaler==16
		SET_BIT(ADCSRA,2);
		CLR_BIT(ADCSRA,1);
		CLR_BIT(ADCSRA,0);
	#elif Prescaler==32
		SET_BIT(ADCSRA,2);
		CLR_BIT(ADCSRA,1);
		SET_BIT(ADCSRA,0);
	#elif Prescaler==64
		SET_BIT(ADCSRA,2);
		SET_BIT(ADCSRA,1);
		CLR_BIT(ADCSRA,0);
	#elif Prescaler==128
		SET_BIT(ADCSRA,2);
		SET_BIT(ADCSRA,1);
		SET_BIT(ADCSRA,0);
	#else
		#error "Wrong Choose Prescaler!"
	#endif
}


void ADC_VidEnable(void)
{
	SET_BIT(ADCSRA,7);
}
	
	
void ADC_VidSingleEnded(void)
{
	#if SingleEndedCh==0
	
		CLR_BIT(ADMUX,4);
		CLR_BIT(ADMUX,3);
		CLR_BIT(ADMUX,2);
		CLR_BIT(ADMUX,1);
		CLR_BIT(ADMUX,0);
	
	#elif SingleEndedCh==1
	
		CLR_BIT(ADMUX,4);
		CLR_BIT(ADMUX,3);
		CLR_BIT(ADMUX,2);
		CLR_BIT(ADMUX,1);
		SET_BIT(ADMUX,0);
	
	#elif SingleEndedCh==2
	
		CLR_BIT(ADMUX,4);
		CLR_BIT(ADMUX,3);
		CLR_BIT(ADMUX,2);
		SET_BIT(ADMUX,1);
		CLR_BIT(ADMUX,0);
	
	#elif SingleEndedCh==3

		CLR_BIT(ADMUX,4);
		CLR_BIT(ADMUX,3);
		CLR_BIT(ADMUX,2);
		SET_BIT(ADMUX,1);
		SET_BIT(ADMUX,0);
	
	#elif SingleEndedCh==4
	
		CLR_BIT(ADMUX,4);
		CLR_BIT(ADMUX,3);
		SET_BIT(ADMUX,2);
		CLR_BIT(ADMUX,1);
		CLR_BIT(ADMUX,0);
	
	#elif SingleEndedCh==5
	
		CLR_BIT(ADMUX,4);
		CLR_BIT(ADMUX,3);
		SET_BIT(ADMUX,2);
		CLR_BIT(ADMUX,1);
		SET_BIT(ADMUX,0);
	
	#elif SingleEndedCh==6
	
		CLR_BIT(ADMUX,4);
		CLR_BIT(ADMUX,3);
		SET_BIT(ADMUX,2);
		SET_BIT(ADMUX,1);
		CLR_BIT(ADMUX,0);
	
	#elif SingleEndedCh==7
	
		CLR_BIT(ADMUX,4);
		CLR_BIT(ADMUX,3);
		SET_BIT(ADMUX,2);
		SET_BIT(ADMUX,1);
		SET_BIT(ADMUX,0);
	
	#else
	
		#error "Wrong Choose Channal Single Ended!"
	#endif
	
}

u16  ADC_u16GetDataSingleEnded(void)
{
	
	
	SET_BIT(ADCSRA,PIN6);
	while(0==GET_BIT(ADCSRA, PIN4));
	
	return ((ADC*5000UL)/1023);
}

void ADC_VidDifferential(void)
{
	#if DifferentialCh==8
		CLR_BIT(ADMUX,4);
		SET_BIT(ADMUX,3);
		CLR_BIT(ADMUX,2);
		CLR_BIT(ADMUX,1);
		CLR_BIT(ADMUX,0);
	#elif DifferentialCh==9
		CLR_BIT(ADMUX,4);
		SET_BIT(ADMUX,3);
		CLR_BIT(ADMUX,2);
		CLR_BIT(ADMUX,1);
		SET_BIT(ADMUX,0);
	#elif DifferentialCh==10
		CLR_BIT(ADMUX,4);
		SET_BIT(ADMUX,3);
		CLR_BIT(ADMUX,2);
		SET_BIT(ADMUX,1);
		CLR_BIT(ADMUX,0);
	#elif DifferentialCh==11
		CLR_BIT(ADMUX,4);
		SET_BIT(ADMUX,3);
		CLR_BIT(ADMUX,2);
		SET_BIT(ADMUX,1);
		SET_BIT(ADMUX,0);
	#elif DifferentialCh==12
		CLR_BIT(ADMUX,4);
		SET_BIT(ADMUX,3);
		SET_BIT(ADMUX,2);
		CLR_BIT(ADMUX,1);
		CLR_BIT(ADMUX,0);
	#elif DifferentialCh==13
		CLR_BIT(ADMUX,4);
		SET_BIT(ADMUX,3);
		SET_BIT(ADMUX,2);
		CLR_BIT(ADMUX,1);
		SET_BIT(ADMUX,0);
	#elif DifferentialCh==14
		CLR_BIT(ADMUX,4);
		SET_BIT(ADMUX,3);
		SET_BIT(ADMUX,2);
		SET_BIT(ADMUX,1);
		CLR_BIT(ADMUX,0);
	#elif DifferentialCh==15
		CLR_BIT(ADMUX,4);
		SET_BIT(ADMUX,3);
		SET_BIT(ADMUX,2);
		SET_BIT(ADMUX,1);
		SET_BIT(ADMUX,0);
	#elif DifferentialCh==16
		SET_BIT(ADMUX,4);
		CLR_BIT(ADMUX,3);
		CLR_BIT(ADMUX,2);
		CLR_BIT(ADMUX,1);
		CLR_BIT(ADMUX,0);
	#elif DifferentialCh==17
		SET_BIT(ADMUX,4);
		CLR_BIT(ADMUX,3);
		CLR_BIT(ADMUX,2);
		CLR_BIT(ADMUX,1);
		SET_BIT(ADMUX,0);
	#elif DifferentialCh==18
		SET_BIT(ADMUX,4);
		CLR_BIT(ADMUX,3);
		CLR_BIT(ADMUX,2);
		SET_BIT(ADMUX,1);
		CLR_BIT(ADMUX,0);
	#elif DifferentialCh==19
		SET_BIT(ADMUX,4);
		CLR_BIT(ADMUX,3);
		CLR_BIT(ADMUX,2);
		SET_BIT(ADMUX,1);
		SET_BIT(ADMUX,0);
	#elif DifferentialCh==20
		SET_BIT(ADMUX,4);
		CLR_BIT(ADMUX,3);
		SET_BIT(ADMUX,2);
		CLR_BIT(ADMUX,1);
		CLR_BIT(ADMUX,0);
	#elif DifferentialCh==21
		SET_BIT(ADMUX,4);
		CLR_BIT(ADMUX,3);
		SET_BIT(ADMUX,2);
		CLR_BIT(ADMUX,1);
		SET_BIT(ADMUX,0);
	#elif DifferentialCh==22
		SET_BIT(ADMUX,4);
		CLR_BIT(ADMUX,3);
		SET_BIT(ADMUX,2);
		SET_BIT(ADMUX,1);
		CLR_BIT(ADMUX,0);
	#elif DifferentialCh==23
		SET_BIT(ADMUX,4);
		CLR_BIT(ADMUX,3);
		SET_BIT(ADMUX,2);
		SET_BIT(ADMUX,1);
		SET_BIT(ADMUX,0);
	#elif DifferentialCh==24
		SET_BIT(ADMUX,4);
		SET_BIT(ADMUX,3);
		CLR_BIT(ADMUX,2);
		CLR_BIT(ADMUX,1);
		CLR_BIT(ADMUX,0);
	#elif DifferentialCh==25
		SET_BIT(ADMUX,4);
		SET_BIT(ADMUX,3);
		CLR_BIT(ADMUX,2);
		CLR_BIT(ADMUX,1);
		SET_BIT(ADMUX,0);
	#elif DifferentialCh==26
		SET_BIT(ADMUX,4);
		SET_BIT(ADMUX,3);
		CLR_BIT(ADMUX,2);
		SET_BIT(ADMUX,1);
		CLR_BIT(ADMUX,0);
	#elif DifferentialCh==27
		SET_BIT(ADMUX,4);
		SET_BIT(ADMUX,3);
		CLR_BIT(ADMUX,2);
		SET_BIT(ADMUX,1);
		SET_BIT(ADMUX,0);
	#elif DifferentialCh==28
		SET_BIT(ADMUX,4);
		SET_BIT(ADMUX,3);
		SET_BIT(ADMUX,2);
		CLR_BIT(ADMUX,1);
		CLR_BIT(ADMUX,0);
	#elif DifferentialCh==29
		SET_BIT(ADMUX,4);
		SET_BIT(ADMUX,3);
		SET_BIT(ADMUX,2);
		CLR_BIT(ADMUX,1);
		SET_BIT(ADMUX,0);
		
	#else
		#error "Wrong Choose Differential Mode Channel"
	#endif
	
}


u16  ADC_u16GetDataDifferential(u8 LOC_u8Gain)
{
		SET_BIT(ADCSRA,PIN6);
		while(0==GET_BIT (ADCSRA, PIN4));
		SET_BIT(ADCSRA,PIN4);
		return ((ADC*5000UL)/(512*LOC_u8Gain));
}

void ADC_VidAutoTriggerSource(void)
{
#if AutoTrigEn==1 && Trigger_Mode==FreeRunning
	SET_BIT(ADCSRA,5);
	CLR_BIT(SFIOR,7);
	CLR_BIT(SFIOR,6);
	CLR_BIT(SFIOR,5);
#elif AutoTrigEn==1 && Trigger_Mode==AnalogComp
	SET_BIT(ADCSRA,5);
	CLR_BIT(SFIOR,7);
	CLR_BIT(SFIOR,6);
	SET_BIT(SFIOR,5);
#elif AutoTrigEn==1 && Trigger_Mode==EXT_I0Req
	SET_BIT(ADCSRA,5);
	CLR_BIT(SFIOR,7);
	SET_BIT(SFIOR,6);
	CLR_BIT(SFIOR,5);
#elif AutoTrigEn==1 && Trigger_Mode==Timer0CompMatch
	SET_BIT(ADCSRA,5);
	CLR_BIT(SFIOR,7);
	SET_BIT(SFIOR,6);
	SET_BIT(SFIOR,5);
#elif AutoTrigEn==1 && Trigger_Mode==Timer0OvFlow
	SET_BIT(ADCSRA,5);
	SET_BIT(SFIOR,7);
	CLR_BIT(SFIOR,6);
	CLR_BIT(SFIOR,5);
#elif AutoTrigEn==1 && Trigger_Mode==Timer1ComMatch
	SET_BIT(ADCSRA,5);
	SET_BIT(SFIOR,7);
	CLR_BIT(SFIOR,6);
	SET_BIT(SFIOR,5);
#elif AutoTrigEn==1 && Trigger_Mode==Timer1OvFlow
	SET_BIT(ADCSRA,5);
	SET_BIT(SFIOR,7);
	SET_BIT(SFIOR,6);
	CLR_BIT(SFIOR,5);
#elif AutoTrigEn==1 && Trigger_Mode==Timer1CapEvent
	SET_BIT(ADCSRA,5);
	SET_BIT(SFIOR,7);
	SET_BIT(SFIOR,6);
	SET_BIT(SFIOR,5);
#endif
}


void __vector_16(void)

{
	DIO_VidSetPinValue(PRTD,PIN0,HIGH);
	_delay_ms(1000);
	DIO_VidSetPinValue(PRTD,PIN0,LOW);

}
