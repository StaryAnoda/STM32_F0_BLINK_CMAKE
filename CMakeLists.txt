cmake_minimum_required(VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE Toolchain-arm-gcc.cmake)

# Allow assembler
enable_language(ASM)

project(BLINK)

set(INCLUDE_DIRS
	BLINK/Drivers/CMSIS/Device/ST/STM32F0xx/Include
	BLINK/Drivers/CMSIS/Core/Include
)

set(C_SRCS
	BLINK/src/main.c
	BLINK/src/system_stm32f0xx.c
)

set(ASM_SRCS
   BLINK/startup_stm32f030x6.s
)

set(GLOBAL_DEFINES
    -DSTM32F030x6
)

set(LINKED_LIBS

)

link_directories(

)

include_directories(${INCLUDE_DIRS})
add_definitions(${GLOBAL_DEFINES})

include(compiler_flags.cmake)

# generate elf file
add_arm_executable(${CMAKE_PROJECT_NAME} ${C_SRCS} ${ASM_SRCS})

arm_link_libraries(${CMAKE_PROJECT_NAME} ${LINKED_LIBS})
