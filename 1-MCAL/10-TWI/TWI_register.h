/*********************************************************/
/*********************************************************/
/***********		Author: Raghad Mohamed 	**************/
/***********		Layer: MCAL			 	**************/
/***********		Component: TWI       	**************/
/**********			Date:12-10-2020         **************/            
/***********		Version: 1.00		 	**************/
/*********************************************************/
/*********************************************************/

#ifndef TWI_REGISTER_H_
#define TWI_REGISTER_H_

#define TWBR 		*((volatile u8*)0x20)		//TWI Bit Rate Register

#define TWCR 		*((volatile u8*)0x56)		//TWI Control Register
#define TWCR_TWINT	7							//TWI Interrupt flag
#define TWCR_TWEA	6							//TWI Enable Acknowledge Bit
#define TWCR_TWSTA 	5							//TWI Start Condition Bit
#define TWCR_TWSTO	4							//TWI Stop Condition Bit
#define TWCR_TWWC	3							//TWI Write Collision Bit
#define TWCR_TWEN	2							//TWI Enable Bit
#define	TWCR_TWIE	0							//TWI Interrupt Enable

#define TWSR 		*((volatile u8*)0x21)		//TWI Status Register
#define TWSR_TWPS1	1							//TWI Prescalar Bit 1
#define TWSR_TWPS0	0							//TWI Prescalar Bit 0

#define TWDR 		*((volatile u8*)0x23)		//TWI Data Register

#define TWAR 		*((volatile u8*)0x22)		//TWI (slave) Address Register
#define TWAR_TWGCE	0							//TWI General Call Recognition Enable Bit



#endif


