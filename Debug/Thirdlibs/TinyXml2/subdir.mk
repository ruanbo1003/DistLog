################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Thirdlibs/TinyXml2/tinyxml2.cpp 

OBJS += \
./Thirdlibs/TinyXml2/tinyxml2.o 

CPP_DEPS += \
./Thirdlibs/TinyXml2/tinyxml2.d 


# Each subdirectory must supply rules for building sources it contributes
Thirdlibs/TinyXml2/%.o: ../Thirdlibs/TinyXml2/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/ruanbo/Codes/DistLog" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


