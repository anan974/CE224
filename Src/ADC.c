#include "ADC.h"
#include "stm32f103c8t6.h"

void ADC_ClockConfig(void)
{
	//HSEON: HSE clock enable
	RCC->RCC_CR |= (1 << 16);
	//External high-speed clock ready flag
	while (!((RCC->RCC_CR >> 17) & 1));
	//External high-speed clock bypass
	//RCC->RCC_CR |= (1 << 18);
	//PLL enable
	RCC->RCC_CR |= (1 << 24);
	//PLL clock ready flag
	while (!((RCC->RCC_CR >> 25) & 1));
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
		//Enable ADC clock
	RCC->RCC_APB2ENR |= (1 << 9);
}

void ADC_Config(ADC_TypeDef* ADC)
{
	//Config clock
	ADC_ClockConfig();
	// ADON: A/D converter ON 
	ADC->ADC_CR2 |= (1 << 0);
	//EOCIE: Interrupt enable for EOC
	ADC->ADC_CR1 |= (1 << 5);
	//CONT: Continuous conversion
	ADC->ADC_CR2 |= (1 << 1);
	//CAL: A/D Calibration
	ADC->ADC_CR2 |= (1 << 2);
	//Check complete calibration
	while ((ADC->ADC_CR2 >> 2) & 1);
	//ALIGN: Data alignment
	ADC->ADC_CR2 &= ~(1u << 11);
	//EXTSEL[2:0]: External event select for regular group
	ADC->ADC_CR2 |= (7 << 17);
	//SMPx[2:0]: Channel x Sample time selection, channel 0 x 1,5 cycles
	ADC->ADC_SMPR2 &= ~(1u << 0);
	// L[3:0]: Regular channel sequence length
	ADC->ADC_SQR1 &= ~(1u << 20);
	//SQ1[4:0]: 1st conversion in regular sequence
	ADC->ADC_SQR3 &= ~(1u << 0);
	
}

void ADC_Start(ADC_TypeDef* ADC)
{
	//A/D converter ON
	  ADC->ADC_CR2 |= (1 << 0);
	for (volatile int i = 0; i < 1000; i++){} // Small delay
	// SWSTART: Start conversion of regular channels
	ADC->ADC_CR2 |= (1 << 22);
	//Wait for conversions started
	while (!((ADC->ADC_SR >> 4) & 1));
	//ADC->ADC_SR &= ~(1u << 4);
}

uint32_t ADC_GetValue(ADC_TypeDef* ADC)
{
	//Wait for conversions ended
	while (!((ADC->ADC_SR >> 1) & 1));
	uint32_t value = ADC->ADC_DR;
	//ADC->ADC_SR &= ~(1u << 1);
	return value;
}
