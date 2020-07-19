#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Timer_Count1_Register.h"
#include "Timer_Count1_Interface.h"

static void (*Tim1CallBackPtrOVFL)(void)=NULL;
static void (*Tim1CallBackPtrCOMA)(void)=NULL;
//static void (*Tim1CallBackPtrCOMB)(void)=NULL;
static void (*Tim1CallBackPtrCapture)(void)=NULL;

void Tim1_VidInit(void)
{
	//Wave Generation Mode
	#if Wavegen==Normal
	CLR_BIT(TCCR1A,0);
	CLR_BIT(TCCR1A,1);
	CLR_BIT(TCCR1B,3);
	CLR_BIT(TCCR1B,4);
	#elif Wavegen==Phase_PWM_8bit
	SET_BIT(TCCR1A,0);
	CLR_BIT(TCCR1A,1);
	CLR_BIT(TCCR1B,3);
	CLR_BIT(TCCR1B,4);
	#elif Wavegen==Phase_PWM_9bit
	CLR_BIT(TCCR1A,0);
	SET_BIT(TCCR1A,1);
	CLR_BIT(TCCR1B,3);
	CLR_BIT(TCCR1B,4);
	#elif Wavegen==Phase_PWM_10bit
	SET_BIT(TCCR1A,0);
	SET_BIT(TCCR1A,1);
	CLR_BIT(TCCR1B,3);
	CLR_BIT(TCCR1B,4);
	#elif Wavegen==CTC_OCR
	CLR_BIT(TCCR1A,0);
	CLR_BIT(TCCR1A,1);
	SET_BIT(TCCR1B,3);
	CLR_BIT(TCCR1B,4);
	#elif Wavegen==Fast_PWM_8bit
	SET_BIT(TCCR1A,0);
	CLR_BIT(TCCR1A,1);
	SET_BIT(TCCR1B,3);
	CLR_BIT(TCCR1B,4);
	#elif Wavegen==Fast_PWM_9bit
	CLR_BIT(TCCR1A,0);
	SET_BIT(TCCR1A,1);
	SET_BIT(TCCR1B,3);
	CLR_BIT(TCCR1B,4);
	#elif Wavegen==Fast_PWM_10bit
	SET_BIT(TCCR1A,0);
	SET_BIT(TCCR1A,1);
	SET_BIT(TCCR1B,3);
	CLR_BIT(TCCR1B,4);
	#elif Wavegen==Phase_PWM_Frq_ICR
	CLR_BIT(TCCR1A,0);
	CLR_BIT(TCCR1A,1);
	CLR_BIT(TCCR1B,3);
	SET_BIT(TCCR1B,4);
	#elif Wavegen==Phase_PWM_Frq_OCR
	SET_BIT(TCCR1A,0);
	CLR_BIT(TCCR1A,1);
	CLR_BIT(TCCR1B,3);
	SET_BIT(TCCR1B,4);
	#elif Wavegen==Phase_PWM_ICR
	CLR_BIT(TCCR1A,0);
	SET_BIT(TCCR1A,1);
	CLR_BIT(TCCR1B,3);
	SET_BIT(TCCR1B,4);
	#elif Wavegen==Phase_PWM_OCR
	SET_BIT(TCCR1A,0);
	SET_BIT(TCCR1A,1);
	CLR_BIT(TCCR1B,3);
	SET_BIT(TCCR1B,4);
	#elif Wavegen==CTC_ICR
	CLR_BIT(TCCR1A,0);
	CLR_BIT(TCCR1A,1);
	SET_BIT(TCCR1B,3);
	SET_BIT(TCCR1B,4);
	#elif Wavegen==Fast_PWM_ICR
	CLR_BIT(TCCR1A,0);
	SET_BIT(TCCR1A,1);
	SET_BIT(TCCR1B,3);
	SET_BIT(TCCR1B,4);
	#elif Wavegen==Fast_PWM_OCR
	SET_BIT(TCCR1A,0);
	SET_BIT(TCCR1A,1);
	SET_BIT(TCCR1B,3);
	SET_BIT(TCCR1B,4);
	#else
		#error "Wrong Mode of Wave Generation"
	#endif
	
	//Prescaler
	#if Prescaler== No_Pres
	CLR_BIT(TCCR1B,0);
	CLR_BIT(TCCR1B,1);
	CLR_BIT(TCCR1B,2);
	#elif Prescaler==1
	SET_BIT(TCCR1B,0);
	CLR_BIT(TCCR1B,1);
	CLR_BIT(TCCR1B,2);
	#elif Prescaler==8
	CLR_BIT(TCCR1B,0);
	SET_BIT(TCCR1B,1);
	CLR_BIT(TCCR1B,2);
	#elif Prescaler==64
	SET_BIT(TCCR1B,0);
	SET_BIT(TCCR1B,1);
	CLR_BIT(TCCR1B,2);
	#elif Prescaler==256
	CLR_BIT(TCCR1B,0);
	CLR_BIT(TCCR1B,1);
	SET_BIT(TCCR1B,2);
	#elif Prescaler==1024
	SET_BIT(TCCR1B,0);
	CLR_BIT(TCCR1B,1);
	SET_BIT(TCCR1B,2);
	#elif Prescaler==EXT_Clk_Falling
	CLR_BIT(TCCR1B,0);
	SET_BIT(TCCR1B,1);
	SET_BIT(TCCR1B,2);
	#elif Prescaler==EXT_Clk_Rising
	SET_BIT(TCCR1B,0);
	SET_BIT(TCCR1B,1);
	SET_BIT(TCCR1B,2);
	#else
		#error	"Wronge Choose of Prescaler"
	#endif
	
	//Noise_Canceller Enable
	#if Noise_Canceller_EN==1
		SET_BIT(TCCR1B,7);
	#elif	Noise_Canceller_EN==0
		CLR_BIT(TCCR1B,0);
	#endif
	
	
}
void Tim1_VidIntEN(void)
{
	#if	INT_EN==INP_Capture
	CLR_BIT(TIMSK,2);
	CLR_BIT(TIMSK,3);
	CLR_BIT(TIMSK,4);
	SET_BIT(TIMSK,5);
	#elif INT_EN==Out_CompareA
	CLR_BIT(TIMSK,2);
	CLR_BIT(TIMSK,3);
	SET_BIT(TIMSK,4);
	CLR_BIT(TIMSK,5);
	#elif INT_EN==Out_CompareB
	CLR_BIT(TIMSK,2);
	SET_BIT(TIMSK,3);
	CLR_BIT(TIMSK,4);
	CLR_BIT(TIMSK,5);
	#elif INT_EN==Overflow
	SET_BIT(TIMSK,2);
	CLR_BIT(TIMSK,3);
	CLR_BIT(TIMSK,4);
	CLR_BIT(TIMSK,5);
	#endif
}

void Tim1_VidOutCompare(void)
{
	#if (Wavegen==Normal || Wavegen==CTC_ICR || Wavegen==CTC_OCR) 
		#if OutComp==Normal
			CLR_BIT(TCCR1A,7);
			CLR_BIT(TCCR1A,5);
			CLR_BIT(TCCR1A,6);
			CLR_BIT(TCCR1A,4);
		#elif OutComp==Toggle
			CLR_BIT(TCCR1A,7);
			CLR_BIT(TCCR1A,5);
			SET_BIT(TCCR1A,6);
			SET_BIT(TCCR1A,4);
		#elif OutComp==Clear
			SET_BIT(TCCR1A,7);
			SET_BIT(TCCR1A,5);
			CLR_BIT(TCCR1A,6);
			CLR_BIT(TCCR1A,4);
		#elif OutComp==Set
			SET_BIT(TCCR1A,7);
			SET_BIT(TCCR1A,5);
			SET_BIT(TCCR1A,6);
			SET_BIT(TCCR1A,4);
		#endif
		
	#elif Wavegen==Fast_PWM_8bit || Wavegen==Fast_PWM_9bit || Wavegen==Fast_PWM_10bit || Wavegen==Fast_PWM_ICR || Wavegen==Fast_PWM_OCR
		#if OutFast==Normal
			CLR_BIT(TCCR1A,7);
			CLR_BIT(TCCR1A,5);
			CLR_BIT(TCCR1A,6);
			CLR_BIT(TCCR1A,4);
		#elif OutFast==Toggle_OC1A
			CLR_BIT(TCCR1A,7);
			CLR_BIT(TCCR1A,5);
			SET_BIT(TCCR1A,6);
			SET_BIT(TCCR1A,4);
		#elif OutFast==Clear
			SET_BIT(TCCR1A,7);
			SET_BIT(TCCR1A,5);
			CLR_BIT(TCCR1A,6);
			CLR_BIT(TCCR1A,4);
		#elif OutFast==Set
			SET_BIT(TCCR1A,7);
			SET_BIT(TCCR1A,5);
			SET_BIT(TCCR1A,6);
			SET_BIT(TCCR1A,4)
		#endif
		
	#elif Wavegen==Phase_PWM_8bit || Wavegen==Phase_PWM_9bit || Wavegen==Phase_PWM_10bit || Wavegen==Phase_PWM_Frq_ICR \\
	|| Wavegen==Phase_PWM_Frq_OCR || Wavegen==Phase_PWM_ICR || Wavegen==Phase_PWM_OCR

		#if OutPhase==Normal
			CLR_BIT(TCCR1A,7);
			CLR_BIT(TCCR1A,5);
			CLR_BIT(TCCR1A,6);
			CLR_BIT(TCCR1A,4);
		#elif OutPhase==Toggle_OC1A
			CLR_BIT(TCCR1A,7);
			CLR_BIT(TCCR1A,5);
			SET_BIT(TCCR1A,6);
			SET_BIT(TCCR1A,4);
		#elif OutPhase==Clear
			SET_BIT(TCCR1A,7);
			SET_BIT(TCCR1A,5);
			CLR_BIT(TCCR1A,6);
			CLR_BIT(TCCR1A,4);
		#elif OutPhase==Set
			SET_BIT(TCCR1A,7);
			SET_BIT(TCCR1A,5);
			SET_BIT(TCCR1A,6);
			SET_BIT(TCCR1A,4)
		#endif 
	#endif	
		
}
void Tim1_VidEdgeSelect(u8 LOC_u16Edge)
{
	if (LOC_u16Edge==0)
	{
		CLR_BIT(TCCR1B,6);
	}
	else if (LOC_u16Edge==1)
	{
		SET_BIT(TCCR1B,6);
	}

}

void Tim1_VidTCNT(u16 LOC_u16TCNT)
{
	TCNT1=LOC_u16TCNT;
}

void Tim1_VidOCRA(u16 LOC_u16OCRA)
{
	OCR1A=LOC_u16OCRA;
}

void Tim1_VidOCRB(u16 LOC_u16OCRB)
{
	OCR1B=LOC_u16OCRB;
}

void Tim1_VidICR(u16 LOC_u16ICR)
{
	ICR1=LOC_u16ICR;
}



//***********************************************************************************************************

void Timer1_VidSetCallBack(void (*Fptr)(void))
{
	if (Fptr !=NULL)
	{
		#if Wavegen==Normal
		Tim1CallBackPtrOVFL=Fptr;
		#elif Wavegen !=Normal || Wavegen !=Fast_PWM_ICR || Wavegen!=Phase_PWM_Frq_ICR ||Wavegen!=CTC_ICR
		Tim1CallBackPtrCOMA=Fptr;
		#elif Wavegen ==Fast_PWM_ICR || Wavegen==Phase_PWM_Frq_ICR ||Wavegen==CTC_ICR
		Tim1CallBackPtrCapture=Fptr
		#endif
	}

	}

void __vector_9(void) //Overflow Interrupt
{
	if (Tim1CallBackPtrOVFL !=NULL)
	{
		Tim1CallBackPtrOVFL();
	}
}

void __vector_7(void) //Compare match A Interrupt
{
	if (Tim1CallBackPtrCOMA !=NULL)
		{
		Tim1CallBackPtrCOMA();
		}
}


void __vector_6(void)
{
	if (Tim1CallBackPtrCapture !=NULL)
		{
		Tim1CallBackPtrCapture();
		}
}
