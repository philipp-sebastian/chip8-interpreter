//
// Created by Sebastian on 17.12.24.
//

#include "../include/input.h"

SDL_AppResult registerInput(AppData_t* appData, SDL_Event* event)
{
    SDL_Keycode* keyMapping = appData->config.keyMap.mapping;
    unsigned char* inputMap = appData->pChip8->inputMap;

    switch (event->type) {
        case SDL_EVENT_KEY_DOWN:
            for (int i = KEYID_0; i <= KEYID_F; i++) {
                if (event->key.key == keyMapping[i]) {
                    //SDL_Log("KeyPressed: %d", i);
                    inputMap[i] = 1;
                    break;
                }
            }
            break;
        case SDL_EVENT_KEY_UP:
            for (int i = KEYID_0; i <= KEYID_F; i++) {
                if (event->key.key == keyMapping[i]) {
                    inputMap[i] = 0;
                    break;
                }
            }
            break;
    }
    return SDL_APP_CONTINUE;
}
