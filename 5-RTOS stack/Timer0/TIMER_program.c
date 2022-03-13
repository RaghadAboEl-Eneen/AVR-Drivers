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

