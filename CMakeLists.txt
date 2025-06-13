cmake_minimum_required(VERSION 3.22)

# This is a very important file, it configures compiler and sets up handy variables.
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/platform/gcc-arm-none-eabi.cmake)

project(Nucleo C ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

# A set of handy definitions with file names.
set(ELF_FILE "${CMAKE_PROJECT_NAME}.elf")
set(HEX_FILE "${CMAKE_PROJECT_NAME}.hex")

# Use "Debug" build type by default.
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif ()

# Add sub-project with platform dependencies i.e. all of that CMSIS stuff.
add_subdirectory(platform)

# This is the main build target.
add_executable(${CMAKE_PROJECT_NAME} main/main.c)

# Add more sources to executable.
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
        # Add user sources here
)

# Link more libraries. Initially, the it links only with the library created from the "platform"
# sub-project.
target_link_libraries(${CMAKE_PROJECT_NAME} platlib
        # Add user defined libraries here.
)

# Add include directories.
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE main/include
        # Add user defined include directories here.
)

# Add project symbols (macros).
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
        # Add user defined symbols
)

# Build an Intel HEX file.
add_custom_command(OUTPUT ${HEX_FILE}
        COMMAND "${CMAKE_OBJCOPY}" "-O" "ihex" "${ELF_FILE}" "${HEX_FILE}"
        DEPENDS "${ELF_FILE}"
        VERBATIM
)
add_custom_target(IntelHex ALL DEPENDS ${HEX_FILE})

# Add a custom "Flash" target for flashing the board with openocd.
add_custom_target(Flash
        "openocd"
        "-s" "${CMAKE_SOURCE_DIR}/platform"
        "-f" "st_nucleo_f103rb.cfg"
        "-c" "program ${ELF_FILE} reset exit"
        VERBATIM
)
# Make sure the binary is up to date before flashing.
add_dependencies(Flash ${CMAKE_PROJECT_NAME})