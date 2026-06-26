/**
 * @file bsp_template.h
 * @brief Board Support Package — hardware definitions for <board_name>
 *
 * This file contains ALL hardware-specific macros and pin assignments.
 * NO logic or function implementations belong here — only #defines.
 *
 * @note Modify these values to match your actual hardware configuration.
 */

#ifndef BSP_TEMPLATE_H
#define BSP_TEMPLATE_H

#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "driver/i2c.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                            Pin Assignments                                  */
/* ========================================================================== */

/** LED */
#define BSP_LED_GPIO_NUM            GPIO_NUM_2
#define BSP_LED_ACTIVE_HIGH         1

/** Button */
#define BSP_BUTTON_GPIO_NUM         GPIO_NUM_0
#define BSP_BUTTON_ACTIVE_LOW       1
#define BSP_BUTTON_DEBOUNCE_MS      50

/** SPI Bus */
#define BSP_SPI_HOST                SPI2_HOST
#define BSP_SPI_MOSI_GPIO           GPIO_NUM_11
#define BSP_SPI_MISO_GPIO           GPIO_NUM_13
#define BSP_SPI_CLK_GPIO            GPIO_NUM_12
#define BSP_SPI_CS_GPIO             GPIO_NUM_10
#define BSP_SPI_CLOCK_SPEED_HZ      40 * 1000 * 1000   /* 40 MHz */

/** I2C Bus */
#define BSP_I2C_PORT                I2C_NUM_0
#define BSP_I2C_SDA_GPIO            GPIO_NUM_8
#define BSP_I2C_SCL_GPIO            GPIO_NUM_9
#define BSP_I2C_CLOCK_SPEED_HZ      400 * 1000          /* 400 kHz */

/** UART */
#define BSP_UART_PORT               UART_NUM_0
#define BSP_UART_TX_GPIO            GPIO_NUM_43
#define BSP_UART_RX_GPIO            GPIO_NUM_44
#define BSP_UART_BAUD_RATE          115200

/* ========================================================================== */
/*                          Peripheral Configuration                           */
/* ========================================================================== */

/** LCD Display */
#define BSP_LCD_PIN_CS              GPIO_NUM_10
#define BSP_LCD_PIN_DC              GPIO_NUM_14
#define BSP_LCD_PIN_RST             GPIO_NUM_15
#define BSP_LCD_PIN_BL              GPIO_NUM_16
#define BSP_LCD_WIDTH               480
#define BSP_LCD_HEIGHT              320
#define BSP_LCD_HOST                SPI2_HOST

/** SD Card */
#define BSP_SD_CARD_CS              GPIO_NUM_4
#define BSP_SD_CARD_HOST            SPI2_HOST

/* ========================================================================== */
/*                              Timing Constants                               */
/* ========================================================================== */

#define BSP_TASK_STACK_SIZE         4096
#define BSP_TASK_PRIORITY           5
#define BSP_LED_BLINK_PERIOD_MS     1000

#ifdef __cplusplus
}
#endif

#endif /* BSP_TEMPLATE_H */
