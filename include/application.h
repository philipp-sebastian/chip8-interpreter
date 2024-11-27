//
// Created by Sebastian on 19.11.24.
//

#ifndef CHIP8_INTERPRETER_APPLICATION_H
#define CHIP8_INTERPRETER_APPLICATION_H

#include "common.h"
#include "chip8.h"
#include "menu.h"

#define FPS 60
#define DESIRED_DELTA_TIME 1000.f/(float) FPS
#define CHIP8_RENDER_SCALE 20
#define MENU_RENDER_SCALE 4
#define APPLICATION_WIDTH 1280
#define APPLICATION_HEIGHT 640

typedef struct MenuData MenuData_t;

typedef enum Screen
{
   CHIP8, OPTION, MENU
} eScreen_t;

typedef enum Color
{
    BLACK, WHITE, RED, GREEN
} eColor_t;


typedef struct PixelData
{
    Position_t position;
    eColor_t color;
    unsigned char alpha;
} PixelData_t;

typedef struct UpdateTracker
{
    PixelData_t pixels[CHIP8_WIDTH * CHIP8_HEIGHT * CHIP8_RENDER_SCALE * CHIP8_RENDER_SCALE];
    unsigned int updateCounter;
} UpdateTracker_t;

typedef struct WindowData
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    UpdateTracker_t* updateTracker;
    eScreen_t currentScreen;
} WindowData_t;

typedef struct AppData
{
    Chip8_t* pChip8;
    WindowData_t* windowData;
    unsigned char* fontData;
    unsigned char display[CHIP8_WIDTH * CHIP8_RENDER_SCALE][CHIP8_HEIGHT * CHIP8_RENDER_SCALE];
    MenuData_t* menuData;
    Bool hasProgram; //TODO: Save in Configtextfile
} AppData_t;

void setRendererColor(SDL_Renderer* renderer, eColor_t color, unsigned char alpha);
void clearScreen(AppData_t* appData);
void updatePixel(AppData_t* appData, PixelData_t pixelData);
void drawDisplay(WindowData_t* windowData);
void changeResolution(WindowData_t* windowData);
void drawLetter(AppData_t* appData, enum Symbol letter, unsigned int x, unsigned int y, unsigned int scale, eColor_t color, unsigned char alpha);


#endif //CHIP8_INTERPRETER_APPLICATION_H
