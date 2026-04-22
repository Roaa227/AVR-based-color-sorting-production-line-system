################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/Timers_Driver/Timer0.c \
../MCAL/Timers_Driver/Timer1.c 

OBJS += \
./MCAL/Timers_Driver/Timer0.o \
./MCAL/Timers_Driver/Timer1.o 

C_DEPS += \
./MCAL/Timers_Driver/Timer0.d \
./MCAL/Timers_Driver/Timer1.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/Timers_Driver/%.o: ../MCAL/Timers_Driver/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


