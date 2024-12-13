//
// Created by meyer on 10.12.2024.
//
#ifndef CHIP8_INTERPRETER_CONFIGHANDLER_H
#define CHIP8_INTERPRETER_CONFIGHANDLER_H

#include "common.h"

typedef struct AppData AppData_t;

typedef enum KeyID {
    KEYID_1 = 0, KEYID_2 = 1, KEYID_3 = 2, KEYID_C = 3, KEYID_4 = 4,
    KEYID_5 = 5, KEYID_6 = 6, KEYID_D = 7, KEYID_7 = 8, KEYID_8 = 9,
    KEYID_9 = 10, KEYID_E = 11, KEYID_A = 12, KEYID_0 = 13, KEYID_B = 14,
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
