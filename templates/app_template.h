/**
 * @file app_template.h
 * @brief Application Layer — <module_name> interface
 *
 * Application-level business logic. All hardware access is delegated
 * to the HAL layer — NO ESP-IDF calls in application code.
 */

#ifndef APP_TEMPLATE_H
#define APP_TEMPLATE_H

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                              Type Definitions                               */
/* ========================================================================== */

/**
 * @brief Application event types for inter-task communication
 */
typedef enum {
    APP_EVENT_START            = 0,
    APP_EVENT_STOP,
    APP_EVENT_SET_BRIGHTNESS,
} app_event_type_t;

/**
 * @brief Application event structure (passed via FreeRTOS queue)
 */
typedef struct {
    app_event_type_t type;
    uint32_t         data;
    void            *context;
} app_event_t;

/* ========================================================================== */
/*                              Public Functions                               */
/* ========================================================================== */

/**
 * @brief Start the application
 *
 * Initializes HAL, creates event queue, and spawns the main task.
 *
 * @return
 *   - ESP_OK on success
 *   - ESP_ERR_NO_MEM if queue or task creation fails
 *   - Propagates error from hal_<module>_init()
 */
esp_err_t app_<module>_start(void);

/**
 * @brief Stop the application
 *
 * Signals the task to exit and deinitializes HAL.
 *
 * @return ESP_OK on success
 */
esp_err_t app_<module>_stop(void);

/**
 * @brief Send an event to the application task
 *
 * Thread-safe; uses FreeRTOS queue under the hood.
 *
 * @param[in] event  Pointer to the event to send
 * @return
 *   - ESP_OK on success
 *   - ESP_ERR_INVALID_STATE if not running
 *   - ESP_ERR_TIMEOUT if queue is full
 */
esp_err_t app_<module>_send_event(const app_event_t *event);

#ifdef __cplusplus
}
#endif

#endif /* APP_TEMPLATE_H */
