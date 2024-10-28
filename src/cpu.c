#include "../include/common.h"

void incrementProgramCounter(Chip8_t* pChip8)
{
    pChip8->programCounter += 2;
}