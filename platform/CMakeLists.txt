cmake_minimum_required(VERSION 3.22)

enable_language(C ASM)

set(CMSIS_CORE ${CMAKE_CURRENT_SOURCE_DIR}/cmsis-core)
set(CMSIS_ST ${CMAKE_CURRENT_SOURCE_DIR}/cmsis-device-f1)

set(CMSIS_Include_Dirs
    ${CMSIS_CORE}/Include
    ${CMSIS_CORE}/Core/Include
    ${CMSIS_ST}/Include
)

set(CMSIS_Platform_Srcs
    ${CMSIS_ST}/Source/Templates/system_stm32f1xx.c
    ${CMSIS_ST}/Source/Templates/gcc/startup_stm32f103xb.s
)

# Make the "platlib" an object-only library, that means the objects won't be archived to produce
# a single library.
add_library(platlib OBJECT
    ${CMSIS_Platform_Srcs}
)

target_include_directories(platlib PUBLIC
    ${CMSIS_Include_Dirs}
)

target_compile_definitions(platlib PUBLIC
    STM32F103xB
)