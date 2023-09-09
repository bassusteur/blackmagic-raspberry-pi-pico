cmake_minimum_required(VERSION 3.15...3.25)

#set(CMAKE_TOOLCHAIN_FILE ./toolchain-arm.cmake)

include(pico_sdk_import.cmake)

include(pico_extras_import_optional.cmake)

project(blackmagicrp2040 VERSION 0.1 LANGUAGES C CXX ASM)

pico_sdk_init()

#add_definitions(-DRP2040 -DNO_LIBOPENCM3 -Dset_idle_state)
add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        -Wno-maybe-uninitialized
        -g
        )

include_directories(../../include ../../target rp2040 ../rp2040)

add_executable( blackmagicrp2040 ../../main.c ../../gdb_main.c ../../command.c 
                ../../crc32.c ../../exception.c ../../gdb_hostio.c ../../gdb_packet.c 
                ../../hex_utils.c ../../maths_utils.c ../../morse.c ../../remote.c 
                ../../rtt.c ../../timing.c ../rp2040/platform.c 
                rp2040/timing_rp2040.c rp2040/gdb_if.c rp2040/usb.c rp2040/jtagtap.c 
                rp2040/swdptap.c rp2040/usb_serial.c rp2040/usb_descriptors.c rp2040/multicore_rp2040.c
                
                ../../target/adiv5_jtag.c ../../target/adiv5_swd.c ../../target/adiv5.c ../../target/ch32f1.c 
                ../../target/cortex.c ../../target/cortexa.c ../../target/cortexm.c ../../target/efm32.c 
                ../../target/gdb_reg.c ../../target/hc32l110.c ../../target/imxrt.c ../../target/jtag_devs.c 
                ../../target/jtag_scan.c ../../target/jtagtap_generic.c
                ../../target/kinetis.c ../../target/lmi.c ../../target/lpc_common.c ../../target/lpc11xx.c
                ../../target/lpc15xx.c ../../target/lpc17xx.c ../../target/lpc40xx.c ../../target/lpc43xx.c
                ../../target/lpc55xx.c ../../target/lpc546xx.c ../../target/msp432e4.c ../../target/msp432p4.c
                ../../target/nrf51.c ../../target/nrf91.c ../../target/nxpke04.c ../../target/renesas.c 
                ../../target/rp.c ../../target/sam3x.c ../../target/sam4l.c ../../target/samd.c
                ../../target/samx5x.c ../../target/sfdp.c ../../target/spi.c ../../target/stm32f1.c
                ../../target/stm32f4.c ../../target/stm32g0.c ../../target/stm32h5.c ../../target/stm32h7.c
                ../../target/stm32l0.c ../../target/stm32l4.c ../../target/swdptap_generic.c ../../target/target_flash.c 
                ../../target/target_probe.c ../../target/target.c
        )

target_link_libraries(blackmagicrp2040 pico_stdlib pico_multicore pico_unique_id tinyusb_device tinyusb_board)

pico_add_extra_outputs(blackmagicrp2040)