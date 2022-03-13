/******************************************************/
/******************************************************/
/**********      AUTHOR: Raghad Mohamed      **********/
/**********      Layer: MCAL                 **********/
/**********      SWC: TIMER    			     **********/
/**********      Date: 24-9-2020             **********/
/**********      Version: 1.00               **********/
/******************************************************/
/******************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER_config.h"
#include "TIMER_interface.h"
#include "TIMER_private.h"
#include "TIMER_register.h"

// Global pointer to callback function to hold the function's address
static void (*Timer0_pvOverflowCallBackFunction)(void) = NULL;

// Global pointer to callback function to hold the function's address
static void (*Timer0_pvCompareMatchCallBackFunction)(void) = NULL;

//Global variable to hold value of Timer0 Counter
static u16 Timer0_u16GlobalCounter = 0;

static u8 Timer0_u8MsTimerActive = 0; // 1 for active , 0 for inactive

void Timer0_voidInit(void) {

	//Initialize waveform generation mode to work as normal mode
	//CLR_BIT(TCCR0, TCCR0_WGM00);
	//CLR_BIT(TCCR0, TCCR0_WGM01);

	//Initialize waveform generation mode to work as CTC mode
	CLR_BIT(TCCR0, TCCR0_WGM00);
	SET_BIT(TCCR0, TCCR0_WGM01);

	//Set the required preload
	//TCNT0 = TIMER0_u8PRELOAD_VALUE;

	//Set the required compared match value
	OSC0 = TIMER0_COMPARE_MATCH_VALUE;


	//Timer0 overflow interrupt enable
	//SET_BIT(TIMSK, TIMSK_TOIE0);

	//Set the required prescaler
	TCCR0 &= TIMER0_PRESCALER_MASK;
	TCCR0 |= TIMER0_u8PRESCALER;

}

void Timer1_voidInit(void) {

	//Compare match output mode: Set on top , Clear on compare (Non-inverted mode)

	//Disable
	CLR_BIT(TCCR1A, TCCR1A_COM1A1);
	CLR_BIT(TCCR1A, TCCR1A_COM1A0);

	//Waveform generation form mode: Fast PWM with ICR1 as top value
	CLR_BIT(TCCR1A, TCCR1A_WGM10);
	SET_BIT(TCCR1A, TCCR1A_WGM11);
	SET_BIT(TCCR1B, TCCR1B_WGM12);
	SET_BIT(TCCR1B, TCCR1B_WGM13);

	//Set Timer1 top value
	ICR1 = 25000;

	//Set Compare Match value OCR1A
	OCR1A = 9375;

	//Prescalar setting: divide by 8
	CLR_BIT(TCCR1B, TCCR1B_CS12);
	SET_BIT(TCCR1B, TCCR1B_CS11);
	CLR_BIT(TCCR1B, TCCR1B_CS10);

}

void Timer1_voidSetCompValue(u16 Copy_u16Value) {

	OCR1A = Copy_u16Value;

}

u8 Timer0_u8OverflowSetCallBack(void (*Copy_pvCallBackFunction)(void)) {

	u8 Local_u8ErrorState = OK;

	if (Copy_pvCallBackFunction != NULL) {
		Timer0_pvOverflowCallBackFunction = Copy_pvCallBackFunction;

	} else {
		Local_u8ErrorState = NULLPOINTER;
		return Local_u8ErrorState;
	}

	return Local_u8ErrorState;

}

u8 Timer0_u8CompareMatchSetCallBack(void (*Copy_pvCallBackFunction)(void)) {

	u8 Local_u8ErrorState = OK;

	if (Copy_pvCallBackFunction != NULL) {
		Timer0_pvCompareMatchCallBackFunction = Copy_pvCallBackFunction;

	} else {
		Local_u8ErrorState = NULLPOINTER;
		return Local_u8ErrorState;
	}

	return Local_u8ErrorState;

}

void Timer0_voidSetPreload(u8 Copy_u8Preload) {

	TCNT0 = Copy_u8Preload;

}

void Timer0_voidEnableCompareMatchInterrupt(void) {

	SET_BIT(TIMSK, TIMSK_OCIE0);

}

void Timer0_voidDisableCompareMatchInterrupt(void) {

	CLR_BIT(TIMSK, TIMSK_OCIE0);

}

void Timer1_voidDisableFastPWM(void) {

	CLR_BIT(TCCR1A, TCCR1A_COM1A0);
	CLR_BIT(TCCR1A, TCCR1A_COM1A1);

}

u8 Timer1_u8SetFastPWM_Mode(u8 Copy_u8Mode) {

	u8 Local_u8ErrorState = OK;

	switch (Copy_u8Mode) {
	case CLEAR_AT_TOP_SET_AT_COMPARE:
		SET_BIT(TCCR1A, TCCR1A_COM1A0);
		SET_BIT(TCCR1A, TCCR1A_COM1A1);
		break;
	case SET_AT_TOP_CLEAR_AT_COMPARE:
		CLR_BIT(TCCR1A, TCCR1A_COM1A0);
		SET_BIT(TCCR1A, TCCR1A_COM1A1);
		break;
	default:
		Local_u8ErrorState = NOOK;
		break;

	}

	return Local_u8ErrorState;
}

u16 Timer1_voidSetTone(u32 Copy_u16Frequency, u16 Copy_u16Duration) {

	u16 local_16OverflowTicks;
	Copy_u16Frequency = Copy_u16Frequency *10;
	//Copy_u16Frequency = (u32)(Copy_u16Frequency / 2);

	if(Copy_u16Frequency >= 140 && Copy_u16Frequency < 170) {
		Copy_u16Frequency+=1000;
	}


	if(Copy_u16Frequency < 1200) {
		Copy_u16Frequency*=2;
	}
	if(Copy_u16Frequency > 2800) {
		Copy_u16Frequency = (u32)(Copy_u16Frequency / 2);
	}

	//to achieve a certain frequency we need to calculate a specific overflow ticks count
	local_16OverflowTicks = (u16)(10000000UL/ (Copy_u16Frequency * 8)) -1 ;


	//Set Timer1 Top Value with calculated overflow ticks
	ICR1 = local_16OverflowTicks;

	//50% duty cycle is needed , 0.5* chosen overflow ticks compare match value will achieve it
	OCR1A = (u16) (local_16OverflowTicks / 2UL);

	//Activate the Fast PWM Set on top Clear on compare
	Timer1_u8SetFastPWM_Mode(SET_AT_TOP_CLEAR_AT_COMPARE);

	//Set the stop watch active flag
	Timer0_u8MsTimerActive = 1;

	//Activate Timer0 Compare Match Interrupt Enable to start a stop watch for duration specified
	Timer0_voidEnableCompareMatchInterrupt();

	//Polling until Ms stop watch reaches duration specified
	while(Timer0_u16GlobalCounter < Copy_u16Duration);
	/********************************************************************************************/

	//Polling ended , reset and disable everything

	//Disable fastPWM
	Timer1_voidDisableFastPWM();

	//Disable Timer interrupt
	Timer0_voidDisableCompareMatchInterrupt();

	//Clear the stop watch active flag
	Timer0_u8MsTimerActive = 0;

	//Reset the global counter
	Timer0_u16GlobalCounter = 0;

}

void Timer0_StopWatchMsISR(void) {

	static u16 Local_u16Counter = 0;
	Local_u16Counter++;
	if(Local_u16Counter == 5) {
		Timer0_u16GlobalCounter++;
		Local_u16Counter = 0;
	}



}

void __vector_11(void) __attribute__((signal));
void __vector_11(void) {

	if (Timer0_pvOverflowCallBackFunction != NULL) {
		Timer0_pvOverflowCallBackFunction();
	} else {
		//Do Nothing
	}

}

void __vector_10(void) __attribute__((signal));
void __vector_10(void) {

	if (Timer0_u8MsTimerActive == 1) {

		Timer0_StopWatchMsISR();

	} else {

		if (Timer0_pvCompareMatchCallBackFunction != NULL) {
			Timer0_pvCompareMatchCallBackFunction();
		} else {
			//Do Nothing
		}
	}
}

