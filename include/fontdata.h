//
// Created by Sebastian on 25.11.24.
//

#ifndef CHIP8_INTERPRETER_FONTDATA_H
#define CHIP8_INTERPRETER_FONTDATA_H

#include "common.h"

#define AMOUNT_OF_SPRITES 24
#define FONT_HEIGHT 7
#define FONT_WIDTH 5

typedef enum Letters
{
    fA = 0, fM = 1, fG = 2, fE = 3, fO = 4, fV = 5, fR = 6, fP = 7, fS = 8,
    fT = 9, f0 = 4, f1 = 10, f2 = 11, f3 = 12, f4 = 13, f5 = 8, f6 = 14, f7 = 15, f8 = 16, f9 = 17, fL = 18,
    fC = 19, fX = 20, fN = 21, fI = 22, fDOT = 23
} eLetters_t;

unsigned char* initializeFont(void);

#endif //CHIP8_INTERPRETER_FONTDATA_H
