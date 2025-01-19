#include "keypad.h"

// Pinos do teclado matricial
static const uint8_t row_pins[ROWS] = {8, 7, 6, 5};  // R1, R2, R3, R4
static const uint8_t col_pins[COLS] = {4, 3, 2, 28}; // C1, C2, C3, C4

static const char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

void init_keypad(void) {
    // Inicializa as linhas como saída e coloca em nível alto
    for (int i = 0; i < ROWS; i++) {
        gpio_init(row_pins[i]);
        gpio_set_dir(row_pins[i], GPIO_OUT);
        gpio_put(row_pins[i], 1);
    }
    
    // Inicializa as colunas como entrada com pull-down
    for (int j = 0; j < COLS; j++) {
        gpio_init(col_pins[j]);
        gpio_set_dir(col_pins[j], GPIO_IN);
        gpio_pull_down(col_pins[j]);
    }
}

char get_key(void) {
    static char last_key = 0;
    char current_key = 0;

    for (int i = 0; i < ROWS; i++) {
        gpio_put(row_pins[i], 1);  
        sleep_us(50);  

        for (int j = 0; j < COLS; j++) {
            if (gpio_get(col_pins[j]) == 1) { 
                sleep_ms(20);  
                if (gpio_get(col_pins[j]) == 1) {
                    current_key = keys[i][j];
                    if (current_key != last_key) {
                        last_key = current_key;
                        gpio_put(row_pins[i], 0);
                        return current_key;
                    }
                }
            }
        }
        gpio_put(row_pins[i], 0);  
    }

    if (current_key == 0) {
        last_key = 0;
    }

    return 0;
}