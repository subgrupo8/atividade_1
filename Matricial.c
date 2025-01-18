#include <stdio.h>
#include "pico/stdlib.h"


#define led_1 11
#define led_2 12
#define led_3 13
#define buz 28

uint8_t i;
char key;

void ledinit(){
for(i = 0; i < 3; i++){
  gpio_init (11+i);}
}

void ledset(){
for(i = 0; i < 3; i++){
  gpio_set_dir(11+i, GPIO_OUT);
  gpio_put(11+i, 0);
  }
}

uint8_t li [4] = {1, 2, 3, 4};
uint8_t co [4] = {5, 6, 7, 8};

char KEY_MAPS[16] = {
  '1', '2', '3', 'A',
  '4', '5', '6', 'B',
  '7', '8', '9', 'C',
  '*', '0', '#', 'D'};

void keyboard() {
    for (int i = 0; i < 4; i++) {
        gpio_init(co[i]);
        gpio_set_dir(co[i], GPIO_OUT);
        gpio_put(co[i], 1); 
        
        gpio_init(li[i]);
        gpio_set_dir(li[i], GPIO_IN);
        gpio_pull_up(li[i]);
    }
}

char check_keyboard() {
    for (int col = 0; col < 4; col++) {
      gpio_put(co[col], 0);

        for (uint8_t lin = 0; lin < 4; lin++) {
            if (gpio_get(li[lin]) == 0) { 
                sleep_ms(20);
                gpio_put(co[col], 1); 
                return KEY_MAPS[lin * 4 + col];
            }
        }
        gpio_put(co[col], 1);
    }
    return '\0';
}
void buzz() {
  gpio_init(28);
  gpio_set_dir(28, GPIO_OUT);
}

void pressed(){
  key = check_keyboard();
  (key != '\0' && key == 'A') ? gpio_put (11, 1) : gpio_put(11, 0);
  (key != '\0' && key == 'B') ? gpio_put (12, 1) : gpio_put(12, 0);
  (key != '\0' && key == 'C') ? gpio_put (13, 1) : gpio_put(13, 0);
  (key != '\0' && key == 'D') ? gpio_put (28, 1) : gpio_put(28, 0);
}


int main(){
ledinit();
ledset();
buzz();
keyboard();

while(1){
sleep_ms(20);
pressed();
sleep_ms(100);
}

}