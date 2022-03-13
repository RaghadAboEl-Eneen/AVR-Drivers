/******************************************************/
/******************************************************/
/**********      AUTHOR: Raghad Mohamed      **********/
/**********      Layer: RTOS stack           **********/
/**********      SWC: RTOS    			     **********/
/**********      Date: 20-10-2020            **********/
/**********      Version: 1.00               **********/
/******************************************************/
/******************************************************/


#ifndef RTOS_INTERFACE_H_
#define RTOS_INTERFACE_H_

void RTOS_voidCreateTask(u8 Copy_u8Priority, u16 Copy_u16Periodicity, void (*Copy_pvTaskFunction)(void));

void RTOS_voidStart(void);




#endif