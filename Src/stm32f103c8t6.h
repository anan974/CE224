#ifndef _STM32F103C8T6_H_
#define _STM32F103C8T6_H_

#include "Clock.h"
#include "GPIO_Register.h"
#include "ADC.h"

//GPIO
#define GPIOA_BASE 				0x40010800
#define GPIOB_BASE 				0x40010C00
#define GPIOC_BASE 	 			0x40011000
#define GPIOD_BASE 				0x40011400
#define GPIOE_BASE 				0x40011800
#define GPIOF_BASE 				0x40011C00 
#define GPIOG_BASE 				0x40012000

#define GPIOA ((GPIORegister_TypeDef*)GPIOA_BASE)
#define GPIOB ((GPIORegister_TypeDef*)GPIOB_BASE)
#define GPIOC ((GPIORegister_TypeDef*)GPIOC_BASE)
#define GPIOD ((GPIORegister_TypeDef*)GPIOD_BASE)
#define GPIOE ((GPIORegister_TypeDef*)GPIOE_BASE)
#define GPIOF ((GPIORegister_TypeDef*)GPIOF_BASE)
#define GPIOG ((GPIORegister_TypeDef*)GPIOG_BASE)

//Clock
#define RCC_AHB_BASE 0x40021000
#define RCC ((RCC_TypeDef*)RCC_AHB_BASE)

//ADC
#define ADC1_APB2_BASE      0x40012400
#define RCC_AHB_ADDRESS			0x40023000
#define ADC1 ((ADC_TypeDef*)ADC1_APB2_BASE)
#define ADC1_PCLK_EN()			(RCC->RCC_APB2ENR |= (1 << 9))

//NVIC
#define NVIC_ISER_BASE  		  0xE000E100
#define NVIC_ICER_BASE				0XE000E180
#define NVIC_ISPR_BASE				0XE000E200
#define NVIC_IABR_BASE				0xE000E300
#define NVIC_IPR_BASE					0xE000E400
#define STIR									0xE000EF00

//Timer 

#endif /* _STM32F103C8T6_H_ */
