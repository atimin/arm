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
#include "stm32f30x.h"
#include "stm32f30x_conf.h"
#include "common.h"

/* Private typedef */
#define PRESCL 		12
#define PWM_BASE	59638
#define PWM_MIN		3282
#define PWM_MAX 	13821

/* Private function prototypes */
void GPIO_Configuration();
void RCC_Configuration();
void TIM3Configuration();


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
	STM_EVAL_LEDOn(LED10);

	RCC_Configuration();
	GPIO_Configuration();

	TIM3Configuration();

	while(1)
	{

	}

	/* Program will never run to this line */
	return 0;
}

void RCC_Configuration()
{
	/* TIM3 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	/* GPIOC clock enable */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
}

void GPIO_Configuration()
{
	GPIO_InitTypeDef gpio;

	gpio.GPIO_Pin = GPIO_Pin_6;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_PuPd = GPIO_PuPd_UP;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;

	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_2);
	GPIO_Init(GPIOC, &gpio);
}

void TIM3Configuration()
{
	TIM_TimeBaseInitTypeDef timInit;
	TIM_OCInitTypeDef timChannelInit;

	/* Time base configuration */
	timInit.TIM_Period = PWM_BASE;
	timInit.TIM_Prescaler = PRESCL;
	timInit.TIM_ClockDivision = TIM_CKD_DIV1;
	timInit.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &timInit);

	/* PWM1 Chanel1 (PC6) */
	timChannelInit.TIM_OCMode = TIM_OCMode_PWM1;
	timChannelInit.TIM_OutputState = TIM_OutputState_Enable;
	timChannelInit.TIM_OCPolarity =TIM_OCPolarity_High;
	timChannelInit.TIM_Pulse = PWM_MAX;

	TIM_OC1Init(TIM3, &timChannelInit);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_CCxCmd(TIM3, TIM_Channel_1, TIM_CCx_Enable);

	TIM_ARRPreloadConfig(TIM3, ENABLE);
	TIM_Cmd(TIM3, ENABLE);
}
