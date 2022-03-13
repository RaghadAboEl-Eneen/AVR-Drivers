/*********************************************************/
/*********************************************************/
/***********		Author: Raghad Mohamed 	**************/
/***********		Layer: HAL			 	**************/
/***********		Component: EEPROM       **************/
/**********			Date:13-10-2020         **************/            
/***********		Version: 1.00		 	**************/
/*********************************************************/
/*********************************************************/


#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_


void EEPROM_voidSendDataByte(u16 Copy_u16LocationAddress, u8 Copy_u8Data);

u8 EEPPROM_u8ReadDataByte(u16 Copy_u16LocationAddress);


#endif