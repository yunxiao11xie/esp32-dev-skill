/**
 * @file hal_template.c
 * @brief Hardware Abstraction Layer — <module_name> implementation
 *
 * Implements the HAL interface defined in hal_template.h.
 * All ESP-IDF driver interactions are encapsulated here.
 */

#include "hal_template.h"
#include "bsp_template.h"

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

static const char *TAG = "hal_<module>";

/* ========================================================================== */
/*                              Module State                                   */
/* ========================================================================== */

/**
 * Module context — all state is static, no global variables exposed in header.
 */
typedef struct {
    bool                initialized;
    hal_template_mode_t mode;
    uint32_t            value;
    void               (*callback)(void *arg);
    void               *callback_arg;
} hal_ctx_t;

static hal_ctx_t s_ctx = { 0 };

/* ========================================================================== */
/*                              Private Helpers                                */
/* ========================================================================== */

static esp_err_t hal_<module>_configure_gpio(void)
{
    /* GPIO configuration example — replace with actual hardware setup */
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << BSP_LED_GPIO_NUM),
        .mode         = GPIO_MODE_OUTPUT,
        .pull_up_en   = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type    = GPIO_INTR_DISABLE,
    };

    esp_err_t ret = gpio_config(&io_conf);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "GPIO config failed: %s", esp_err_to_name(ret));
    }
    return ret;
}

/* ========================================================================== */
/*                              Public Functions                               */
/* ========================================================================== */

esp_err_t hal_<module>_init(const hal_template_config_t *config)
{
    if (s_ctx.initialized) {
        ESP_LOGW(TAG, "Already initialized");
        return ESP_OK;
    }

    if (config != NULL) {
        s_ctx.mode = config->mode;
    } else {
        s_ctx.mode = HAL_TEMPLATE_MODE_OFF;
    }

    esp_err_t ret = hal_<module>_configure_gpio();
    if (ret != ESP_OK) {
        return ret;
    }

    /* Set initial output state */
    gpio_set_level(BSP_LED_GPIO_NUM, 0);

    s_ctx.value       = 0;
    s_ctx.callback    = NULL;
    s_ctx.callback_arg = NULL;
    s_ctx.initialized = true;

    ESP_LOGI(TAG, "Initialized (mode=%d)", s_ctx.mode);
    return ESP_OK;
}

esp_err_t hal_<module>_deinit(void)
{
    if (!s_ctx.initialized) {
        return ESP_OK;
    }

    /* Reset GPIO to safe state */
    gpio_reset_pin(BSP_LED_GPIO_NUM);

    memset(&s_ctx, 0, sizeof(s_ctx));
    ESP_LOGI(TAG, "Deinitialized");
    return ESP_OK;
}

esp_err_t hal_<module>_set_value(uint32_t value)
{
    if (!s_ctx.initialized) {
        ESP_LOGE(TAG, "Not initialized");
        return ESP_ERR_INVALID_STATE;
    }

    s_ctx.value = value;
    gpio_set_level(BSP_LED_GPIO_NUM, value ? 1 : 0);

    ESP_LOGD(TAG, "Value set to %" PRIu32, value);
    return ESP_OK;
}

esp_err_t hal_<module>_get_value(uint32_t *value)
{
    if (!s_ctx.initialized) {
        return ESP_ERR_INVALID_STATE;
    }
    if (value == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    *value = s_ctx.value;
    return ESP_OK;
}

esp_err_t hal_<module>_register_callback(void (*callback)(void *arg), void *arg)
{
    if (!s_ctx.initialized) {
        return ESP_ERR_INVALID_STATE;
    }

    s_ctx.callback    = callback;
    s_ctx.callback_arg = arg;
    return ESP_OK;
}
