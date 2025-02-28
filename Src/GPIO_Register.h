 #ifndef INC_GPIO_REGISTER_H_
 
#include "stdint.h"

typedef struct
{
	uint32_t GPIOx_CRL;
	uint32_t GPIOx_CRH;
	uint32_t GPIOx_IDR;
	uint32_t GPIOx_ODR;
	uint32_t GPIOx_BSRR;
	uint32_t GPIOx_BRR;
	uint32_t GPIOx_LCKR;
} GPIORegister_TypeDef;

#define INC_GPIO_REGISTER_H_

#endif /* INC_GPIO_REGISTER_H_ */
