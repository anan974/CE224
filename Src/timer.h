#ifndef _TIMER_H_
#define _TIMER_H_

#include "stdint.h"
#include "stm32f103c8t6.h"

#define TIMER2_BASE_ADDRESS  0x40000000
#define TIMER3_BASE_ADDRESS  0x40000400
#define TIMER4_BASE_ADDRESS  0x40000800
#define TIMER5_BASE_ADDRESS  0x40000C00 

#define TIMER2 							((TIMER_Typedef*) TIMER2_BASE_ADDRESS)
#define TIMER3 							((TIMER_Typedef*) TIMER3_BASE_ADDRESS)
#define TIMER4 							((TIMER_Typedef*) TIMER4_BASE_ADDRESS)
#define TIMER5 							((TIMER_Typedef*) TIMER5_BASE_ADDRESS)

//Enable clock
#define TIMER2_PCLK_EN()						(RCC->RCC_APB1ENR |= (1 << 0))		
#define TIMER3_PCLK_EN()						(RCC->RCC_APB1ENR |= (1 << 1))		
#define TIMER4_PCLK_EN()						(RCC->RCC_APB1ENR |= (1 << 2))		
#define TIMER5_PCLK_EN()						(RCC->RCC_APB1ENR |= (1 << 3))		


typedef struct
{
	volatile uint32_t TIMx_CR1;
	volatile uint32_t TIMx_CR2;
	volatile uint32_t TIMx_SMCR;
	volatile uint32_t TIMx_DIER;
	volatile uint32_t TIMx_SR;
	volatile uint32_t TIMx_EGR;
	volatile uint32_t TIMx_CCMR1;
	volatile uint32_t TIMx_CCMR2;
	volatile uint32_t TIMx_CCER;
	volatile uint32_t TIMx_CNT;
	volatile uint32_t TIMx_PSC;
	volatile uint32_t TIMx_ARR;
					 uint32_t RESERVED0;
	volatile uint32_t TIMx_CCR1;
	volatile uint32_t TIMx_CCR2;
	volatile uint32_t TIMx_CCR3;
	volatile uint32_t TIMx_CCR4;
					 uint32_t RESERVED1;
	volatile uint32_t TIMx_DCR;
	volatile uint32_t TIMx_DMAR;
} TIMER_Typedef;

void TIM_ClockEnable(TIMER_Typedef* timer);
void TIM_Config(TIMER_Typedef* timer);
void TIM_Base_Start(TIMER_Typedef* timer);
void TIM_Base_Start_IT(TIMER_Typedef* timer);
void TIM_Stop_Base(TIMER_Typedef* timer);
void TIM_Stop_IT(TIMER_Typedef* timer);

#endif /* _TIMER_H_ */
