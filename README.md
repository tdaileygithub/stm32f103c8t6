# stm32f103c8t6 - $3 wonder

- ARM Cortex-M3 MCU 
- 64/128 Kbytes Flash
    - I got both variants and none have been official
- 72 MHz CPU
- motor control
- USB and CAN 

# blinky test

## stm32cube mx 

- PC13 is the tamper light - set it to GPIO output

## Generate MDK-ARM Project

Set Toolchain / IDE to MDK-ARM.  

Segger Embedded Studio can import these projects and this allows cube mx to generate the project and segger to compile and run. 

This is necessary because the knockoff blue-pills I received from china are NOT able to be debugged using cube ide through either the cheap st-link usb adapter OR the official st link adapter.  Their programmer knows it is a fake MCU and bails.

## Import MDK-ARM Project into Segger Embedded Studio

- File -> Import Kiel MDK Project ...
- Select Internal Toolchain