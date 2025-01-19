#include <stdio.h>
#include "pico/stdlib.h"

#define led_1 11
#define led_2 12
#define led_3 13
#define buz 28

uint8_t i;

void ledinitset(){  // Ligando os LEDs e direcionando
    for(i = 0; i < 3; i++){
        gpio_init(11 + i);
        gpio_set_dir(11 + i, GPIO_OUT);
        gpio_put(11 + i, 0);
    }
}

uint8_t rows[4] = {1, 2, 3, 4}; // Linhas do teclado
uint8_t cols[4] = {5, 6, 7, 8}; // Colunas do teclado

// Mapeando as teclas do teclado matricial
char key_maps[16] = {'1', '2', '3', 'A', '4', '5', '6', 'B', '7', '8', '9', 'C', '*', '0', '#', 'D'};

void keyboard() { // Configurações do teclado
    for (int i = 0; i < 4; i++) {
        gpio_init(cols[i]);
        gpio_set_dir(cols[i], GPIO_OUT);
        gpio_put(cols[i], 1); 
        
        gpio_init(rows[i]);
        gpio_set_dir(rows[i], GPIO_IN);
        gpio_pull_up(rows[i]);
    }
}

char check_keyboard() {   // Função responsável por ler o teclado
    for (int col = 0; col < 4; col++) {
        gpio_put(cols[col], 0); // Coloca as colunas em LOW

        for (uint8_t row = 0; row < 4; row++) {
            if (gpio_get(rows[row]) == 0) { // Detecta se uma tecla foi pressionada
                sleep_ms(50); // Debounce

                if (gpio_get(rows[row]) == 0) { // Verifica novamente se a tecla ainda está pressionada
                    gpio_put(cols[col], 1); // Restaura a coluna para HIGH
                    return key_maps[row * 4 + col]; // index = row * 4 + col
                }
            }
        }
        gpio_put(cols[col], 1); // Restaura a coluna para HIGH
    }
    return '\0'; // Retorna que nenhuma tecla foi pressionada
}

void buzz() { // Configuração do buzzer
    gpio_init(28);
    gpio_set_dir(28, GPIO_OUT);
}

void pressed() {  // Função que faz a relação entre o teclado e os atuadores
    char key;
    key = check_keyboard(); // Verifica qual tecla foi pressionada

    // Usando operador ternário para controlar o estado dos LEDs e do buzzer
    (key != '\0' && key == 'A') ? gpio_put(11, 1) : gpio_put(11, 0);
    (key != '\0' && key == 'B') ? gpio_put(12, 1) : gpio_put(12, 0);
    (key != '\0' && key == 'C') ? gpio_put(13, 1) : gpio_put(13, 0);
    (key != '\0' && key == 'D') ? gpio_put(28, 1) : gpio_put(28, 0);
}

int main(){  // Função principal
    ledinitset();
    buzz();
    keyboard();

    while(1){ // Laço principal
        sleep_ms(20);
        pressed();  // Verifica se alguma tecla foi pressionada
        sleep_ms(100);  // Aguarda um pouco antes de fazer a próxima leitura
    }
}