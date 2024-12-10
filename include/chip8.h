#ifndef CHIP8_INTERPRETER_CHIP8_H
#define CHIP8_INTERPRETER_CHIP8_H

#include "common.h"
#include "display.h"

#define STACKSIZE 16
#define MEMORYSIZE 4096
#define STARTGAMEMEMORY 0x200
#define CHIP8_WIDTH 64
#define CHIP8_HEIGHT 32

typedef struct AppData AppData_t;

typedef enum GprRegisters
{
   V0, V1, V2, V3, V4, V5, V6, V7, V8, V9, VA, VB, VC, VD, VE, VF
} GprRegisters_t;

typedef struct Stack
{
    uint16_t stackMemory[STACKSIZE];
    unsigned short stackPointer;
} Stack_t;

//TODO: Program starts at address 0x200 (512 Decimal)

typedef struct Chip8 {
    unsigned char memory[MEMORYSIZE]; //TODO: signed or unsigned char?
    uint16_t programCounter;
    unsigned char display[CHIP8_WIDTH][CHIP8_HEIGHT];
    uint16_t indexRegister;
    Stack_t stack;
    unsigned char delayTimer;
    unsigned char soundTimer;
    unsigned char gpr[16];
    unsigned char inputMap[16];
} Chip8_t;

Chip8_t* initializeComponents(void);
void freeComponents(Chip8_t* pChip8);
void resetChip8(AppData_t* appData);

#endif //CHIP8_INTERPRETER_CHIP8_H

//Definition der Grundstruktur von CHIP-8 (Speicher, Register, Stack).
// Initialisierung und Reset der Kernkomponenten.
// Hilfsfunktionen für Kernoperationen wie Speicherzugriff und Stack-Management.
