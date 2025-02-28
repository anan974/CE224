################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/ADC.c \
../Src/Clock.c \
../Src/I2C.c \
../Src/NVIC.c \
../Src/Oled.c \
../Src/gpio.c \
../Src/main.c \
../Src/timer.c 

OBJS += \
./Src/ADC.o \
./Src/Clock.o \
./Src/I2C.o \
./Src/NVIC.o \
./Src/Oled.o \
./Src/gpio.o \
./Src/main.o \
./Src/timer.o 

C_DEPS += \
./Src/ADC.d \
./Src/Clock.d \
./Src/I2C.d \
./Src/NVIC.d \
./Src/Oled.d \
./Src/gpio.d \
./Src/main.d \
./Src/timer.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/ADC.cyclo ./Src/ADC.d ./Src/ADC.o ./Src/ADC.su ./Src/Clock.cyclo ./Src/Clock.d ./Src/Clock.o ./Src/Clock.su ./Src/I2C.cyclo ./Src/I2C.d ./Src/I2C.o ./Src/I2C.su ./Src/NVIC.cyclo ./Src/NVIC.d ./Src/NVIC.o ./Src/NVIC.su ./Src/Oled.cyclo ./Src/Oled.d ./Src/Oled.o ./Src/Oled.su ./Src/gpio.cyclo ./Src/gpio.d ./Src/gpio.o ./Src/gpio.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/timer.cyclo ./Src/timer.d ./Src/timer.o ./Src/timer.su

.PHONY: clean-Src

