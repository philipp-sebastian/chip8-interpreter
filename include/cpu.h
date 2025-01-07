//
// Created by Sebastian on 28.10.24.
//

#ifndef CHIP8_INTERPRETER_CPU_H
#define CHIP8_INTERPRETER_CPU_H

#include "common.h"
#include "chip8.h"
#include "application.h"
#include "instructions.h"

typedef struct InstructionData {
   unsigned char x;
   unsigned char y;
   unsigned char n;
   unsigned char nn;
   uint16_t nnn;
} InstructionData_t ;

//TODO: Define Makros for Opcode => Return Numbers
//TODO: Implement Functionpointer Array => Indices are the previous defined Makros

void incrementProgramCounter(Chip8_t* pChip8);
void decrementProgramCounter(Chip8_t* pChip8);
void setProgramCounter(Chip8_t* pChip8, const uint16_t* address);
uint16_t fetch(Chip8_t* pChip8);
void decode(AppData_t* appData, uint16_t instruction);
void fetchDecodeCycle(AppData_t* appData);

#endif //CHIP8_INTERPRETER_CPU_H

//Implementierung des Fetch, Decode und Execute Zyklus.
//Ausführung von spezifischen Instruktionen basierend auf Opcodes.
