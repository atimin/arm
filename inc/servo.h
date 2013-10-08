/*
 * servo.h
 *
 *  Created on: 17.06.2013
 *      Author: flipback
 *
 *  Distribution: It's module for controlling of servo. Required TIM3, TIM4
 *
 *  SERVO_1 PC6
 *  SERVO_2 PC7
 *  SERVO_3 PC8
 *  SERVO_4	PC9
 *  SERVO_5	PD12
 *  SERVO_6	PD13
 *
 *****************************************************************************
 */

#ifndef SERVO_H_

#include "stm32f30x_conf.h"
#include "stm32f30x.h"
#include "stm32f3_discovery.h"
#include <math.h>

#define SERVOn		6

#define SERVO_MOVING 	1
#define SERVO_STOPED 	0

#define PRESCL 		12
#define PWM_BASE	59638
#define PWM_MIN		3282
#define PWM_MAX 	13821
#define PWM_MIDLE 	((PWM_MAX-PWM_MIN) / 2 + PWM_MIN)

#define SERVO1_PIN		GPIO_Pin_6
#define SERVO1_PORT		GPIOC
#define SERVO1_SRC		GPIO_PinSource6
#define SERVO1_TIM		TIM3
#define SERVO1_CHANNEL	TIM_Channel_1

#define SERVO2_PIN	GPIO_Pin_7
#define SERVO2_PORT	GPIOC
#define SERVO2_SRC	GPIO_PinSource7
#define SERVO2_TIM		TIM3
#define SERVO2_CHANNEL	TIM_Channel_2

#define SERVO3_PIN	GPIO_Pin_8
#define SERVO3_PORT	GPIOC
#define SERVO3_SRC	GPIO_PinSource8
#define SERVO3_TIM		TIM3
#define SERVO3_CHANELL	TIM_Channel_3

#define SERVO4_PIN 	GPIO_Pin_9
#define SERVO4_PORT	GPIOC
#define SERVO4_SRC	GPIO_PinSource9
#define SERVO4_TIM		TIM3
#define SERVO4_CHANELL	TIM_Channel_4

#define SERVO5_PIN	GPIO_Pin_12
#define SERVO5_PORT	GPIOD
#define SERVO5_SRC	GPIO_PinSource12
#define SERVO5_TIM		TIM4
#define SERVO5_CHANELL	TIM_Channel_1

#define SERVO6_PIN 	GPIO_Pin_13
#define SERVO6_PORT	GPIOD
#define SERVO6_SRC	GPIO_PinSource13
#define SERVO6_TIM		TIM4
#define SERVO6_CHANELL	TIM_Channel_2

typedef enum
{
	SERVO1 = 0,
	SERVO2,
	SERVO3,
	SERVO4,
	SERVO5,
	SERVO6
} Servo_TypeDef;

typedef struct
{
	uint8_t id;					// number of servo
	float_t currentAngle;		// current angle 0 - pi/2 [rad]
	float_t setAngle;			// setpoint from 0 - pi/2 [rad]
	float_t velocity;			// velocity [rad/s]
} Servo_TypeStruct;

extern void Servo_Init(Servo_TypeDef serv);
extern void Servo_SetAngle(Servo_TypeDef serv, float_t angle, float_t velocity);
extern float_t Servo_GetAngle(Servo_TypeDef serv);
extern float_t Servo_GetVelocity(Servo_TypeDef serv);
extern uint8_t Servo_IsMove(Servo_TypeDef serv);

#define SERVO_H_

#endif /* SERVO_H_ */
