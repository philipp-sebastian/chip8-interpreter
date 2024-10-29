//
// Created by Sebastian on 28.10.24.
//

#ifndef CHIP8_INTERPRETER_CPU_H
#define CHIP8_INTERPRETER_CPU_H

#include "common.h"

typedef struct InstructionData {
   char x;
   char y;
   char n;
   char nn;
   uint16_t nnn;
} InstructionData_t ;

typedef void (*command) (Chip8_t* pChip8);

//TODO: Define Makros for Opcode => Return Numbers
//TODO: Implement Functionpointer Array => Indices are the previous defined Makros

//fetch function

//decode function

//execute function

void incrementProgramCounter(Chip8_t* pChip8);
uint16_t fetch(Chip8_t* pChip8);

#endif //CHIP8_INTERPRETER_CPU_H

//Implementierung des Fetch, Decode und Execute Zyklus.
//Ausführung von spezifischen Instruktionen basierend auf Opcodes.