/*****************************************************************/
/*****************************************************************/
/********************		Author: Raghad Mohamed	**************/
/********************		Layer: MCAL				**************/
/********************		SWC: ADC				**************/
/********************		Version: 1.00			**************/
/********************		Date: 17-9-2020			**************/
/*****************************************************************/
/*****************************************************************/

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

typedef struct {
	u8 NumberOfConversions;
	u16 * Results;
	u8 * Channels;
	void (*NotificationFunction)(void);
} Chain_T;

void ADC_voidInit(void);

u8 ADC_u8StartSingleConversionSynch(u8 Copy_u8Channel, u16* Copy_pu16Result);

/*
 *
 * Preconditions: Enable the global interrupt before calling this function*/
u8 ADC_u8StartSingleConversionAsynch(u8 Copy_u8Channel, u16* Copy_pu16Result, void (*Copy_pvNotificationFunc)(void));

u8 ADC_u8StartChainConversionASynch(Chain_T * Copy_Chain);

#endif
