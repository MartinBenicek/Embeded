################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/m_benicek/Documents/m_benicek24/utb_frdm_vyuka/FreeRTOS/src/croutine.c \
C:/Users/m_benicek/Documents/m_benicek24/utb_frdm_vyuka/FreeRTOS/src/event_groups.c \
C:/Users/m_benicek/Documents/m_benicek24/utb_frdm_vyuka/FreeRTOS/src/heap_1.c \
C:/Users/m_benicek/Documents/m_benicek24/utb_frdm_vyuka/FreeRTOS/src/heap_2.c \
C:/Users/m_benicek/Documents/m_benicek24/utb_frdm_vyuka/FreeRTOS/src/heap_3.c \
C:/Users/m_benicek/Documents/m_benicek24/utb_frdm_vyuka/FreeRTOS/src/heap_4.c \
C:/Users/m_benicek/Documents/m_benicek24/utb_frdm_vyuka/FreeRTOS/src/list.c \
C:/Users/m_benicek/Documents/m_benicek24/utb_frdm_vyuka/FreeRTOS/src/queue.c \
C:/Users/m_benicek/Documents/m_benicek24/utb_frdm_vyuka/FreeRTOS/src/tasks.c \
C:/Users/m_benicek/Documents/m_benicek24/utb_frdm_vyuka/FreeRTOS/src/timers.c 

OBJS += \
./FreeRTOS/src/croutine.o \
./FreeRTOS/src/event_groups.o \
./FreeRTOS/src/heap_1.o \
./FreeRTOS/src/heap_2.o \
./FreeRTOS/src/heap_3.o \
./FreeRTOS/src/heap_4.o \
./FreeRTOS/src/list.o \
./FreeRTOS/src/queue.o \
./FreeRTOS/src/tasks.o \
./FreeRTOS/src/timers.o 

C_DEPS += \
./FreeRTOS/src/croutine.d \
./FreeRTOS/src/event_groups.d \
./FreeRTOS/src/heap_1.d \
./FreeRTOS/src/heap_2.d \
./FreeRTOS/src/heap_3.d \
./FreeRTOS/src/heap_4.d \
./FreeRTOS/src/list.d \
./FreeRTOS/src/queue.d \
./FreeRTOS/src/tasks.d \
./FreeRTOS/src/timers.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/src/croutine.o: C:/Users/m_benicek/Documents/m_benicek24/utb_frdm_vyuka/FreeRTOS/src/croutine.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DCLOCK_SETUP=1 -I"../Sources" -I"../Includes" -I"../../../CMSIS_Driver" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\KSDK\hal" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\KSDK\mkl25z4" -I"../../../drivers/lcd" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\include" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\port" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\src" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS/src/event_groups.o: C:/Users/m_benicek/Documents/m_benicek24/utb_frdm_vyuka/FreeRTOS/src/event_groups.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DCLOCK_SETUP=1 -I"../Sources" -I"../Includes" -I"../../../CMSIS_Driver" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\KSDK\hal" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\KSDK\mkl25z4" -I"../../../drivers/lcd" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\include" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\port" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\src" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS/src/heap_1.o: C:/Users/m_benicek/Documents/m_benicek24/utb_frdm_vyuka/FreeRTOS/src/heap_1.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DCLOCK_SETUP=1 -I"../Sources" -I"../Includes" -I"../../../CMSIS_Driver" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\KSDK\hal" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\KSDK\mkl25z4" -I"../../../drivers/lcd" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\include" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\port" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\src" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS/src/heap_2.o: C:/Users/m_benicek/Documents/m_benicek24/utb_frdm_vyuka/FreeRTOS/src/heap_2.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DCLOCK_SETUP=1 -I"../Sources" -I"../Includes" -I"../../../CMSIS_Driver" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\KSDK\hal" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\KSDK\mkl25z4" -I"../../../drivers/lcd" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\include" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\port" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\src" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS/src/heap_3.o: C:/Users/m_benicek/Documents/m_benicek24/utb_frdm_vyuka/FreeRTOS/src/heap_3.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DCLOCK_SETUP=1 -I"../Sources" -I"../Includes" -I"../../../CMSIS_Driver" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\KSDK\hal" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\KSDK\mkl25z4" -I"../../../drivers/lcd" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\include" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\port" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\src" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS/src/heap_4.o: C:/Users/m_benicek/Documents/m_benicek24/utb_frdm_vyuka/FreeRTOS/src/heap_4.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DCLOCK_SETUP=1 -I"../Sources" -I"../Includes" -I"../../../CMSIS_Driver" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\KSDK\hal" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\KSDK\mkl25z4" -I"../../../drivers/lcd" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\include" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\port" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\src" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS/src/list.o: C:/Users/m_benicek/Documents/m_benicek24/utb_frdm_vyuka/FreeRTOS/src/list.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DCLOCK_SETUP=1 -I"../Sources" -I"../Includes" -I"../../../CMSIS_Driver" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\KSDK\hal" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\KSDK\mkl25z4" -I"../../../drivers/lcd" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\include" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\port" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\src" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS/src/queue.o: C:/Users/m_benicek/Documents/m_benicek24/utb_frdm_vyuka/FreeRTOS/src/queue.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DCLOCK_SETUP=1 -I"../Sources" -I"../Includes" -I"../../../CMSIS_Driver" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\KSDK\hal" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\KSDK\mkl25z4" -I"../../../drivers/lcd" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\include" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\port" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\src" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS/src/tasks.o: C:/Users/m_benicek/Documents/m_benicek24/utb_frdm_vyuka/FreeRTOS/src/tasks.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DCLOCK_SETUP=1 -I"../Sources" -I"../Includes" -I"../../../CMSIS_Driver" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\KSDK\hal" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\KSDK\mkl25z4" -I"../../../drivers/lcd" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\include" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\port" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\src" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS/src/timers.o: C:/Users/m_benicek/Documents/m_benicek24/utb_frdm_vyuka/FreeRTOS/src/timers.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DCLOCK_SETUP=1 -I"../Sources" -I"../Includes" -I"../../../CMSIS_Driver" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\KSDK\hal" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\KSDK\mkl25z4" -I"../../../drivers/lcd" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\include" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\port" -I"C:\Users\m_benicek\Documents\m_benicek24\utb_frdm_vyuka\FreeRTOS\src" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


