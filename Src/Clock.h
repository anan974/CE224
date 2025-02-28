#ifndef _CLOCK_H_
#define _CLOCK_H_

#include "stdint.h"

struct __RCC_HandleTypeDef
{
	volatile uint32_t RCC_CR;
	volatile uint32_t RCC_CFGR;
	volatile uint32_t RCC_CIR;
	volatile uint32_t RCC_APB2RSTR;
	volatile uint32_t RCC_APB1RSTR;
	volatile uint32_t RCC_AHBENR;
	volatile uint32_t RCC_APB2ENR;
	volatile uint32_t RCC_APB1ENR;
	volatile uint32_t RCC_BDCR;
	volatile uint32_t RCC_CSR;
	volatile uint32_t RCC_AHBSTR;
	volatile uint32_t RCC_CFGR2;
};

typedef struct __RCC_HandleTypeDef RCC_TypeDef;

void RCC_HSEConfig(void);
void RCC_AdcConfig(void);
void RCC_PLLConfig(void);

#endif /* _CLOCK_H_ */
