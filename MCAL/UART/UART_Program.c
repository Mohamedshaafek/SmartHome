#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"
#include "UART_Interface.h"
#include "UART_Register.h"


void UART_VidInit(u16 LOC_u16BaudRate)
{
	//Baud Rate
	u16 UBRR=0;
	UBRR=((8000000/(16*(u32)LOC_u16BaudRate))-1);
	UBRRL=UBRR;
	UBRRH=0;



	//Enable double speed
	#if DoubleSpeed==0
		CLR_BIT(UCSRA,U2X);
	#elif DoubleSpeed==1
		SET_BIT(UCSRA,U2X)
	#endif
		
	//Enable Multiple Processor Mode
	#if MutiProcessor==0
		CLR_BIT(UCSRA,MPCM);
	#elif MutiProcessor==1
		SET_BIT(UCSRA,MPCM);
	#endif
	
	//Character Size
		u8 UCSR1=0;
	#if CharSize==5
	CLR_BIT(UCSRB,UCSZ2);
	CLR_BIT(UCSR1,UCSZ1);
	CLR_BIT(UCSR1,UCSZ0);
	#elif CharSize==6
	CLR_BIT(UCSRB,UCSZ2);
	CLR_BIT(UCSR1,UCSZ1);
	SET_BIT(UCSR1,UCSZ0);
	#elif CharSize==7
	CLR_BIT(UCSRB,UCSZ2);
	SET_BIT(UCSR1,UCSZ1);
	CLR_BIT(UCSR1,UCSZ0);
	#elif CharSize==8
	CLR_BIT(UCSRB,UCSZ2);
	SET_BIT(UCSR1,UCSZ1);
	SET_BIT(UCSR1,UCSZ0);
	#elif CharSize==9
	SET_BIT(UCSRB,UCSZ2);
	SET_BIT(UCSR1,UCSZ1);
	SET_BIT(UCSR1,UCSZ0);
	#endif
	SET_BIT(UCSR1,7);
	//To choose Asynchronous and Synchronous
		#if ModeSelect==0
		CLR_BIT(UCSR1,UMSEL);
		#elif ModeSelect==1
		SET_BIT(UCSR1,UMSEL)
		#endif
		
	// TO Enable Parity
		#if ParityMode==0
		CLR_BIT(UCSR1,UPM1);
		CLR_BIT(UCSR1,UPM0);
		#elif ParityMode==1
		SET_BIT(UCSR1,UPM1);
		CLR_BIT(UCSR1,UPM0);
		#elif ParityMode==2
		SET_BIT(UCSR1,UPM1);
		SET_BIT(UCSR1,UPM0);
		#endif
		
		//Stop Bit Mode
		#if StopMode==0
		CLR_BIT(UCSR1,USBS);
		#elif StopMode==1
		SET_BIT(UCSR1,USBS);
		#endif
		
		//Clock Polarity 
		#if ClkPolarity==0
		CLR_BIT(UCSR1,UCPOL);
		#elif UCPOL==1
		SET_BIT(UCSR1,UCPOL);
		#endif
		
		//Enable Tx Rx 
		#if RxEnable==1 
		SET_BIT(UCSRB,RXEN);
		#elif RxEnable==0
		CLR_BIT(UCSRB,RXEN);
		#endif
		
		#if TxEnable==1
		SET_BIT(UCSRB,TXEN);

		#elif TxEnable==0
		CLR_BIT(UCSRB,TXEN);
		#endif
		UCSRC=UCSR1;
}


void UART_VidSendData(u8 data)
{
	while( !(GET_BIT(UCSRA,UDRE)));
	UDR = data ;
}

u8 UART_u8ReadData(void)
{
	while(!GET_BIT(UCSRA,RXC))
	{ /* wait for data to be received */ }

	return UDR;
}
