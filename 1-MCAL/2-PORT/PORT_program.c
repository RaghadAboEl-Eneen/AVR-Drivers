/******************************************************/
/******************************************************/
/**********      AUTHOR: Raghad Mohamed      **********/
/**********      Layer: MCAL                 **********/
/**********      SWC: PORT                   **********/
/**********      Date: 31-8-2020             **********/
/**********      Version: 1.00               **********/
/******************************************************/
/******************************************************/


#include "STD_TYPES.h"

#include "PORT_config.h"
#include "PORT_private.h"
#include "Port_register.h"
#include "Port_interface.h"


void PORT_voidInit(void) {
	DDRA = PORTA_DIR;
	DDRB = PORTB_DIR;
	DDRC = PORTC_DIR;
	DDRD = PORTD_DIR;
	
	PORTA = PORTA_INITIAL_VALUE;
	PORTB = PORTB_INITIAL_VALUE;
	PORTC = PORTC_INITIAL_VALUE;
	PORTD = PORTD_INITIAL_VALUE;
	
}
