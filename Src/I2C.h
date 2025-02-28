 #ifndef INC_I2C_H_

#include "I2C_Register.h"
#include "GPIO.h"

#define i2c_FM 0x2d
#define i2c_SM 0xB4


void i2c_init(I2C_TypeDef *I2Cx, unsigned short speed_mode);
void i2c_start(I2C_TypeDef *I2Cx);
void i2c_add(I2C_TypeDef *I2Cx, char address, char RW);
void i2c_data(I2C_TypeDef *I2Cx, char data);
void i2c_write(I2C_TypeDef *I2Cx, char address, char data[]);
void i2c_stop(I2C_TypeDef *I2Cx);

#define INC_I2C_H_

#endif /* INC_I2C_H_ */

