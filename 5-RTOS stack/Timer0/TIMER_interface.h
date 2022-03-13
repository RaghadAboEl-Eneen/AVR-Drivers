/******************************************************/
/******************************************************/
/**********      AUTHOR: Raghad Mohamed      **********/
/**********      Layer: MCAL                 **********/
/**********      SWC: TIMER    			     **********/
/**********      Date: 24-9-2020             **********/
/**********      Version: 1.00               **********/
/******************************************************/
/******************************************************/

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_


#define SET_AT_TOP_CLEAR_AT_COMPARE			1
#define CLEAR_AT_TOP_SET_AT_COMPARE			2



void Timer0_voidInit(void);
void Timer1_voidInit(void);

void Timer1_voidSetCompValue(u16 Copy_u16Value);
void Timer1_voidDisableFastPWM(void);
u8 Timer1_u8SetFastPWM_Mode(u8 Copy_u8Mode);

u8 Timer0_u8OverflowSetCallBack(void (*Copy_pvCallBackFunction)(void));
u8 Timer0_u8CompareMatchSetCallBack(void (*Copy_pvCallBackFunction)(void));

void Timer0_voidSetPreload(u8 Copy_u8Preload);

void Timer0_voidEnableCompareMatchInterrupt(void);
void Timer0_voidDisableCompareMatchInterrupt(void);

void Timer0_StopWatchMsISR(void);

u16 Timer1_voidSetTone( u32 Copy_u16Frequency, u16 Copy_u16Duration);

#endif
