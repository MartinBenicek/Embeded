################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/student/Documents/Scheibinger/utb_frdm_vyuka_20180912/utb_frdm_vyuka_20180912/drivers/gpio/drv_gpio.c \
../Sources/drv_lcd.c \
C:/Users/student/Documents/Scheibinger/utb_frdm_vyuka_20180912/utb_frdm_vyuka_20180912/drivers/systick/drv_systick.c \
../Sources/main.c 

OBJS += \
./Sources/drv_gpio.o \
./Sources/drv_lcd.o \
./Sources/drv_systick.o \
./Sources/main.o 

C_DEPS += \
./Sources/drv_gpio.d \
./Sources/drv_lcd.d \
./Sources/drv_systick.d \
./Sources/main.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/drv_gpio.o: C:/Users/student/Documents/Scheibinger/utb_frdm_vyuka_20180912/utb_frdm_vyuka_20180912/drivers/gpio/drv_gpio.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -I"C:\Users\student\Documents\Scheibinger\utb_frdm_vyuka_20180912\utb_frdm_vyuka_20180912\drivers\gpio" -I"C:\Users\student\Documents\Scheibinger\utb_frdm_vyuka_20180912\utb_frdm_vyuka_20180912\drivers\systick" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -I"C:\Users\student\Documents\Scheibinger\utb_frdm_vyuka_20180912\utb_frdm_vyuka_20180912\drivers\gpio" -I"C:\Users\student\Documents\Scheibinger\utb_frdm_vyuka_20180912\utb_frdm_vyuka_20180912\drivers\systick" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/drv_systick.o: C:/Users/student/Documents/Scheibinger/utb_frdm_vyuka_20180912/utb_frdm_vyuka_20180912/drivers/systick/drv_systick.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -I"C:\Users\student\Documents\Scheibinger\utb_frdm_vyuka_20180912\utb_frdm_vyuka_20180912\drivers\gpio" -I"C:\Users\student\Documents\Scheibinger\utb_frdm_vyuka_20180912\utb_frdm_vyuka_20180912\drivers\systick" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


