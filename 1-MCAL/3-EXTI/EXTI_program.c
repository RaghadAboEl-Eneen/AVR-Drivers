/******************************************************/
/******************************************************/
/**********      AUTHOR: Raghad Mohamed      **********/
/**********      Layer: MCAL                 **********/
/**********      SWC: External Interrupt     **********/
/**********      Date: 14-9-2020             **********/
/**********      Version: 1.00               **********/
/******************************************************/
/******************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EXTI_register.h"
#include "EXTI_interface.h"
#include "EXTI_config.h"
#include "EXTI_private.h"

/*Define the global array of pointers to functions to carry  ISR application address*/
void (*EXTI_pvCallBackFunction[3])(void);

void EXTI_voidINT0Init(void) {

#if   EXTI_INT0_SENSE == LOW_LEVEL
	CLR_BIT(MCUCR, MCUCR_ISC00);
	CLR_BIT(MCUCR, MCUCR_ISC01);

#elif EXTI_INT0_SENSE == ON_CHANGE
	SET_BIT(MCUCR, MCUCR_ISC00);
	CLR_BIT(MCUCR, MCUCR_ISC01);

#elif EXTI_INT0_SENSE == FALLING_EDGE
	CLR_BIT(MCUCR, MCUCR_ISC00);
	SET_BIT(MCUCR, MCUCR_ISC01);

#elif EXTI_INT0_SENSE == RISING_EDGE
	SET_BIT(MCUCR, MCUCR_ISC00);
	SET_BIT(MCUCR, MCUCR_ISC01);

#else
#error "Wrong_EXTI_INT0_SENSE configuration"

#endif

#if   EXTI_INT0_INITIAL_STATE == ENABLED
	  SET_BIT(GICR, GICR_INT0);

#elif EXTI_INT0_INITIAL_STATE == DISABLED
	CLR_BIT(GICR, GICR_INT0);
#else
#error "Wrong_EXTI_INT0_INITIAL_STATE configuration"

#endif

}

void EXTI_voidINT1Init(void) {

#if   EXTI_INT1_SENSE == LOW_LEVEL
	  CLR_BIT(MCUCR, MCUCR_ISC10);
	  CLR_BIT(MCUCR, MCUCR_ISC11);

#elif EXTI_INT1_SENSE == ON_CHANGE
	  SET_BIT(MCUCR, MCUCR_ISC10);
	  CLR_BIT(MCUCR, MCUCR_ISC11);

#elif EXTI_INT1_SENSE == FALLING_EDGE
	  SET_BIT(MCUCR, MCUCR_ISC10);
	  SET_BIT(MCUCR, MCUCR_ISC11);

#elif EXTI_INT1_SENSE == RISING_EDGE
	  CLR_BIT(MCUCR, MCUCR_ISC10);
	  SET_BIT(MCUCR, MCUCR_ISC11);

#else
#error "Wrong_EXTI_INT1_SENSE configuration"

#endif

#if   EXTI_INT1_INITIAL_STATE == ENABLED
	  SET_BIT(GICR, GICR_INT1);

#elif EXTI_INT1_INITIAL_STATE == DISABLED
	  CLR_BIT(GICR, GICR_INT1);
#else
#error "Wrong_EXTI_INT1_INITIAL_STATE configuration"

#endif
}

void EXTI_voidINT2Init(void) {

#if   EXTI_INT2_SENSE == RISING_EDGE
	  SET_BIT(MCUCR, MCUCR_ISC2);

#elif EXTI_INT2_SENSE == FALLING_EDGE
	  CLR_BIT(MCUCR, MCUCR_ISC2);

#else
#error "WRONG_EXTI_INT2_SENSE configuration"
#endif

#if   EXTI_INT2_INITIAL_STATE == ENABLED
	  SET_BIT(GICR, GICR_INT2);

#elif EXTI_INT2_INITIAL_STATE == DISABLED
	  CLR_BIT(GICR, GICR_INT2);
#else
#error "Wrong_EXTI_INT2_INITIAL_STATE configuration"

#endif

}





u8 EXTI_u8INTSetSenseControl(u8 Copy_u8Sense, u8 Copy_u8IntNumber) {

	u8 Local_u8ErrorState = OK;

	switch (Copy_u8IntNumber) {
	case EXTI_INT0:
		switch (Copy_u8Sense) {
		case LOW_LEVEL: 	CLR_BIT(MCUCR, MCUCR_ISC00); CLR_BIT(MCUCR, MCUCR_ISC01); break;
		case ON_CHANGE: 	SET_BIT(MCUCR, MCUCR_ISC00); CLR_BIT(MCUCR, MCUCR_ISC01); break;
		case FALLING_EDGE:  CLR_BIT(MCUCR, MCUCR_ISC00); SET_BIT(MCUCR, MCUCR_ISC01); break;
		case RISING_EDGE: 	SET_BIT(MCUCR, MCUCR_ISC00); SET_BIT(MCUCR, MCUCR_ISC01); break;
		default: Local_u8ErrorState = NOOK;											  break;
		}
		break;

	case EXTI_INT1:
		switch (Copy_u8Sense) {
		case LOW_LEVEL: 	CLR_BIT(MCUCR, MCUCR_ISC10); CLR_BIT(MCUCR, MCUCR_ISC11); break;
		case ON_CHANGE: 	SET_BIT(MCUCR, MCUCR_ISC10); CLR_BIT(MCUCR, MCUCR_ISC11); break;
		case RISING_EDGE:   SET_BIT(MCUCR, MCUCR_ISC10); SET_BIT(MCUCR, MCUCR_ISC11); break;
		case FALLING_EDGE:  CLR_BIT(MCUCR, MCUCR_ISC10); SET_BIT(MCUCR, MCUCR_ISC11); break;
		default: Local_u8ErrorState = NOOK; 										  break;
		}
		break;
	case EXTI_INT2:
		switch (Copy_u8Sense) {
		case RISING_EDGE:   SET_BIT(MCUCR, MCUCR_ISC2); break;
		case FALLING_EDGE:  CLR_BIT(MCUCR, MCUCR_ISC2); break;
		default: Local_u8ErrorState = NOOK;			    break;
		}
		break;
		default:Local_u8ErrorState = NOOK; break;

	}

	return Local_u8ErrorState;

}


u8 EXTI_u8INTSetCallBack( void (*Copy_pvCallBackFunction)(void), u8 Copy_u8IntNumber){

	u8 Local_u8ErrorState = OK ;

	if(Copy_pvCallBackFunction != NULL) {

		EXTI_pvCallBackFunction[Copy_u8IntNumber] = Copy_pvCallBackFunction;

	} else {
		Local_u8ErrorState = NULLPOINTER;
	}


	return Local_u8ErrorState;

}


u8 EXTI_u8EnableInterrupt(u8 Copy_u8IntNumber) {

	u8 Local_u8ErrorState = OK;

	switch(Copy_u8IntNumber) {
	case EXTI_INT0: SET_BIT(GICR, GICR_INT0); break;
	case EXTI_INT1: SET_BIT(GICR, GICR_INT1); break;
	case EXTI_INT2: SET_BIT(GICR, GICR_INT2); break;
	default: Local_u8ErrorState = NOOK;
	}

	return Local_u8ErrorState;



}
u8 EXTI_u8DisableInterrupt(u8 Copy_u8IntNumber) {

	    u8 Local_u8ErrorState = OK;

		switch(Copy_u8IntNumber) {
		case EXTI_INT0: CLR_BIT(GICR, GICR_INT0); break;
		case EXTI_INT1: CLR_BIT(GICR, GICR_INT1); break;
		case EXTI_INT2: CLR_BIT(GICR, GICR_INT2); break;
		default: Local_u8ErrorState = NOOK;
		}

		return Local_u8ErrorState;

}

u8 EXTI_u8INTClearFlag(u8 Copy_u8IntNumber) {

    u8 Local_u8ErrorState = OK;

	switch(Copy_u8IntNumber) {
	case EXTI_INT0: SET_BIT(GIFR, GIFR_INTF0); break;
	case EXTI_INT1: SET_BIT(GIFR, GIFR_INTF1); break;
	case EXTI_INT2: SET_BIT(GIFR, GIFR_INTF2); break;
	default: Local_u8ErrorState = NOOK;
	}

	return Local_u8ErrorState;
}


// ISR Of INT0
void __vector_1 (void)       __attribute__((signal));
void __vector_1 (void) {

	if(EXTI_pvCallBackFunction[EXTI_INT0] != NULL){

		EXTI_pvCallBackFunction[EXTI_INT0]();

	}
}

// ISR Of INT1
void __vector_2 (void)       __attribute__((signal));
void __vector_2 (void) {

	if(EXTI_pvCallBackFunction[EXTI_INT1] != NULL){

		EXTI_pvCallBackFunction[EXTI_INT1]();

	}
}

// ISR Of INT2
void __vector_3 (void)       __attribute__((signal));
void __vector_3 (void) {

	if(EXTI_pvCallBackFunction[EXTI_INT2] != NULL){

		EXTI_pvCallBackFunction[EXTI_INT2]();

	}
}

