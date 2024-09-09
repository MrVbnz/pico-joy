cmake_minimum_required(VERSION 3.13)

# TinyUSB Settings
set(TINY_USB_PATH $ENV{PICO_SDK_PATH}/lib/tinyusb)
set(FAMILY rp2040)
set(BOARD raspberry_pi_pico)

# Includes
include(${TINY_USB_PATH}/hw/bsp/family_support.cmake)

set(PROJECT pico_joy)
project(${PROJECT})

## Init
family_initialize_project(${PROJECT} ${CMAKE_CURRENT_LIST_DIR})
## Set main executable
add_executable(${PROJECT} src/main.c)
pico_add_extra_outputs(${PROJECT})
## Pico SDK Board settings
pico_enable_stdio_usb(${PROJECT} 0)
pico_enable_stdio_uart(${PROJECT} 0)

target_sources(${PROJECT} PRIVATE
    src/main.c
    src/blinker.c
    src/pico_hid.c
    src/usb_descriptors.c
)

target_include_directories(${PROJECT} PRIVATE
    src
    ${TINY_USB_PATH}/src/class/hid/
)

target_link_libraries(${PROJECT} pico_stdlib tinyusb_device tinyusb_board hardware_adc)