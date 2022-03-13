/******************************************************/
/******************************************************/
/**********      AUTHOR: Raghad Mohamed      **********/
/**********      Layer: HAL                  **********/
/**********      SWC: LED    			     **********/
/**********      Date: 26-9-2020             **********/
/**********      Version: 1.00               **********/
/******************************************************/
/******************************************************/


#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

#define SINK		0
#define SOURCE		1


typedef struct {
	u8 Control_Port;
	u8 Control_Pin;
	u8 Type;
} LED_T;


u8 LED_u8LED_ON( LED_T *Copy_LED_Config_Struct);
u8 LED_u8LED_OFF( LED_T *Copy_LED_Config_Struct);
u8 LED_u8LED_TOGGLE( LED_T *Copy_LED_Config_Struct);



#endif
