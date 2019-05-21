set(CMAKE_SYSTEM_NAME "Generic")
set(CMAKE_SYSTEM_PROCESSOR "arm")

# Adapt this to a valid toolchain location
set(tools "C:/opt/gcc-arm-none-eabi-6-2017-q2-update-win32")

set(prefix "arm-none-eabi")
set(compiler_flags "--specs=nosys.specs -Wall -fdata-sections -ffunction-sections")
set(mcu "-mcpu=cortex-m3 -mthumb")

set(CMAKE_C_COMPILER "${tools}/bin/${prefix}-gcc.exe")
set(CMAKE_C_COMPILER_AR "${tools}/bin/${prefix}-ar.exe")
set(CMAKE_ASM_COMPILER "${tools}/bin/${prefix}-gcc.exe")
set(CMAKE_LINKER "${tools}/bin/${prefix}-ld.exe")

set(CMAKE_C_FLAGS "${mcu} ${compiler_flags}")
set(CMAKE_ASM_FLAGS "${mcu} ${compiler_flags}")
set(CMAKE_EXE_LINKER_FLAGS "${mcu} -T ${CMAKE_SOURCE_DIR}/platform/STM32F103XB_FLASH.ld")