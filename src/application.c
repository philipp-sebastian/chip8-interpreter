//
// Created by Sebastian on 19.11.24.
//

#include "../include/application.h"
#include "../include/input.h"


void setRendererColor(SDL_Renderer *renderer, eColor_t color, unsigned char alpha) {
    switch (color) {
        case BLACK:
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, alpha);
            break;
        case WHITE:
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, alpha);
            break;
        case RED:
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, alpha);
            break;
        case GREEN:
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, alpha);
            break;
    }
}

void clearScreen(AppData_t *appData) {
    memset(appData->pChip8->display, 0, sizeof(appData->pChip8->display));
    setRendererColor(appData->windowData->renderer, BLACK, 255);
    SDL_RenderClear(appData->windowData->renderer);
    setRendererColor(appData->windowData->renderer, WHITE, 255);
}

void updatePixel(AppData_t *appData, PixelData_t pixelData) {
    switch (appData->windowData->currentScreen) {
        case CHIP8:
            appData->pChip8->display[pixelData.position.x][pixelData.position.y] = pixelData.color;
            break;
        case OPTION:
        case MENU:
            appData->display[pixelData.position.x][pixelData.position.y] = pixelData.color; //TODO: Not needed, change code to simple if else
            break;
    }

    appData->windowData->updateTracker->pixels[appData->windowData->updateTracker->updateCounter] = pixelData;
    appData->windowData->updateTracker->updateCounter++;
}

void drawDisplay(WindowData_t *windowData) {
    for (int i = 0; i < windowData->updateTracker->updateCounter; i++) {
        setRendererColor(windowData->renderer, windowData->updateTracker->pixels[i].color,
                         windowData->updateTracker->pixels[i].alpha);
        SDL_RenderPoint(windowData->renderer, windowData->updateTracker->pixels[i].position.x,
                        windowData->updateTracker->pixels[i].position.y);
    }

    windowData->updateTracker->updateCounter = 0;
    SDL_RenderPresent(windowData->renderer);
}

void changeResolution(WindowData_t *windowData) {
    int newRenderscale;

    switch (windowData->currentScreen) {
        case CHIP8:
            newRenderscale = CHIP8_RENDER_SCALE; //for a 64x32 display because (1280x640)/20 => 64x32
            break;
        case OPTION:
        case MENU:
            newRenderscale = MENU_RENDER_SCALE;
            break;
    }

    SDL_SetRenderScale(windowData->renderer, (float) newRenderscale, (float) newRenderscale);

}

void
drawLetter(AppData_t *appData, enum Symbol letter, unsigned int x, unsigned int y, unsigned int scale, eColor_t color,
           unsigned char alpha) {
    unsigned int letterIndex = letter * RF_FONTHEIGHT;

    for (unsigned int height = 0; height < RF_FONTHEIGHT; height++) {
        unsigned char rowData = appData->fontData[letterIndex + height];

        for (unsigned int width = 0; width < RF_FONTWIDTH; width++) {
            if ((rowData >> (8 - width - 1) & 1) == 1) {
                for (unsigned int hScale = 0; hScale < scale; hScale++) {
                    for (unsigned int wScale = 0; wScale < scale; wScale++) {
                        PixelData_t pixelData = {{wScale + width * scale + x, hScale + height * scale + y}, color,
                                                 alpha};
                        updatePixel(appData, pixelData);
                    }
                }
            } else {
                for (unsigned int hScale = 0; hScale < scale; hScale++) {
                    for (unsigned int wScale = 0; wScale < scale; wScale++) {
                        PixelData_t pixelData = {{wScale + width * scale + x, hScale + height * scale + y}, BLACK, 255};
                        updatePixel(appData, pixelData);
                    }
                }
            }
        }
    }
}

SDL_AppResult chip8EventHandler(AppData_t *appData, SDL_Event *event) {
    if (event->type == SDL_EVENT_KEY_DOWN) {
        switch (event->key.key) {
            case SDLK_ESCAPE:
                loadMenu(appData);
                resetChip8(appData);
                return SDL_APP_CONTINUE;
        }
    }

    registerInput(appData, event);

    return SDL_APP_CONTINUE;
}

//TODO: Move this method in menu.c ?
SDL_AppResult optionEventHandler(AppData_t *appData, SDL_Event *event) {
    if (event->type == SDL_EVENT_KEY_DOWN) {
        switch (event->key.key) {
            case SDLK_ESCAPE:
                loadMenu(appData);
                return SDL_APP_CONTINUE;
            case SDLK_S:
            case SDLK_DOWN:
                if (appData->optionData->selection.selectedItem < 3) {
                    Position_t position;
                    position = appData->optionData->selection.positions[appData->optionData->selection.selectedItem];
                    drawLetter(appData, RF_DOT, position.x, position.y, FONT_SCALE_OPTION_FACTOR, BLACK, 255);
                    appData->optionData->selection.selectedItem++;
                    position = appData->optionData->selection.positions[appData->optionData->selection.selectedItem];
                    drawLetter(appData, RF_DOT, position.x, position.y, FONT_SCALE_OPTION_FACTOR, WHITE, 255);
                }
                onItemSelect(appData);
                break;
            case SDLK_W:
            case SDLK_UP:
                if (appData->optionData->selection.selectedItem > 0) {
                    Position_t position;
                    position = appData->optionData->selection.positions[appData->optionData->selection.selectedItem];
                    drawLetter(appData, RF_DOT, position.x, position.y, FONT_SCALE_OPTION_FACTOR, BLACK, 255);
                    appData->optionData->selection.selectedItem--;
                    position = appData->optionData->selection.positions[appData->optionData->selection.selectedItem];
                    drawLetter(appData, RF_DOT, position.x, position.y, FONT_SCALE_OPTION_FACTOR, WHITE, 255);
                }
                onItemSelect(appData);
                break;
            case SDLK_RETURN:
                switch (appData->optionData->selection.selectedItem) {
                    //TODO: Impmenetation
                    case CLOCK_FREQUENCY:
                        //Unused
                        break;
                    case KEYBINDINGS:
                        break;
                    case LOGGING:
                        break;
                    case EXIT_OPTION:
                        loadMenu(appData);
                        break;
                }
                break;
            //Relevant for Clock-Frequency
            case SDLK_RIGHT:
            case SDLK_D:
            case SDLK_PLUS:
                if (appData->optionData->selection.selectedItem == CLOCK_FREQUENCY) {
                    appData->pChip8->cpuFrequency += 50;
                    drawFrequency(appData, appData->pChip8->cpuFrequency);
                }
                break;
            case SDLK_LEFT:
            case SDLK_A:
            case SDLK_MINUS:
                if (appData->optionData->selection.selectedItem == CLOCK_FREQUENCY) {
                    if (appData->pChip8->cpuFrequency > 50) {
                        appData->pChip8->cpuFrequency -= 50;
                    }
                    drawFrequency(appData, appData->pChip8->cpuFrequency);
                }
                break;
        }
    }

    return SDL_APP_CONTINUE;
}

void drawFrequency(AppData_t *data, unsigned int frequency) {
    char num[MAX_FREQUENCY_DIGITS + 1];
    snprintf(num, sizeof(num), "%d", frequency);

    int numLen = (int) strlen(num);

    int symbols[numLen + 1];
    StringToSymbols(num, symbols, numLen);

    unsigned int spaceBetween = 2 * FONT_SCALE_OPTION_FACTOR;
    unsigned int widthFactor = RF_FONTWIDTH * FONT_SCALE_OPTION_FACTOR + spaceBetween;

    //Draw < Symbol
    if (data->pChip8->cpuFrequency > 50) {
        drawLetter(data, RF_LESS_THAN,
                   data->optionData->selection.positions[CLOCK_FREQUENCY].x + 120,
                   data->optionData->selection.positions[CLOCK_FREQUENCY].y,
                   FONT_SCALE_OPTION_FACTOR, WHITE, 255);
    }

    for (int i = 1; i <= numLen; i++) {
        drawLetter(data, symbols[i - 1],
                   data->optionData->selection.positions[CLOCK_FREQUENCY].x + 120 + (i * widthFactor),
                   data->optionData->selection.positions[CLOCK_FREQUENCY].y,
                   FONT_SCALE_OPTION_FACTOR, WHITE, 255);
    }

     //Remove old chars that are not needed anymore
    for (int i = numLen + 1; i <= MAX_FREQUENCY_DIGITS; i++) {
        drawLetter(data, RF_SPACE,
                   data->optionData->selection.positions[CLOCK_FREQUENCY].x + 120 + (i * widthFactor),
                   data->optionData->selection.positions[CLOCK_FREQUENCY].y,
                   FONT_SCALE_OPTION_FACTOR, BLACK, 255);
    }

    //Draw > Symbol
    drawLetter(data, RF_GREATER_THAN,
               data->optionData->selection.positions[CLOCK_FREQUENCY].x + 120 + (numLen + 1) * widthFactor,
               data->optionData->selection.positions[CLOCK_FREQUENCY].y,
               FONT_SCALE_OPTION_FACTOR, WHITE, 255);
}

void clearFrequency(AppData_t* data)
{
    unsigned int spaceBetween = 2 * FONT_SCALE_OPTION_FACTOR;
    unsigned int widthFactor = RF_FONTWIDTH * FONT_SCALE_OPTION_FACTOR + spaceBetween;

    for (int i = 0; i < MAX_FREQUENCY_DIGITS; i++) {
        drawLetter(data, RF_SPACE,
                   data->optionData->selection.positions[CLOCK_FREQUENCY].x + 120 + (i * widthFactor),
                   data->optionData->selection.positions[CLOCK_FREQUENCY].y,
                   FONT_SCALE_OPTION_FACTOR, BLACK, 255);
    }
}

//TODO: Clear function
void drawKeybinds(AppData_t* data)
{
    unsigned int spaceBetween = 2 * FONT_SCALE_OPTION_FACTOR;
    unsigned int widthFactor = RF_FONTWIDTH * FONT_SCALE_OPTION_FACTOR + spaceBetween;

    int symbols[16];

    int xCount = 0;
    int yCount = 0;

    for (int i = 0; i < 16; i++) {
        SDL_Keycode keyCode = data->config.keyMap.mapping[i];
        if (keyCode == SDLK_Y) keyCode = SDLK_Z;
        if (keyCode == SDLK_Z) keyCode = SDLK_Y;

        StringToSymbols(SDL_GetKeyName(keyCode), symbols + i, 1);
    }

    //TODO: Remove me, just for testing purposes
    for (int i = 0; i < 16; i++) {
        printf("%c\n", data->config.keyMap.mapping[i]);
    }

    for (int i = 0; i < 16; i++)
    {
        if (i != 0 && i % 4 == 0)
        {
            yCount++;
            xCount = 0;
        }

        drawLetter(data, symbols[i], data->optionData->selection.positions[CLOCK_FREQUENCY].x + 120 + (xCount * widthFactor),
                   data->optionData->selection.positions[CLOCK_FREQUENCY].y + (yCount * 20),
                   FONT_SCALE_OPTION_FACTOR, WHITE, 255);
        xCount++;
    }
}

void clearKeybinds(AppData_t* data)
{
    unsigned int spaceBetween = 2 * FONT_SCALE_OPTION_FACTOR;
    unsigned int widthFactor = RF_FONTWIDTH * FONT_SCALE_OPTION_FACTOR + spaceBetween;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
        drawLetter(data, RF_SPACE, data->optionData->selection.positions[CLOCK_FREQUENCY].x + 120 + (j * widthFactor),
                   data->optionData->selection.positions[CLOCK_FREQUENCY].y + (i * 20),
                   FONT_SCALE_OPTION_FACTOR, BLACK, 255);
        }
    }
}

void onItemSelect(AppData_t* appData)
{
    //TODO: First, clear everything^
    clearFrequency(appData);
    clearKeybinds(appData);

    switch (appData->optionData->selection.selectedItem) {
        case CLOCK_FREQUENCY:
            drawFrequency(appData, appData->pChip8->cpuFrequency);
            break;
        case KEYBINDINGS:
            //TODO: Print Keys on Display
//            for (int i = 0; i < 16; i++) {
//                printf("%s", SDL_GetKeyName(appData->config.keyMap.mapping[i]));
//            }
            drawKeybinds(appData);
            break;
        case LOGGING:
            break;
        case EXIT_OPTION:
            break;
    }
}
