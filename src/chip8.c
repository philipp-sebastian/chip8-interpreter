#include "../include/chip8.h"
#include "../include/application.h"

Chip8_t* initializeComponents(void)
{
    Chip8_t* pChip8 = NULL;
    pChip8 = (Chip8_t*) malloc(sizeof(Chip8_t));

    //Set randomizer
    srand(time(NULL));

    if (pChip8 == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error while allocating memory in Heap for Chip8 Components\n");
        return NULL;
    }

    //TODO: Initialize Components
    //start at program-memory
    pChip8->programCounter = STARTGAMEMEMORY;
    //initializing 32x64pixels display
    memset(pChip8->display, 0, sizeof(pChip8->display));
    pChip8->indexRegister = 0;
    pChip8->stack.stackPointer = 0;
    memset(pChip8->inputMap, 0, sizeof(pChip8->inputMap));

    initializeFontData(pChip8);

    return pChip8;
}

void freeComponents(Chip8_t* pChip8)
{
    free(pChip8);
    pChip8 = NULL;
    printf("Freed allocated Chip8 Components in Heap");
}

void resetChip8(AppData_t* appData)
{
    clearScreen(appData);
    memset(appData->pChip8->gpr, 0, sizeof (appData->pChip8->gpr));
    appData->pChip8->programCounter = STARTGAMEMEMORY;
    appData->pChip8->indexRegister = 0;
    appData->pChip8->stack.stackPointer = 0;
    memset(appData->pChip8->memory + STARTGAMEMEMORY, 0, MEMORYSIZE - STARTGAMEMEMORY);
    loadGame(appData, appData->filePath.path); //TODO: Fix on Mac!
}
