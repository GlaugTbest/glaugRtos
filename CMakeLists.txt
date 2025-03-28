# Generated CMake Pico project file
cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialize pico_sdk from installed location
# (note this can come from environment, CMake cache, etc.)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()

set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)

if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================

set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(blink C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Set FreeRTOS Kernel Path
set(FREERTOS_KERNEL_PATH "C:/Users/glaugtbest/FreeRTOS-LTS/FreeRTOS/FreeRTOS-Kernel")
message(STATUS "Using FreeRTOS Kernel path: ${FREERTOS_KERNEL_PATH}")

# Include FreeRTOS Kernel import CMake
include(${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

# Include directories
include_directories(${FREERTOS_KERNEL_PATH}/include)
include_directories(${CMAKE_SOURCE_DIR})

# Add executable. Default name is the project name, version 0.1
add_executable(blink
    blink.c
)

# Pull in common dependencies
target_link_libraries(blink pico_stdlib FreeRTOS-Kernel FreeRTOS-Kernel-Heap4)

if (PICO_CYW43_SUPPORTED)
    target_link_libraries(blink pico_cyw43_arch_none)
endif()

# Ensure FreeRTOSConfig.h is included
target_include_directories(blink PRIVATE ${CMAKE_SOURCE_DIR}/glaugRtos)

# Create map/bin/hex file etc.
pico_add_extra_outputs(blink)

# Add URL via pico_set_program_url
