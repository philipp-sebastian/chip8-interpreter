#include "../include/common.h"

Chip8_t* initializeComponents(void)
{
    Chip8_t* pChip8 = NULL;
    pChip8 = (Chip8_t*) malloc(sizeof(Chip8_t));

    //Set randomizer
    srand(time(NULL));

    if (pChip8 == NULL)
    {
        printf("Error while allocating memory in Heap for Chip8 Components");
        return NULL;
    }

    //TODO: Initialize Components
    //start at program-memory
    pChip8->programCounter = STARTGAMEMEMORY;
    //initializing 32x64pixels display
    memset(pChip8->display, 0, sizeof(pChip8->display));
    pChip8->indexRegister = 0;
    pChip8->stack.stackPointer = 0;
    initializeFontData(pChip8);

    return pChip8;
}

void freeComponents(Chip8_t* pChip8)
{
    free(pChip8);
    pChip8 = NULL;
    printf("Freed allocated Chip8 Components in Heap");
}
