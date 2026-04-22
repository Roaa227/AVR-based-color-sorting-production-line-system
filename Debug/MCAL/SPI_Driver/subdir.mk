################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/SPI_Driver/SPI_inetrface.c 

OBJS += \
./MCAL/SPI_Driver/SPI_inetrface.o 

C_DEPS += \
./MCAL/SPI_Driver/SPI_inetrface.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/SPI_Driver/%.o: ../MCAL/SPI_Driver/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


