#include "../include/common.h"

void incrementProgramCounter(Chip8_t* pChip8)
{
    pChip8->programCounter += 2;
}

void setProgramCounter(Chip8_t* pChip8, const uint16_t* address)
{
    pChip8->programCounter = *address;
}

uint16_t fetch(Chip8_t* pChip8)
{
    uint16_t instruction;
    instruction = (pChip8->memory[pChip8->programCounter] << 8) | pChip8->memory[pChip8->programCounter + 1];
    //big endian
    incrementProgramCounter(pChip8);
    return instruction;
}

void decode(Chip8_t* pChip8, uint16_t instruction)
{
    //TODO: Free memory
    InstructionData_t* instructionData = malloc(sizeof(InstructionData_t));

    char commandType = (instruction & 0xF000) >> 12;

    instructionData->x = (instruction & 0x0F00) >> 8;
    instructionData->y = (instruction & 0x00F0) >> 4;
    instructionData->n = instruction & 0x000F;
    instructionData->nn = instruction & 0x00FF;
    instructionData->nnn = instruction & 0x0FFF;

    switch (commandType)
    {
        case 0x0:
            if (instructionData->x == 0x0 && instructionData->n == 0x0)
            {
                cls_clear_display(pChip8, instructionData);
            }
            else if (instructionData->x == 0x0)
            {
                ret_return_subroutine(pChip8, instructionData);
            }
            else
            {
                sys_jump_to_addr(pChip8, instructionData);
            }
            break;
        case 0x1:
            jp_jump_to_addr(pChip8, instructionData);
            break;
        case 0x2:
            call_subroutine(pChip8, instructionData);
            break;
        case 0x3:
            se_skip_if_equal(pChip8, instructionData);
            break;
        case 0x4:
            sne_skip_if_not_equal(pChip8, instructionData);
            break;
        case 0x5:
            se_skip_if_vx_equals_vy(pChip8, instructionData);
            break;
        case 0x6:
            ld_set_vx(pChip8, instructionData);
            break;
        case 0x7:
            add_add_to_vx(pChip8, instructionData);
            break;
        case 0x8:
            switch (instructionData->n)
            {
                case 0x0:
                    ld_set_vx_to_vy(pChip8, instructionData);
                    break;
                case 0x1:
                    or_set_vx_or_vy(pChip8, instructionData);
                    break;
                case 0x2:
                    and_set_vx_and_vy(pChip8, instructionData);
                    break;
                case 0x3:
                    xor_set_vx_xor_vy(pChip8, instructionData);
                    break;
                case 0x4:
                    add_add_vx_vy(pChip8, instructionData);
                    break;
                case 0x5:
                    sub_vx_minus_vy(pChip8, instructionData);
                    break;
                case 0x6:
                    shr_shift_right_vx(pChip8, instructionData);
                    break;
                case 0x7:
                    subn_vy_minus_vx(pChip8, instructionData);
                    break;
                case 0xE:
                    shl_shift_left_vx(pChip8, instructionData);
                    break;
                default:
                    printf("Invalid 8xy-Command\n");
                    break;
            }
            break;
        case 0x9:
            sne_skip_if_vx_not_equal_vy(pChip8, instructionData);
            break;
        case 0xA:
            ld_set_i(pChip8, instructionData);
            break;
        case 0xB:
            jp_v0_plus_addr(pChip8, instructionData);
            break;
        case 0xC:
            rnd_vx_random_and_byte(pChip8, instructionData);
            break;
        case 0xD:
            drw_draw_sprite(pChip8, instructionData);
            break;
        case 0xE:
            if (instructionData->y == 0x9 && instructionData->n == 0xE)
            {
                skp_skip_if_key_pressed(pChip8, instructionData);
            }
            else if (instructionData->y == 0xA && instructionData->n == 0x1)
            {
                sknp_skip_if_key_not_pressed(pChip8, instructionData);
            }
            else
            {
                printf("Invalid Ex-Command\n");
            }
            break;
        case 0xF:
            switch (instructionData->nn)
            {
                case 0x07:
                    ld_set_vx_to_delay_timer(pChip8, instructionData);
                    break;
                case 0x0A:
                    ld_wait_for_key_press(pChip8, instructionData);
                    break;
                case 0x15:
                    ld_set_delay_timer(pChip8, instructionData);
                    break;
                case 0x18:
                    ld_set_sound_timer(pChip8, instructionData);
                    break;
                case 0x1E:
                    add_add_i_and_vx(pChip8, instructionData);
                    break;
                case 0x29:
                    ld_set_i_to_sprite_addr(pChip8, instructionData);
                    break;
                case 0x33:
                    ld_store_bcd(pChip8, instructionData);
                    break;
                case 0x55:
                    ld_store_v0_to_vx(pChip8, instructionData);
                    break;
                case 0x65:
                    ld_read_v0_to_vx(pChip8, instructionData);
                    break;
                default:
                    printf("Invalid Fx-Command\n");
                    break;
            }
            break;
        default:
            printf("Invalid Command\n");
            break;
    }

    free(instructionData);
}
