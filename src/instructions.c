#include "../include/common.h"

int sys_jump_to_addr(Chip8_t *pChip8, InstructionData_t *instructionData);

int cls_clear_display(Chip8_t *pChip8, InstructionData_t *instructionData);

int ret_return_subroutine(Chip8_t *pChip8, InstructionData_t *instructionData);

int jp_jump_to_addr(Chip8_t *pChip8, InstructionData_t *instructionData);

int call_subroutine(Chip8_t *pChip8, InstructionData_t *instructionData);

int se_skip_if_equal(Chip8_t *pChip8, InstructionData_t *instructionData);

int sne_skip_if_not_equal(Chip8_t *pChip8, InstructionData_t *instructionData);

int se_skip_if_vx_equals_vy(Chip8_t *pChip8, InstructionData_t *instructionData);

int ld_set_vx(Chip8_t *pChip8, InstructionData_t *instructionData);

int add_add_to_vx(Chip8_t *pChip8, InstructionData_t *instructionData);

int ld_set_vx_to_vy(Chip8_t *pChip8, InstructionData_t *instructionData);

int or_set_vx_or_vy(Chip8_t *pChip8, InstructionData_t *instructionData);

int and_set_vx_and_vy(Chip8_t *pChip8, InstructionData_t *instructionData);

int xor_set_vx_xor_vy(Chip8_t *pChip8, InstructionData_t *instructionData);

int add_add_vx_vy(Chip8_t *pChip8, InstructionData_t *instructionData);

int sub_vx_minus_vy(Chip8_t *pChip8, InstructionData_t *instructionData);

int shr_shift_right_vx(Chip8_t *pChip8, InstructionData_t *instructionData);

int subn_vy_minus_vx(Chip8_t *pChip8, InstructionData_t *instructionData);

int shl_shift_left_vx(Chip8_t *pChip8, InstructionData_t *instructionData);

int sne_skip_if_vx_not_equal_vy(Chip8_t *pChip8, InstructionData_t *instructionData);

/**
 * sets Index register to instruction nnn
 * @param pChip8
 * @param instructionData
 * @return
 */
int ld_set_i(Chip8_t *pChip8, InstructionData_t *instructionData)
{
    if (pChip8 == NULL || instructionData == NULL)
    {
        return -1;
    }

    pChip8->indexRegister = instructionData->nnn;
    return 0;
}

int jp_v0_plus_addr(Chip8_t *pChip8, InstructionData_t *instructionData)
{
    if (pChip8 == NULL || instructionData == NULL)
    {
        return -1;
    }

    pChip8->programCounter = instructionData->nnn + pChip8->gpr[V0];

    return 0;
}

/**
 * Gets a random number and ANDs it with nn instruction data and puts it register V0
 * @param pChip8
 * @param instructionData
 * @return
 */
int rnd_vx_random_and_byte(Chip8_t *pChip8, InstructionData_t *instructionData)
{
    if (pChip8 == NULL || instructionData == NULL)
    {
        return -1;
    }

    unsigned char random = rand() % 256;
    pChip8->gpr[V0] = random & instructionData->nn;

    return 0;
}

/**
 * draws an n pixels tall sprite depending on index register at given coordinates at vx and vy
 *
 * @param pChip8
 * @param instructionData
 * @return
 */
int drw_draw_sprite(Chip8_t *pChip8, InstructionData_t *instructionData)
{
    if (pChip8 == NULL || instructionData == NULL)
    {
        return -1;
    }

    char x = pChip8->gpr[instructionData->x] % WIDTH;
    char y = pChip8->gpr[instructionData->y] % HEIGHT;
    char collision = 0;

    pChip8->gpr[VF] = 0;

    for (int row = 0; row < instructionData->n; row++) {
        char fetchedByte = pChip8->memory[pChip8->indexRegister + row];

        //sprite is clipping, if out of bounce
        if ((y + row) >= HEIGHT)
        {
            break;
        }

        //filters every bit, starting with the largest bit
        for (int bit = 0; bit < BYTESIZE; bit++) {

            //sprite is clipping, if out of bounce
            if ((x + bit) >= WIDTH)
            {
                break;
            }

            char bitValue = fetchedByte >> (BYTESIZE - 1 - bit) & 1;
            char displayBitValue = pChip8->display[x + bit][y + row];

            if (bitValue == 1 && displayBitValue == 1) {
                collision = 1;
            }

            //flip bit
            pChip8->display[x + bit][y + row] ^= bitValue;
        }
    }

    if (collision == 1) {
        pChip8->gpr[VF] = collision;
    }

    return 0;
}

/**
 * increments the programCounter if the coressponding key to the value of VX is pressed
 * @param pChip8
 * @param instructionData
 * @return
 */
int skp_skip_if_key_pressed(Chip8_t *pChip8, InstructionData_t *instructionData)
{
    if (pChip8 == NULL || instructionData == NULL)
    {
        return -1;
    }

    if (getKeyboardInput() == pChip8->gpr[instructionData->x])
    {
        incrementProgramCounter(pChip8);
    }

    return 0;
}


int sknp_skip_if_key_not_pressed(Chip8_t *pChip8, InstructionData_t *instructionData)
{
    if (pChip8 == NULL || instructionData == NULL)
    {
        return -1;
    }

    if (getKeyboardInput() != pChip8->gpr[instructionData->x])
    {
        incrementProgramCounter(pChip8);
    }

    return 0;
}

/**
 * puts the value of the delay timer in VX
 * @param pChip8
 * @param instructionData
 * @return
 */
int ld_set_vx_to_delay_timer(Chip8_t *pChip8, InstructionData_t *instructionData)
{
    if (pChip8 == NULL || instructionData == NULL)
    {
        return -1;
    }

    pChip8->gpr[instructionData->x] = pChip8->delayTimer;

    return 0;
}

/**
 * Wait until a key is pressed and put the value in VX
 * @param pChip8
 * @param instructionData
 * @return
 */
int ld_wait_for_key_press(Chip8_t *pChip8, InstructionData_t *instructionData)
{
    if (pChip8 == NULL || instructionData == NULL)
    {
        return -1;
    }

    pChip8->gpr[instructionData->x] = WaitForKeyboardInput();

    return 0;
}

/**
 * Sets the delay timer to value in VX
 * @param pChip8
 * @param instructionData
 * @return
 */
int ld_set_delay_timer(Chip8_t *pChip8, InstructionData_t *instructionData)
{
    if (pChip8 == NULL || instructionData == NULL)
    {
        return -1;
    }

    pChip8->delayTimer = pChip8->gpr[instructionData->x];

    return 0;
}

int ld_set_sound_timer(Chip8_t *pChip8, InstructionData_t *instructionData)
{
    if (pChip8 == NULL || instructionData == NULL)
    {
        return -1;
    }

    pChip8->soundTimer = pChip8->gpr[instructionData->x];

    return 0;
}

/**
 * adds the value in VX to the indexRegister
 * @param pChip8
 * @param instructionData
 * @return
 */
int add_add_i_and_vx(Chip8_t *pChip8, InstructionData_t *instructionData)
{
    if (pChip8 == NULL || instructionData == NULL)
    {
        return -1;
    }

    pChip8->indexRegister += pChip8->gpr[instructionData->x];

    return 0;
}

/**
 * Sets indexRegister to the address of the font character in VX. Uses only the last nibble of VX
 * @param pChip8
 * @param instructionData
 * @return
 */
int ld_set_i_to_sprite_addr(Chip8_t *pChip8, InstructionData_t *instructionData)
{
    if (pChip8 == NULL || instructionData == NULL)
    {
        return -1;
    }

    pChip8->indexRegister = FONTSTARTADRESS + (pChip8->gpr[instructionData->x] & 0xF) * FONTHEIGHT;

    return 0;
}

/**
 * Binary coded decimal conversion puts the three demical number parts
 * from the value in VX and safes them independently starting at the address in indexRegister
 * @param pChip8
 * @param instructionData
 * @return
 */
int ld_store_bcd(Chip8_t *pChip8, InstructionData_t *instructionData)
{
    if (pChip8 == NULL || instructionData == NULL)
    {
        return -1;
    }

    unsigned char value = pChip8->gpr[instructionData->x];

    for (int number = 0; number < 3; number++)
    {
        pChip8->memory[pChip8->indexRegister] = value % 10;
        value /= 10;
    }

    return 0;
}

/**
 * copies the values of V0 - VX into memory starting at the address in indexRegister
 * @param pChip8
 * @param instructionData
 * @return
 */
int ld_store_v0_to_vx(Chip8_t *pChip8, InstructionData_t *instructionData)
{
    //TODO add configurability if
    // indexRegister should be incremented? Was in old chips but implemented version is more common
    if (pChip8 == NULL || instructionData == NULL)
    {
        return -1;
    }

    for (int counter = 0; counter <= instructionData->x; counter ++)
    {
        pChip8->memory[pChip8->indexRegister + counter] = pChip8->gpr[counter];
    }

    return 0;
}

/**
 * reads x values starting from the register in indexRegister and saves them in V0 - VX
 * @param pChip8
 * @param instructionData
 * @return
 */
int ld_read_v0_to_vx(Chip8_t *pChip8, InstructionData_t *instructionData)
{
    //TODO add configurability if
    // indexRegister should be incremented? Was in old chips but implemented version is more common
    if (pChip8 == NULL || instructionData == NULL)
    {
        return -1;
    }

    for (int counter = 0; counter <= instructionData->x; counter ++)
    {
        pChip8->gpr[counter] = pChip8->memory[pChip8->indexRegister + counter];
    }

    return 0;
}