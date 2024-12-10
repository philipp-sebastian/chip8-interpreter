//
// Created by meyer on 10.12.2024.
//

#include "configHandler.h"

int writeConfig(AppData_t* appData)
{
    FILE* file = fopen("config", "wb+");

    if (file == NULL)
    {
        SDL_Log("failed to open config file");
        return -1;
    }

    fwrite(&appData->config, sizeof(appData->config), 1, file);

    fclose(file);

    return 0;
}

int readConfig(AppData_t* appData)
{
    FILE* file = fopen("config", "rb");
    if (file == NULL)
    {
        initKeyMap(appData);
        writeConfig(appData);
        return 1;
    }

    fread(&appData->config, sizeof (Config_t), 1, file);

    fclose(file);

    return 0;

}

int initkeyMap(AppData_t* appData)
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

