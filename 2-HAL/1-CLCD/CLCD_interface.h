/******************************************************/
/******************************************************/
/**********      AUTHOR: Raghad Mohamed      **********/
/**********      Layer: MCAL                 **********/
/**********      SWC: CLCD                   **********/
/**********      Date: 25-8-2020             **********/
/**********      Version: 1.00               **********/
/******************************************************/
/******************************************************/

#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_


void CLCD_voidSendCommand(u8 Copy_u8Command);

void CLCD_voidSendData(u8 Copy_u8Data);

void CLCD_voidInit(void);

void CLCD_voidWriteString(const char * Copy_pu8String);

void CLCD_voidSendNumber(u32 Copy_u32Number);

u8   CLCD_u8ReadAddress


#define CLCD_TURN_DISPLAY_OFF  		0b00001000
#define CLCD_TURN_DISPLAY_ON   		0b00001100
#define CLCD_CLEAR_DISPLAY     		0b00000001
#define CLCD_TURN_CURSOR_ON    		0b00001110
#define CLCD_TURN_CURSOR_OFF   		0b00001100
#define CLCD_SHIFT_CURSOR_LEFT  	0b00010000
#define CLCD_SHIFT_CURSOR_RIGHT  	0b00010100
#define CLCD_SHIFT_DISPLAY_LEFT  	0b00011000
#define CLCD_SHIFT_DISPLAY_RIGHT  	0b00011100
#define CLCD_ENTRY_MODE				0b00000101
#define CLCD_RETURN_HOME            0b00000010


#endif
