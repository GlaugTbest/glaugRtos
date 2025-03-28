#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#define BUTTON_PIN 5
#define LED_PIN 12

QueueHandle_t buttonQueue;

void init_hardware() {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);
}

void button_task(void *pvParameters) {
    bool button_state;
    while (1) {
        button_state = !gpio_get(BUTTON_PIN);
        xQueueSend(buttonQueue, &button_state, portMAX_DELAY);
        printf("Task 1: Botão lido - Estado: %d\n", button_state);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void processing_task(void *pvParameters) {
    bool button_state;
    while (1) {
        if (xQueueReceive(buttonQueue, &button_state, portMAX_DELAY)) {
            printf("Task 2: Processando botão - Estado: %d\n", button_state);
            if (button_state) {
                xQueueSend(buttonQueue, &button_state, portMAX_DELAY);
            }
        }
    }
}

void led_task(void *pvParameters) {
    bool led_state;
    while (1) {
        if (xQueueReceive(buttonQueue, &led_state, portMAX_DELAY)) {
            gpio_put(LED_PIN, led_state);
            printf("Task 3: LED %s\n", led_state ? "ACESO" : "APAGADO");
        }
    }
}

int main() {
    stdio_init_all();
    init_hardware();
    buttonQueue = xQueueCreate(5, sizeof(bool));

    if (buttonQueue == NULL) {
        printf("Erro ao criar fila!\n");
        while (1);
    }

    xTaskCreate(button_task, "Button Task", 256, NULL, 1, NULL);
    xTaskCreate(processing_task, "Processing Task", 256, NULL, 2, NULL);
    xTaskCreate(led_task, "LED Task", 256, NULL, 3, NULL);

    vTaskStartScheduler();

    while (1);
    return 0;
}
