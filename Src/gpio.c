#include "GPIO.h"
#include "stm32f103c8t6.h"

void GPIO_ClockEnable(GPIORegister_TypeDef* gpiox)
{
	if (gpiox == GPIOA)
	{
		GPIOA_PCLK_EN();
	}
	else if (gpiox == GPIOB)
	{
		GPIOB_PCLK_EN();
	} 
	else if (gpiox == GPIOC)
	{
		GPIOC_PCLK_EN();
	}
	else if (gpiox == GPIOD)
	{
		GPIOD_PCLK_EN();
	} 
	else if (gpiox == GPIOE)
	{
		GPIOE_PCLK_EN();
	} 
	
}

void GPIO_Init(GPIORegister_TypeDef *GPIOx, unsigned int pin, unsigned int mode, unsigned int config) {
    volatile uint32_t *CR;
    unsigned int tPIN = pin;
		
		GPIO_TypeDef GPIO_InitStruct = {0};	
		GPIO_InitStruct.GPIO_PinMode = mode;
		GPIO_InitStruct.GPIO_PinNumber = pin;
		GPIO_InitStruct.GPIO_PinType = config;  
	
    // Enable clock for port
	  GPIO_ClockEnable(GPIOx);
    // Choose CRL or CRH 
    if (pin < 8) {
        CR = &GPIOx->GPIOx_CRL;  
    } else {
        CR = &GPIOx->GPIOx_CRH;  
        tPIN -= 8;  
    }

    // Reset bits 
    *CR &= ~(0xF << (tPIN * 4));  

    // Set mode and configuration
    *CR |= (mode << (tPIN * 4)) | (config << (tPIN * 4 + 2));
}

void GPIO_WriteOutputPin(GPIORegister_TypeDef* gpiox, unsigned int pin, unsigned int value)
{
    if (value) 
		{
        gpiox->GPIOx_ODR |= (1 << pin);  
    } 
		else 
		{
        gpiox->GPIOx_ODR &= ~(1 << pin); 
    }
}


uint8_t GPIO_ReadInputPin(GPIORegister_TypeDef* gpiox, unsigned int pinNumber)
{
	uint8_t value;
	value = ((gpiox->GPIOx_IDR) >> pinNumber) & 0x00000001;
	return value;
}

void GPIO_TogglePin(GPIORegister_TypeDef* gpiox, unsigned int pinNumber)
{
	if (((gpiox->GPIOx_ODR >> pinNumber) & GPIO_PIN_SET))
		gpiox->GPIOx_ODR &= ~(1u << pinNumber);
	else if (!((gpiox->GPIOx_ODR >> pinNumber) & GPIO_PIN_SET))
		gpiox->GPIOx_ODR |= (1 << pinNumber);

}
