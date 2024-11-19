#include "../include/common.h"
#include "SDL3/SDL_main.h"

SDL_AppResult SDL_AppInit(void** appData, int argc, char*argv[])
{
    int i = argc;
    char** a = argv;
    printf("%d %s", i , *a);

    Chip8_t* pChip8 = initializeComponents();

    if (pChip8 == NULL)
    {
        return SDL_APP_FAILURE;
    }

    AppData_t* data = malloc(sizeof(AppData_t));
    WindowData_t* windowData = malloc(sizeof(WindowData_t));

    *appData = (void*)data;

    data->windowData = windowData;
    data->pChip8 = pChip8;

    int renderScale = 10; //TODO: Calculate the correct Renderscale

    if (!SDL_CreateWindowAndRenderer("Chip8-Interpreter", WIDTH * renderScale, HEIGHT * renderScale, 0, &windowData->window, &windowData->renderer))
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to create Window and Renderer\n");
        return SDL_APP_FAILURE;
    }

    SDL_SetRenderScale(windowData->renderer, (float) renderScale, (float) renderScale);

    clearScreen(appData);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appData)
{
    (void)appData; // Unused parameter
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appData, SDL_Event* event)
{
    (void)appData; // Unused parameter
    (void)event;   // Unused parameter
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appData, SDL_AppResult result)
{
    (void)appData; // Unused parameter
    (void)result;  // Unused parameter
}
