/**
 *****************************************************************************
 **
 **  File        : main.c
 **
 **  Abstract    : main function.
 **
 **  Functions   : main
 **
 **  Environment : Atollic TrueSTUDIO(R)
 **
 **  Distribution: The file is distributed �as is,� without any warranty
 **                of any kind.
 **
 **  (c)Copyright Atollic AB.
 **  You may use this file as-is or modify it according to the needs of your
 **  project. Distribution of this file (unmodified or modified) is not
 **  permitted. Atollic AB permit registered Atollic TrueSTUDIO(R) users the
 **  rights to distribute the assembled, compiled & linked contents of this
 **  file as part of an application binary file, provided that it is built
 **  using the Atollic TrueSTUDIO(R) toolchain.
 **
 *****************************************************************************
 */

/* Includes */
#include "servo.h"
#include "stm32f30x.h"
#include "stm32f30x_conf.h"
#include "common.h"

/* Private typedef */
#define PRESCL 		12
#define PWM_BASE	59638
#define PWM_MIN		3282
#define PWM_MAX 	13821
#define PWM_MIDLE 	((PWM_MAX-PWM_MIN) / 2 + PWM_MIN)



/* Private functions */

/* Global variables */




/**
 **===========================================================================
 **
 **  Abstract: main program
 **
 **===========================================================================
 */
int main(void)
{
	STM_EVAL_LEDInit(LED10);

	Servo_Init(SERVO1);
	Servo_Init(SERVO2);
	Servo_Init(SERVO3);
	Servo_Init(SERVO4);
	Servo_Init(SERVO5);
	Servo_Init(SERVO6);

	Servo_SetAngle(SERVO1, M_PI_2, M_PI_4 / 10);
	Servo_SetAngle(SERVO2, M_PI_2, M_PI_4 / 10);
	Servo_SetAngle(SERVO3, M_PI_2, M_PI_4 / 10);

	while(1)
	{

	}

	/* Program will never run to this line */
	return 0;
}

