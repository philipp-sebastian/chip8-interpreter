//
// Created by Sebastian on 28.10.24.
//

#ifndef CHIP8_INTERPRETER_CPU_H
#define CHIP8_INTERPRETER_CPU_H

#include "common.h"

typedef struct InstructionData {
   unsigned char x;
   unsigned char y;
   unsigned char n;
   unsigned char nn;
   uint16_t nnn;
} InstructionData_t ;

//TODO: Define Makros for Opcode => Return Numbers
//TODO: Implement Functionpointer Array => Indices are the previous defined Makros

//fetch function

//decode function

//execute function

void incrementProgramCounter(Chip8_t* pChip8);
void setProgramCounter(Chip8_t* pChip8, const uint16_t* address);
uint16_t fetch(Chip8_t* pChip8);

#endif //CHIP8_INTERPRETER_CPU_H

//Implementierung des Fetch, Decode und Execute Zyklus.
//Ausführung von spezifischen Instruktionen basierend auf Opcodes.
