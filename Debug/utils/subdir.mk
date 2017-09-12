################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../utils/Config.cpp \
../utils/DebugLog.cpp \
../utils/EpollOp.cpp \
../utils/LineBuffer.cpp \
../utils/RingBuff.cpp \
../utils/SockOp.cpp \
../utils/TcpOp.cpp 

OBJS += \
./utils/Config.o \
./utils/DebugLog.o \
./utils/EpollOp.o \
./utils/LineBuffer.o \
./utils/RingBuff.o \
./utils/SockOp.o \
./utils/TcpOp.o 

CPP_DEPS += \
./utils/Config.d \
./utils/DebugLog.d \
./utils/EpollOp.d \
./utils/LineBuffer.d \
./utils/RingBuff.d \
./utils/SockOp.d \
./utils/TcpOp.d 


# Each subdirectory must supply rules for building sources it contributes
utils/%.o: ../utils/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/ruanbo/Codes/DistLog" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


