################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Msg/GenMsg.cpp \
../Msg/MsgHead.cpp \
../Msg/MsgLogin.cpp \
../Msg/MsgReader.cpp \
../Msg/MsgVote.cpp \
../Msg/MsgWriter.cpp 

OBJS += \
./Msg/GenMsg.o \
./Msg/MsgHead.o \
./Msg/MsgLogin.o \
./Msg/MsgReader.o \
./Msg/MsgVote.o \
./Msg/MsgWriter.o 

CPP_DEPS += \
./Msg/GenMsg.d \
./Msg/MsgHead.d \
./Msg/MsgLogin.d \
./Msg/MsgReader.d \
./Msg/MsgVote.d \
./Msg/MsgWriter.d 


# Each subdirectory must supply rules for building sources it contributes
Msg/%.o: ../Msg/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/ruanbo/Codes/DistLog" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


