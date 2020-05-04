#ifndef U8G2_COM_ARM_STM32_SSD_I2C_HEADER
#define U8G2_COM_ARM_STM32_SSD_I2C_HEADER

#include "u8g2.h"

#define SSD1306_I2C_ADDRESS 0x78

uint8_t u8x8_byte_stm32_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
uint8_t u8x8_stm32_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);

#endif
