/*********************************************************/
/*********************************************************/
/***********		Author: Raghad Mohamed 	**************/
/***********		Layer: MCAL			 	**************/
/***********		Component: USART 		**************/
/**********			Date: 5-10-2020         **************/            
/***********		Version: 1.00		 	**************/
/*********************************************************/
/*********************************************************/

#ifndef USART_CONFIG_H_
#define USART_CONFIG_H_


#define USART_u32TIMEOUT	10000000UL



/*Character Size Selection:
 * Options: 1-FIVE_BITS
 * 			2-SIX_BITS
 * 			3-SEVEN_BITS
 * 			4-EIGHT_BITS
 * 			5-NINE_BITS
 **/
#define CHARACTER_SIZE     EIGHT_BITS

#define RECEIVER_STATE	   ENABLED
#define TRANSMITTER_STATE  ENABLED


/*USART Mode Selection:
 * Options: 1-SYNCHRONOUS
 * 			2-ASYNCHRONOUS
 **/
#define MODE_SELECT		ASYNCHRONOUS


/*Parity Mode Selection:
 * Options: 1-DISABLED
 * 			2-EVEN_PARITY
 * 			3-ODD_PARITY
 **/
#define PARITY_MODE		DISABLED

/*Stop Bit Selection:
 * Options: 1-ONE_BIT
 * 			2-TWO_BITS
 **/
#define STOP_BITS	ONE_BIT

/*Clock Polarity Selection: (Synchronous mode only)
 * Options: 1-FALLING_EDGE
 * 			Transmit data at falling edge and receive data at rising edge.
 * 			2-RISING_EDGE
 * 			Transmit data at rising  edge and receive data at falling edge.
 **/
#define CLOCK_POLARITY RISING_EDGE

//Baud rate selection in bps(bits per second)
#define BAUD_RATE 9600UL



/*When enabled selected transmission speed (baud rate) will be doubled
 * Options:1-ENABLED
 * 		   2-DISABLED
 **/
#define DOUBLE_TRANSMISSION_SPEED DISABLED

#endif
