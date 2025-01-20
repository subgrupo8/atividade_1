#include <stdio.h>
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

// Configuração do teclado matricial 4x4
#define ROWS 4
#define COLS 4

const uint rows[ROWS] = {9, 8, 7, 6};      // Pinos das linhas
const uint cols[COLS] = {5, 4, 3, 2};      // Pinos das colunas

// Matriz de teclas
const char key_map[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Configuração dos LEDs e buzzer
#define LED1 11   // LED1 no pino GPIO 11
#define LED2 12   // LED2 no pino GPIO 12
#define LED3 13   // LED3 no pino GPIO 13
#define BUZZER_PIN 21 // Buzzer no pino GPIO 21

// Frequência do buzzer (em Hz)
#define BUZZER_FREQUENCY 1000

// Configura os pinos dos LEDs como saída
void setup_leds() {
    gpio_init(LED1);
    gpio_set_dir(LED1, GPIO_OUT);
    gpio_init(LED2);
    gpio_set_dir(LED2, GPIO_OUT);
    gpio_init(LED3);
    gpio_set_dir(LED3, GPIO_OUT);
}

// Configura o pino do buzzer como saída PWM
void pwm_init_buzzer(uint pin) {
    // Configurar o pino como saída de PWM
    gpio_set_function(pin, GPIO_FUNC_PWM);

    // Obter o slice do PWM associado ao pino
    uint slice_num = pwm_gpio_to_slice_num(pin);

    // Configurar o PWM com frequência desejada
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, clock_get_hz(clk_sys) / (BUZZER_FREQUENCY * 4096)); // Divisor de clock
    pwm_init(slice_num, &config, true);

    // Iniciar o PWM no nível baixo
    pwm_set_gpio_level(pin, 0);
}

// Função para emitir um beep com duração especificada
void beep(uint pin, uint duration_ms) {
    uint slice_num = pwm_gpio_to_slice_num(pin);

    // Configurar o duty cycle para 50% (ativo)
    pwm_set_gpio_level(pin, 2048);

    // Temporização
    sleep_ms(duration_ms);

    // Desativar o sinal PWM (duty cycle 0)
    pwm_set_gpio_level(pin, 0);

    // Pausa entre os beeps
    sleep_ms(100); // Pausa de 100ms
}

// Configura os pinos das linhas como saída e as colunas como entrada com pull-up
void setup_keypad() {
    for (int i = 0; i < ROWS; i++) {
        gpio_init(rows[i]);
        gpio_set_dir(rows[i], GPIO_OUT);
        gpio_put(rows[i], 1); // Inicialmente, todas as linhas em estado ALTO
    }

    for (int j = 0; j < COLS; j++) {
        gpio_init(cols[j]);
        gpio_set_dir(cols[j], GPIO_IN);
        gpio_pull_up(cols[j]); // Habilita o pull-up nas colunas
    }
}

// Função para identificar a tecla pressionada no teclado
char get_key_pressed() {
    for (int i = 0; i < ROWS; i++) {
        gpio_put(rows[i], 0); // Ativa a linha atual
        for (int j = 0; j < COLS; j++) {
            if (gpio_get(cols[j]) == 0) { // Verifica se há conexão com a coluna
                while (gpio_get(cols[j]) == 0); // Aguarda o botão ser solto
                gpio_put(rows[i], 1); // Desativa a linha
                return key_map[i][j]; // Retorna a tecla correspondente
            }
        }
        gpio_put(rows[i], 1); // Desativa a linha
    }
    return '\0'; // Nenhuma tecla pressionada
}

// Função para controlar os LEDs e o buzzer com base na tecla pressionada
void control(char key) {
    switch (key) {
        case '1': // Liga o LED1
            gpio_put(LED1, 1);
            gpio_put(LED2, 0);
            gpio_put(LED3, 0);
            break;
        case '2': // Liga o LED2
            gpio_put(LED1, 0);
            gpio_put(LED2, 1);
            gpio_put(LED3, 0);
            break;
        case '3': // Liga o LED3
            gpio_put(LED1, 0);
            gpio_put(LED2, 0);
            gpio_put(LED3, 1);
            break;
        case 'A': // Toca o buzzer com PWM
            beep(BUZZER_PIN, 500); // Duração do beep em ms
            break;
        default: // Desliga tudo
            gpio_put(LED1, 0);
            gpio_put(LED2, 0);
            gpio_put(LED3, 0);
            gpio_put(BUZZER_PIN, 0);
            break;
    }
}

// Função principal
int main() {
    stdio_init_all(); // Inicializa o stdio para printf

    setup_leds();     // Configura os LEDs
    pwm_init_buzzer(BUZZER_PIN); // Configura o buzzer PWM
    setup_keypad();   // Configura o teclado matricial

    while (true) {
        char key = get_key_pressed(); // Obtém a tecla pressionada
        if (key != '\0') {            // Se houver uma tecla pressionada
            printf("Tecla %c pressionada\n", key); // Imprime a tecla no console
        }
        control(key); // Controla LEDs e buzzer com base na tecla pressionada
        sleep_ms(100); // Pequeno delay para evitar leituras duplicadas
    }

    return 0;
}
