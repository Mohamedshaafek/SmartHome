#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"
#include "EXT_Interface.h"
#include "EXT_Register.h"



void EXT_Vidinit(void)
{
#if EXT0_EN==1
	DIO_VidSetPinDirection(PRTD,PIN2,INPUT);
	DIO_VidSetPinValue(PRTD,PIN2,HIGH);
#endif
#if EXT1_EN==1
	DIO_VidSetPinDirection(PRTD,PIN3,INPUT);
	DIO_VidSetPinValue(PRTD,PIN3,HIGH);
#endif
#if EXT2_EN==1
	DIO_VidSetPinDirection(PRTB,PIN2,INPUT);
	DIO_VidSetPinValue(PRTB,PIN2,HIGH);
#endif
	#if EXT0_EN==0 && EXT1_EN==0 && EXT2_EN==0
	#error "NO Choose of EXT Interrupt"
#endif
}

void EXT_VidSense(void)
{
#if SENCE_MODE_EX0 ==FALLING && EXT0_EN==1
	SET_BIT(MCUCR,1);
	CLR_BIT(MCUCR,0);
#elif SENCE_MODE_EX0 ==RISING && EXT0_EN==1
	SET_BIT(MCUCR,0);
	SET_BIT(MCUCR,1);
#elif SENCE_MODE_EX0 ==IOC && EXT0_EN==1
	CLR_BIT(MCUCR,1);
	SET_BIT(MCUCR,0);
#elif SENCE_MODE_EX0 ==LOW_LEVLE && EXT0_EN==1
	CLR_BIT(MCUCR,0);
	CLR_BIT(MCUCR,1);

	#endif

#if SENCE_MODE_EX1 ==FALLING && EXT1_EN==1
	SET_BIT(MCUCR,3);
	CLR_BIT(MCUCR,2);
#elif SENCE_MODE_EX1 ==RISING && EXT1_EN==1
	SET_BIT(MCUCR,3);
	SET_BIT(MCUCR,2);
#elif SENCE_MODE_EX1 ==IOC && EXT1_EN==1
	CLR_BIT(MCUCR,3);
	SET_BIT(MCUCR,2	);
#elif SENCE_MODE_EX1 ==LOW_LEVLE && EXT1_EN==1
	CLR_BIT(MCUCR,3);
	CLR_BIT(MCUCR,2);

	#endif

#if SENCE_MODE_EX2==RISING && EXT2_EN==1
	SET_BIT(MCUCSR,6);
#elif SENCE_MODE_EX2==FALLING && EXT2_EN==1
	CLR_BIT(MCUCSR,6);
#endif

}

void EXT_VidEnable(void)
{
#if EXT0_EN==1
	SET_BIT(GICR,6);
#endif

#if EXT1_EN==1
	SET_BIT(GICR,7);
#endif
#if EXT2_EN==1
	SET_BIT(GICR,5);
#endif
}
void EXT_VidDisable(void)
{
#if EXT0_EN==1
	CLR_BIT(GICR,6);
#endif

#if EXT1_EN==1
	CLR_BIT(GICR,7);
#endif
#if EXT2_EN==1
	CLR_BIT(GICR,5);
#endif
	}




void __vector_1(void)

{
	DIO_VidSetPinValue(PRTA,PIN7,HIGH);
	_delay_ms(1000);
	DIO_VidSetPinValue(PRTA,PIN7,LOW);
}



void __vector_2(void)

{
	static u8 flag =0;
	if (0==flag)
	{

	DIO_VidSetPinValue(PRTD,PIN0,HIGH);
	_delay_ms(1000);
	flag=1;
	}
	else
	{
		DIO_VidSetPinValue(PRTD,PIN0,LOW);
			_delay_ms(1000);
			flag=0;
	}
}





