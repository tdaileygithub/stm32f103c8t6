# stm32f103c8t6 - $3 wonder

- ARM Cortex-M3 MCU 
- 64/128 Kbytes Flash
    - I got both variants and none have been official
- 72 MHz CPU
- motor control
- USB and CAN 

# blinky test

## stm32cube mx 

![](pics/001-mcuselect.png?raw=true)

![](pics/002-blinky.png?raw=true)

- PC13 is the tamper light - set it to GPIO output
- SYS -> Debug -> Serial Wire

![](pics/006-swd.png?raw=true)

## Generate MDK-ARM Project

![](pics/003-mdk-arm-codegen.png?raw=true)

- Set Toolchain / IDE to MDK-ARM.  

Segger Embedded Studio can import these projects and this allows cube mx to generate the project and segger to compile and run. 

This is necessary because the knockoff blue-pills I received from china are NOT able to be debugged using cube ide through either the cheap st-link usb adapter OR the official st link adapter.  Their programmer knows it is a fake MCU and bails.

## Import MDK-ARM Project into Segger Embedded Studio

![](pics/004-internal-toolchain.png?raw=true)

![](pics/005-ide.png?raw=true)

- File -> Import Kiel MDK Project ...
- Select Internal Toolchain

## Blinky Code - Main.c

The following will blink the green light - PC13 on my board - every 500ms.  PC13 was setup as GPIO output in cube and the codegenerator handled all the init.

    /* USER CODE BEGIN 3 */

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
    HAL_Delay(500);

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
    HAL_Delay(500);

### Blinky in Action

Not very exciting - but at least the board works.

# DSD TECH - SSD1603 based IIC OLED LCD Screen - 4$ oled

[http://www.dsdtech-global.com/2018/05/iic-oled-lcd-u8glib.html]()

## Screen Variants

- 0.91 inch (128*32)
- 0.96 inch (128*64)

Libraries
- [https://github.com/olikraus/u8g2/wiki/u8g2setupc#introduction]()
- [https://blog.domski.pl/stm32-hal-driver-for-i2c-oled-display-with-u8glib/]()

Deprecated Libraries
- [https://github.com/olikraus/u8glib]()
- [https://bintray.com/olikraus/u8glib/ARM]()
