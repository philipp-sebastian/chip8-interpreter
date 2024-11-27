//
// Created by Sebastian on 25.11.24.
//

#include "../include/menu.h"

void loadMenu(AppData_t *appData) {
    appData->windowData->currentScreen = MENU;
    appData->menuData->selection.selectedItem = START_GAME;
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
        appData->menuData->selection.positions[i].x = startX - widthFactor;
        appData->menuData->selection.positions[i].y = startY + i * heightFactor;
    }

    drawLetter(appData, RF_DOT, appData->menuData->selection.positions[appData->menuData->selection.selectedItem].x,
               appData->menuData->selection.positions[appData->menuData->selection.selectedItem].y, FONT_SCALE_FACTOR, WHITE, 255);

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

    const SDL_DialogFileFilter filters[] = {
            {"Chip8-Game", "ch8"}
    };

    switch (event->type) {
        case SDL_EVENT_KEY_DOWN:

            switch (event->key.key) {
                case SDLK_S:
                case SDLK_DOWN:
                    if (appData->menuData->selection.selectedItem < 3) {
                        Position_t position;
                        position = appData->menuData->selection.positions[appData->menuData->selection.selectedItem];
                        drawLetter(appData, RF_DOT, position.x, position.y, FONT_SCALE_FACTOR, BLACK, 255);
                        appData->menuData->selection.selectedItem++;
                        position = appData->menuData->selection.positions[appData->menuData->selection.selectedItem];
                        drawLetter(appData, RF_DOT, position.x, position.y, FONT_SCALE_FACTOR, WHITE, 255);
                    }
                    break;
                case SDLK_W:
                case SDLK_UP:
                    if (appData->menuData->selection.selectedItem > 0) {
                        Position_t position;
                        position = appData->menuData->selection.positions[appData->menuData->selection.selectedItem];
                        drawLetter(appData, RF_DOT, position.x, position.y, FONT_SCALE_FACTOR, BLACK, 255);
                        appData->menuData->selection.selectedItem--;
                        position = appData->menuData->selection.positions[appData->menuData->selection.selectedItem];
                        drawLetter(appData, RF_DOT, position.x, position.y, FONT_SCALE_FACTOR, WHITE, 255);
                    }
                    break;
                case SDLK_RETURN:
                    switch (appData->menuData->selection.selectedItem) {
                        case START_GAME:
                            break;
                        case LOAD_GAME:

                            SDL_ShowOpenFileDialog(openFileHandler, NULL ,appData->windowData->window, filters, 1, "../games", 0);
                            break;
                        case OPTIONS:
                            break;
                        case EXIT:
                            return SDL_APP_SUCCESS;
                    }
                    break;
            }
    }
    return SDL_APP_CONTINUE;
}

void(*openFileHandler)(void * userdata, const char *const * fileList, int filter)
{
    AppData_t* data = (AppData_t*) userdata;

    if (data == NULL)
    {
        return;
    }

    if (fileList == NULL)
    {
        if (filter == -1)
        {
            SDL_Log("File format is not supported");
        }
        else
        {
            SDL_Log("Error or dialog was cancelled");
        }

        return;
    }

    loadGame(data->pChip8, *fileList);

}


