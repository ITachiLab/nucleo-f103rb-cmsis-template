cmake_minimum_required(VERSION 3.2)

set(CMAKE_C_STANDARD 11)
set(CMAKE_TOOLCHAIN_FILE "arm.cmake")

project(nucleo_template C ASM)

add_executable(nucleo_template 
	platform/startup_stm32f103xb.s
    platform/system_stm32f1xx.c
	main/main.c)

target_include_directories(nucleo_template PUBLIC
	main
	platform)

target_link_libraries(nucleo_template c m)

add_custom_target(program "openocd" "-f board/st_nucleo_f103rb.cfg -c \"program nucleo_template reset exit\"")

add_definitions(-DSTM32F103xB)
