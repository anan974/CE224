#include "NVIC.h"
#include "timer.h"

void TIM_ClockEnable(TIMER_Typedef* timer)
{
	if (timer == TIMER2) TIMER2_PCLK_EN(); 
	else if (timer == TIMER3) TIMER3_PCLK_EN();
	else if (timer == TIMER4) TIMER4_PCLK_EN();
	else if (timer == TIMER5) TIMER5_PCLK_EN();
}
void TIM_Config(TIMER_Typedef* timer)
{
	//Enable clock for timer
	TIM_ClockEnable(timer);
	//CKD: No Clock division 
	timer->TIMx_CR1 &= ~(1u << 8);
	//ARPE: Auto-reload preload enable
	timer->TIMx_CR1 |= (1 << 7);
	//Counter used as upcounter
	timer->TIMx_CR1 &= ~(1u << 4);
	//URS: Update request source
	timer->TIMx_CR1 &= ~(1u << 2);
	//UDIS: Update enable
	timer->TIMx_CR1 &= ~(1u << 1);
	//Update interrupt enable
	timer->TIMx_DIER |= (1 << 0);
	//Timer prescale value
	timer->TIMx_PSC = (72 - 1);
	//TIMx auto-reload register
	timer->TIMx_ARR = (20000 - 1);
}

void TIM_Base_Start(TIMER_Typedef* timer)
{
	//Start timer
	timer->TIMx_CR1 |= (1 << 0);
}

void TIM_Base_Start_IT(TIMER_Typedef* timer)
{
	//NVIC enable 
	NVIC_EnableIRQ(TIM2_IRQn);
	//Set priority 
	NVIC_SetPriority(TIM2_IRQn,0);
		//Start timer
	timer->TIMx_CR1 |= (1 << 0);
}

void TIM_Stop_Base(TIMER_Typedef* timer)
{
	
}

void TIM_Stop_IT(TIMER_Typedef* timer)
{
	
}
