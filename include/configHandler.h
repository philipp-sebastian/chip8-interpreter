//
// Created by meyer on 10.12.2024.
//
#ifndef CHIP8_INTERPRETER_CONFIGHANDLER_H
#define CHIP8_INTERPRETER_CONFIGHANDLER_H

#include "common.h"

typedef struct AppData AppData_t;

typedef enum KeyID {
    KEYID_0 = 0, KEYID_1 = 1, KEYID_2 = 2, KEYID_3= 3, KEYID_4 = 4,
    KEYID_5 = 5, KEYID_6 = 6, KEYID_7 = 7, KEYID_8 = 8, KEYID_9 = 9,
    KEYID_A = 10, KEYID_B = 11, KEYID_C = 12, KEYID_D = 13, KEYID_E = 14,
    KEYID_F = 15
} eKeyID_t;

typedef struct KeyMap {
    SDL_Keycode mapping[16];
} KeyMap_t;

typedef struct Config {
    KeyMap_t keyMap;
} Config_t;

int writeConfig(AppData_t* appData);
int readConfig(AppData_t* appData);
int initKeyMap(AppData_t* appData);
SDL_Keycode getDefaultKeyCode(unsigned int index);

#endif //CHIP8_INTERPRETER_CONFIGHANDLER_H
