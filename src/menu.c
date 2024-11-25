//
// Created by Sebastian on 25.11.24.
//

#include "../include/common.h"

void loadMenu(AppData_t* appData)
{
    appData->windowData->currentScreen = MENU;
    changeResolution(appData->windowData);
    drawMenuSelection(appData);
}

void drawMenuSelection(AppData_t* appData)
{
    int scale = 5;

    drawLetter(appData, fS, 0, 0, scale, WHITE, 255);
}

SDL_AppResult MenuEventHandler(AppData_t* appData, SDL_Event* event)
{
    switch (event->key.key) {
        case SDLK_ESCAPE:
            return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}


