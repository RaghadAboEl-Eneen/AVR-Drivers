/*********************************************************/
/*********************************************************/
/***********		Author: Raghad Mohamed 	**************/
/***********		Layer: MCAL			 	**************/
/***********		Component: USART 		**************/
/**********			Date: 5-10-2020         **************/
/***********		Version: 1.00		 	**************/
/*********************************************************/
/*********************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "USART_interface.h"
#include "USART_private.h"
#include "USART_register.h"
#include "USART_config.h"

//Global pointer to function to hold the transmit complete callback function
static void (*USART_pvTransmitCompleteCallBackFunction)(void) = NULL;

//Global pointer to function to hold the Receive complete callback function
static void (*USART_pvReceiveCompleteCallBackFunction)(void) = NULL;

//Global pointer to character to hold the transmitted string
static const char * USART_pchString = NULL;

//Global pointer to u8 to hold received data
static u8 * USART_pu8ReceivedData = NULL;

//Global variable u8  to hold buffer size
static u8 USART_u8BufferSize = 0;

//Global counter
static u16 USART_u16Counter = 0;

void USART_voidInit(void) {

	//Local variable to hold the UCSRC register value
	u8 Local_u8UCSRCValue = 0;

	//Local variable to hold the UBBR register value
	u16 Local_u16UBBRValue = 0;

	//Local variable to hold the UBBRH register value
	u8 Local_u8UBBRHValue = 0;

	//Select the UCSRC register
	SET_BIT(Local_u8UCSRCValue, UCSRC_URSEL);

//Mode Selection
#if   MODE_SELECT == SYNCHRONOUS
	SET_BIT(Local_u8UCSRCValue,UCSRC_UMSEL);

#elif MODE_SELECT == ASYNCHRONOUS
	CLR_BIT(Local_u8UCSRCValue, UCSRC_UMSEL);

#else
#error "Wrong Mode Select Configuration"

#endif

//Parity Mode Selection
#if   PARITY_MODE == DISABLED
	CLR_BIT(Local_u8UCSRCValue, UCSRC_UPM0);
	CLR_BIT(Local_u8UCSRCValue, UCSRC_UPM1);

#elif PARITY_MODE == EVEN_PARITY
	CLR_BIT(Local_u8UCSRCValue, UCSRC_UPM0);
	SET_BIT(Local_u8UCSRCValue, UCSRC_UPM1);

#elif PARITY_MODE == ODD_PARITY
	SET_BIT(Local_u8UCSRCValue, UCSRC_UPM0);
	SET_BIT(Local_u8UCSRCValue, UCSRC_UPM1);

#else
#error "Wrong Parity Mode Configuration"

#endif

//Stop Bits Selection
#if   STOP_BITS == ONE_BIT
	CLR_BIT(Local_u8UCSRCValue, UCSRC_USBS);

#elif STOP_BITS == TWO_BITS
	SET_BIT(Local_u8UCSRCValue, UCSRC_USBS);

#else
#error "Wrong Stop Bits Configuration"

#endif

//Character size : 8 bits
#if   CHARACTER_SIZE == FIVE_BITS
	CLR_BIT(Local_u8UCSRCValue, UCSRC_UCSZ0);
	CLR_BIT(Local_u8UCSRCValue, UCSRC_UCSZ1);
	CLR_BIT(UCSRB, UCSRB_UCSZ2);

#elif CHARACTER_SIZE == SIX_BITS
	SET_BIT(Local_u8UCSRCValue, UCSRC_UCSZ0);
	CLR_BIT(Local_u8UCSRCValue, UCSRC_UCSZ1);
	CLR_BIT(UCSRB, UCSRB_UCSZ2);

#elif CHARACTER_SIZE == SEVEN_BITS
	CLR_BIT(Local_u8UCSRCValue, UCSRC_UCSZ0);
	SET_BIT(Local_u8UCSRCValue, UCSRC_UCSZ1);
	CLR_BIT(UCSRB, UCSRB_UCSZ2);

#elif CHARACTER_SIZE == EIGHT_BITS
	SET_BIT(Local_u8UCSRCValue, UCSRC_UCSZ0);
	SET_BIT(Local_u8UCSRCValue, UCSRC_UCSZ1);
	CLR_BIT(UCSRB, UCSRB_UCSZ2);

#elif CHARACTER_SIZE == NINE_BITS
	SET_BIT(Local_u8UCSRCValue, UCSRC_UCSZ0);
	SET_BIT(Local_u8UCSRCValue, UCSRC_UCSZ1);
	SET_BIT(UCSRB, UCSRB_UCSZ2);

#else
#error "Wrong Bit Size Configuration"

#endif

//Clock Polarity Selection (Synchronous mode only)
#if MODE_SELECT == SYNCHRONOUS

#if   CLOCK_POLARITY == RISING_EDGE
	CLR_BIT(Local_u8UCSRCValue, UCSRC_UCPOL);

#elif CLOCK_POLARITY == FALLING_EDGE
	SET_BIT(Local_u8UCSRCValue, UCSRC_UCPOL);

#else
#error "Wrong Clock Polarity Configuration"

#endif

#endif

//Assigning the UCSRC value in one operation
	UCSRC = Local_u8UCSRCValue;

#if MODE_SELECT == ASYNCHRONOUS

#if DOUBLE_TRANSMISSION_SPEED == ENABLED
	Local_u16UBBRValue = (u16) (10000000UL / (8UL * (u32) BAUD_RATE)) - 1;

#elif DOUBLE_TRANSMISSION_SPEED == DISABLED
	Local_u16UBBRValue = ((u16) (10000000UL / (u32) (16UL * BAUD_RATE))) - 1;

#else
#error "Wrong double transmission speed configuration"

#endif

#elif MODE_SELECT == SYNCHRONOUS
	Local_u16UBBRValue = (u16)(10000000UL / (2UL * (u32)BAUD_RATE)) - 1;

#endif

	//Selecting the UBRRH Register
	CLR_BIT(Local_u8UBBRHValue, UBRRH_URSEL);

	if (Local_u16UBBRValue >= 2048) {
		SET_BIT(Local_u8UBBRHValue, 3);
		Local_u16UBBRValue -= 2048;
	}
	if (Local_u16UBBRValue >= 1024) {
		SET_BIT(Local_u8UBBRHValue, 2);
		Local_u16UBBRValue -= 1024;
	}
	if (Local_u16UBBRValue >= 512) {
		SET_BIT(Local_u8UBBRHValue, 1);
		Local_u16UBBRValue -= 512;
	}
	if (Local_u16UBBRValue >= 256) {
		SET_BIT(Local_u8UBBRHValue, 0);
		Local_u16UBBRValue -= 256;
	}

	//Assigning the UBRRH value in one operation
	UBRRH = Local_u8UBBRHValue;
	UBRRL = Local_u16UBBRValue;

//baud rate setting to 9600 bps
//UBRRL = 64;

//Receiver Enable
#if RECEIVER_STATE == ENABLED
	SET_BIT(UCSRB, UCSRB_RXEN);

#elif RECEIVER_STATE == DISABLED
	CLR_BIT(UCSRB, UCSRB_RXEN);

#else
#error "Wrong Receiver State Configuration"

#endif

//Transmitter enable
#if TRANSMITTER_STATE == ENABLED
	SET_BIT(UCSRB, UCSRB_TXEN);

#elif TRANSMITTER_STATE == DISABLED
	CLR_BIT(UCSRB, UCSRB_TXEN);

#else
#error "Wrong Transmitter State Configuration"

#endif

}

u8 USART_u8SendData(u8 Copy_u8Data) {

	u8 Local_u8ErrorState = OK;
	u32 Local_32TimeoutCounter = 0;

	//wait until the transmitter buffer is empty
	while (GET_BIT(UCSRA, UCSRA_UDRE) == 0 && Local_32TimeoutCounter < USART_u32TIMEOUT) {
		Local_32TimeoutCounter++;
	}

	if (GET_BIT(UCSRA, UCSRA_UDRE) == 1) {
		UDR = Copy_u8Data;

	} else {
		Local_u8ErrorState = TIMEOUT_STATE;
	}
	return Local_u8ErrorState;

}

u8 USART_u8RecieveData(u8 * Copy_pu8Data) {

	u8 Local_u8ErrorState = OK;
	u32 Local_u32TimeoutCounter = 0;

	//wait until the receive complete event happens
	while ((GET_BIT(UCSRA, UCSRA_RXC) == 0) && (Local_u32TimeoutCounter < USART_u32TIMEOUT)) {
		Local_u32TimeoutCounter++;
	}

	if (GET_BIT(UCSRA, UCSRA_RXC) == 1) {
		*Copy_pu8Data = UDR;
	} else {
		Local_u8ErrorState = TIMEOUT_STATE;

	}

	return Local_u8ErrorState;

}

u8 USART_u8SendStringSynchronous(const char * Copy_pchString) {

	u8 Local_u8ErrorState = OK;
	u32 Local_u32TimeoutCounter = 0;
	u16 Local_u16Counter = 0;

	while (Copy_pchString[Local_u16Counter] != '\0') {

		//Polling until UDRE (data register empty) flag is Set or timeout is reached
		while ((GET_BIT(UCSRA,UCSRA_UDRE) == 0) && (Local_u32TimeoutCounter < USART_u32TIMEOUT)) {
			Local_u32TimeoutCounter++;
		}

		if (GET_BIT(UCSRA,UCSRA_UDRE) == 1) {
			//Resetting the timeout counter
			Local_u32TimeoutCounter = 0;

			//Sending the current character
			UDR = Copy_pchString[Local_u16Counter];

			//Increment the counter
			Local_u16Counter++;
		} else {
			Local_u8ErrorState = TIMEOUT_STATE;
			break;
		}

	}

	return Local_u8ErrorState;

}

//Global interrupt must be enabled
u8 USART_u8SendStringAsynchronous(const char * Copy_pchString, void (*Copy_pvNotificationFunction)(void)) {

	u8 Local_u8ErrorState = OK;

	if (Copy_pvNotificationFunction != NULL && Copy_pchString != NULL) {

		//Set the Callback function
		USART_pvTransmitCompleteCallBackFunction = Copy_pvNotificationFunction;

		//Set the Global pointer to string
		USART_pchString = Copy_pchString;

		//Enable the Register Empty Interrupt;
		SET_BIT(UCSRB, UCSRB_UDRIE);

	} else {
		Local_u8ErrorState = NULLPOINTER;
	}

	return Local_u8ErrorState;

}

u8 USART_u8ReceiveBufferSynchronous(u8 * Copy_pu8Data, u8 Copy_u8BufferSize) {

	u8 Local_u8ErrorState = OK;
	u32 Local_32TimeoutCounter = 0;
	u8 Local_u8Counter = 0;

	if (Copy_pu8Data != NULL) {

		for (Local_u8Counter = 0; Local_u8Counter < Copy_u8BufferSize; Local_u8Counter++) {

			//polling until data is received or timeout reached
			while ( (GET_BIT(UCSRA, UCSRA_RXC) == 0) && (Local_32TimeoutCounter < USART_u32TIMEOUT) ) {
				Local_32TimeoutCounter++;
			}

			if (GET_BIT(UCSRA, UCSRA_RXC) == 1) {

				//Receive the data
				*(Copy_pu8Data + Local_u8Counter) = UDR;

			} else {
				Local_u8ErrorState = TIMEOUT_STATE;
				break;
			}

		}

	} else {
		Local_u8ErrorState = NULLPOINTER;
	}

	return Local_u8ErrorState;

}

u8 USART_u8ReceiveBufferAsynchronous(u8 * Copy_pu8Data, u8 Copy_u8BufferSize, void (*Copy_pvNotificationFunction)(void)) {
	u8 Local_u8ErrorState = OK;


	if(Copy_pu8Data != NULL && Copy_pvNotificationFunction != NULL) {

		//Setting the callback function
		USART_pvReceiveCompleteCallBackFunction = Copy_pvNotificationFunction;

		//Setting the buffer size
		USART_u8BufferSize = Copy_u8BufferSize;

		//Setting the pointer to data
		USART_pu8ReceivedData = Copy_pu8Data;

		//Enable the Receive Complete interrupt
		SET_BIT(UCSRB,UCSRB_RXCIE);
	} else {
		Local_u8ErrorState = NULLPOINTER;
	}




	return Local_u8ErrorState;

}

//Receive Complete interrupt
void __vector_13(void) __attribute__((signal));
void __vector_13(void) {

	//Reading the data
	*(USART_pu8ReceivedData + USART_u16Counter) = UDR;

	//Incrementing the counter
	USART_u16Counter++;

	if(USART_u16Counter == USART_u8BufferSize) {

		//Reset the counter
		USART_u16Counter = 0;

		//Disable the receive complete interrupt
		CLR_BIT(UCSRB,UCSRB_RXCIE);

		//Call the receive complete callback function
		USART_pvReceiveCompleteCallBackFunction();

	} else {

		/*Do nothing*/

	}



}

//Data Register Empty Interrupt
void __vector_14(void) __attribute__((signal));
void __vector_14(void) {

	//Send the character
	UDR = USART_pchString[USART_u16Counter];

	//Increment the counter
	USART_u16Counter++;

	if (USART_pchString[USART_u16Counter] == '\0') {

		//Reset the counter
		USART_u16Counter = 0;

		//Disable the register empty interrupt
		CLR_BIT(UCSRB, UCSRB_UDRIE);

		//Call the Transmit complete back function
		USART_pvTransmitCompleteCallBackFunction();

	} else {

		/*Do nothing*/
	}

}

//Transmit Complete Interrupt
void __vector_15(void) __attribute__((signal));
void __vector_15(void) {

}

