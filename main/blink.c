#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "freertos/semphr.h"
#include "outputvt.h"
#define BUTTON_GPIO GPIO_NUM_0

void button_pressed_callback(void) {
    // Xử lý khi nút được nhấn
    printf("Button pressed!\n");
}

void app_main(void) {

    button_handler_init(GPIO_NUM_0, button_pressed_callback);

    // Thêm các hành động chính của chương trình ở đây
    while (1) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
