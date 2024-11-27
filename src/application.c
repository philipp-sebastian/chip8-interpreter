//
// Created by Sebastian on 19.11.24.
//

#include "../include/application.h"

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
    switch (appData->windowData->currentScreen)
    {
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

void changeResolution(WindowData_t* windowData)
{
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

void drawLetter(AppData_t* appData, enum Symbol letter, unsigned int x, unsigned int y, unsigned int scale, eColor_t color, unsigned char alpha)
{
    unsigned int letterIndex = letter * RF_FONTHEIGHT;

    for (unsigned int height = 0; height < RF_FONTHEIGHT; height++)
    {
        unsigned char rowData = appData->fontData[letterIndex + height];

        for (unsigned int width = 0; width < RF_FONTWIDTH; width++)
        {
            if ((rowData >> (8 - width - 1) & 1) == 1)
            {
                for (unsigned int hScale = 0; hScale < scale; hScale++)
                {
                    for (unsigned int wScale = 0; wScale < scale; wScale++)
                    {
                        PixelData_t pixelData = { {wScale + width * scale + x, hScale + height * scale + y}, color, alpha };
                        updatePixel(appData, pixelData);
                    }
                }
            }
            else
            {
                for (unsigned int hScale = 0; hScale < scale; hScale++)
                {
                    for (unsigned int wScale = 0; wScale < scale; wScale++)
                    {
                        PixelData_t pixelData = { {wScale + width * scale + x, hScale + height * scale + y}, BLACK, 255 };
                        updatePixel(appData, pixelData);
                    }
                }
            }
        }
    }
}
