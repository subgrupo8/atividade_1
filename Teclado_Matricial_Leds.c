#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"

#define ROWS 4
#define COLS 4

#define LED_VERMELHO 13
#define LED_AZUL 12
#define LED_VERDE 11
#define BUZZER 21

const uint8_t rows_pins[ROWS] = {8, 7, 6, 5};
const uint8_t cols_pins[COLS] = {4, 3, 2, 28};
char AcaoRealizada[25] = "Nenhuma ação.";

const char key_map[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

void setup() {
    for (int i = 0; i < ROWS; i++) {
        gpio_init(rows_pins[i]);
        gpio_set_dir(rows_pins[i], GPIO_OUT);
        gpio_put(rows_pins[i], 0);
    }
    for (int i = 0; i < COLS; i++) {
        gpio_init(cols_pins[i]);
        gpio_set_dir(cols_pins[i], GPIO_IN);
        gpio_pull_down(cols_pins[i]);
    }

    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);

    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);

    gpio_init(LED_AZUL);
    gpio_set_dir(LED_AZUL, GPIO_OUT);

    gpio_init(BUZZER);
    gpio_set_dir(BUZZER, GPIO_OUT);

    gpio_put(LED_VERMELHO, 0);
    gpio_put(LED_VERDE, 0);
    gpio_put(LED_AZUL, 0);
    gpio_put(BUZZER, 0);
}

char read_keypad() {
    for (int row = 0; row < ROWS; row++) {
        gpio_put(rows_pins[row], 1);
        sleep_us(10); 

        for (int col = 0; col < COLS; col++) {
            if (gpio_get(cols_pins[col])) {
                gpio_put(rows_pins[row], 0); 
                return key_map[row][col];  
            }
        }

        gpio_put(rows_pins[row], 0);
    }
    return '\0';
}

int main() {
    stdio_init_all();
    setup();

    while (true) {
        sleep_ms(100);
        char key = read_keypad();
        if (key != '\0') {
            switch (key) {
                case 'A':
                    gpio_put(LED_VERMELHO, 0);
                    gpio_put(LED_VERDE, 1);
                    gpio_put(LED_AZUL, 0);
                    sleep_ms(1000);
                    strcpy(AcaoRealizada, "Acender LED VERDE.");
                    break;
                case 'B':
                    gpio_put(LED_VERMELHO, 0);
                    gpio_put(LED_VERDE, 0);
                    gpio_put(LED_AZUL, 1);
                    sleep_ms(1000);
                    strcpy(AcaoRealizada, "Acender LED AZUL.");
                    break;
                case 'C':
                    gpio_put(LED_VERMELHO, 1);
                    gpio_put(LED_VERDE, 0);
                    gpio_put(LED_AZUL, 0);
                    sleep_ms(1000);
                    strcpy(AcaoRealizada, "Acender LED VERMELHO.");
                    break;
                case 'D':
                    gpio_put(LED_VERMELHO, 1);
                    gpio_put(LED_VERDE, 1);
                    gpio_put(LED_AZUL, 1);
                    sleep_ms(1000);
                    strcpy(AcaoRealizada, "Acender TODOS LEDS.");
                    break;
                case '#':
                    gpio_put(BUZZER, 1);
                    sleep_ms(1000); 
                    gpio_put(BUZZER, 0);
                    sleep_ms(1000);
                    strcpy(AcaoRealizada, "Acionar BUZZER.");                    
                    break;                
            }
            printf("Tecla pressionada: %c\n", key);
            printf("Ação realizada: %s\n", AcaoRealizada);
        } else { 
            gpio_put(LED_VERMELHO, 0);
            gpio_put(LED_VERDE, 0);
            gpio_put(LED_AZUL, 0);
        }
    }
    return 0;
}
