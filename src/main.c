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

#include <stdint.h>
#include <stdio.h>
/* Includes */
#include "servo.h"
#include "stm32f30x.h"
#include "stm32f30x_conf.h"
#include "common.h"
#include "usb_lib.h"
#include "usb_pwr.h"
#include "usb_istr.h"






/* Private functions */

/* Global variables */



void USB_LP_CAN1_RX0_IRQHandler(void)
{
  USB_Istr();
}

/**
 **===========================================================================
 **
 **  Abstract: main program
 **
 **===========================================================================
 */
int main(void)
{

	Set_System();
	Set_USBClock();
	USB_Interrupts_Config();
	USB_Init();
  PowerOn();

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

