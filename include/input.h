//
// Created by Sebastian on 28.10.24.
//

#ifndef CHIP8_INTERPRETER_INPUT_H
#define CHIP8_INTERPRETER_INPUT_H

SDL_AppResult registerInput(Chip8_t* pChip8, SDL_Event* event)
{
    switch (event->type) {
        case SDL_EVENT_KEY_DOWN:
            switch (event->key.key) {

            }
    }
    return SDL_APP_CONTINUE;
}


#endif //CHIP8_INTERPRETER_INPUT_H

//Abfrage und Verwaltung des Zustandes der Tastatur.
