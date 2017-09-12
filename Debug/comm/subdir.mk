################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../comm/IThread.cpp \
../comm/comm.cpp \
../comm/global.cpp 

OBJS += \
./comm/IThread.o \
./comm/comm.o \
./comm/global.o 

CPP_DEPS += \
./comm/IThread.d \
./comm/comm.d \
./comm/global.d 


# Each subdirectory must supply rules for building sources it contributes
comm/%.o: ../comm/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/ruanbo/Codes/DistLog" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


