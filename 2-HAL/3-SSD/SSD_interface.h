/******************************************************/
/******************************************************/
/**********      AUTHOR: Raghad Mohamed      **********/
/**********      Layer: MCAL                 **********/
/**********      SWC: TIMER    			     **********/
/**********      Date: 24-9-2020             **********/
/**********      Version: 1.00               **********/
/******************************************************/
/******************************************************/

#ifndef SSD_INTERFACE_H_
#define SSD_INTERFACE_H_


#define CKATHODE		0
#define CANODE			1



typedef struct {

	u8 Type;
	u8 Data_Port;
	u8 Enable_Port;
	u8 Enable_Pin;

}SSD_T;




u8 SSD_u8SetNumber(SSD_T * Copy_SSD_Config_Struct, u8 Copy_u8Number);

u8 SSD_u8On(SSD_T * Copy_SSD_Config_Struct);

u8 SSD_u8Off(SSD_T * Copy_SSD_Config_Struct);

#endif
