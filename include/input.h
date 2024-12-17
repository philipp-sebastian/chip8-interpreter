//
// Created by Sebastian on 28.10.24.
//

#ifndef CHIP8_INTERPRETER_INPUT_H
#define CHIP8_INTERPRETER_INPUT_H

#include "common.h"
#include "application.h"

SDL_AppResult registerInput(AppData_t* appData, SDL_Event* event);

#endif //CHIP8_INTERPRETER_INPUT_H

//Abfrage und Verwaltung des Zustandes der Tastatur.
