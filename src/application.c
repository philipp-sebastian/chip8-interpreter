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

void clearScreen(void* appData)
{
    AppData_t* data = (AppData_t*) appData;

    memset(data->pChip8->display, 0, sizeof(data->pChip8->display));
    setRendererColor(data->windowData->renderer, BLACK, 255);
    SDL_RenderClear(data->windowData->renderer);
    setRendererColor(data->windowData->renderer, WHITE, 255);
}
