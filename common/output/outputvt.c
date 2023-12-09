#include <stdio.h>
#include "driver/gpio.h"
#include <esp_log.h>
#include "outputvt.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static SemaphoreHandle_t xButtonSemaphore = NULL;
static ButtonCallback_t buttonCallback = NULL;

static void IRAM_ATTR button_isr_handler(void *arg) {
    xSemaphoreGiveFromISR(xButtonSemaphore, NULL);
}

void button_handler_init(gpio_num_t button_gpio, ButtonCallback_t callback) {
    // Khởi tạo GPIO cho nút
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << button_gpio),
        .mode = GPIO_MODE_INPUT,
        .intr_type = GPIO_INTR_POSEDGE,
    };
    gpio_config(&io_conf);

    // Tạo semaphore để xử lý ngắt
    xButtonSemaphore = xSemaphoreCreateBinary();

    // Lưu trữ callback
    buttonCallback = callback;

    // Khởi tạo ngắt cho nút
    gpio_install_isr_service(0);
    gpio_isr_handler_add(button_gpio, button_isr_handler, NULL);

    // Tạo task để xử lý sự kiện khi nút được nhấn
    xTaskCreate(button_handler_task, "button_handler_task", 2048, NULL, 13, NULL);
}

void button_handler_task(void *arg) {
    while (1) {
        if (xSemaphoreTake(xButtonSemaphore, portMAX_DELAY)) {
            if (buttonCallback != NULL) {
                buttonCallback();
            }
        }
    }
}



void output_io_create(gpio_num_t gpio_num)
{
    gpio_pad_select_gpio(gpio_num);
    gpio_set_direction(gpio_num, GPIO_MODE_INPUT_OUTPUT);
     
}
void output_io_set_level(gpio_num_t gpio_num, int level)
{
    gpio_set_level(gpio_num,level);
}
void toggle(gpio_num_t gpio_num)
{
    int status = gpio_get_level(gpio_num);
    gpio_set_level(gpio_num,1-status);
}

