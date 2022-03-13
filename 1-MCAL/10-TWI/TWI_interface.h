/*********************************************************/
/*********************************************************/
/***********		Author: Raghad Mohamed 	**************/
/***********		Layer: MCAL			 	**************/
/***********		Component: TWI       	**************/
/**********			Date:12-10-2020         **************/            
/***********		Version: 1.00		 	**************/
/*********************************************************/
/*********************************************************/

#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_

typedef enum {
	
	NoError,
	StartConditionError,
	RepeatedStartError,
	SlaveAddressWithWriteError,
	SlaveAddressWithReadError,
	MasterWriteByteError,
	MasterReadByteError,
	
}TWI_ErrorStatus;

#define NO_ADDRESS	0


//Set master address to NO_ADDRESS if master will not be addressed
void TWI_voidInitMaster(u8 Copy_u8MasterAddress);

void TWI_voidInitSlave(u8 Copy_u8Address);

TWI_ErrorStatus TWI_SendStartCondition(void);

TWI_ErrorStatus TWI_SendRepeatedStart(void);

TWI_ErrorStatus TWI_SendSlaveAddressWithWrite(u8 Copu_u8SlaveAddress);

TWI_ErrorStatus TWI_SendSlaveAddressWithRead(u8 Copu_u8SlaveAddress);

TWI_ErrorStatus TWI_MasterWriteDataByte(u8 Copy_u8DataByte);

TWI_ErrorStatus TWI_MasterReadDataByte(u8 * Copy_pu8DataByte);

void TWI_SendStopCondition(void);

#endif	
