#ifndef CHIP8_INTERPRETER_COMMON_H
#define CHIP8_INTERPRETER_COMMON_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <SDL3/SDL.h>

#define RETROFONT_C
#include "RetroFont.h"

typedef enum Bool
{
    FALSE, TRUE
} Bool;

typedef struct Position
{
    unsigned int x;
    unsigned int y;
} Position_t;

#endif // CHIP8_INTERPRETER_COMMON_H
