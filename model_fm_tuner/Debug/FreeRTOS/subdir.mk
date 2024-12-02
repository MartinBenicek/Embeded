################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
C:/Users/m_benicek/Documents/m_benicek24/utb_frdm_vyuka/FreeRTOS/startup_MKL25Z4.S 

OBJS += \
./FreeRTOS/startup_MKL25Z4.o 

S_UPPER_DEPS += \
./FreeRTOS/startup_MKL25Z4.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/startup_MKL25Z4.o: C:/Users/m_benicek/Documents/m_benicek24/utb_frdm_vyuka/FreeRTOS/startup_MKL25Z4.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


