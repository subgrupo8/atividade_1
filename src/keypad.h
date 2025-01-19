#ifndef KEYPAD_H
#define KEYPAD_H

#include "pico/stdlib.h"

#define ROWS 4
#define COLS 4

void init_keypad(void);
char get_key(void);

#endif
