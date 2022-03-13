/*********************************************************/
/*********************************************************/
/***********		Author: Raghad Mohamed 	**************/
/***********		Layer: MCAL			 	**************/
/***********		Component: SPI   		**************/
/**********			Date:8-10-2020          **************/
/***********		Version: 1.00		 	**************/
/*********************************************************/
/*********************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SPI_interface.h"
#include "SPI_private.h"
#include "SPI_register.h"
#include "SPI_config.h"

//Global pointer to function to hold Callback function
static void (*SPI_pvNotificationFunction) (void) = NULL;

//Global variable to hold buffer size
static u8 SPI_u8BufferSize;

//Global counter
static u8 SPI_u8Counter = 0;

//Global pointer to u8 to hold Received Data
static u8 * SPI_pu8ReceivedData = NULL;

//Global pointer to u8 to hold Sent Data
static u8 * SPI_pu8SentData = NULL;

static u8 SPI_u8State = IDLE;

void SPI_voidInit(void) {

//initialize the clock polarity
#if CLOCK_POLARITY == RISING_EDGE
	CLR_BIT(SPCR, SPCR_CPOL);

#elif CLOCK_POLARITY == FALLING_EDGE
	Set_BIT(SPCR, SPCR_CPOL);

#else
#error "Wrong clock polarity configuration"

#endif

//initialize the clock phase
#if CLOCK_PHASE == RECEIVE
	CLR_BIT(SPCR, SPCR_CPHA);

#elif CLOCK_PHASE == SEND
	SET_BIT(SPCR, SPCR_CPHA);

#else
#error "Wrong clock phase configuration"

#endif

//Select mode
#if MODE_SELECT == MASTER
   SET_BIT(SPCR, SPCR_MSTR);
//Set prescalar to divide by 16
#if PRESCALAR == DIVIDE_BY_4
	CLR_BIT(SPCR, SPCR_SPR0);
	CLR_BIT(SPCR, SPCR_SPR1);
	CLR_BIT(SPSR, SPSR_SPI2X);

#elif PRESCALAR == DIVIDE_BY_16
	SET_BIT(SPCR, SPCR_SPR0);
	CLR_BIT(SPCR, SPCR_SPR1);
CLR_BIT(SPSR, SPSR_SPI2X);

#elif PRESCALAR == DIVIDE_BY_64
CLR_BIT(SPCR, SPCR_SPR0);
SET_BIT(SPCR, SPCR_SPR1);
CLR_BIT(SPSR, SPSR_SPI2X);

#elif PRESCALAR == DIVIDE_BY_128
SET_BIT(SPCR, SPCR_SPR0);
SET_BIT(SPCR, SPCR_SPR1);
CLR_BIT(SPSR, SPSR_SPI2X);

#elif PRESCALAR == DIVIDE_BY_2
CLR_BIT(SPCR, SPCR_SPR0);
CLR_BIT(SPCR, SPCR_SPR1);
SET_BIT(SPSR, SPSR_SPI2X);

#elif PRESCALAR == DIVIDE_BY_8
SET_BIT(SPCR, SPCR_SPR0);
CLR_BIT(SPCR, SPCR_SPR1);
SET_BIT(SPSR, SPSR_SPI2X);

#elif PRESCALAR == DIVIDE_BY_32
CLR_BIT(SPCR, SPCR_SPR0);
SET_BIT(SPCR, SPCR_SPR1);
SET_BIT(SPSR, SPSR_SPI2X);

#else
#error "Wrong clock rate configuration"

#endif

#elif MODE_SELECT == SLAVE
CLR_BIT(SPCR, SPCR_MSTR);

#else
#error "Wrong mode select configuration"

#endif

//Set first bit transferred to be most significant bit
#if   DATA_ORDER == MSB
CLR_BIT(SPCR, SPCR_DORD);

#elif DATA_ORDER == LSB
SET_BIT(SPCR, SPCR_DORD);

#else
#error "Wrong data order configuration"

#endif


//Enable SPI
SET_BIT(SPCR, SPCR_SPE);

}



u8 SPI_u8Transcieve(u8 Copy_u8SentData, u8 * Copy_pu8ReceivedData) {

u8 Local_u8ErrorState = OK;
u32 Local_u32Timeout = 0;

if (Copy_pu8ReceivedData != NULL) {
	//Writing the data to the data register
	SPDR = Copy_u8SentData;

	//Polling until flag is set
	while ((GET_BIT(SPSR,SPSR_SPIF) == 0) && Local_u32Timeout < SPI_u32TIMEOUT) {
		Local_u32Timeout++;
	}

	if (GET_BIT(SPSR,SPSR_SPIF) == 1) {
		//Copy the Data Register with the received data to the variable
		*Copy_pu8ReceivedData = SPDR;
	} else {
		Local_u8ErrorState = TIMEOUT_STATE;
	}
} else {
	Local_u8ErrorState = NULLPOINTER;
}
return Local_u8ErrorState;

}

u8 SPI_u8TransceiveBufferSynchronous(u8 * Copy_pu8SentData, u8 * Copy_pu8ReceivedData, u8 Copy_u8BufferSize) {

u8 Local_u8ErrorState = OK;
u8 Local_u8Counter = 0;

if(Copy_pu8SentData != NULL && Copy_pu8ReceivedData != NULL) {

	for(Local_u8Counter = 0; Local_u8Counter < Copy_u8BufferSize; Local_u8Counter++) {

		SPI_u8Transcieve(Copy_pu8SentData[Local_u8Counter], (Copy_pu8ReceivedData + Local_u8Counter));
	}

} else {

	Local_u8ErrorState = NULLPOINTER;
}

return Local_u8ErrorState;

}

//Global interrupt must be enabled
u8 SPI_u8TransceiveBufferAsynchronous(u8 * Copy_pu8SentData, u8 * Copy_pu8ReceivedData, u8 Copy_u8BufferSize, void(*Copy_pvNotificationFunction)(void)) {

	u8 Local_u8ErrorState = OK;

	if(SPI_u8State == IDLE) {

	if(Copy_pu8SentData != NULL && Copy_pu8ReceivedData!= NULL && Copy_pvNotificationFunction != NULL) {

		//Change state to busy
		SPI_u8State = BUSY;

		//Set the callback function
		SPI_pvNotificationFunction = Copy_pvNotificationFunction;

		//Set the received data pointer
		SPI_pu8ReceivedData = Copy_pu8ReceivedData;

		//Set the sent data pointer
		SPI_pu8SentData = Copy_pu8SentData;

		//Set the buffer size
		SPI_u8BufferSize = Copy_u8BufferSize;

		//Enable the SPI interrupt
		SET_BIT(SPCR, SPCR_SPIE);

		//Write data to the SPDR and initiate communication
		SPDR = SPI_pu8SentData[SPI_u8Counter];


	} else {

		Local_u8ErrorState = NULLPOINTER;
	}

	} else {
		Local_u8ErrorState = BUSY;
	}
	return Local_u8ErrorState;

}


void __vector_12(void)			__attribute__((signal));
void __vector_12(void) {


	//Read the received data
	SPI_pu8ReceivedData[SPI_u8Counter] = SPDR;

	//Increment the counter
	SPI_u8Counter++;


	if(SPI_u8Counter == SPI_u8BufferSize ) {

		//Disable the SPI interrupt
		CLR_BIT(SPCR, SPCR_SPIE);

		//Change state to idle
		SPI_u8State = IDLE;

		//Reset the counter
		SPI_u8Counter = 0;

		//Call the Notification function
		SPI_pvNotificationFunction();

	} else {

		//Start the next communication
		SPDR = SPI_pu8SentData[SPI_u8Counter];

	}




}


