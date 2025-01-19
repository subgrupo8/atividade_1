#include <stdio.h>
#include "pico/stdlib.h"

#define ROWS 4  // Número de linhas
#define COLS 4  // Número de colunas
#define LEDR 18 // Led vermelho
#define LEDG 22 // Led verde
#define LEDB 27 // Led azul
#define Buzzer 28 //Buzzer

// Define os GPIOs para as linhas e colunas
uint rows[ROWS] = {8, 7, 6, 5};  // Pinos GPIO das linhas
uint cols[COLS] = {4, 3, 2, 1};  // Pinos GPIO das colunas

// Mapeamento das teclas
char key_map[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

//Cria o som do buzzer
void play_note(int buzzer, int frequency, int duration) {

    int delay = 1000000 / frequency / 2; // Meio ciclo da frequência
    int cycles = (frequency * duration) / 1000;

    for (int i = 0; i < cycles; i++) {
        gpio_put(buzzer, 1);
        sleep_us(delay);
        gpio_put(buzzer, 0);
        sleep_us(delay);
    }
}

// Digitaliza o teclado e retorna a tecla pressionada
char scan_keypad() {
    for (int i = 0; i < ROWS; i++) {
        gpio_put(rows[i], 0);  // Coloca a linha em nível baixo

        for (int j = 0; j < COLS; j++) {
            if (gpio_get(cols[j]) == 0) {  // Verifica se a coluna está em nível baixo
                while (gpio_get(cols[j]) == 0);  // Aguarda até a tecla ser solta
                gpio_put(rows[i], 1);  // Restaura a linha para nível alto
                return key_map[i][j];  // Retorna a tecla correspondente
            }
        }

        gpio_put(rows[i], 1);  // Restaura a linha para nível alto
    }

    return '\0';  // Retorna nulo se nenhuma tecla foi pressionada
}

int main() {
    stdio_init_all();
    for (int i = 0; i < ROWS; i++) {
        gpio_init(rows[i]);
        gpio_set_dir(rows[i], GPIO_OUT);
        gpio_put(rows[i], 1);  // Mantém as linhas em nível alto
    }

    for (int j = 0; j < COLS; j++) {
        gpio_init(cols[j]);
        gpio_set_dir(cols[j], GPIO_IN);
        gpio_pull_up(cols[j]);  // Ativa resistor pull-up nas colunas
    }
    printf("Teclado conectado. Pressione uma tecla...\n");
    gpio_init(LEDR);
    gpio_set_dir(LEDR, GPIO_OUT);
    gpio_init(LEDG);
    gpio_set_dir(LEDG, GPIO_OUT);
    gpio_init(LEDB);
    gpio_set_dir(LEDB, GPIO_OUT);
    gpio_init(Buzzer);
    gpio_set_dir(Buzzer, GPIO_OUT);
    while (1) {
        
        sleep_ms(100);
        char key = scan_keypad();  // Verifica o teclado
        if (key != '\0') {         // Se uma tecla foi pressionada
            printf("Tecla pressionada: %c\n", key);
            if(key == '1'){
               gpio_put(LEDR,true);
            }
            if(key == '2'){
               gpio_put(LEDG,true);
               
            }
            if(key == '3'){
               gpio_put(LEDB,true);
               
            }
            if(key == '4'){
              gpio_put(LEDR,false);
            }
            if(key == '5'){
              gpio_put(LEDG,false);
            }
            if(key == '6'){
              gpio_put(LEDB,false); 
            }
            if(key == '7'){
               for (int i = 0; i < 3; i++) {
            gpio_put(LEDR, 1); // Liga o led
            sleep_ms(500);
            gpio_put(LEDR, 0); // Desliga o led
            sleep_ms(500);
              }  
            }
            if(key == '8'){
               for (int i = 0; i < 3; i++) {
            gpio_put(LEDG, 1); // Liga o led
            sleep_ms(500);
            gpio_put(LEDG, 0); // Desliga o led
            sleep_ms(500);
              }  
            }
            if(key == '9'){
               for (int i = 0; i < 3; i++) {
            gpio_put(LEDB, 1); // Liga o led
            sleep_ms(500);
            gpio_put(LEDB, 0); // Desliga o led
            sleep_ms(500);
              }  
            }
            if(key == '0'){
               play_note(Buzzer, 262,1000);
            }
          
            }
        }
    }


