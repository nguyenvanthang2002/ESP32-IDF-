#ifndef OUTPUTVT_H
#define OUTPUTVT_H
#include "esp_err.h"
#include "hal/gpio_types.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

#define EVENT_BIT_BUTTON (1 << 0)
#define LONG_PRESS_DELAY 3000 // 3 giây




typedef void (*ButtonCallback_t)(void);

void button_handler_init(gpio_num_t button_gpio, ButtonCallback_t callback);
void button_handler_task(void *arg);
void button_long_press_task(void *arg);

TickType_t get_button_press_duration();




//void input_io_create(gpio_num_t gpio_num, interrupt_type_elde_t type);
void output_io_set_level(gpio_num_t gpio_num, int level);
void output_io_create(gpio_num_t gpio_num);
void toggle(gpio_num_t gpio_num);


#endif