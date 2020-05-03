# stm32f103c8t6 - $3 wonder

- ARM Cortex-M3 MCU 
- 64/128 Kbytes Flash
    - I got both variants and none have been official
- 72 MHz CPU
- motor control
- USB and CAN 

# blinky test - stm32cube mx -> mdk-arm -> segger embedded studio

Segger Embedded Studio can import kiel projects. 

This allows cube mx to generate a kiel project and segger to import.

JLink can then be used to debug in gdb.  Segger Embedded Studio is the most familiar IDE and it JLINK does not care that the MCU is a knock off.

**Note:** The knockoff blue-pills I received from china via amzaon are NOT able to be debugged using cube ide through either the cheap st-link usb adapter, the official st link adapter, or jlink ;-(

## stm32cube mx 

![](pics/001-mcuselect.png?raw=true)

![](pics/002-blinky.png?raw=true)

- PC13 is the tamper light - set it to GPIO output
- SYS -> Debug -> Serial Wire

![](pics/006-swd.png?raw=true)

## Generate MDK-ARM Project

![](pics/003-mdk-arm-codegen.png?raw=true)

- Set Toolchain / IDE to MDK-ARM.  

## Import MDK-ARM Project into Segger Embedded Studio

![](pics/004-internal-toolchain.png?raw=true)

![](pics/005-ide.png?raw=true)

- File -> Import Kiel MDK Project ...
- Select Internal Toolchain

## Blinky Code - Main.c

The following blinks the green light - PC13 on my board - every 500ms.  PC13 was setup as GPIO output in cube and codegenerator handled all the initialzation - cool.

    /* USER CODE BEGIN 3 */

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
    HAL_Delay(500);

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
    HAL_Delay(500);

### Blinky in Action

Not very exciting - but at least the board works.

# DSD TECH - 0.91 inch SSD1603 128x32 IIC OLED LCD Screen - 5$ oled

Now that board is confirmed functional let's add a display.

![](pics/007-128x32pin.png?raw=true)

- [Buy one at Amazon](https://www.amazon.com/gp/product/B07D9H83R4)
- [http://www.dsdtech-global.com/2018/05/iic-oled-lcd-u8glib.html]()

Current Libraries
- [https://github.com/olikraus/u8g2/wiki/u8g2setupc#introduction]()
- [https://blog.domski.pl/stm32-hal-driver-for-i2c-oled-display-with-u8glib/]()

Deprecated Libraries
- [https://github.com/olikraus/u8glib]()
- [https://bintray.com/olikraus/u8glib/ARM]()


## u8glib

[https://github.com/olikraus/u8glib]

Using this excellent blog as reference

- [https://blog.domski.pl/stm32-hal-driver-for-i2c-oled-display-with-u8glib/]
- [https://github.com/wdomski/SSD1603-example/tree/master/fntsrc]()

- Download the repo as a zip.
- Create folder Drivers\u8glib
    - Copy contents of csrc\ into u8glib
- Add files to the segger project
   -  Remove the drivers that are not relevant to save flash space
-  Main Driver File
   -  u8g_dev_ssd1306_128x32.c


## Modify Code

**inc\u8g_com_arm_stm32.h**

    /**
    * Author Wojciech Domski <Wojciech.Domski@gmail.com>
    * www: www.Domski.pl
    */

    #ifndef U8G_COM_ARM_STM32_SSD_I2C_HEADER
    #define U8G_COM_ARM_STM32_SSD_I2C_HEADER

    #include "u8g.h"

    #define SSD1306_I2C_ADDRESS 0x78

    uint8_t u8g_com_arm_stm32_ssd_i2c_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr);

    #endif


## main.c 

### #include u8g_com_arm_stm32.h

    /* USER CODE BEGIN Includes */
    #include "u8g_com_arm_stm32.h"

### Declare u8g_t instance

    /* USER CODE BEGIN 1 */
    u8g_t u8g;
    /* USER CODE END 1 */

### Initialize iic paramaters

    /* USER CODE BEGIN 2 */
    u8g_InitComFn(&u8g, &u8g_dev_ssd1306_128x32_i2c, u8g_com_arm_stm32_ssd_i2c_fn);

### Add fonts

- Create fonts directory
- Copy from [https://github.com/wdomski/SSD1603-example/tree/master/fntsrc]()

Get the fonts here:
- [https://github.com/olikraus/u8glib/tree/master/fntsrc]()

Font Converter Tool
- [https://github.com/olikraus/u8glib/wiki/bdf2u8g]()

    bdf2u8g.exe -b 32 -e 127 5x7.bdf font5x7 font5x7.c

### main loop - draw stuff

    u8g_FirstPage(&u8g);
    do {
        u8g_SetFont(&u8g, u8g_font_profont12);
        u8g_DrawStr(&u8g, 0, 12,  "    Hello there :)");
        u8g_DrawStr(&u8g, 0, 26, "    Visit my blog");
    } while (u8g_NextPage(&u8g));

    HAL_Delay(2000);

    u8g_FirstPage(&u8g);
    do {
        u8g_SetFont(&u8g, u8g_font_profont12);
        u8g_DrawStr(&u8g, 0, 15, "blog.domski.pl");
    } while (u8g_NextPage(&u8g));

    HAL_Delay(2000);

### Running

![](pics/008-run.jpeg?raw=true)
