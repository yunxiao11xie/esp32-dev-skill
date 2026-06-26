/**
 * @file hal_template.h
 * @brief Hardware Abstraction Layer — <module_name> interface
 *
 * This layer hides hardware details behind a clean, portable API.
 * All ESP-IDF driver calls belong here, NOT in the application layer.
 *
 * Usage:
 *   hal_<module>_init();
 *   hal_<module>_set_value(x);
 *   hal_<module>_get_value(&x);
 */

#ifndef HAL_TEMPLATE_H
#define HAL_TEMPLATE_H

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                              Type Definitions                               */
/* ========================================================================== */

/**
 * @brief <module_name> operating mode
 */
typedef enum {
    HAL_TEMPLATE_MODE_OFF = 0,
    HAL_TEMPLATE_MODE_ON,
    HAL_TEMPLATE_MODE_AUTO,
    HAL_TEMPLATE_MODE_MAX,
} hal_template_mode_t;

/**
 * @brief <module_name> configuration parameters
 */
typedef struct {
    hal_template_mode_t mode;
    uint32_t            threshold;
    uint32_t            timeout_ms;
} hal_template_config_t;

/**
 * @brief <module_name> state / status
 */
typedef struct {
    bool        is_initialized;
    bool        is_busy;
    uint32_t    current_value;
    esp_err_t   last_error;
} hal_template_state_t;

/* ========================================================================== */
/*                              Public Functions                               */
/* ========================================================================== */

/**
 * @brief Initialize the <module_name> hardware
 *
 * Configures GPIOs, initializes peripherals, and sets the module to a known
 * idle state. Safe to call multiple times (idempotent).
 *
 * @param[in] config  Pointer to configuration struct (NULL = use defaults)
 * @return
 *   - ESP_OK on success
 *   - ESP_ERR_INVALID_ARG if config is invalid
 *   - ESP_ERR_NO_MEM if resource allocation fails
 *   - ESP_FAIL if hardware initialization fails
 */
esp_err_t hal_<module>_init(const hal_template_config_t *config);

/**
 * @brief Deinitialize the <module_name> hardware
 *
 * Releases all resources and puts the hardware into low-power state.
 *
 * @return ESP_OK on success, otherwise an error code
 */
esp_err_t hal_<module>_deinit(void);

/**
 * @brief Set the output value
 *
 * @param[in] value  Value to set (range depends on implementation)
 * @return
 *   - ESP_OK on success
 *   - ESP_ERR_INVALID_STATE if not initialized
 *   - ESP_ERR_INVALID_ARG if value out of range
 */
esp_err_t hal_<module>_set_value(uint32_t value);

/**
 * @brief Get the current value
 *
 * @param[out] value  Pointer to store the current value
 * @return
 *   - ESP_OK on success
 *   - ESP_ERR_INVALID_STATE if not initialized
 *   - ESP_ERR_INVALID_ARG if value is NULL
 */
esp_err_t hal_<module>_get_value(uint32_t *value);

/**
 * @brief Register a callback for hardware events
 *
 * @param[in] callback  Function pointer (NULL to unregister)
 * @param[in] arg       User context passed to the callback
 * @return ESP_OK on success
 */
esp_err_t hal_<module>_register_callback(void (*callback)(void *arg), void *arg);

#ifdef __cplusplus
}
#endif

#endif /* HAL_TEMPLATE_H */
