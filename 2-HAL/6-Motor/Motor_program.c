/******************************************************/
/******************************************************/
/**********      AUTHOR: Raghad Mohamed      **********/
/**********      Layer: HAL                  **********/
/**********      SWC: Motor 			     **********/
/**********      Date: 28-9-2020             **********/
/**********      Version: 1.00               **********/
/******************************************************/
/******************************************************/

#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "PORT_interface.h"


#include "Motor_interface.h"

u8 Motor_u8TurnOff(Motor_T * Copy_puMotor_T_Config) {

	u8 Local_u8ErrorState = OK;

	if (Copy_puMotor_T_Config != NULL) {

		DIO_u8SetPinValue(Copy_puMotor_T_Config->Control_Port, Copy_puMotor_T_Config->Control_PinA, DIO_u8PIN_LOW);
		DIO_u8SetPinValue(Copy_puMotor_T_Config->Control_Port, Copy_puMotor_T_Config->Control_PinB, DIO_u8PIN_LOW);

	} else {
		Local_u8ErrorState = NULLPOINTER;
	}
	return Local_u8ErrorState;

}

u8 Motor_u8RotateClockwise(Motor_T * Copy_puMotor_T_Config) {

	u8 Local_u8ErrorState = OK;

	if (Copy_puMotor_T_Config != NULL) {

		DIO_u8SetPinValue(Copy_puMotor_T_Config->Control_Port, Copy_puMotor_T_Config->Control_PinB, DIO_u8PIN_LOW);
		DIO_u8SetPinValue(Copy_puMotor_T_Config->Control_Port, Copy_puMotor_T_Config->Control_PinA, DIO_u8PIN_HIGH);

	} else {
		Local_u8ErrorState = NULLPOINTER;
	}
	return Local_u8ErrorState;

}

u8 Motor_u8RotateAntiClockwise(Motor_T  * Copy_puMotor_T_Config) {

	u8 Local_u8ErrorState = OK;

	if (Copy_puMotor_T_Config != NULL) {

		DIO_u8SetPinValue(Copy_puMotor_T_Config->Control_Port, Copy_puMotor_T_Config->Control_PinA, DIO_u8PIN_LOW);
		DIO_u8SetPinValue(Copy_puMotor_T_Config->Control_Port, Copy_puMotor_T_Config->Control_PinB, DIO_u8PIN_HIGH);

	} else {
		Local_u8ErrorState = NULLPOINTER;
	}
	return Local_u8ErrorState;

}

