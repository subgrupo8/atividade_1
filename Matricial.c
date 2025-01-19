#include <stdio.h>
#include "pico/stdlib.h"

//definição das portas
#define led_1 11
#define led_2 12
#define led_3 13
#define buz 28

//definição das variáveis a utilizar
uint8_t i;
char key;

//ligando os leds e direcionando
void ledinitset(){
for(i = 0; i < 3; i++){
  gpio_init (11+i);
  gpio_set_dir(11+i, GPIO_OUT);
  gpio_put(11+i, 0);
  }
}

//definindo as linhas e colunas do teclado matricial
uint8_t rows [4] = {1, 2, 3, 4};
uint8_t cols [4] = {5, 6, 7, 8};

//mapeando as teclas do matricial
char KEY_MAPS[16] = {
  '1', '2', '3', 'A',
  '4', '5', '6', 'B',
  '7', '8', '9', 'C',
  '*', '0', '#', 'D'};

//ligando o teclado, direcionando a coluna e ativando o pull_up das linhas
void keyboard() {
    for (int i = 0; i < 4; i++) {
        gpio_init(cols[i]);
        gpio_set_dir(cols[i], GPIO_OUT);
        gpio_put(cols[i], 1); 
        
        gpio_init(rows[i]);
        gpio_set_dir(rows[i], GPIO_IN);
        gpio_pull_up(rows[i]);
    }
}
//função responsável por fazer a leitura do teclado
char check_keyboard() {
    for (int col = 0; col < 4; col++) {
      gpio_put(cols[col], 0); // Coloca as colunas em LOW de forma alternada

        for (uint8_t row = 0; row < 4; row++) {
            if (gpio_get(rows[row]) == 0) { // busca ativamente qual linha foi desligada ao pressionar algma tecla
                sleep_ms(50); //debounce
                gpio_put(cols[col], 1); // coloca em HIGH a coluna que tava desativada.
                return KEY_MAPS[row * 4 + col]; //index = linha * 4 + Coluna = Tecla pressionada
            } /*A coluna que tava em LOW é revertida para HIGH quando uma row é acionada e os valores
        } armazenados em row e col são utilizados no cálculo (index) para definir qual tecla foi pressionada */
        gpio_put(cols[col], 1);
    }
    return '\0'; // retorna que nenhuma tecla foi pressionada.
    }
}
void buzz() { //ligando e direcinando o buzzer
  gpio_init(28);
  gpio_set_dir(28, GPIO_OUT);
}

void pressed(){  //função responsável por criar a relação de ação entre o teclado e os outros atuadores
  key = check_keyboard();
  (key != '\0' && key == 'A') ? gpio_put (11, 1) : gpio_put(11, 0);
  (key != '\0' && key == 'B') ? gpio_put (12, 1) : gpio_put(12, 0);
  (key != '\0' && key == 'C') ? gpio_put (13, 1) : gpio_put(13, 0);
  (key != '\0' && key == 'D') ? gpio_put (28, 1) : gpio_put(28, 0);
}


int main(){  // função principal
ledinitset();
buzz();
keyboard();

  while(1){ //código de ação
sleep_ms(20);
pressed();
sleep_ms(100);
  }
}