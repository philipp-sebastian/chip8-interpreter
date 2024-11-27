//
// Created by Sebastian on 25.11.24.
//

#ifndef CHIP8_INTERPRETER_MENU_H
#define CHIP8_INTERPRETER_MENU_H

#include "common.h"
#include "application.h"
#include "loadgame.h"

#define FONT_SCALE_FACTOR 2

typedef struct AppData AppData_t;

typedef enum MenuSelection
{
   START_GAME, LOAD_GAME, OPTIONS, EXIT
} eMenuSelection_t;

typedef struct SelectedItem
{
  Position_t positions[4];
  eMenuSelection_t selectedItem;
} SelectedItem_t;

typedef struct MenuData
{
    SelectedItem_t selection;
} MenuData_t;

void loadMenu(AppData_t* appData);
void drawMenuSelection(AppData_t* appData);
SDL_AppResult MenuEventHandler(AppData_t* appData, SDL_Event* event);
void(*openFileHandler)(void *, const char *const *, int);

#endif //CHIP8_INTERPRETER_MENU_H
