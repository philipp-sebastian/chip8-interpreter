//
// Created by Sebastian on 19.11.24.
//

#ifndef CHIP8_INTERPRETER_APPLICATION_H
#define CHIP8_INTERPRETER_APPLICATION_H

#include "common.h"

#define FPS 60
#define DESIRED_DELTA_TIME 1000.f/(float) FPS

typedef enum Color
{
    BLACK, WHITE
} eColor_t;

typedef struct Position
{
    unsigned char x;
    unsigned char y;
} Position_t;

typedef struct PixelData
{
    Position_t position;
    eColor_t color;
    unsigned char alpha;
} PixelData_t;

typedef struct UpdateTracker
{
    PixelData_t pixels[WIDTH * HEIGHT];
    unsigned int updateCounter;
} UpdateTracker_t;

typedef struct WindowData
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    UpdateTracker_t* updateTracker;
} WindowData_t;

typedef struct AppData
{
    Chip8_t* pChip8;
    WindowData_t* windowData;
} AppData_t;

void setRendererColor(SDL_Renderer* renderer, eColor_t color, unsigned char alpha);
void clearScreen(AppData_t* appData);
void updatePixel(AppData_t* appData, PixelData_t pixelData);
void drawDisplay(WindowData_t* windowData);

#endif //CHIP8_INTERPRETER_APPLICATION_H
