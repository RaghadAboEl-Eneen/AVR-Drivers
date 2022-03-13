/*********************************************************/
/*********************************************************/
/***********		Author: Raghad Mohamed 	**************/
/***********		Layer: HAL			 	**************/
/***********		Component: EEPROM       **************/
/**********			Date:13-10-2020         **************/
/***********		Version: 1.00		 	**************/
/*********************************************************/
/*********************************************************/

#include <util/delay.h>

#include "STD_TYPES.h"

#include "TWI_interface.h"

#include "EEPROM_interface.h"
#include "EEPROM_private.h"
#include "EEPROM_config.h"

void EEPROM_voidSendDataByte(u16 Copy_u16LocationAddress, u8 Copy_u8Data) {

	u8 Local_u8AddressPacket;

	Local_u8AddressPacket = EEPROM_FIXED_ADDRESS | A2_CONNECTION << 2 | Copy_u16LocationAddress >> 8;

	//Send start condition
	TWI_SendStartCondition();

	//Send the Address packet
	TWI_SendSlaveAddressWithWrite(Local_u8AddressPacket);

	//Send the rest 8bits of the location address
	TWI_MasterWriteDataByte((u8) (Copy_u16LocationAddress));

	//Send the data byte to the memory location
	TWI_MasterWriteDataByte(Copy_u8Data);

	//Send stop condition
	TWI_SendStopCondition();

	//Delay until the write cycle is finished
	_delay_ms(10);

}

u8 EEPPROM_u8ReadDataByte(u16 Copy_u16LocationAddress) {

	u8 Local_u8Data;

	u8 Local_u8AddressPacket;

	Local_u8AddressPacket = EEPROM_FIXED_ADDRESS | A2_CONNECTION << 2 | Copy_u16LocationAddress >> 8;

	//Send start condition
	TWI_SendStartCondition();

	//Send the Address packet with write request
	TWI_SendSlaveAddressWithWrite(Local_u8AddressPacket);

	//Send the rest 8bits of the location address
	TWI_MasterWriteDataByte((u8) (Copy_u16LocationAddress));

	//Send repeated start to change write request to read request
	TWI_SendRepeatedStart();

	//Send the same address packet with read request
	TWI_SendSlaveAddressWithRead(Local_u8AddressPacket);

	//Get the data from memory
	TWI_MasterReadDataByte(&Local_u8Data);

	//Send stop condition
	TWI_SendStopCondition();

	return Local_u8Data;



	return Local_u8Data;
}

