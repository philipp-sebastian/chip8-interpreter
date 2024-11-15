#include "../include/common.h"

/**
 *
 * @return
 */
int main(void)
{
    Chip8_t* pChip8 = initializeComponents();

    if (pChip8 == NULL)
    {
        printf("Closing Program");
        return -1;
    }

    loadGame(pChip8);

    while (1)
    {
        //imlementation
        break;
    }

}
