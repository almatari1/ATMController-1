################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/atm_common_defs.cc \
../src/atm_controller.cc \
../src/atm_hardware_factory.cc \
../src/atm_hardware_interface.cc \
../src/bank_api.cc \
../src/bank_server_connection.cc \
../src/console_io.cc \
../src/io_factory.cc \
../src/io_interface.cc \
../src/main.cc \
../src/sample_atm_hardware.cc \
../src/sample_bank.cc 

CC_DEPS += \
./src/atm_common_defs.d \
./src/atm_controller.d \
./src/atm_hardware_factory.d \
./src/atm_hardware_interface.d \
./src/bank_api.d \
./src/bank_server_connection.d \
./src/console_io.d \
./src/io_factory.d \
./src/io_interface.d \
./src/main.d \
./src/sample_atm_hardware.d \
./src/sample_bank.d 

OBJS += \
./src/atm_common_defs.o \
./src/atm_controller.o \
./src/atm_hardware_factory.o \
./src/atm_hardware_interface.o \
./src/bank_api.o \
./src/bank_server_connection.o \
./src/console_io.o \
./src/io_factory.o \
./src/io_interface.o \
./src/main.o \
./src/sample_atm_hardware.o \
./src/sample_bank.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


