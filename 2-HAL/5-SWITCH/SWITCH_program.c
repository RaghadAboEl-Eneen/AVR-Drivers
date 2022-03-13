/******************************************************/
/******************************************************/
/**********      AUTHOR: Raghad Mohamed      **********/
/**********      Layer: HAL                  **********/
/**********      SWC: SWITCH 			     **********/
/**********      Date: 26-9-2020             **********/
/**********      Version: 1.00               **********/
/******************************************************/
/******************************************************/

#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "PORT_interface.h"

#include "SWITCH_config.h"
#include "SWITCH_interface.h"
#include "SWITCH_private.h"

u8 SWITCH_u8GetState(SWITCH_T * Copy_pSWITCH_T_Configuartion_struct) {

	u8 Local_u8ErrorState = OK;
	u8 Local_u8State;
	DIO_u8GetPinValue(Copy_pSWITCH_T_Configuartion_struct->Input_Port,
			Copy_pSWITCH_T_Configuartion_struct->Input_Pin, &Local_u8State);

	if (Copy_pSWITCH_T_Configuartion_struct != NULL) {
		if (Local_u8State == DIO_u8PIN_HIGH) {

			if (Copy_pSWITCH_T_Configuartion_struct->Type == PULLUP) {
				Local_u8State = NOT_PRESSED;
			} else if (Copy_pSWITCH_T_Configuartion_struct->Type == PULLDOWN) {
				Local_u8State = PRESSED;
			}

		} else if (Local_u8State == DIO_u8PORT_LOW) {

			if (Copy_pSWITCH_T_Configuartion_struct->Type == PULLUP) {
				Local_u8State = PRESSED;
			} else if (Copy_pSWITCH_T_Configuartion_struct->Type == PULLDOWN) {
				Local_u8State = NOT_PRESSED;
			}

		}
	} else {
		Local_u8ErrorState = NULLPOINTER;
		return Local_u8ErrorState;
	}
	return Local_u8State;

}
