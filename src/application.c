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

/**
 * Handles the rebinding of a key
 * @param appData
 * @param key
 * @return 0 if key is not valid
 */
char rebindKey(AppData_t* appData, SDL_Keycode key) {
    switch (key) {
        case SDLK_BACKSPACE:
        case SDLK_ESCAPE:
        case SDLK_RETURN:
        case SDLK_TAB:
        case SDLK_DELETE:
        case SDLK_INSERT:
        case SDLK_HOME:
        case SDLK_END:
        case SDLK_PAGEUP:
        case SDLK_PAGEDOWN:
        case SDLK_UP:
        case SDLK_DOWN:
        case SDLK_LEFT:
        case SDLK_RIGHT:
        case SDLK_CAPSLOCK:
        case SDLK_SCROLLLOCK:
        case SDLK_NUMLOCKCLEAR:
        case SDLK_PRINTSCREEN:
        case SDLK_PAUSE:
        case SDLK_F1: case SDLK_F2: case SDLK_F3: case SDLK_F4:
        case SDLK_F5: case SDLK_F6: case SDLK_F7: case SDLK_F8:
        case SDLK_F9: case SDLK_F10: case SDLK_F11: case SDLK_F12:
            return 0;
        default:
            break;
    }

    appData->config.keyMap.mapping[getKeyIDFromIndex(appData->optionData->selectedKeybind)] = key;
    if (writeConfig(appData) == -1) return 0;

    selectKeyInKeyMap(appData);
    return 1;
}

//TODO: Move this method in menu.c ?
SDL_AppResult optionEventHandler(AppData_t *appData, SDL_Event *event) {
    if (event->type == SDL_EVENT_KEY_DOWN) {
        if (appData->optionData->selection.selectedItem == KEYBINDINGS && appData->optionData->inKeymap == 1) {
            if (rebindKey(appData, event->key.key)) return SDL_APP_CONTINUE;
        }

        switch (event->key.key) {
            case SDLK_ESCAPE:
                if (appData->optionData->selection.selectedItem == KEYBINDINGS && appData->optionData->inKeymap == 1) {
                    appData->optionData->inKeymap = 0;
                    drawKeybinds(appData, NO_KEYBIND_MARKED);
                    break;
                }

                loadMenu(appData);
                return SDL_APP_CONTINUE;
            case SDLK_S:
            case SDLK_DOWN:
                if (appData->optionData->selection.selectedItem == KEYBINDINGS && appData->optionData->inKeymap == 1) {
                    if (appData->optionData->selectedKeybind + 4 < 16) appData->optionData->selectedKeybind += 4;
                    selectKeyInKeyMap(appData);
                    break;
                }

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
                if (appData->optionData->selection.selectedItem == KEYBINDINGS && appData->optionData->inKeymap == 1) {
                    if (appData->optionData->selectedKeybind - 4 >= 0) appData->optionData->selectedKeybind -= 4;
                    selectKeyInKeyMap(appData);
                    break;
                }

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
                        if (appData->optionData->inKeymap == 0) {
                            appData->optionData->selectedKeybind = getKeyPadIndex(KEYID_1);
                            appData->optionData->inKeymap = 1;
                            selectKeyInKeyMap(appData);
                        }
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

                if (appData->optionData->selection.selectedItem == KEYBINDINGS && appData->optionData->inKeymap == 1) {
                    if (appData->optionData->selectedKeybind < 15) appData->optionData->selectedKeybind++;
                    selectKeyInKeyMap(appData);
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

                if (appData->optionData->selection.selectedItem == KEYBINDINGS && appData->optionData->inKeymap == 1) {
                    if (appData->optionData->selectedKeybind > 0) appData->optionData->selectedKeybind--;
                    selectKeyInKeyMap(appData);
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

//TODO: What to do with Return Key?
void drawKeybinds(AppData_t* data, char selectedKey)
{
    char keys[16];
    int symbolBuf[16];

    for (int i = 0; i < 16; i++) {
        SDL_Keycode keyCode = data->config.keyMap.mapping[i];
        keys[i] = *SDL_GetKeyName(keyCode); //Only takes the FIRST Char from GetKeyName()
    }

    StringToSymbols(keys, symbolBuf, 16);

    for (int i = 0; i < 16; i++) {
        if (getKeyPadIndex(i) == selectedKey) {
            drawKeybind(data, i, symbolBuf[i], 100);
        } else {
            drawKeybind(data, i, symbolBuf[i], 255);
        }
    }
}

void drawKeybind(AppData_t* data, enum KeyID keyPos, int key, unsigned char alpha)
{
    int index = getKeyPadIndex(keyPos);

    int xCount = index % 4;
    int yCount = index / 4;

    drawLetter(data, key, data->optionData->selection.positions[CLOCK_FREQUENCY].x + 120 + (xCount * WIDTH_FACTOR_OPTION),
               data->optionData->selection.positions[CLOCK_FREQUENCY].y + (yCount * 20),
               FONT_SCALE_OPTION_FACTOR, WHITE, alpha);
}

int getKeyPadIndex(enum KeyID key) {
    switch (key) {
        case KEYID_0:
            return 13;
            break;
        case KEYID_1:
            return 0;
            break;
        case KEYID_2:
            return 1;
            break;
        case KEYID_3:
            return 2;
            break;
        case KEYID_4:
            return 4;
            break;
        case KEYID_5:
            return 5;
            break;
        case KEYID_6:
            return 6;
            break;
        case KEYID_7:
            return 8;
            break;
        case KEYID_8:
            return 9;
            break;
        case KEYID_9:
            return 10;
            break;
        case KEYID_A:
            return 12;
            break;
        case KEYID_B:
            return 14;
            break;
        case KEYID_C:
            return 3;
            break;
        case KEYID_D:
            return 7;
            break;
        case KEYID_E:
            return 11;
            break;
        case KEYID_F:
            return 15;
            break;
    }
}

enum KeyID getKeyIDFromIndex(int index) {
    switch (index) {
        case 0:
            return KEYID_1;
        case 1:
            return KEYID_2;
        case 2:
            return KEYID_3;
        case 3:
            return KEYID_C;
        case 4:
            return KEYID_4;
        case 5:
            return KEYID_5;
        case 6:
            return KEYID_6;
        case 7:
            return KEYID_D;
        case 8:
            return KEYID_7;
        case 9:
            return KEYID_8;
        case 10:
            return KEYID_9;
        case 11:
            return KEYID_E;
        case 12:
            return KEYID_A;
        case 13:
            return KEYID_0;
        case 14:
            return KEYID_B;
        case 15:
            return KEYID_F;
        default:
            return -1; // Invalid index
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
            drawKeybinds(appData, NO_KEYBIND_MARKED);
            break;
        case LOGGING:
            break;
        case EXIT_OPTION:
            break;
    }
}

void selectKeyInKeyMap(AppData_t* appData)
{
    //First clear previous selections
    clearKeybinds(appData);
    drawKeybinds(appData, appData->optionData->selectedKeybind);
}
