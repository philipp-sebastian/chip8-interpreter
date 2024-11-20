//
// Created by Sebastian on 19.11.24.
//

#include "common.h"

void setRendererColor(SDL_Renderer* renderer, eColor_t color, unsigned char alpha)
{
    switch (color) {
        case BLACK:
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, alpha);
            break;
        case WHITE:
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, alpha);
            break;
    }
}

void clearScreen(AppData_t* appData)
{
    memset(appData->pChip8->display, 0, sizeof(appData->pChip8->display));
    setRendererColor(appData->windowData->renderer, BLACK, 255);
    SDL_RenderClear(appData->windowData->renderer);
    setRendererColor(appData->windowData->renderer, WHITE, 255);
}

void updatePixel(AppData_t* appData, PixelData_t pixelData)
{
    appData->pChip8->display[pixelData.position.x][pixelData.position.y] = pixelData.color;
    appData->windowData->updateTracker->pixels[appData->windowData->updateTracker->updateCounter] = pixelData;

    appData->windowData->updateTracker->updateCounter++;
}

void drawDisplay(WindowData_t* windowData)
{
    for (int i = 0; i < windowData->updateTracker->updateCounter; i++)
    {
        setRendererColor(windowData->renderer, windowData->updateTracker->pixels[i].color, windowData->updateTracker->pixels[i].alpha);
        SDL_RenderPoint(windowData->renderer, windowData->updateTracker->pixels[i].position.x, windowData->updateTracker->pixels[i].position.y);
    }

    windowData->updateTracker->updateCounter = 0;
    SDL_RenderPresent(windowData->renderer);
}
