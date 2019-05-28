cmake_minimum_required(VERSION 3.2)

set(CMAKE_C_STANDARD 11)
set(CMAKE_TOOLCHAIN_FILE "arm.cmake")

set(TARGET "main")

set(TARGET_ELF "${TARGET}.elf")
set(TARGET_HEX "${TARGET}.hex")
set(TARGET_BIN "${TARGET}.bin")

project(nucleo_template C ASM)

add_executable(${TARGET_ELF}
    platform/startup_stm32f103xb.s
    platform/system_stm32f1xx.c
    main/main.c)

target_include_directories(${TARGET_ELF} PUBLIC
    main
    platform)

add_custom_target(${TARGET_HEX} ALL COMMAND ${OBJCOPY} -O ihex ${TARGET_ELF} ${TARGET_HEX})
add_dependencies(${TARGET_HEX} ${TARGET_ELF})

add_custom_target(${TARGET_BIN} ALL COMMAND ${OBJCOPY} -O binary -S ${TARGET_ELF} ${TARGET_BIN})
add_dependencies(${TARGET_BIN} ${TARGET_ELF})

add_custom_command(TARGET ${TARGET_ELF} POST_BUILD COMMAND ${SIZE} ${TARGET_ELF})

add_custom_target(program "openocd" "-f board/st_nucleo_f103rb.cfg -c \"program ${TARGET_ELF} reset exit\"")