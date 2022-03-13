/******************************************************/
/******************************************************/
/**********      AUTHOR: Raghad Mohamed      **********/
/**********      Layer: HAL                  **********/
/**********      SWC: Motor 			     **********/
/**********      Date: 28-9-2020             **********/
/**********      Version: 1.00               **********/
/******************************************************/
/******************************************************/

#ifndef MOTOR_INTERFACE_H_
#define MOTOR_INTERFACE_H_


typedef struct {
	u8 Control_Port;
	u8 Control_PinA;
	u8 Control_PinB;
}Motor_T;

u8 Motor_u8TurnOff(Motor_T * Copy_puMotor_T_Config);
u8 Motor_u8RotateClockwise(Motor_T * Copy_puMotor_T_Config);
u8 Motor_u8RotateAntiClockwise(Motor_T * Copy_puMotor_T_Config);





#endif
