/******************************************************/
/******************************************************/
/**********      AUTHOR: Raghad Mohamed      **********/
/**********      Layer: MCAL                 **********/
/**********      SWC: External Interrupt     **********/
/**********      Date: 14-9-2020             **********/
/**********      Version: 1.00               **********/
/******************************************************/
/******************************************************/



#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

/* INT == Interrupt
 * INT0 PORTD PIN2
 * INT1 PORTD PIN3
 * INT2 PORTB PIN2 */

#define EXTI_INT0	0
#define EXTI_INT1	1
#define EXTI_INT2	2



#define LOW_LEVEL		1
#define ON_CHANGE 		2
#define FALLING_EDGE	3
#define RISING_EDGE		4

void EXTI_voidINT0Init(void);
void EXTI_voidINT1Init(void);
void EXTI_voidINT2Init(void);



/* Description: The function sets the required sense control for the available 3 external interrupts
 * Inputs: 1- Copy_u8Sense : This is the required sense control
 * 		   Options: 1- LOW_LEVEL
 * 	 	 	 	 	2- ON_CHANGE
 *	 	 	 	 	3- FALLING_EDGE
 *	 	 	 	 	4- RISING_EDGE
 *         2- Copy_u8IntNumber: The Interrupt number required to set sense control
 *         Options: 1- EXTI_INT0
 *          	   	   	2- EXTI_INT1
 *          	   	   	3- EXTI_INT2`
 *  Outputs: Error State: To indicate that the function worked correctly
 *	 	   Options: 1- OK
 *	 	     		2- NOK
 *	 	 	 	 	*/
u8 EXTI_u8INTSetSenseControl(u8 Copy_u8Sense, u8 Copy_u8IntNumber);

u8 EXTI_u8EnableInterrupt(u8 Copy_u8IntNumber);
u8 EXTI_u8DisableInterrupt(u8 Copy_u8IntNumber);

u8 EXTI_u8INTSetCallBack( void (*Copy_pvCallBackFunction)(void), u8 Copy_u8IntNumber);

u8 EXTI_u8INTClearFlag(u8 Copy_u8IntNumber);


#endif
