/**
 *****************************************************************************
 **
 **  File        : servo.c
 **
 **  Abstract    : Servo control.
 **
 **  Functions   :
 **
 **  Environment : Eclipse
 **
 **  Distribution: It's module for controlling of servo. Required TIM3, TIM4
 **
 **
 *****************************************************************************
 */
#include "servo.h"

GPIO_TypeDef* SERVO_PORT[SERVOn] = { SERVO1_PORT, SERVO2_PORT, SERVO3_PORT,
		SERVO4_PORT, SERVO5_PORT, SERVO6_PORT };

const uint16_t SERVO_PIN[SERVOn] = { SERVO1_PIN, SERVO2_PIN, SERVO3_PIN,
		SERVO4_PIN, SERVO5_PIN, SERVO6_PIN };

const uint16_t SERVO_SRC[SERVOn] = { SERVO1_SRC, SERVO2_SRC, SERVO3_SRC,
		SERVO4_SRC, SERVO5_SRC, SERVO6_SRC };

const uint16_t TIM_CHANNEL[SERVOn] = { SERVO1_CHANNEL, SERVO2_CHANNEL, SERVO3_CHANELL,
		SERVO4_CHANELL, SERVO5_CHANELL, SERVO6_CHANELL };

TIM_TypeDef* TIM[SERVOn] = { SERVO1_TIM, SERVO2_TIM, SERVO3_TIM,
		SERVO4_TIM, SERVO5_TIM, SERVO6_TIM };

void (*TIM_OCXInit[SERVOn])(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct)= {
		TIM_OC1Init, TIM_OC2Init, TIM_OC3Init, TIM_OC4Init
};

void (*TIM_OCXPreloadConfig[SERVOn])(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload) = {
		TIM_OC1PreloadConfig, TIM_OC2PreloadConfig, TIM_OC3PreloadConfig, TIM_OC4PreloadConfig
};

static uint8_t rccOn = 0;


void RCC_Configuration()
{

	/* TIM3 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	/* TIM4 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	/* GPIOC clock enable */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	/* GPIOD clock enable */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);


}

void TIM_Configuration()
{
	TIM_TimeBaseInitTypeDef timInit;

	/* TIM2&3&4 */
	/* Time base configuration */
	timInit.TIM_Period = PWM_BASE;
	timInit.TIM_Prescaler = PRESCL;
	timInit.TIM_ClockDivision = TIM_CKD_DIV1;
	timInit.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM3, &timInit);
	TIM_TimeBaseInit(TIM4, &timInit);


	TIM_ITConfig(TIM3, TIM_IT_Update , ENABLE);

	/* Turn on interrupt for TIM2 */
	NVIC_InitTypeDef NVIC_InitStructure;
	/* Enable the TIM2 gloabal Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void InitServo(Servo_TypeDef serv)
{
	GPIO_InitTypeDef gpio;
	TIM_OCInitTypeDef timChannelInit;

	/* Turn on clock and timers if they're turned off */
	if (!rccOn) {
		RCC_Configuration();
		TIM_Configuration();
		rccOn = 1;
	}

	/* Init GPIO pin for PWM */
	gpio.GPIO_Pin = SERVO_PIN[serv];
	gpio.GPIO_Mode = GPIO_Mode_AF;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_PuPd = GPIO_PuPd_UP;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;

	GPIO_PinAFConfig(GPIOC, SERVO_SRC[serv], GPIO_AF_2);
	GPIO_Init(SERVO_PORT[serv], &gpio);

	/* Init channel */
	timChannelInit.TIM_OCMode = TIM_OCMode_PWM1;
	timChannelInit.TIM_OutputState = TIM_OutputState_Enable;
	timChannelInit.TIM_OCPolarity =TIM_OCPolarity_High;
	timChannelInit.TIM_Pulse = PWM_MIDLE;

	TIM_OCXInit[serv](TIM[serv], &timChannelInit);
	TIM_OCXPreloadConfig[serv](TIM[serv], TIM_OCPreload_Enable);
	TIM_CCxCmd(TIM[serv], TIM_CHANNEL[serv], TIM_CCx_Enable);

	TIM_ARRPreloadConfig(TIM[serv], ENABLE);
	TIM_Cmd(TIM[serv], ENABLE);
}

static uint32_t a = 0;
void TIM3_IRQHandler()
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {
		if (++a == 50) {
			STM_EVAL_LEDToggle(LED10);
			a = 0;
		}
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}

}
