################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Network/ClientAgent.cpp \
../Network/MsgHandlers.cpp \
../Network/MsgRequest.cpp \
../Network/NetMngr.cpp \
../Network/NetTests.cpp \
../Network/Pools.cpp \
../Network/TcpServer.cpp \
../Network/VoteLeader.cpp \
../Network/Votes.cpp 

OBJS += \
./Network/ClientAgent.o \
./Network/MsgHandlers.o \
./Network/MsgRequest.o \
./Network/NetMngr.o \
./Network/NetTests.o \
./Network/Pools.o \
./Network/TcpServer.o \
./Network/VoteLeader.o \
./Network/Votes.o 

CPP_DEPS += \
./Network/ClientAgent.d \
./Network/MsgHandlers.d \
./Network/MsgRequest.d \
./Network/NetMngr.d \
./Network/NetTests.d \
./Network/Pools.d \
./Network/TcpServer.d \
./Network/VoteLeader.d \
./Network/Votes.d 


# Each subdirectory must supply rules for building sources it contributes
Network/%.o: ../Network/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/ruanbo/Codes/DistLog" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


