#include "I2C.h"
#include "stm32f103c8t6.h"

void i2c_init(I2C_TypeDef *I2Cx, unsigned short speed_mode)
{
    // Enable AF Clock
    RCC->RCC_APB2ENR |= 1; 

    if (I2Cx == I2C1)
    {
        // Enable clock I2C1
        RCC->RCC_APB1ENR |= (1 << 21);
        
        GPIO_Init(GPIOB, GPIO_PIN_6, GPIO_OUTPUT_SPEED50_MODE, GPIO_MODE_AF_OD);
        GPIO_Init(GPIOB, GPIO_PIN_7, GPIO_OUTPUT_SPEED50_MODE, GPIO_MODE_AF_OD);
        
        // Reset and config I2C1
        I2Cx->I2C_CR1 |= (1<<15); 
        I2Cx->I2C_CR1 &= ~(1u<<15); 
        I2Cx->I2C_CR2 = 0x8; 
        I2Cx->I2C_CCR = speed_mode; 
        I2Cx->I2C_TRISE = 0x9; 
        I2Cx->I2C_CR1 |= 1; 
    }
    else if (I2Cx == I2C2)
    {
        // Enable clock I2C2
        RCC->RCC_APB1ENR |= (1 << 22);

        GPIO_Init(GPIOB, GPIO_PIN_10, GPIO_OUTPUT_SPEED50_MODE, GPIO_MODE_AF_OD); 
        GPIO_Init(GPIOB, GPIO_PIN_11, GPIO_OUTPUT_SPEED50_MODE, GPIO_MODE_AF_OD);

        // Reset and config I2C2
        I2Cx->I2C_CR1 |= (1 << 15); 
        I2Cx->I2C_CR1 &= ~(1u << 15); 
        I2Cx->I2C_CR2 = 0x8; 
        I2Cx->I2C_CCR = speed_mode; 
        I2Cx->I2C_TRISE = 0x9; 
        I2Cx->I2C_CR1 |= 1;
    }
}

// Start bit and wait
void i2c_start(I2C_TypeDef *I2Cx)
{
    I2Cx->I2C_CR1 |= (1 << 8);


    int timeout = 100000; 
    while (!(I2Cx->I2C_SR1 & 0x1)) 
    {
        if (--timeout == 0)
        {
            return;  
        }
    }
	}

// Send address + R or Write	
void i2c_add(I2C_TypeDef *I2Cx, char address, char RW)
{
    volatile uint32_t tmp;

    
    I2Cx->I2C_DR = (address | RW);  

    // ADDR flag
    int timeout = 100000;
    while (!(I2Cx->I2C_SR1 & 0x0002))  
    {
        if (--timeout == 0)
        {
                return;
        }
    }

    if (I2Cx->I2C_SR1 & 0x0100) 
    {
        I2Cx->I2C_SR1 &= ~0x0100; 
        return;
    }

    if (I2Cx->I2C_SR1 & 0x0200) 
    {
       I2Cx->I2C_SR1 &= ~0x0200;
       return;
    }

    // Xóa ADDR  =  doc SR1 và SR2
    tmp = I2Cx->I2C_SR1;
    tmp = I2Cx->I2C_SR2;
}



void i2c_data(I2C_TypeDef *I2Cx, char data)
{
	volatile uint32_t tmp;
    
    while ((I2Cx->I2C_SR1 & 0x80) == 0) {}

    I2Cx->I2C_DR = data;

    while ((I2Cx->I2C_SR1 & 0x80) == 0) {}

    // check  Bus Error (BERR) và Arbitration Lost (ARLO) sau khi gui data
    if (I2Cx->I2C_SR1 & 0x0100)  // (I2C_SR1_BERR)
    {
        I2Cx->I2C_SR1 &= ~0x0100; 
        return;
    }

    if (I2Cx->I2C_SR1 & 0x0200)  // (I2C_SR1_ARLO)
    {
        I2Cx->I2C_SR1 &= ~0x0200;  
        return;
    }

    
    if (I2Cx->I2C_SR1 & 0x0002)  // Ki?m tra ADDR flag
    {
        tmp = I2Cx->I2C_SR1;
        tmp = I2Cx->I2C_SR2;  // Xóa c? ADDR
    }
}


void i2c_stop(I2C_TypeDef *I2Cx)
{
    volatile uint32_t tmp;
    tmp = I2Cx->I2C_SR1;       
    tmp = I2Cx->I2C_SR2;       
    I2Cx->I2C_CR1 |= 0x200;    
}


// i2c_write()
void i2c_write(I2C_TypeDef *I2Cx, char address, char data[])
{
    int i = 0;

    i2c_start(I2Cx);

    // Send address with Write flag
    i2c_add(I2Cx, address, 0);

    // Send data
    while (data[i]) {
        i2c_data(I2Cx, data[i]);
        i++;
    }

    // Stop condition
    i2c_stop(I2Cx);
}

