/*******************************************************************************
 * Projeto: Sistema de Controle de LEDs e Buzzer com Teclado Matricial
 * 
 * Descrição:
 * Este projeto implementa um sistema interativo usando um Raspberry Pi Pico W,
 * onde um teclado matricial 4x4 controla três LEDs (vermelho, verde e azul) 
 * e um buzzer. O sistema permite acender diferentes LEDs e ativar o buzzer
 * baseado nas teclas pressionadas.
 * 
 * Funcionalidades:
 * - Tecla 1: Acende LED vermelho
 * - Tecla 2: Acende LED verde
 * - Tecla 3: Acende LED azul
 * - Tecla #: Ativa o buzzer por 500ms
 * 
 * Hardware:
 * - Raspberry Pi Pico W
 * - Teclado Matricial 4x4
 * - 3 LEDs (vermelho, verde, azul)
 * - 3 Resistores 220Ω (para os LEDs)
 * - 1 Buzzer
 * 
 * Pinagem:
 * LEDs:
 * - LED Vermelho: GP13
 * - LED Verde: GP11
 * - LED Azul: GP12
 * 
 * Teclado Matricial:
 * Linhas (OUTPUT):
 * - R1: GP8
 * - R2: GP7
 * - R3: GP6
 * - R4: GP5
 * 
 * Colunas (INPUT com pull-down):
 * - C1: GP4
 * - C2: GP3
 * - C3: GP2
 * - C4: GP28
 * 
 * Outros:
 * - Buzzer: GP21
 * 
 * Dependências:
 * - pico/stdlib.h
 * 
 * Compilação:
 * Este projeto utiliza o SDK do Raspberry Pi Pico (pico-sdk)
 * e deve ser compilado usando CMake.
 * 
 * Autor: subgrupo8
 * Data de Criação: 19/01/2025
 * Última Atualização: 19/01/2025
 * Versão: 1.0
 * 
 * Licença: [Tipo de Licença]
 * 
 * Membros Subequipe 8:
 * Allef
 * Cauã
 * Hugo
 * Jonatan
 * Josemar
 * Lethícia
 * Lucas Meira
 * Maria Clara
 * Ruth
 ******************************************************************************/



#include "pico/stdlib.h"
#include "src/keypad.h"


#define LED_RED 13    
#define LED_GREEN 11  
#define LED_BLUE 12  
#define BUZZER 21    

// Inicializa os periféricos (LEDs e Buzzer)
void init_peripherals(void) {
    // Inicializa LEDs
    gpio_init(LED_RED);
    gpio_init(LED_GREEN);
    gpio_init(LED_BLUE);
    
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_set_dir(LED_BLUE, GPIO_OUT);

    // Inicializa o Buzzer
    gpio_init(BUZZER);
    gpio_set_dir(BUZZER, GPIO_OUT);

    // Garante que todos os LEDs e o Buzzer estejam desligados
    gpio_put(LED_RED, 0);
    gpio_put(LED_GREEN, 0);
    gpio_put(LED_BLUE, 0);
    gpio_put(BUZZER, 0);
}

// Lógica de controle dos LEDs e Buzzer com base na tecla pressionada
void handle_key(char key) {
    
    gpio_put(LED_RED, 0);
    gpio_put(LED_GREEN, 0);
    gpio_put(LED_BLUE, 0);
    
    
    sleep_ms(10);

    switch (key) {
        case '1':
            gpio_put(LED_RED, 1);    
            break;
        case '2':
            gpio_put(LED_GREEN, 1);  
            break;
        case '3':
            gpio_put(LED_BLUE, 1);  
            break;
        case '#':
            gpio_put(BUZZER, 1);     
            sleep_ms(500);          
            gpio_put(BUZZER, 0);     
            break;
    }
}

int main(void) {
    stdio_init_all();
    
    // Inicializa periféricos primeiro
    init_peripherals();
    
    // Depois inicializa o teclado
    init_keypad();

    while (1) {
        char key = get_key();
        if (key != 0) {
            handle_key(key);
        }
        sleep_ms(50);  
    }
    return 0;
}
