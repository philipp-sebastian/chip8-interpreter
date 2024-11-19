//
// Created by Sebastian on 19.11.24.
//

#ifndef CHIP8_INTERPRETER_APPLICATION_H
#define CHIP8_INTERPRETER_APPLICATION_H

#include "common.h"

typedef struct WindowData
{
    SDL_Window* window;
    SDL_Renderer* renderer;
} WindowData_t;

typedef struct AppData
{
    Chip8_t* pChip8;
    WindowData_t* windowData;
} AppData_t;

typedef enum Color
{
    BLACK, WHITE
} eColor_t;

void setRendererColor(SDL_Renderer* renderer, eColor_t color, unsigned char alpha);
void clearScreen(void* appData);

#endif //CHIP8_INTERPRETER_APPLICATION_H
