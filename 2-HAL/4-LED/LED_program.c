/******************************************************/
/******************************************************/
/**********      AUTHOR: Raghad Mohamed      **********/
/**********      Layer: HAL                  **********/
/**********      SWC: LED    			     **********/
/**********      Date: 26-9-2020             **********/
/**********      Version: 1.00               **********/
/******************************************************/
/******************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "PORT_interface.h"

#include "LED_config.h"
#include "LED_interface.h"
#include "LED_private.h"

u8 LED_u8LED_ON(LED_T *Copy_LED_Config_Struct) {

	u8 Local_u8ErrorState = OK;

	if (Copy_LED_Config_Struct != NULL) {
		if (Copy_LED_Config_Struct->Type == SOURCE) {
			DIO_u8SetPinValue(Copy_LED_Config_Struct->Control_Port,
					Copy_LED_Config_Struct->Control_Pin, DIO_u8PIN_HIGH);

		} else if (Copy_LED_Config_Struct->Type == SINK) {
			DIO_u8SetPinValue(Copy_LED_Config_Struct->Control_Port,
					Copy_LED_Config_Struct->Control_Pin, DIO_u8PIN_LOW);

		} else {
			Local_u8ErrorState = NOOK;
		}
	} else {
		Local_u8ErrorState = NULLPOINTER;
	}
	return Local_u8ErrorState;
}

u8 LED_u8LED_OFF(LED_T *Copy_LED_Config_Struct) {

	u8 Local_u8ErrorState = OK;

	if (Copy_LED_Config_Struct != NULL) {
		if (Copy_LED_Config_Struct->Type == SOURCE) {
			DIO_u8SetPinValue(Copy_LED_Config_Struct->Control_Port,
					Copy_LED_Config_Struct->Control_Pin, DIO_u8PIN_LOW);

		} else if (Copy_LED_Config_Struct->Type == SINK) {
			DIO_u8SetPinValue(Copy_LED_Config_Struct->Control_Port,
					Copy_LED_Config_Struct->Control_Pin, DIO_u8PIN_HIGH);

		} else {
			Local_u8ErrorState = NOOK;
		}
	} else {
		Local_u8ErrorState = NULLPOINTER;
	}

	return Local_u8ErrorState;
}

u8 LED_u8LED_TOGGLE(LED_T *Copy_LED_Config_Struct) {

	u8 Local_u8ErrorState = OK;

	if (Copy_LED_Config_Struct != NULL) {
		DIO_u8TogglePinValue(Copy_LED_Config_Struct->Control_Port,
				Copy_LED_Config_Struct->Control_Pin);
	} else {
		Local_u8ErrorState = NULLPOINTER;
	}

	return Local_u8ErrorState;
}

