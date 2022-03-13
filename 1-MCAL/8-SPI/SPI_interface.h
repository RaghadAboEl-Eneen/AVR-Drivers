/*********************************************************/
/*********************************************************/
/***********		Author: Raghad Mohamed 	**************/
/***********		Layer: MCAL			 	**************/
/***********		Component: SPI   		**************/
/**********			Date:8-10-2020          **************/            
/***********		Version: 1.00		 	**************/
/*********************************************************/
/*********************************************************/


#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_



void SPI_voidInit(void);

u8 SPI_u8Transcieve(u8 Copy_u8SentData, u8 * Copy_pu8ReceivedData);

u8 SPI_u8TransceiveBufferSynchronous(u8 * Copy_pu8SentData, u8 * Copy_pu8ReceivedData, u8 Copy_u8BufferSize);

u8 SPI_u8TransceiveBufferAsynchronous(u8 * Copy_pu8SentData, u8 * Copy_pu8ReceivedData, u8 Copy_u8BufferSize, void(*Copy_pvNotificationFunction)(void));



#endif
