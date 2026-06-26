/**
 * @file app_template.c
 * @brief Application Layer — <module_name> business logic
 *
 * This file implements the application-level behavior.
 * IMPORTANT: It must NOT call ESP-IDF functions directly.
 * All hardware access goes through the HAL layer.
 */

#include "hal_template.h"

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

static const char *TAG = "app_<module>";

/* ========================================================================== */
/*                              Module State                                   */
/* ========================================================================== */

typedef struct {
    bool    running;
    uint8_t brightness;
} app_ctx_t;

static app_ctx_t s_ctx = { 0 };

/* ========================================================================== */
/*                              Private Functions                              */
/* ========================================================================== */

/**
 * @brief Main application task
 *
 * Implements the core business logic loop.
 * Uses FreeRTOS queues for inter-task communication.
 */
static void app_<module>_task(void *arg)
{
    QueueHandle_t queue = (QueueHandle_t)arg;
    app_event_t   event;

    ESP_LOGI(TAG, "Application task started");

    while (s_ctx.running) {
        /* Wait for events from other tasks or ISRs */
        if (xQueueReceive(queue, &event, pdMS_TO_TICKS(100)) == pdTRUE) {
            switch (event.type) {
                case APP_EVENT_START:
                    ESP_LOGI(TAG, "Received START event");
                    /* Call HAL — the ONLY way to interact with hardware */
                    hal_<module>_set_value(s_ctx.brightness);
                    break;

                case APP_EVENT_STOP:
                    ESP_LOGI(TAG, "Received STOP event");
                    hal_<module>_set_value(0);
                    break;

                case APP_EVENT_SET_BRIGHTNESS:
                    s_ctx.brightness = event.data;
                    ESP_LOGI(TAG, "Brightness set to %u", s_ctx.brightness);
                    hal_<module>_set_value(s_ctx.brightness);
                    break;

                default:
                    ESP_LOGW(TAG, "Unknown event type: %d", event.type);
                    break;
            }
        }
    }

    ESP_LOGI(TAG, "Application task exiting");
    vTaskDelete(NULL);
}

/* ========================================================================== */
/*                              Public Functions                               */
/* ========================================================================== */

esp_err_t app_<module>_start(void)
{
    if (s_ctx.running) {
        ESP_LOGW(TAG, "Already running");
        return ESP_OK;
    }

    /* Initialize HAL first */
    esp_err_t ret = hal_<module>_init(NULL);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "HAL init failed: %s", esp_err_to_name(ret));
        return ret;
    }

    /* Create event queue for inter-task communication */
    QueueHandle_t queue = xQueueCreate(10, sizeof(app_event_t));
    if (queue == NULL) {
        ESP_LOGE(TAG, "Failed to create event queue");
        hal_<module>_deinit();
        return ESP_ERR_NO_MEM;
    }

    /* Create the application task */
    s_ctx.running = true;
    TaskHandle_t task_handle = NULL;

    ret = xTaskCreate(
        app_<module>_task,
        "app_<module>",
        4096,
        (void *)queue,
        5,
        &task_handle
    );

    if (ret != pdPASS) {
        ESP_LOGE(TAG, "Failed to create task");
        s_ctx.running = false;
        vQueueDelete(queue);
        hal_<module>_deinit();
        return ESP_ERR_NO_MEM;
    }

    ESP_LOGI(TAG, "Application started");
    return ESP_OK;
}

esp_err_t app_<module>_stop(void)
{
    s_ctx.running = false;
    hal_<module>_deinit();
    ESP_LOGI(TAG, "Application stopped");
    return ESP_OK;
}
