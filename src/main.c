#include "../include/application.h"
#include "../include/configHandler.h"
#include "../include/chip8.h"
#include "../include/common.h"
#include "../include/cpu.h"
#include "../include/display.h"
#include "../include/input.h"
#include "../include/instructions.h"
#include "../include/loadgame.h"
#include "../include/main.h"
#include "../include/menu.h"
#include "../include/timer.h"

#include "SDL3/SDL_main.h"

SDL_AppResult SDL_AppInit(void** appData, int argc, char* argv[])
{
    Chip8_t* pChip8 = initializeComponents();

    if (pChip8 == NULL)
    {
        return SDL_APP_FAILURE;
    }

    AppData_t* data = malloc(sizeof(AppData_t));
    *appData = (void*)data;
    WindowData_t* windowData = malloc(sizeof(WindowData_t));
    UpdateTracker_t* updateTracker = malloc(sizeof(UpdateTracker_t));
    MenuData_t* menuData = malloc(sizeof(MenuData_t));
    unsigned char* fontData = InitializeFont();

    windowData->updateTracker = updateTracker;
    data->windowData = windowData;
    data->pChip8 = pChip8;
    data->fontData = fontData;
    data->menuData = menuData;

    readConfig(data);

    data->hasProgram = FALSE; //TODO: Fetch from configfile

    if (data->windowData == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "windowdata is null\n");
    }

    if (!SDL_CreateWindowAndRenderer("Chip8-Interpreter", APPLICATION_WIDTH, APPLICATION_HEIGHT, 0, &windowData->window, &windowData->renderer))
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to create Window and Renderer\n");
        return SDL_APP_FAILURE;
    }

    if (!SDL_SetRenderDrawBlendMode(data->windowData->renderer, SDL_BLENDMODE_BLEND))
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s\n", SDL_GetError());
    }

    clearScreen(data);

    loadMenu(data);


    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appData)
{
    AppData_t* data = (AppData_t*) appData;

    uint64_t currentTime = SDL_GetTicks();
    static uint64_t lastFrameTime = 0;

    //TODO: Make Framerate to 500-1000Hz
    if (data->windowData->currentScreen == CHIP8)
    {
        fetchDecodeCycle(appData);
    }

    if (currentTime - lastFrameTime >= DESIRED_DELTA_TIME)
    {
        drawDisplay(data->windowData);
        //TODO: Delay- / Soundtimer
        lastFrameTime = currentTime;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appData, SDL_Event* event)
{
    AppData_t* data = (AppData_t*) appData;

    switch (event->type) {
        case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS;
    }

    switch (data->windowData->currentScreen) {
        case CHIP8:
            return chip8EventHandler(data, event);
        case OPTION:
            break;
        case MENU:
            return MenuEventHandler(data, event); //TODO: ???
    }

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appData, SDL_AppResult result)
{
    AppData_t* data = (AppData_t*) appData;

    SDL_DestroyWindow(data->windowData->window);
    SDL_DestroyRenderer(data->windowData->renderer);

    free(data->windowData->updateTracker);
    free(data->windowData);
    free(data->menuData);
    free(data->pChip8);
    free(data);

}
