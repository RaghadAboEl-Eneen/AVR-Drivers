/*********************************************************/
/*********************************************************/
/***********		Author: Raghad Mohamed 	**************/
/***********		Layer: MCAL			 	**************/
/***********		Component: WATCHDOG   	**************/
/**********			Date:11-10-2020         **************/            
/***********		Version: 1.00		 	**************/
/*********************************************************/
/*********************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "WATCH_DOG_interface.h"
#include "WATCH_DOG_register.h"
#include "WATCH_DOG_private.h"
#include "WATCH_DOG_config.h"



void WDT_voidEnable() {

	SET_BIT(WDTCR, WDTCR_WDE);


}

void WDT_voidDisable() {

	WDTCR |= (1<<WDTCR_WDE) | (1<<WDTCR_WDTOE); // Both WDE and WDTOE must be set in the same operation so it works

	WDTCR  = 0;

}

u8 WDT_u8Sleep(u8 Copy_u8Sleep) {


	u8 Local_u8ErrorState = OK;

	if(Copy_u8Sleep < 8 ) {

		WDTCR &= 0b11111000;
		WDTCR = Copy_u8Sleep;


	} else {
		Local_u8ErrorState = NOOK;
	}

	return Local_u8ErrorState;
}



