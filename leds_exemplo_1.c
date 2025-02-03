#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

// Definição dos pinos
const uint led_red = 13;
const uint led_yellow = 12;
const uint led_green = 11;
const uint button = 5;

volatile bool running = false; // Flag para impedir nova ativação durante o temporizador

// Callbacks para o temporizador
int64_t turn_off_green(alarm_id_t id, void *user_data);
int64_t turn_off_yellow(alarm_id_t id, void *user_data);
int64_t turn_off_red(alarm_id_t id, void *user_data) {
    gpio_put(led_red, 0);
    add_alarm_in_ms(3000, turn_off_yellow, NULL, false);
    return 0;
}

int64_t turn_off_yellow(alarm_id_t id, void *user_data) {
    gpio_put(led_yellow, 0);
    add_alarm_in_ms(3000, turn_off_green, NULL, false);
    return 0;
}

int64_t turn_off_green(alarm_id_t id, void *user_data) {
    gpio_put(led_green, 0);
    running = false; // Permite nova ativação
    return 0;
}

// Função de debounce e ativação
void button_callback(uint gpio, uint32_t events) {
    if (!running) {
        running = true;
        gpio_put(led_red, 1);
        gpio_put(led_yellow, 1);
        gpio_put(led_green, 1);
        add_alarm_in_ms(3000, turn_off_red, NULL, false);
    }
}

int main() {
    stdio_init_all();
    gpio_init(led_red);
    gpio_set_dir(led_red, GPIO_OUT);
    gpio_init(led_yellow);
    gpio_set_dir(led_yellow, GPIO_OUT);
    gpio_init(led_green);
    gpio_set_dir(led_green, GPIO_OUT);
    gpio_init(button);
    gpio_set_dir(button, GPIO_IN);
    gpio_pull_up(button);

    gpio_set_irq_enabled_with_callback(button, GPIO_IRQ_EDGE_RISE, true, &button_callback);

    while (true) {
        sleep_ms(100);
    }
}
