#include "Clock.h"
#include "stm32f103c8t6.h"

void RCC_HSEConfig(void)
{
	//External high-speed clock bypass
	RCC->RCC_CR |= (1 << 18);
	//HSEON: HSE clock enable
	RCC->RCC_CR |= (1 << 16);
	//External high-speed clock ready flag
	RCC->RCC_CR |= (1 << 17);
	//PLL clock ready flag
	while (!((RCC->RCC_CR << 25) & 1));
}

void RCC_PLLConfig(void)
{
	//PLL enable
	RCC->RCC_CR |= (1 << 24);
	//Microcontroller clock output: System clock (SYSCLK) selected
	RCC->RCC_CFGR |= (4 <<24);
	// PLL multiplication factor: 9
	RCC->RCC_CFGR |= (7 << 18);
	//HSE divider for PLL entry: HSE clock not divided
	RCC->RCC_CFGR &= ~(1u << 17);
	//PLL entry clock source: HSE
	RCC->RCC_CFGR |= (1 << 16);
	//ADC prescaler: 8
	RCC->RCC_CFGR |= (3 << 14);
	//APB high-speed prescaler (APB2): 1
	RCC->RCC_CFGR &= ~(1u << 11);
	//AHB prescaler: 1
	RCC->RCC_CFGR &= ~(1u << 4);
	//System clock switch: PLL selected as system clock
	RCC->RCC_CFGR |= (2 << 0);
}

void RCC_AdcConfig(void)
{

}
