################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/sources/BSTree.cpp \
../src/sources/DataParser.cpp \
../src/sources/FibonacciTree.cpp \
../src/sources/FileManager.cpp \
../src/sources/Heuristics.cpp \
../src/sources/ProblemSolver.cpp 

OBJS += \
./src/sources/BSTree.o \
./src/sources/DataParser.o \
./src/sources/FibonacciTree.o \
./src/sources/FileManager.o \
./src/sources/Heuristics.o \
./src/sources/ProblemSolver.o 

CPP_DEPS += \
./src/sources/BSTree.d \
./src/sources/DataParser.d \
./src/sources/FibonacciTree.d \
./src/sources/FileManager.d \
./src/sources/Heuristics.d \
./src/sources/ProblemSolver.d 


# Each subdirectory must supply rules for building sources it contributes
src/sources/%.o: ../src/sources/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


