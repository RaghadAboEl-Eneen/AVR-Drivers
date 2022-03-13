/******************************************************/
/******************************************************/
/**********      AUTHOR: Raghad Mohamed      **********/
/**********      Layer: MCAL                 **********/
/**********      SWC: External Interrupt     **********/
/**********      Date: 14-9-2020             **********/
/**********      Version: 1.00               **********/
/******************************************************/
/******************************************************/

#ifndef EXTI_CONFIG_H_
#define EXTI_CONFIG_H_

// Choose INT0 Sense control (trigger)
// Options: 1- LOW_LEVEL
//			2- ON_CHANGE
//			3- FALLING_EDGE
//  		4- RISING_EDGE
#define EXTI_INT0_SENSE  	RISING_EDGE

// Choose INT0 Sense control (trigger)
// Options: 1- LOW_LEVEL
//			2- ON_CHANGE
//			3- FALLING_EDGE
//  		4- RISING_EDGE
#define EXTI_INT1_SENSE 	RISING_EDGE


// Choose INT0 Sense control (trigger)
// Options: 1- FALLING_EDGE
//  		2- RISING_EDGE
#define EXTI_INT2_SENSE     RISING_EDGE

// Choose INT0, INT1 and INT2 peripherals interrupt enable initial state
// Options: 1- ENABLED
//			2- DISABLED
#define EXTI_INT0_INITIAL_STATE		ENABLED
#define EXTI_INT1_INITIAL_STATE		ENABLED
#define EXTI_INT2_INITIAL_STATE		ENABLED


#endif
