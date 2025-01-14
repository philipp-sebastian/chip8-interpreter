//
// Created by Sebastian on 25.11.24.
//

#ifndef CHIP8_INTERPRETER_MENU_H
#define CHIP8_INTERPRETER_MENU_H

#include "common.h"
#include "application.h"
#include "loadgame.h"

#define FONT_SCALE_MENU_FACTOR 2
#define FONT_SCALE_OPTION_FACTOR 1

typedef struct AppData AppData_t;

typedef enum MenuSelection
{
   START_GAME, LOAD_GAME, OPTIONS, EXIT
} eMenuSelection_t;

typedef enum OptionSelection
{
    CLOCK_FREQUENCY, KEYBINDINGS, LOGGING, EXIT_OPTION
} eOptionSelection_t;

typedef struct SelectedMenuItem
{
  Position_t positions[4];
  eMenuSelection_t selectedItem;
} SelectedMenuItem_t;

typedef struct SelectedOptionItem
{
    Position_t positions[4];
    eOptionSelection_t selectedItem;
} SelectedOptionItem_t;

typedef struct MenuData
{
    SelectedMenuItem_t selection;
    Position_t gameInMemoryIndicator;
    Position_t startGamePosition;
} MenuData_t;

typedef struct OptionData
{
    SelectedOptionItem_t selection;
} OptionData_t;

void loadMenu(AppData_t* appData);
void loadChip8(AppData_t* appData);
void loadOptionsMenu(AppData_t* appData);
void drawMenuSelection(AppData_t* appData);
void drawOptionsSelection(AppData_t *appData);
SDL_AppResult MenuEventHandler(AppData_t* appData, SDL_Event* event);
void updateGameInMemoryIndicator(AppData_t* appData);
void updateStartGameText(AppData_t* appData);
void openFileHandler(void *userdata, const char *const *fileList, int filter);

#endif //CHIP8_INTERPRETER_MENU_H
