//
// Created by Sebastian on 25.11.24.
//

#include "../include/menu.h"

void loadMenu(AppData_t *appData) {
    appData->windowData->currentScreen = MENU;
    appData->menuData->selection.selectedItem = START_GAME;
    changeResolution(appData->windowData);
    clearScreen(appData);
    drawMenuSelection(appData);
}

void loadChip8(AppData_t* appData)
{
    appData->windowData->currentScreen = CHIP8;
    changeResolution(appData->windowData);
    clearScreen(appData);
}

void loadOptionsMenu(AppData_t* appData)
{
    appData->windowData->currentScreen = OPTION;
    appData->optionData->selection.selectedItem = CLOCK_FREQUENCY;
    changeResolution(appData->windowData);
    clearScreen(appData);
    drawOptionsSelection(appData);
}

void drawMenuSelection(AppData_t *appData) {
    unsigned int spaceBetween = 2 * FONT_SCALE_MENU_FACTOR;
    unsigned int widthFactor = RF_FONTWIDTH * FONT_SCALE_MENU_FACTOR + spaceBetween;
    unsigned int heightFactor = RF_FONTHEIGHT * FONT_SCALE_MENU_FACTOR + spaceBetween;

    unsigned int maxCols = 10;
    unsigned int maxRows = 4;

    unsigned int startX = (APPLICATION_WIDTH / MENU_RENDER_SCALE / 2) - (RF_FONTWIDTH / 2) -
                          ((maxCols / 2) * widthFactor) - (4 * widthFactor);
    unsigned int startY = (APPLICATION_HEIGHT / MENU_RENDER_SCALE / 2) - (RF_FONTHEIGHT / 2) -
                          ((maxRows / 2) * heightFactor);

    unsigned int currentX = startX;
    unsigned int currentY = startY;

    for (int i = 0; i < 4; i++) //TODO Makros
    {
        appData->menuData->selection.positions[i].x = startX - widthFactor;
        appData->menuData->selection.positions[i].y = currentY + i * heightFactor;
    }


    enum MenuSelection indicatorStart = START_GAME;
    if (appData->hasProgram == FALSE) {
        indicatorStart = LOAD_GAME;
        appData->menuData->selection.selectedItem++;
    }

    drawLetter(appData, RF_DOT, appData->menuData->selection.positions[indicatorStart].x,
               appData->menuData->selection.positions[indicatorStart].y, FONT_SCALE_MENU_FACTOR, WHITE, 255);


    int symbolBuf[10];
    StringToSymbols("START GAME", symbolBuf, sizeof(symbolBuf)); //TODO: Change in lib

    appData->menuData->startGamePosition.x = currentX;
    appData->menuData->startGamePosition.y = currentY;

    for (int i = 0; i < strlen("START GAME"); i++) {
        drawLetter(appData, symbolBuf[i], currentX, currentY, FONT_SCALE_MENU_FACTOR, WHITE, 70);
        currentX += widthFactor;
    }

    appData->menuData->gameInMemoryIndicator.x = currentX + widthFactor / 2;
    appData->menuData->gameInMemoryIndicator.y = currentY;

    currentX = startX;
    currentY += heightFactor;

    StringToSymbols("LOAD GAME", symbolBuf, sizeof(symbolBuf));

    for (int i = 0; i < strlen("LOAD GAME"); i++) {
        drawLetter(appData, symbolBuf[i], currentX, currentY, FONT_SCALE_MENU_FACTOR, WHITE, 255);
        currentX += widthFactor;
    }

    currentX = startX;
    currentY += heightFactor;

    StringToSymbols("OPTIONS", symbolBuf, sizeof(symbolBuf));

    for (int i = 0; i < strlen("OPTIONS"); i++) {
        drawLetter(appData, symbolBuf[i], currentX, currentY, FONT_SCALE_MENU_FACTOR, WHITE, 255);
        currentX += widthFactor;
    }

    currentX = startX;
    currentY += heightFactor;

    StringToSymbols("EXIT", symbolBuf, sizeof(symbolBuf));

    for (int i = 0; i < strlen("EXIT"); i++) {
        drawLetter(appData, symbolBuf[i], currentX, currentY, FONT_SCALE_MENU_FACTOR, WHITE, 255);
        currentX += widthFactor;
    }

    updateGameInMemoryIndicator(appData);
}

void drawOptionsSelection(AppData_t *appData) {
    unsigned int spaceBetween = 2 * FONT_SCALE_OPTION_FACTOR;
    unsigned int widthFactor = RF_FONTWIDTH * FONT_SCALE_OPTION_FACTOR + spaceBetween;
    unsigned int heightFactor = RF_FONTHEIGHT * (FONT_SCALE_OPTION_FACTOR * 3) + spaceBetween;

    unsigned int maxCols = 15;
    unsigned int maxRows = 4;

    //TODO: Please help me
    //First, take the center of the screen. After that, subtract half of one char to center the char, then center the longest word, then subtract 11 (based on looks) chars
    unsigned int startX = (APPLICATION_WIDTH / MENU_RENDER_SCALE / 2) - (RF_FONTWIDTH / 2) -
                          (((maxCols / 2) + 1) * widthFactor) - (10 * widthFactor);

    unsigned int startY = (APPLICATION_HEIGHT / MENU_RENDER_SCALE / 2) - (RF_FONTHEIGHT / 2) -
                          ((maxRows / 2) * heightFactor);

    unsigned int currentX = startX;
    unsigned int currentY = startY;

    for (int i = 0; i < 4; i++) //TODO Makros
    {
        appData->optionData->selection.positions[i].x = startX - widthFactor;
        appData->optionData->selection.positions[i].y = currentY + i * heightFactor;
    }

    enum OptionSelection indicatorStart = CLOCK_FREQUENCY;

    drawLetter(appData, RF_DOT, appData->optionData->selection.positions[indicatorStart].x,
               appData->optionData->selection.positions[indicatorStart].y, FONT_SCALE_OPTION_FACTOR, WHITE, 255);


    int symbolBuf[15];
    StringToSymbols("CLOCK FREQUENCY", symbolBuf, sizeof(symbolBuf)); //TODO: Change in lib

    for (int i = 0; i < strlen("CLOCK FREQUENCY"); i++) {
        drawLetter(appData, symbolBuf[i], currentX, currentY, FONT_SCALE_OPTION_FACTOR, WHITE, 255);
        currentX += widthFactor;
    }

    currentX = startX;
    currentY += heightFactor;

    StringToSymbols("KEY BINDINGS", symbolBuf, sizeof(symbolBuf));

    for (int i = 0; i < strlen("KEY BINDINGS"); i++) {
        drawLetter(appData, symbolBuf[i], currentX, currentY, FONT_SCALE_OPTION_FACTOR, WHITE, 255);
        currentX += widthFactor;
    }

    currentX = startX;
    currentY += heightFactor;

    StringToSymbols("LOGGING", symbolBuf, sizeof(symbolBuf));

    for (int i = 0; i < strlen("LOGGING"); i++) {
        drawLetter(appData, symbolBuf[i], currentX, currentY, FONT_SCALE_OPTION_FACTOR, WHITE, 255);
        currentX += widthFactor;
    }

    currentX = startX;
    currentY += heightFactor;

    StringToSymbols("EXIT", symbolBuf, sizeof(symbolBuf));

    for (int i = 0; i < strlen("EXIT"); i++) {
        drawLetter(appData, symbolBuf[i], currentX, currentY, FONT_SCALE_OPTION_FACTOR, WHITE, 255);
        currentX += widthFactor;
    }

    if (appData->optionData->selection.selectedItem == CLOCK_FREQUENCY)
    {
        drawFrequency(appData, appData->pChip8->cpuFrequency);
    }
}

SDL_AppResult MenuEventHandler(AppData_t *appData, SDL_Event *event) {
    if (event->type == SDL_EVENT_KEY_DOWN) {
    switch (event->key.key) {
        case SDLK_ESCAPE:
            return SDL_APP_SUCCESS;
    }
    }

    const SDL_DialogFileFilter filters[] = {
            {"Chip8-Game", "ch8"} //TODO: Accept more files??
    };
    int nfilters = 1;

    switch (event->type) {
        case SDL_EVENT_KEY_DOWN:

            switch (event->key.key) {
                case SDLK_S:
                case SDLK_DOWN:
                    if (appData->menuData->selection.selectedItem < 3) {
                        Position_t position;
                        position = appData->menuData->selection.positions[appData->menuData->selection.selectedItem];
                        drawLetter(appData, RF_DOT, position.x, position.y, FONT_SCALE_MENU_FACTOR, BLACK, 255);
                        appData->menuData->selection.selectedItem++;
                        position = appData->menuData->selection.positions[appData->menuData->selection.selectedItem];
                        drawLetter(appData, RF_DOT, position.x, position.y, FONT_SCALE_MENU_FACTOR, WHITE, 255);
                    }
                    break;
                case SDLK_W:
                case SDLK_UP:
                    if (appData->menuData->selection.selectedItem > 0 &&
                        !(appData->menuData->selection.selectedItem == LOAD_GAME && appData->hasProgram == FALSE)) {
                        Position_t position;
                        position = appData->menuData->selection.positions[appData->menuData->selection.selectedItem];
                        drawLetter(appData, RF_DOT, position.x, position.y, FONT_SCALE_MENU_FACTOR, BLACK, 255);
                        appData->menuData->selection.selectedItem--;
                        position = appData->menuData->selection.positions[appData->menuData->selection.selectedItem];
                        drawLetter(appData, RF_DOT, position.x, position.y, FONT_SCALE_MENU_FACTOR, WHITE, 255);
                    }
                    break;
                case SDLK_RETURN:
                    switch (appData->menuData->selection.selectedItem) {
                        case START_GAME:
                            loadChip8(appData);
                            break;
                        case LOAD_GAME:
#ifdef _WIN32
                            nfilters = 0; //Because windows does not support the filters
#endif
                            SDL_ShowOpenFileDialog(openFileHandler, appData, appData->windowData->window, filters,
                                                   nfilters,
                                                   "../games", 0);

                            break;
                        case OPTIONS:
                            loadOptionsMenu(appData);
                            break;
                        case EXIT:
                            return SDL_APP_SUCCESS;
                    }
                    break;
            }
    }
    return SDL_APP_CONTINUE;
}

void updateGameInMemoryIndicator(AppData_t *appData) {
    eColor_t color = RED;

    if (appData->hasProgram == TRUE) {
        color = GREEN;
    }

    drawLetter(appData, RF_DOT, appData->menuData->gameInMemoryIndicator.x, appData->menuData->gameInMemoryIndicator.y,
               FONT_SCALE_MENU_FACTOR, color, 255);
}

void updateStartGameText(AppData_t *appData) {
    unsigned int spaceBetween = 2 * FONT_SCALE_MENU_FACTOR;
    unsigned int widthFactor = RF_FONTWIDTH * FONT_SCALE_MENU_FACTOR + spaceBetween;

    unsigned int currentX = appData->menuData->startGamePosition.x;
    unsigned int currentY = appData->menuData->startGamePosition.y;

    int symbolBuf[10];
    StringToSymbols("START GAME", symbolBuf, sizeof(symbolBuf));
    unsigned char alpha = 255;

    for (int i = 0; i < strlen("START GAME"); i++) {
        drawLetter(appData, symbolBuf[i], currentX, currentY, FONT_SCALE_MENU_FACTOR, BLACK, alpha);
        currentX += widthFactor;
    }
    currentX = appData->menuData->startGamePosition.x;
    currentY = appData->menuData->startGamePosition.y;

    if (appData->hasProgram == FALSE) {
        alpha = 70;
    }
    for (int i = 0; i < strlen("START GAME"); i++) {
        drawLetter(appData, symbolBuf[i], currentX, currentY, FONT_SCALE_MENU_FACTOR, WHITE, alpha);
        currentX += widthFactor;
    }
}

void openFileHandler(void *userdata, const char *const *fileList, int filter) {
    AppData_t *data = (AppData_t *) userdata;
    if (data == NULL) {
        return;
    }

    if (fileList == NULL) {
        if (filter == -1) {
            SDL_Log("File format is not supported");
        } else {
            SDL_Log("Error or dialog was cancelled");
        }

        return;
    }

    const char *filePath = *fileList;
    size_t length = strlen(filePath);

    if (strcmp((char *) filePath + length - 4, ".ch8") != 0) {
        SDL_Log("Tried to load: %s", filePath);
        SDL_Log("Invalid file format. Supported is .ch8.");
        data->hasProgram = FALSE;
        updateStartGameText(data);
        updateGameInMemoryIndicator(data);
        return;
    }


    loadGame(data, filePath);

}


