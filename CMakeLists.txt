cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)

project(st7789_demo C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(st7789_demo
    code.c
)

target_link_libraries(st7789_demo
    pico_stdlib
    hardware_spi
)

pico_add_extra_outputs(st7789_demo)