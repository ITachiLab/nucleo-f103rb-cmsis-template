set(CMAKE_SYSTEM_NAME "Generic")
set(CMAKE_SYSTEM_PROCESSOR "arm")

# Adapt this to a valid toolchain location
if (UNIX)
set(tools "/opt/gcc-arm-none-eabi-6-2017-q2-update")
set(suffix "")
endif (UNIX)

if (WIN32)
set(tools "C:/opt/gcc-arm-none-eabi-6-2017-q2-update-win32")
set(suffix ".exe")
endif (WIN32)

set(prefix "arm-none-eabi")
set(compiler_flags "-Wall -fdata-sections -ffunction-sections -Os")
set(linker_script "${CMAKE_SOURCE_DIR}/platform/STM32F103XB_FLASH.ld")
set(mcu "-mcpu=cortex-m3 -mthumb")
set(linker_flags "${mcu} -specs=nano.specs -T${linker_script} -lc -lm -lnosys -Wl,--gc-sections")

set(CMAKE_C_COMPILER "${tools}/bin/${prefix}-gcc${suffix}")
set(CMAKE_C_COMPILER_AR "${tools}/bin/${prefix}-ar${suffix}")
set(CMAKE_ASM_COMPILER "${tools}/bin/${prefix}-gcc${suffix}")
set(CMAKE_LINKER "${tools}/bin/${prefix}-ld${suffix}")

set(CMAKE_C_FLAGS "${mcu} ${compiler_flags}")
set(CMAKE_ASM_FLAGS "${mcu} ${compiler_flags}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${linker_flags}") 
