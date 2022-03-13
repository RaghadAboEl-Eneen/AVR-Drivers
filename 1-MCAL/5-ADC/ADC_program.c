/*****************************************************************/
/*****************************************************************/
/********************		Author: Raghad Mohamed	**************/
/********************		Layer: MCAL				**************/
/********************		SWC: ADC				**************/
/********************		Version: 1.00			**************/
/********************		Date: 17-9-2020			**************/
/*****************************************************************/
/*****************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_register.h"
#include "ADC_config.h"

/*Global pointer to carry the conversion result in the asynchronous execution*/
static u16* ADC_pu16ConversionResult = NULL;

/*Global pointer to function to carry the notification function called by ISR*/
static void (*ADC_pvNotificationFunc)(void) = NULL;

/*Global flag to indicate for the ADC busy state*/
static u8 ADC_u8State = IDLE;

static u8 ADC_u8Counter = 0;

static u8 ADC_u8ChainConversionFlag = NOT_WORKING;

static u8 ADC_u8NumberOfConversions;

static u8* ADC_pu8NeededChannels = NULL;

void ADC_voidInit(void) {
	/*Select AVCC reference voltage*/
	SET_BIT(ADMUX, ADMUX_REFS0);
	CLR_BIT(ADMUX, ADMUX_REFS1);

	/*Activate Left adjust result(8 bit resolution)*/
	SET_BIT(ADMUX, ADMUX_ADLAR);

	ADCSRA &= 0b11111000; /*Clear first 3 bits in adcsra register*/
	ADCSRA |= ADC_u8PRESCALER; /*set the required configuration*/

	/*Enable ADC peripheral*/
	SET_BIT(ADCSRA, ADCSRA_ADEN);
}

u8 ADC_u8StartSingleConversionSynch(u8 Copy_u8Channel, u16* Copy_pu16Result) {

	u32 Local_u32Counter = 0;
	u8 Local_u8ErrorState = OK;

	if (Copy_pu16Result != NULL) {
		if (ADC_u8State == IDLE) {
			/*ADC is now busy*/
			ADC_u8State = BUSY;

			/*Clear first 5 bits in ADMUX register*/
			ADMUX &= 0b11100000;

			/*set required channel*/
			ADMUX |= Copy_u8Channel;

			/*Start conversion*/
			SET_BIT(ADCSRA, ADCSRA_ADSC);

			/*Busy waiting (polling) until the conversion is complete or until timeout is reached*/
			while (((GET_BIT(ADCSRA, ADCSRA_ADIF)) == 0) && (Local_u32Counter < ADC_u32TIMEOUT)) {
				Local_u32Counter++;
			}
			if (Local_u32Counter == ADC_u32TIMEOUT) {
				/*Loop is broken because timeout is reached*/
				Local_u8ErrorState = TIMEOUT_STATE;
			} else {
				/*Loop is broken because flag is raised*/
				/*clear the interrupt flag*/
				SET_BIT(ADCSRA, ADCSRA_ADIF);

				*Copy_pu16Result = ADCH;
			}
			/*ADC is finished and is now Idle*/
			ADC_u8State = IDLE;
		} else {
			Local_u8ErrorState = BUSY_STATE;
		}
	} else {
		Local_u8ErrorState = NULLPOINTER;
	}

	return Local_u8ErrorState;
}

u8 ADC_u8StartSingleConversionAsynch(u8 Copy_u8Channel, u16* Copy_pu16Result, void (*Copy_pvNotificationFunc)(void)) {
	u8 Local_u8ErrosState = OK;

	if ((Copy_pu16Result != NULL) && (Copy_pvNotificationFunc != NULL)) {
		if (ADC_u8State == IDLE) {
			/*ADC is now busy*/
			ADC_u8State = BUSY;

			/*Initialize the global result pointer*/
			ADC_pu16ConversionResult = Copy_pu16Result;

			/*Initialize the global notification function pointer*/
			ADC_pvNotificationFunc = Copy_pvNotificationFunc;

			/*Clear first 5 bits in ADMUX register*/
			ADMUX &= ADC_u8CHANNEL_MASK;

			/*set required channel*/
			ADMUX |= Copy_u8Channel;

			/*Start the conversion*/
			SET_BIT(ADCSRA, ADCSRA_ADSC);

			/*ADC conversion complete interrupt enable*/
			SET_BIT(ADCSRA, ADCSRA_ADIE);
		} else {
			Local_u8ErrosState = BUSY_STATE;
		}
	} else {
		Local_u8ErrosState = NULLPOINTER;
	}

	return Local_u8ErrosState;
}

u8 ADC_u8StartChainConversionASynch(Chain_T * Copy_Chain) {
	u8 Local_u8ErrorState = OK;

	ADC_u8NumberOfConversions = Copy_Chain->NumberOfConversions;

	/*Chain conversion now starts*/
	ADC_u8ChainConversionFlag = WORKING;

	if (Copy_Chain != NULL) {

		if ((Copy_Chain->Results != NULL) && (Copy_Chain->NotificationFunction != NULL) && (Copy_Chain->Channels != NULL)) {

			if (ADC_u8State == IDLE) {

				/*ADC is now busy*/
				ADC_u8State = BUSY;

				/*Initialize the global result pointer*/
				ADC_pu16ConversionResult = Copy_Chain->Results;

				/*Initialize the global notification  function pointer*/
				ADC_pvNotificationFunc = Copy_Chain->NotificationFunction;

				/*Initialize the global pointer of channels*/
				ADC_pu8NeededChannels = Copy_Chain->Channels;

				//Clear first 5 bits  in ADMUX register
				ADMUX &= ADC_u8CHANNEL_MASK;

				/*Set required channel*/
				ADMUX |= Copy_Chain->Channels[ADC_u8Counter];

				/*Start conversion*/
				SET_BIT(ADCSRA, ADCSRA_ADSC);

				/*ADC conversion complete  interrupt enable*/
				SET_BIT(ADCSRA, ADCSRA_ADIE);
			} else {
				Local_u8ErrorState = BUSY_STATE;
			}

		} else {
			Local_u8ErrorState = NULLPOINTER;
		}

	} else {
		Local_u8ErrorState = NULLPOINTER;
	}

	return Local_u8ErrorState;
}

void __vector_16(void) __attribute__((signal));
void __vector_16(void)

{
	if (ADC_u8ChainConversionFlag == NOT_WORKING) {

		/*Read the result*/
		*ADC_pu16ConversionResult = ADCH;

		/*ADC is now idle*/
		ADC_u8State = IDLE;

		/*Invoke the callback notification function*/
		ADC_pvNotificationFunc();

		/*Disable the ADC conversion complete interrupt*/
		CLR_BIT(ADCSRA, ADCSRA_ADIE);

	} else if (ADC_u8ChainConversionFlag == WORKING) {

		/*Read the result*/
		ADC_pu16ConversionResult[ADC_u8Counter] = ADCH;

		if (ADC_u8Counter == (ADC_u8NumberOfConversions - 1)) {
			/*Disable the ADC conversion complete interrupt*/
			CLR_BIT(ADCSRA, ADCSRA_ADIE);

			//ADC is now idle
			ADC_u8State = IDLE;

			//Reset the counter
			ADC_u8Counter = 0;

			//Disable the chain conversion flag
			ADC_u8ChainConversionFlag = NOT_WORKING;

			//Invoke the callback notification function
			ADC_pvNotificationFunc();

		} else {
			//Increment the chain conversion counter
			ADC_u8Counter += 1;

			//Clear first 5 bits  in ADMUX register
			ADMUX &= ADC_u8CHANNEL_MASK;

			/*Set required channel*/
			ADMUX |= ADC_pu8NeededChannels[ADC_u8Counter];

			/*Start conversion*/
			SET_BIT(ADCSRA, ADCSRA_ADSC);

		}

	}

}

