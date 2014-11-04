################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/sources/ClarkeWright.cpp \
../src/sources/DataParser.cpp \
../src/sources/FileManager.cpp \
../src/sources/Heuristics.cpp 

OBJS += \
./src/sources/ClarkeWright.o \
./src/sources/DataParser.o \
./src/sources/FileManager.o \
./src/sources/Heuristics.o 

CPP_DEPS += \
./src/sources/ClarkeWright.d \
./src/sources/DataParser.d \
./src/sources/FileManager.d \
./src/sources/Heuristics.d 


# Each subdirectory must supply rules for building sources it contributes
src/sources/%.o: ../src/sources/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


