=====================
Nucleo F103RB & CMSIS
=====================

This repository contains a template of CMSIS project for Nucleo F103RB
development board. I created it because I wasn't able to find
anything similar with only CMSIS and a minimum amount of code needed to get the
board up and running.

I completely understand the purpose and assumptions of HAL, but I'm not a big
fan of it. I started my STM32 journey when StdPeriph was a big thing, and up
to this day I still think that was the best what could happen to STM32 world.
I wasn't able to find a good template for HAL-free projects where only a minimum
amount of code is used to setup everything, so I created ony by myself.

Content description
*******************

main
----

This directory is dedicated to user code. The only source file there is
``main.c`` with a bunch of basic clock configurations, and a simple routine
lighting up the user LED on a board.

platform
--------

The directory with files specific for this board and MCU. It includes two
Git submodules:

* **cmsis-core** - basic CMSIS sources and headers,
* **cmsis-device-f1** - additional sources and headers specific to STM32.

In addition to that, there are a couple of other files:

* **CMakeLists.txt** - CMake configuration for the platform project,
* **gcc-arm-none-eabi.cmake** - toolchain file,
* **st_nucleo_f103rb.cfg** - board configuration for OpenOCD.

Building on Linux
*****************

Toolchain
---------

The first step is to obtain a correct toolchain. STMicroelectronics maintains a
project named: `STM32CubeCLT <https://www.st.com/en/development-tools/stm32cubeclt.html>`_,
which basically is just a set of tools to build and debug STM32 projects without
that CubeIDE and CubeMX overhead. Once installed, toolchain binaries can be
found in: ``<CUBECLT INSTALL DIR>/GNU-tools-for-STM32/bin``. It's enough to put
this path to system PATH to have all tools available in command line.

Alternatively, a GCC toolchain for ARM can be used. The best way to get it is to
download an appropriate package from the `official website <https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads>`_.
It should work equally well, however, some people complaint that specific
versions couldn't compile their projects (due to some bizarre compilation
errors).

Building
--------

First, create a build directory, and generate makefiles::

    $ mkdir build
    $ cd build
    $ cmake -G "Unix Makefiles" ..

Now, there are two options to build a project, either by simply invoking
``make``, or by using CMake command: ``cmake --build .``

The default target will generate both ``.elf`` and ``.hex`` files. Use your
favorite method to transfer them to MCU, or if you have OpenOCD installed, there
is a dedicated target that can flash the MCU for you::

    $ make Flash

Or with a CMake command::

    $ cmake --build . -t Flash

You don't have to manually rebuild the project each time before flashing. The
``Flash`` target depends on the project's output, so it is always kept up to
date before flashing.