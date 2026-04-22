################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include MCAL/UART_Driver/subdir.mk
-include MCAL/Timers_Driver/subdir.mk
-include MCAL/TWI_Driver/subdir.mk
-include MCAL/SPI_Driver/subdir.mk
-include MCAL/External_Interrupts_Driver/subdir.mk
-include MCAL/DIO_Driver/subdir.mk
-include MCAL/ADC_Driver/subdir.mk
-include HAL/StepperMotor_Driver/subdir.mk
-include HAL/ServoMotor/subdir.mk
-include HAL/LM35_Driver/subdir.mk
-include HAL/LDR_Driver/subdir.mk
-include HAL/LCD_Driver/subdir.mk
-include HAL/KeyPad_Driver/subdir.mk
-include HAL/EXTERNAL_EEPROM_DRIVER/subdir.mk
-include HAL/DcMotor_Driver/subdir.mk
-include HAL/ColorSensor_Driver/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
ProductionLine.lss \

FLASH_IMAGE += \
ProductionLine.hex \

EEPROM_IMAGE += \
ProductionLine.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: ProductionLine.elf secondary-outputs

# Tool invocations
ProductionLine.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,ProductionLine.map -mmcu=atmega32 -o "ProductionLine.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

ProductionLine.lss: ProductionLine.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S ProductionLine.elf  >"ProductionLine.lss"
	@echo 'Finished building: $@'
	@echo ' '

ProductionLine.hex: ProductionLine.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex ProductionLine.elf  "ProductionLine.hex"
	@echo 'Finished building: $@'
	@echo ' '

ProductionLine.eep: ProductionLine.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex ProductionLine.elf  "ProductionLine.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: ProductionLine.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 ProductionLine.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) ProductionLine.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
