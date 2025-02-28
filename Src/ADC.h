#ifndef INC_ADC_H_

#include "Clock.h"
	
#define ADC_RESOLUTION 4095
#define ADC_INTERRUPT_ENABLE 1
#define ADC_DMA_ENABLE

struct __ADC_HandleTypeDef
{
	volatile uint32_t ADC_SR;
  volatile uint32_t ADC_CR1;
  volatile uint32_t ADC_CR2;
  volatile uint32_t ADC_SMPR1;
  volatile uint32_t ADC_SMPR2;
  volatile uint32_t ADC_JOFR1;
  volatile uint32_t ADC_JOFR2;
  volatile uint32_t ADC_JOFR3;
  volatile uint32_t ADC_JOFR4;
  volatile uint32_t ADC_HTR;
  volatile uint32_t ADC_LTR;
  volatile uint32_t ADC_SQR1;
  volatile uint32_t ADC_SQR2;
  volatile uint32_t ADC_SQR3;
  volatile uint32_t ADC_JSQR;
  volatile uint32_t ADC_JDR1;
  volatile uint32_t ADC_JDR2;
  volatile uint32_t ADC_JDR3;
  volatile uint32_t ADC_JDR4;
  volatile uint32_t ADC_DR;
};

typedef struct __ADC_HandleTypeDef ADC_TypeDef;

void ADC_ClockConfig(void);

void ADC_Config(ADC_TypeDef* ACD);

void ADC_Start(ADC_TypeDef* ACD);

uint32_t ADC_GetValue(ADC_TypeDef* ACD);

#define INC_ADC_H_

#endif /* INC_ADC_H_ */
