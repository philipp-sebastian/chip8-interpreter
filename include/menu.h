//
// Created by Sebastian on 25.11.24.
//

#ifndef CHIP8_INTERPRETER_MENU_H
#define CHIP8_INTERPRETER_MENU_H

#include "common.h"

void loadMenu(AppData_t* appData);
void drawMenuSelection(AppData_t* appData);
SDL_AppResult MenuEventHandler(AppData_t* appData, SDL_Event* event);

#endif //CHIP8_INTERPRETER_MENU_H
