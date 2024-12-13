//
// Created by meyer on 10.12.2024.
//

#include "configHandler.h"
#include "application.h"

int writeConfig(AppData_t* appData)
{
    FILE* file = fopen("config.ini", "wb+");

    if (file == NULL)
    {
        SDL_Log("failed to open config file");
        return -1;
    }

    const char keyNames[] = {"123C456D789EA0BF"};

    for (int i = 0; i <= KEYID_F; i++)
    {
        fprintf(file, "Key_%c: %c\n", keyNames[i], appData->config.keyMap.mapping[i]);
    }

    fclose(file);

    return 0;
}

int readConfig(AppData_t* appData)
{
    FILE* file = fopen("config.ini", "rb");

    if (file == NULL)
    {
        SDL_Log("Creating config file");
        initKeyMap(appData);
        writeConfig(appData);
        return 1;
    }

    SDL_Log("reading from config file");

    char line[64];
    char hasError = 0;

    for (int i = 0; i <= KEYID_F; i++)
    {
        if (fgets(line, sizeof(line), file) == NULL)
        {
            SDL_Log("Format error in row %d config.ini", i);
            appData->config.keyMap.mapping[i] = getDefaultKeyCode(i);
            writeConfig(appData);
            return -1;
        }

        char* pos = strstr(line, ":");

        if (pos == NULL)
        {
            SDL_Log("Format error in config.ini");
            appData->config.keyMap.mapping[i] = getDefaultKeyCode(i);
            writeConfig(appData);
            return -1;
        }

        SDL_Keycode keyCode = SDL_GetKeyFromName(pos);

        if (keyCode == SDLK_UNKNOWN)
        {
            keyCode = getDefaultKeyCode(i);
            hasError = 1;
        }

        appData->config.keyMap.mapping[i] = keyCode;
        SDL_Log("%s", SDL_GetKeyName(keyCode));
    }

    fclose(file);

    if (hasError)
    {
        writeConfig(appData);
    }

    return 0;

}

int initKeyMap(AppData_t* appData)
{
    appData->config.keyMap.mapping[KEYID_1] = SDLK_1;
    appData->config.keyMap.mapping[KEYID_2] = SDLK_2;
    appData->config.keyMap.mapping[KEYID_3] = SDLK_3;
    appData->config.keyMap.mapping[KEYID_C] = SDLK_4;
    appData->config.keyMap.mapping[KEYID_4] = SDLK_Q;
    appData->config.keyMap.mapping[KEYID_5] = SDLK_W;
    appData->config.keyMap.mapping[KEYID_6] = SDLK_E;
    appData->config.keyMap.mapping[KEYID_D] = SDLK_R;
    appData->config.keyMap.mapping[KEYID_7] = SDLK_A;
    appData->config.keyMap.mapping[KEYID_8] = SDLK_S;
    appData->config.keyMap.mapping[KEYID_9] = SDLK_D;
    appData->config.keyMap.mapping[KEYID_E] = SDLK_F;
    appData->config.keyMap.mapping[KEYID_A] = SDLK_Z;
    appData->config.keyMap.mapping[KEYID_0] = SDLK_X;
    appData->config.keyMap.mapping[KEYID_B] = SDLK_C;
    appData->config.keyMap.mapping[KEYID_F] = SDLK_V;

    return 0;
}

SDL_Keycode getDefaultKeyCode(unsigned int index)
{
    switch (index) {
        case KEYID_1:
            return SDLK_1;
        case KEYID_2:
            return SDLK_2;
        case KEYID_3:
            return SDLK_3;
        case KEYID_C:
            return SDLK_4;
        case KEYID_4:
            return SDLK_Q;
        case KEYID_5:
            return SDLK_W;
        case KEYID_6:
            return SDLK_E;
        case KEYID_D:
            return SDLK_R;
        case KEYID_7:
            return SDLK_A;
        case KEYID_8:
            return SDLK_S;
        case KEYID_9:
            return SDLK_D;
        case KEYID_E:
            return SDLK_F;
        case KEYID_A:
            return SDLK_Z;
        case KEYID_0:
            return SDLK_X;
        case KEYID_B:
            return SDLK_C;
        case KEYID_F:
            return SDLK_V;
        default:
            return SDLK_UNKNOWN;
    }
}


