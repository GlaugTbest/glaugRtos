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

void button_task(void *pvParameters) {
    while (1) {
        button_pressed = !gpio_get(BUTTON_PIN);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void led_task(void *pvParameters) {
    while (1) {
        if (button_pressed) {
            gpio_put(LED_PIN, 1);
        } else {
            gpio_put(LED_PIN, 0);
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

int main() {
    stdio_init_all();

    init_led();
    init_button();

    xTaskCreate(button_task, "Button Task", 256, NULL, 1, NULL);
    xTaskCreate(led_task, "LED Task", 256, NULL, 2, NULL);

    vTaskStartScheduler();

    while (1) {
        __wfi();
    }

    return 0;
}
