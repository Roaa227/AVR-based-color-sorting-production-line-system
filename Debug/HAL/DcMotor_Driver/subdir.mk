################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/DcMotor_Driver/DcMotor.c 

OBJS += \
./HAL/DcMotor_Driver/DcMotor.o 

C_DEPS += \
./HAL/DcMotor_Driver/DcMotor.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/DcMotor_Driver/%.o: ../HAL/DcMotor_Driver/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


