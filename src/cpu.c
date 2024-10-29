#include "../include/common.h"

void incrementProgramCounter(Chip8_t* pChip8)
{
    pChip8->programCounter += 2;
}

uint16_t fetch(Chip8_t* pChip8)
{
    uint16_t instruction;
    instruction = (pChip8->memory[pChip8->programCounter] << 8) | pChip8->memory[pChip8->programCounter + 1];
    //big endian
    incrementProgramCounter(pChip8);
    return instruction;
}

void decode(Chip8_t* pChip8, uint16_t instruction)
{
    //TODO: Free memory
    InstructionData_t* instructionData = malloc(sizeof(InstructionData_t));

    char commandType = (instruction & 0xF000) >> 12;

    instructionData->x = (instruction & 0x0F00) >> 8;
    instructionData->y = (instruction & 0x00F0) >> 4;
    instructionData->n = instruction & 0x000F;
    instructionData->nn = instruction & 0x00FF;
    instructionData->nnn = instruction & 0x0FFF;

    switch (commandType)
    {
        case 0x0:
            if (instructionData->x == 0x0 && instructionData->n == 0x0)
            {
                //cls-function
            }
            else if (instructionData->x == 0x0)
            {
                //ret
            }
            else
            {
                //sys addr
            }
            break;
        case 0x1:
            //jump
            break;
        case 0x2:
            //call
            break;
        case 0x3:
            //se Vx, byte
            break;
        case 0x4:
            //SNE Vx, byte
            break;
        case 0x5:
            //SE Vx, Vy
            break;
        case 0x6:
            //LD Vx, byte
            break;
        case 0x7:
            //ADD Vx, Byte
            break;
        case 0x8:
            switch (instructionData->n)
            {
                case 0x0:
                    //LD Vx, Vy
                    break;
                case 0x1:
                    //OR Vx, Vy
                    break;
                case 0x2:
                    //AND Vx, Vy
                    break;
                case 0x3:
                    //XOR Vx, Vy
                    break;
                case 0x4:
                    //ADD Vx, Vy
                    break;
                case 0x5:
                    //SUB Vx, Vy
                    break;
                case 0x6:
                    //SHR Vx, Vy
                    break;
                case 0x7:
                    //SUBN Vx, Vy
                    break;
                case 0xE:
                    //SHL Vx, Vy
                    break;
            }
            break;
        case 0x9:
            //SNE Vx, Vy
            break;
        case 0xA:
            //LD I, ADDR
            break;
        case 0xB:
            //JP v0, addr
            break;
        case 0xC:
            //rnd vx, byte
            break;
        case 0xD:
            //draw vx, vy, nibble
            break;
        case 0xE:
            if (instructionData->y == 0x9 && instructionData->n == 0xE)
            {
                //skp vx
            }
            else if (instructionData->y == 0xA && instructionData->n == 0x1)
            {
                //sknp Vx
            }
            else
            {
                printf("Invalid Command!");
            }
            break;
        case 0xF:
            //jump
            break;
    }
    free(instructionData);
}