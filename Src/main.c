#include "Clock.h"
#include "ADC.h"
#include "Oled.h"
#include "GPIO.h"
#include "stm32f103c8t6.h"
#include "timer.h"

#define VCC									(double)		3.3
#define FIXED_RESISTOR 			(int) 			10000
#define RFlexMin 						(int)				40000
#define RFlexMax 						(int)				100000
#define AngleMin 						(int)				0
#define AngleMax 						(int)				90
#define MIN_TOLERANCE(X)		(uint32_t)	(X * 0.7)
#define MAX_TOLERANCE(X)		(uint32_t)	(X * 1.3)

static uint32_t value = 0;
static uint32_t prev_value = 0;
static uint8_t update_flag = 0; // Flag to signal OLED update
static double angle;
static int Rflex = 0;

void ADC1_2_IRQHandler(ADC_TypeDef* ADC);
void  TIM2_IRQHandler(void);
int map(int x, int in_min, int in_max, int out_min, int out_max);
double GetAngle(uint32_t adcValue);
void delay(volatile int time);
void Convert_ADC(uint32_t adc);


void delay(volatile int time)
{
		while (time--);
}

int map( int x, int in_min, int in_max, int out_min, int out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void Convert_ADC(uint32_t adc)
{
	oled_clear(I2C1);
	
	if (adc > 700 )
	{
		GPIO_WriteOutputPin(GPIOA, GPIO_PIN_4, 0);
		GPIO_WriteOutputPin(GPIOA, GPIO_PIN_5, 0);
		oled_print(I2C1, 4, 30, "DO NOTHING", 's');
	}
	else if ((adc > 550) && (adc < 700 ))
	{
		GPIO_WriteOutputPin(GPIOA, GPIO_PIN_4, 1);
		GPIO_WriteOutputPin(GPIOA, GPIO_PIN_5, 0);
		oled_print(I2C1, 4, 20, "I'M HUNGRY/THIRSTY", 's');
	}
	else if ((adc < 550 ))
	{
		GPIO_WriteOutputPin(GPIOA, GPIO_PIN_4, 0);
		GPIO_WriteOutputPin(GPIOA, GPIO_PIN_5, 1);
		
		oled_print(I2C1, 4, 20, "I NEED TO GO WC", 's');
	}
	
	delay(3000000);
}

double GetAngle(uint32_t adcValue)
{
		double voltage;
	  double temp;

    voltage = (double)((adcValue * VCC) / ADC_RESOLUTION);

    Rflex = (int)(((VCC * FIXED_RESISTOR) / voltage) - FIXED_RESISTOR);

    temp = (double)(map(Rflex, RFlexMin, RFlexMax, AngleMin, AngleMax));
	
		if (temp <=  AngleMin) temp = AngleMin;
		else if (temp >= AngleMax) temp = AngleMax; 

    return temp;
}

int main()
{
	//Initialize A0 in analog mode for reading ADC 
	GPIO_Init(GPIOA, GPIO_PIN_0, GPIO_MODE_INPUT, GPIO_MODE_ANALOG);
	//Initialize A4 and A5 for LEDs configuration 
	GPIO_Init(GPIOA, GPIO_PIN_4, GPIO_OUTPUT_SPEED10_MODE, GPIO_MODE_OUTPUT_PP);
	GPIO_Init(GPIOA, GPIO_PIN_5, GPIO_OUTPUT_SPEED10_MODE, GPIO_MODE_OUTPUT_PP);
	
	//Config ADC1 and start reading value
	ADC_Config(ADC1);
	ADC_Start(ADC1);

	//Config TIMER 2 and enable Interrupt
	TIM_Config(TIMER2);
	TIM_Base_Start_IT(TIMER2);
	
	//Initialize OLED
	oled_init_64(I2C1);
	oled_clear(I2C1);
	while (1) 
	{
		if (update_flag) 
		{
			 Convert_ADC(value);
			 update_flag = 0;
		} 
	}
}

void  TIM2_IRQHandler(void)
{
	if ((TIMER2->TIMx_SR) & (1 << 0)) {
		//Get ADC's value
		value = ADC_GetValue(ADC1);
		update_flag = 1;
		//Handle tolerance of sensor
		if ((value > MIN_TOLERANCE(prev_value)) && (value < MAX_TOLERANCE(prev_value)))
		 {
			 value = prev_value;
			 update_flag = 0;
		 }
		 //Turn off conversion's ended flag
		TIMER2->TIMx_SR &= ~(1u << 0);
	}
}	

