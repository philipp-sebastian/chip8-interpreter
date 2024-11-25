//
// Created by Sebastian on 28.10.24.
//

#ifndef CHIP8_INTERPRETER_DISPLAY_H
#define CHIP8_INTERPRETER_DISPLAY_H

#include "common.h"
#define FONTSTARTADRESS 0x50
#define CHIP8_FONT_HEIGHT 5

void initializeFontData(Chip8_t* pChip8);

#endif //CHIP8_INTERPRETER_DISPLAY_H

//Initialisierung und Aktualisierung des Displays.
//Funktionen zum Zeichnen und Löschen von Sprites.
