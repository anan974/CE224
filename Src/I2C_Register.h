#pragma once

#include "stdint.h"
#include "Clock.h"

// Base address
#define I2C1_BASE  0x40005400
#define I2C2_BASE  0x40005800

//I2C register structure
typedef struct
{
    volatile unsigned int I2C_CR1;  
    volatile unsigned int I2C_CR2;  
    volatile unsigned int I2C_OAR1;  
    volatile unsigned int I2C_OAR2;  
    volatile unsigned int I2C_DR;    
    volatile unsigned int I2C_SR1;   
    volatile unsigned int I2C_SR2;   
    volatile unsigned int I2C_CCR;   
    volatile unsigned int I2C_TRISE; 
} I2C_TypeDef;

#define I2C1 ((I2C_TypeDef*)I2C1_BASE)
#define I2C2 ((I2C_TypeDef*)I2C2_BASE)



