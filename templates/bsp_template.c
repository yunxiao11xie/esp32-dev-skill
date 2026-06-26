/**
 * @file bsp_template.c
 * @brief BSP initialization functions
 *
 * BSP layer is primarily macro definitions (see bsp_template.h).
 * This file contains only board-level initialization that crosses
 * multiple peripherals (e.g., bus initialization, power sequencing).
 */

#include "bsp_template.h"
#include "esp_log.h"

static const char *TAG = "bsp";

/* -------------------------------------------------------------------------- */
/*                              Public Functions                               */
/* -------------------------------------------------------------------------- */

esp_err_t bsp_init(void)
{
    esp_err_t ret = ESP_OK;

    ESP_LOGI(TAG, "Board initialization started");

    /* Initialize SPI bus shared by LCD and SD card */
    spi_bus_config_t bus_cfg = {
        .mosi_io_num     = BSP_SPI_MOSI_GPIO,
        .miso_io_num     = BSP_SPI_MISO_GPIO,
        .sclk_io_num     = BSP_SPI_CLK_GPIO,
        .quadwp_io_num   = -1,
        .quadhd_io_num   = -1,
        .max_transfer_sz = BSP_LCD_WIDTH * BSP_LCD_HEIGHT * 2 + 8,
    };

    ret = spi_bus_initialize(BSP_SPI_HOST, &bus_cfg, SPI_DMA_CH_AUTO);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "SPI bus initialization failed: %s", esp_err_to_name(ret));
        return ret;
    }
    ESP_LOGI(TAG, "SPI bus initialized");

    /* Initialize I2C bus for touch/audio */
    i2c_config_t i2c_cfg = {
        .mode             = I2C_MODE_MASTER,
        .sda_io_num       = BSP_I2C_SDA_GPIO,
        .scl_io_num       = BSP_I2C_SCL_GPIO,
        .sda_pullup_en    = GPIO_PULLUP_ENABLE,
        .scl_pullup_en    = GPIO_PULLUP_ENABLE,
        .master.clk_speed = BSP_I2C_CLOCK_SPEED_HZ,
    };

    ret = i2c_param_config(BSP_I2C_PORT, &i2c_cfg);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "I2C config failed: %s", esp_err_to_name(ret));
        return ret;
    }

    ret = i2c_driver_install(BSP_I2C_PORT, i2c_cfg.mode, 0, 0, 0);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "I2C driver install failed: %s", esp_err_to_name(ret));
        return ret;
    }
    ESP_LOGI(TAG, "I2C bus initialized");

    ESP_LOGI(TAG, "Board initialization complete");
    return ESP_OK;
}
