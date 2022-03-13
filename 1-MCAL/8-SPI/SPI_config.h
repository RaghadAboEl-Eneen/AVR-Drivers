/*********************************************************/
/*********************************************************/
/***********		Author: Raghad Mohamed 	**************/
/***********		Layer: MCAL			 	**************/
/***********		Component: SPI   		**************/
/**********			Date:8-10-2020          **************/            
/***********		Version: 1.00		 	**************/
/*********************************************************/
/*********************************************************/

#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

#define SPI_u32TIMEOUT		10000000UL

/*Data order Selection
 * Options:1-MSB (Most significant bit)
 * 		   2-LSB (Least significant bit)
 **/
#define DATA_ORDER		MSB


/*Clock polarity Selection
 * Options:1-leading edge is RISING_EDGE
 * 		   3-leading edge is FALLING_EDGE
 **/
#define CLOCK_POLARITY	RISING_EDGE


/*Clock phase Selection
 * Options:1-RECEIVE at leading edge
 * 		   2-SEND at leading edge
 **/
#define CLOCK_PHASE		RECEIVE


/*Prescalar configuration
 *Final rate is Fosc/prescalar
 * Options: 1- DIVIDE_BY_2
 * 			2- DIVIDE_BY_4
 * 			3- DIVIDE_BY_8
 * 			4- DIVIDE_BY_16
 * 			5- DIVIDE_BY_32
 * 			6- DIVIDE_BY_64
 *			7- DIVIDE_BY_128
 **/
#define PRESCALAR	DIVIDE_BY_16

/*Mode selection
 * Options:1-MASTER
 * 		   2-SLAVE
 **/
#define MODE_SELECT	MASTER


#endif
