//
// Created by Sebastian on 25.11.24.
//

#include "../include/menu.h"

void loadMenu(AppData_t *appData) {
    appData->windowData->currentScreen = MENU;
    appData->menuDotPosition = 0;
    changeResolution(appData->windowData);
    drawMenuSelection(appData);
}

void drawMenuSelection(AppData_t *appData) {
    unsigned int spaceBetween = 2 * FONT_SCALE_FACTOR;
    unsigned int widthFactor = RF_FONTWIDTH * FONT_SCALE_FACTOR + spaceBetween;
    unsigned int heightFactor = RF_FONTHEIGHT * FONT_SCALE_FACTOR + spaceBetween;

    unsigned int maxCols = 10;
    unsigned int maxRows = 4;

    unsigned int startX = (APPLICATION_WIDTH / MENU_RENDER_SCALE / FONT_SCALE_FACTOR) - (RF_FONTWIDTH / 2) -
                          ((maxCols / 2) * widthFactor) - (4 * widthFactor);
    unsigned int startY = (APPLICATION_HEIGHT / MENU_RENDER_SCALE / FONT_SCALE_FACTOR) - (RF_FONTHEIGHT / 2) -
                          ((maxRows / 2) * heightFactor);

    unsigned int currentX = startX;
    //unsigned int currentY = startY;

    for (int i = 0; i < 4; i++) //TODO Makros
    {
        appData->menuItemDotPositions[i].x = startX - widthFactor;
        appData->menuItemDotPositions[i].y = startY + i * heightFactor;
    }

    drawLetter(appData, RF_DOT, appData->menuItemDotPositions[appData->menuDotPosition].x,
               appData->menuItemDotPositions[appData->menuDotPosition].y, FONT_SCALE_FACTOR, WHITE, 255);

    int symbolBuf[10];
    StringToSymbols("START GAME", symbolBuf, sizeof(symbolBuf)); //TODO: Change in lib

    for (int i = 0; i < strlen("START GAME"); i++) {
        drawLetter(appData, symbolBuf[i], currentX, startY, FONT_SCALE_FACTOR, WHITE, 255);
        currentX += widthFactor;
    }

    currentX = startX;
    startY += heightFactor;

    StringToSymbols("LOAD GAME", symbolBuf, sizeof(symbolBuf));

    for (int i = 0; i < strlen("LOAD GAME"); i++) {
        drawLetter(appData, symbolBuf[i], currentX, startY, FONT_SCALE_FACTOR, WHITE, 255);
        currentX += widthFactor;
    }

    currentX = startX;
    startY += heightFactor;

    StringToSymbols("OPTIONS", symbolBuf, sizeof(symbolBuf));

    for (int i = 0; i < strlen("OPTIONS"); i++) {
        drawLetter(appData, symbolBuf[i], currentX, startY, FONT_SCALE_FACTOR, WHITE, 255);
        currentX += widthFactor;
    }

    currentX = startX;
    startY += heightFactor;

    StringToSymbols("EXIT", symbolBuf, sizeof(symbolBuf));

    for (int i = 0; i < strlen("EXIT"); i++) {
        drawLetter(appData, symbolBuf[i], currentX, startY, FONT_SCALE_FACTOR, WHITE, 255);
        currentX += widthFactor;
    }
}

SDL_AppResult MenuEventHandler(AppData_t *appData, SDL_Event *event) {
    switch (event->key.key) {
        case SDLK_ESCAPE:
            return SDL_APP_SUCCESS;
    }

    switch (event->type) {
        case SDL_EVENT_KEY_DOWN:
            switch (event->key.key) {
                case SDLK_S:
                case SDLK_DOWN:
                    if (appData->menuDotPosition < 3) {
                        drawLetter(appData, RF_DOT, appData->menuItemDotPositions[appData->menuDotPosition].x,
                                   appData->menuItemDotPositions[appData->menuDotPosition].y, FONT_SCALE_FACTOR, BLACK,
                                   255);
                        appData->menuDotPosition++;
                        drawLetter(appData, RF_DOT, appData->menuItemDotPositions[appData->menuDotPosition].x,
                                   appData->menuItemDotPositions[appData->menuDotPosition].y, FONT_SCALE_FACTOR, WHITE,
                                   255);
                    }
                    break;
                case SDLK_W:
                case SDLK_UP:
                    if (appData->menuDotPosition > 0) {
                        drawLetter(appData, RF_DOT, appData->menuItemDotPositions[appData->menuDotPosition].x,
                                   appData->menuItemDotPositions[appData->menuDotPosition].y, FONT_SCALE_FACTOR, BLACK,
                                   255);
                        appData->menuDotPosition--;
                        drawLetter(appData, RF_DOT, appData->menuItemDotPositions[appData->menuDotPosition].x,
                                   appData->menuItemDotPositions[appData->menuDotPosition].y, FONT_SCALE_FACTOR, WHITE,
                                   255);
                    }
                    break;
            }
    }
    return SDL_APP_CONTINUE;
}


