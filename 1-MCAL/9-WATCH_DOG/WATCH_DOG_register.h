/*********************************************************/
/*********************************************************/
/***********		Author: Raghad Mohamed 	**************/
/***********		Layer: MCAL			 	**************/
/***********		Component: WATCHDOG   	**************/
/**********			Date:11-10-2020         **************/            
/***********		Version: 1.00		 	**************/
/*********************************************************/
/*********************************************************/

#ifndef WATCH_DOG_REGISTER_H_
#define WATCH_DOG_REGISTER_H_

#define WDTCR  			*((volatile u8*)0x41)	//Watchdog timer
#define WDTCR_WDTOE		4						//Watchdog turn off enable
#define WDTCR_WDE		3						//Watchdog enable



#endif