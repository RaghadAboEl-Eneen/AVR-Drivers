/******************************************************/
/******************************************************/
/**********      AUTHOR: Raghad Mohamed      **********/
/**********      Layer: MCAL                 **********/
/**********      SWC: External Interrupt     **********/
/**********      Date: 14-9-2020             **********/
/**********      Version: 1.00               **********/
/******************************************************/
/******************************************************/



#ifndef EXTI_REGISTER_H_
#define EXTI_REGISTER_H_


#define MCUCR  						*((volatile u8*)0x55) 		//Micro-controller control register

#define MCUCR_ISC11					3							//INT1 sense control Bit1
#define MCUCR_ISC10					2							//INT1 sense control Bit0
#define MCUCR_ISC01					1							//INT0 sense control Bit1
#define MCUCR_ISC00					0							//INT0 sense control Bit0

#define MCUCSR 						*((volatile u8*)0x54) 		//Micro-controller control and status register
#define MCUCR_ISC2  				6							//INT2 sense control

#define GICR						*((volatile u8*)0x5B)  		//General interrupt control register 
#define GICR_INT1					7							//INT1 PIE
#define GICR_INT0					6							//INT0 PIE
#define GICR_INT2					5      						//INT2 PIE

#define GIFR 						*((volatile u8*)0x5A)		//General interrupt flag register
#define GIFR_INTF1					7							//INT1 Flag
#define GIFR_INTF0					6							//INT0 Flag
#define GIFR_INTF2					5							//INT2 Flag

#endif
