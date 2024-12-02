################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/m_benicek/Documents/m_benicek24/utb_frdm_vyuka/FreeRTOS/port/port.c 

OBJS += \
./FreeRTOS/port/port.o 

C_DEPS += \
./FreeRTOS/port/port.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/port/port.o: C:/Users/m_benicek/Documents/m_benicek24/utb_frdm_vyuka/FreeRTOS/port/port.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DCLOCK_SETUP=1 -I"../Sources" -I"../Includes" -I"../../../CMSIS_Driver" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\KSDK\hal" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\KSDK\mkl25z4" -I"../../../drivers/lcd" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\include" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\port" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\src" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


