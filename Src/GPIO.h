 #ifndef INC_GPIO_H_
 
 #include "GPIO_Register.h"
 #include "Clock.h"
 #include "stdint.h"
  
 //Define GPIOx pin
 #define GPIO_PIN_0 		0
 #define GPIO_PIN_1 		1
 #define GPIO_PIN_2 		2
 #define GPIO_PIN_3 		3
 #define GPIO_PIN_4 		4
 #define GPIO_PIN_5 		5
 #define GPIO_PIN_6			6
 #define GPIO_PIN_7 		7
 #define GPIO_PIN_8 		8
 #define GPIO_PIN_9 		9
 #define GPIO_PIN_10 		10
 #define GPIO_PIN_11 		11
 #define GPIO_PIN_12 		12
 #define GPIO_PIN_13 		13
 #define GPIO_PIN_14 		14
 #define GPIO_PIN_15 		15
 
 #define GPIO_PIN_SET 		1
 #define GPIO_PIN_RESET 	0
 
 //Define mode
 #define GPIO_MODE_INPUT 						0
 #define GPIO_OUTPUT_SPEED10_MODE		1
 #define GPIO_OUTPUT_SPEED2_MODE		2
 #define GPIO_OUTPUT_SPEED50_MODE		3
 
 //Input type
 #define GPIO_MODE_ANALOG 				  0
 #define GPIO_FLIN									1
 #define GPIO_PULLUD								2
 #define GPIO_RESERVED							3
 
 //Output type
 #define GPIO_MODE_OUTPUT_PP				0
 #define GPIO_MODE_OUTPUT_OD				1
 #define GPIO_MODE_AF_PP						2
 #define GPIO_MODE_AF_OD						3

//GPIO pull define
//#define  GPIO_NOPULL        0   
#define  GPIO_PULLUP        				1   
#define  GPIO_PULLDOWN      				0   

//Clock enable for GPIOx peripheral
#define GPIOA_PCLK_EN()							(RCC->RCC_APB2ENR |= (1 << 2))
#define GPIOB_PCLK_EN()							(RCC->RCC_APB2ENR |= (1 << 3))
#define GPIOC_PCLK_EN()							(RCC->RCC_APB2ENR |= (1 << 4))
#define GPIOD_PCLK_EN()							(RCC->RCC_APB2ENR |= (1 << 5))
#define GPIOE_PCLK_EN()							(RCC->RCC_APB2ENR |= (1 << 6))

//Clock disable for GPIOx peripheral
#define GPIOA_PCLK_DIS()						(RCC->RCC_APB2ENR &= ~(1u << 2))		
#define GPIOB_PCLK_DIS()						(RCC->RCC_APB2ENR &= ~(1u << 3))		
#define GPIOC_PCLK_DIS()						(RCC->RCC_APB2ENR &= ~(1u << 4))		
#define GPIOD_PCLK_DIS()						(RCC->RCC_APB2ENR &= ~(1u << 5))		
#define GPIOE_PCLK_DIS()						(RCC->RCC_APB2ENR &= ~(1u << 6))			

typedef struct
{
    GPIORegister_TypeDef *      GPIO_Port;                  /*!< Gpio base pointer.  */
    uint32_t           					GPIO_PinNumber;        /*!< Pin number.*/
    uint32_t           					GPIO_PinMode;          /*!< Pin_mode */
	  uint32_t		  							GPIO_PinType;
			
} GPIO_TypeDef;


void GPIO_ClockEnable(GPIORegister_TypeDef* gpiox);
void GPIO_Init(GPIORegister_TypeDef *GPIOx, unsigned int pin, unsigned int mode, unsigned int config);
void GPIO_DeInit(GPIORegister_TypeDef* gpiox);

void GPIO_WriteOutputPin(GPIORegister_TypeDef* gpiox, unsigned int pinNumber, unsigned int value);
uint8_t GPIO_ReadInputPin(GPIORegister_TypeDef* gpiox, unsigned int pinNumber);
void GPIO_TogglePin(GPIORegister_TypeDef* gpiox, unsigned int pinNumber);

#define INC_GPIO_H_

#endif /* INC_GPIO_H_ */
