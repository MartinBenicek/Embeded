################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/m_benicek/Documents/m_benicek24/utb_frdm_vyuka/CMSIS_Driver/I2C_MKL25Z4.c \
C:/Users/m_benicek/Documents/m_benicek24/utb_frdm_vyuka/drivers/lcd/drv_lcd.c \
C:/Users/m_benicek/Documents/m_benicek24/utb_frdm_vyuka/programs/model_fm_tuner/model_fm_tuner.c 

OBJS += \
./Sources/I2C_MKL25Z4.o \
./Sources/drv_lcd.o \
./Sources/model_fm_tuner.o 

C_DEPS += \
./Sources/I2C_MKL25Z4.d \
./Sources/drv_lcd.d \
./Sources/model_fm_tuner.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/I2C_MKL25Z4.o: C:/Users/m_benicek/Documents/m_benicek24/utb_frdm_vyuka/CMSIS_Driver/I2C_MKL25Z4.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DCLOCK_SETUP=1 -I"../Sources" -I"../Includes" -I"../../../CMSIS_Driver" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\KSDK\hal" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\KSDK\mkl25z4" -I"../../../drivers/lcd" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\include" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\src" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\port" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/drv_lcd.o: C:/Users/m_benicek/Documents/m_benicek24/utb_frdm_vyuka/drivers/lcd/drv_lcd.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DCLOCK_SETUP=1 -I"../Sources" -I"../Includes" -I"../../../CMSIS_Driver" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\KSDK\hal" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\KSDK\mkl25z4" -I"../../../drivers/lcd" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\include" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\src" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\port" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/model_fm_tuner.o: C:/Users/m_benicek/Documents/m_benicek24/utb_frdm_vyuka/programs/model_fm_tuner/model_fm_tuner.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DCLOCK_SETUP=1 -I"../Sources" -I"../Includes" -I"../../../CMSIS_Driver" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\KSDK\hal" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\KSDK\mkl25z4" -I"../../../drivers/lcd" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\include" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\src" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\port" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


