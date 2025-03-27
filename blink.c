#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"

#define BUTTON_PIN 5
#define LED_PIN 12

bool button_pressed = false;

void init_led() {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
}

void init_button() {
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);
}

void button_led_task(void *pvParameters) {
    while (1) {
        if (!gpio_get(BUTTON_PIN)) {
            vTaskDelay(100 / portTICK_PERIOD_MS);
            gpio_put(LED_PIN, 1);
        } else {
            gpio_put(LED_PIN, 0);
        }

        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

int main() {
    stdio_init_all();
    init_led();
    init_button();
    xTaskCreate(button_led_task, "Button LED Task", 256, NULL, 1, NULL);
    vTaskStartScheduler();

    while (1) {
        __wfi();
    }

    return 0;
}
