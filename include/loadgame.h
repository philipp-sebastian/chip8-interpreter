//
// Created by Sebastian on 15.11.24.
//

#ifndef CHIP8_INTERPRETER_LOADGAME_H
#define CHIP8_INTERPRETER_LOADGAME_H

#include "common.h"
#include "chip8.h"
#include "application.h"

typedef struct AppData AppData_t;

int loadGame(AppData_t* appData, const char* filePath);

#endif //CHIP8_INTERPRETER_LOADGAME_H
