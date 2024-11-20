#include "../include/common.h"
#include "SDL3/SDL_main.h"

SDL_AppResult SDL_AppInit(void** appData, int argc, char* argv[])
{
    Chip8_t* pChip8 = initializeComponents();

    if (pChip8 == NULL)
    {
        return SDL_APP_FAILURE;
    }

    AppData_t* data = malloc(sizeof(AppData_t));
    WindowData_t* windowData = malloc(sizeof(WindowData_t));
    UpdateTracker_t* updateTracker = malloc(sizeof(UpdateTracker_t));

    windowData->updateTracker = updateTracker;
    data->windowData = windowData;
    data->pChip8 = pChip8;

    *appData = (void*)data;

    if (data->windowData == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "windowdata is null\n");
    }

    int renderScale = 20; //TODO: Calculate the correct Renderscale

    if (!SDL_CreateWindowAndRenderer("Chip8-Interpreter", WIDTH * renderScale, HEIGHT * renderScale, 0, &windowData->window, &windowData->renderer))
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to create Window and Renderer\n");
        return SDL_APP_FAILURE;
    }

    SDL_SetRenderScale(windowData->renderer, (float) renderScale, (float) renderScale);

    clearScreen(data);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appData)
{
    AppData_t* data = (AppData_t*) appData;

    Uint64 frameStart = SDL_GetTicks();
    drawDisplay(data->windowData);
    Uint64 frameEnd = SDL_GetTicks();

    Uint64 frameTime = frameEnd - frameStart;

    int timeLeft = DESIRED_DELTA_TIME - (float) frameTime;

    if (timeLeft < 0)
    {
        timeLeft = 0;
    }

    SDL_Delay(timeLeft);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appData, SDL_Event* event)
{
    switch (event->type) {
        case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS;
    }

    switch (event->key.key) {
        case SDLK_ESCAPE:
            return SDL_APP_SUCCESS;
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
    free(data->pChip8);
    free(data);

}
