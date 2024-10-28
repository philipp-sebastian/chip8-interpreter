#ifndef CHIP8_INTERPRETER_CHIP8_H
#define CHIP8_INTERPRETER_CHIP8_H

#include "common.h"

#define V0 0
#define V1 1
#define V2 2
#define V3 3
#define V4 4
#define V5 5
#define V6 6
#define V7 7
#define V8 8
#define V9 9
#define VA 10
#define VB 11
#define VC 12
#define VD 13
#define VE 14
#define VF 15

typedef struct Stack {
    uint16_t stackMemory[16];
    unsigned short stackPointer;
} Stack_t;

//TODO: Program starts at address 0x200 (512 Decimal)

typedef struct Chip8 {
    char memory[4096];
    uint16_t programCounter;
    char display[32][64];
    uint16_t indexRegister;
    Stack_t stack;
    char delayTimer;
    char soundTimer;
    char gpr[16];
} Chip8_t;

Chip8_t* initializeComponents();
void freeComponents(Chip8_t* pChip8);

#endif //CHIP8_INTERPRETER_CHIP8_H

//Definition der Grundstruktur von CHIP-8 (Speicher, Register, Stack).
// Initialisierung und Reset der Kernkomponenten.
// Hilfsfunktionen für Kernoperationen wie Speicherzugriff und Stack-Management.