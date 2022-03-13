/******************************************************/
/******************************************************/
/**********      AUTHOR: Raghad Mohamed      **********/
/**********      Layer: HAL                  **********/
/**********      SWC: SWITCH 			     **********/
/**********      Date: 26-9-2020             **********/
/**********      Version: 1.00               **********/
/******************************************************/
/******************************************************/


#ifndef SWITCH_INTERFACE_H_
#define SWITCH_INTERFACE_H_

#define PULLDOWN 		0
#define PULLUP 			1

#define PRESSED			2
#define NOT_PRESSED		3

typedef struct{

	u8 Type;
	u8 Input_Port;
	u8 Input_Pin;

}SWITCH_T;





u8 SWITCH_u8GetState(SWITCH_T * Copy_pSWITCH_T_Configuartion_struct);

#endif
