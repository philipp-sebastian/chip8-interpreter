#ifndef CHIP8_INTERPRETER_COMMON_H
#define CHIP8_INTERPRETER_COMMON_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <SDL3/SDL.h>

#define RETROFONT_C
#include "RetroFont.h"

#include "application.h"
#include "chip8.h"
#include "cpu.h"
#include "display.h"
#include "input.h"
#include "main.h"
#include "timer.h"
#include "instructions.h"
#include "menu.h"

#endif // CHIP8_INTERPRETER_COMMON_H
