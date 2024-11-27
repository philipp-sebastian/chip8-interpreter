//
// Created by Sebastian on 15.11.24.
//

#include "../include/loadgame.h"

int loadGame(Chip8_t* pChip8)
{
    if (pChip8 == NULL)
    {
        return -1;
    }

    const char* filePath = "../games/wonkypong.ch8";
    FILE* fileHandle;

    if ((fileHandle = fopen(filePath, "rb")) == NULL)
    {
        perror("Error while opening the file: ");
        return -1;
    }

    fseek(fileHandle, 0, SEEK_END);
    size_t rom_len = ftell(fileHandle);
    fseek(fileHandle, 0, SEEK_SET);

    if (rom_len >= (MEMORYSIZE - STARTGAMEMEMORY))
    {
        printf("Memory overload\n");
        fclose(fileHandle);
        return -1;
    }

    size_t readBytes = fread((void*) (pChip8->memory + STARTGAMEMEMORY), sizeof(char), rom_len, fileHandle);

    if (readBytes != rom_len)
    {
        printf("Error while reading\n");
        fclose(fileHandle);
        return -1;
    }

    fclose(fileHandle);

//    printf("%d Romlen: %d\n", (int) readBytes, (int) rom_len);
//    for (size_t i = 0; i < rom_len; i++)
//    {
//        printf("%d ", *(pChip8->memory + STARTGAMEMEMORY + i));
//    }

    return 0;
}
