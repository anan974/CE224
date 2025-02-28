	
#define ADC_RESOLUTION 4095
#define ADC_INTERRUPT_ENABLE 1
#define ADC_DMA_ENABLE

#define ADC1_APB2_BASE      0x40012400
#define RCC_AHB_ADDRESS			0x40023000
#define ADC1 ((ADC_TypeDef*)ADC1_APB2_BASE)

enum ADC_Mode {
  SINGLE_CONVERSION,
	CONTINUOUS,
  SCAN,
	DISCONTINUOUS
};

enum ADC_DataAlignment  
{
	RIGHT_ALIGNMENT,
  LEFT_ALIGNMENT	
};

struct __ADC_HandleTypeDef
{
	unsigned int ADC_SR;
	unsigned int ADC_CR1;
	unsigned int ADC_CR2;
	unsigned int ADC_SMPR1;
	unsigned int ADC_SMPR2;
	unsigned int ADC_JOFR1;
	unsigned int ADC_JOFR2;
	unsigned int ADC_JOFR3;
	unsigned int ADC_JOFR4;
	unsigned int ADC_HTR;
	unsigned int ADC_LTR;
	unsigned int ADC_SQR1;
	unsigned int ADC_SQR2;
	unsigned int ADC_SQR3;
	unsigned int ADC_JSQR;
	unsigned int ADC_JDR1;
	unsigned int ADC_JDR2;
	unsigned int ADC_JDR3;
	unsigned int ADC_JDR4;
	unsigned int ADC_DR;
};

typedef struct __ADC_HandleTypeDef ADC_TypeDef;

void ADC_Config(ADC_TypeDef* adc);

void ADC_Start(ADC_TypeDef* adc);

int ADC_ReadValue(ADC_TypeDef* adc);




