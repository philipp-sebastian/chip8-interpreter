#include "../include/cpu.h"


void incrementProgramCounter(Chip8_t *pChip8) {
    pChip8->programCounter += 2;
}

void setProgramCounter(Chip8_t *pChip8, const uint16_t *address) {
    pChip8->programCounter = *address;
}

uint16_t fetch(Chip8_t *pChip8) {
    uint16_t instruction;
    instruction = (pChip8->memory[pChip8->programCounter] << 8) | pChip8->memory[pChip8->programCounter + 1];
    //big endian
    incrementProgramCounter(pChip8);
    return instruction;
}

void decode(AppData_t *appData, uint16_t instruction) {
    //TODO: Free memory
    InstructionData_t *instructionData = malloc(sizeof(InstructionData_t));
    //SDL_Log("Instruction: %x", instruction);
    char commandType = (instruction & 0xF000) >> 12;

    instructionData->x = (instruction & 0x0F00) >> 8;
    instructionData->y = (instruction & 0x00F0) >> 4;
    instructionData->n = instruction & 0x000F;
    instructionData->nn = instruction & 0x00FF;
    instructionData->nnn = instruction & 0x0FFF;

    char debugBuf[256];

    switch (commandType) {
        case 0x0:
            if (instructionData->x == 0x0 && instructionData->n == 0x0) {
                cls_clear_display(appData, instructionData);
                snprintf(debugBuf, sizeof(debugBuf), "Executed: Clear Display (CLS)");
            } else if (instructionData->x == 0x0) {
                ret_return_subroutine(appData->pChip8, instructionData);
                snprintf(debugBuf, sizeof(debugBuf), "Executed: Return from Subroutine (RET)");
            } else {
                sys_jump_to_addr(appData->pChip8, instructionData);
                snprintf(debugBuf, sizeof(debugBuf), "Executed: System Jump to Address (SYS)");
            }
            break;
        case 0x1:
            jp_jump_to_addr(appData->pChip8, instructionData);
            snprintf(debugBuf, sizeof(debugBuf), "Executed: Jump to Address (JP)");
            break;
        case 0x2:
            call_subroutine(appData->pChip8, instructionData);
            snprintf(debugBuf, sizeof(debugBuf), "Executed: Call Subroutine (CALL)");
            break;
        case 0x3:
            se_skip_if_equal(appData->pChip8, instructionData);
            snprintf(debugBuf, sizeof(debugBuf), "Executed: Skip if Equal (SE)");
            break;
        case 0x4:
            sne_skip_if_not_equal(appData->pChip8, instructionData);
            snprintf(debugBuf, sizeof(debugBuf), "Executed: Skip if Not Equal (SNE)");
            break;
        case 0x5:
            se_skip_if_vx_equals_vy(appData->pChip8, instructionData);
            snprintf(debugBuf, sizeof(debugBuf), "Executed: Skip if Vx == Vy (SE_VX_VY)");
            break;
        case 0x6:
            ld_set_vx(appData->pChip8, instructionData);
            snprintf(debugBuf, sizeof(debugBuf), "Executed: Set Vx (LD_VX)");
            break;
        case 0x7:
            add_add_to_vx(appData->pChip8, instructionData);
            snprintf(debugBuf, sizeof(debugBuf), "Executed: Add to Vx (ADD_VX)");
            break;
        case 0x8:
            switch (instructionData->n) {
                case 0x0:
                    ld_set_vx_to_vy(appData->pChip8, instructionData);
                    snprintf(debugBuf, sizeof(debugBuf), "Executed: Set Vx = Vy (LD_VX_VY)");
                    break;
                case 0x1:
                    or_set_vx_or_vy(appData->pChip8, instructionData);
                    snprintf(debugBuf, sizeof(debugBuf), "Executed: Vx = Vx OR Vy (OR_VX_VY)");
                    break;
                case 0x2:
                    and_set_vx_and_vy(appData->pChip8, instructionData);
                    snprintf(debugBuf, sizeof(debugBuf), "Executed: Vx = Vx AND Vy (AND_VX_VY)");
                    break;
                case 0x3:
                    xor_set_vx_xor_vy(appData->pChip8, instructionData);
                    snprintf(debugBuf, sizeof(debugBuf), "Executed: Vx = Vx XOR Vy (XOR_VX_VY)");
                    break;
                case 0x4:
                    add_add_vx_vy(appData->pChip8, instructionData);
                    snprintf(debugBuf, sizeof(debugBuf), "Executed: Add Vy to Vx (ADD_VX_VY)");
                    break;
                case 0x5:
                    sub_vx_minus_vy(appData->pChip8, instructionData);
                    snprintf(debugBuf, sizeof(debugBuf), "Executed: Subtract Vy from Vx (SUB_VX_VY)");
                    break;
                case 0x6:
                    shr_shift_right_vx(appData->pChip8, instructionData);
                    snprintf(debugBuf, sizeof(debugBuf), "Executed: Shift Vx Right (SHR_VX)");
                    break;
                case 0x7:
                    subn_vy_minus_vx(appData->pChip8, instructionData);
                    snprintf(debugBuf, sizeof(debugBuf), "Executed: Subtract Vx from Vy (SUBN_VY_VX)");
                    break;
                case 0xE:
                    shl_shift_left_vx(appData->pChip8, instructionData);
                    snprintf(debugBuf, sizeof(debugBuf), "Executed: Shift Vx Left (SHL_VX)");
                    break;
                default:
                    snprintf(debugBuf, sizeof(debugBuf), "Error: Invalid 8xy Command");
                    break;
            }
            break;
        case 0x9:
            sne_skip_if_vx_not_equal_vy(appData->pChip8, instructionData);
            snprintf(debugBuf, sizeof(debugBuf), "Executed: Skip if Vx != Vy (SNE_VX_VY)");
            break;
        case 0xA:
            ld_set_i(appData->pChip8, instructionData);
            snprintf(debugBuf, sizeof(debugBuf), "Executed: Set I (LD_I)");
            break;
        case 0xB:
            jp_v0_plus_addr(appData->pChip8, instructionData);
            snprintf(debugBuf, sizeof(debugBuf), "Executed: Jump to V0 + Address (JP_V0)");
            break;
        case 0xC:
            rnd_vx_random_and_byte(appData->pChip8, instructionData);
            snprintf(debugBuf, sizeof(debugBuf), "Executed: Generate Random and AND (RND_VX)");
            break;
        case 0xD:
            drw_draw_sprite(appData, instructionData);
            snprintf(debugBuf, sizeof(debugBuf), "Executed: Draw Sprite (DRW)");
            break;
        case 0xE:
            if (instructionData->y == 0x9 && instructionData->n == 0xE) {
                skp_skip_if_key_pressed(appData->pChip8, instructionData);
                snprintf(debugBuf, sizeof(debugBuf), "Executed: Skip if Key Pressed (SKP)");
            } else if (instructionData->y == 0xA && instructionData->n == 0x1) {
                sknp_skip_if_key_not_pressed(appData->pChip8, instructionData);
                snprintf(debugBuf, sizeof(debugBuf), "Executed: Skip if Key Not Pressed (SKNP)");
            } else {
                snprintf(debugBuf, sizeof(debugBuf), "Error: Invalid Ex Command");
            }
            break;
        case 0xF:
            switch (instructionData->nn) {
                case 0x07:
                    ld_set_vx_to_delay_timer(appData->pChip8, instructionData);
                    snprintf(debugBuf, sizeof(debugBuf), "Executed: Set Vx to Delay Timer (LD_VX_DT)");
                    break;
                case 0x0A:
                    ld_wait_for_key_press(appData->pChip8, instructionData);
                    snprintf(debugBuf, sizeof(debugBuf), "Executed: Wait for Key Press (LD_KEY)");
                    break;
                case 0x15:
                    ld_set_delay_timer(appData->pChip8, instructionData);
                    snprintf(debugBuf, sizeof(debugBuf), "Executed: Set Delay Timer (LD_DT)");
                    break;
                case 0x18:
                    ld_set_sound_timer(appData->pChip8, instructionData);
                    snprintf(debugBuf, sizeof(debugBuf), "Executed: Set Sound Timer (LD_ST)");
                    break;
                case 0x1E:
                    add_add_i_and_vx(appData->pChip8, instructionData);
                    snprintf(debugBuf, sizeof(debugBuf), "Executed: Add Vx to I (ADD_I_VX)");
                    break;
                case 0x29:
                    ld_set_i_to_sprite_addr(appData->pChip8, instructionData);
                    snprintf(debugBuf, sizeof(debugBuf), "Executed: Set I to Sprite Address (LD_I_SPRITE)");
                    break;
                case 0x33:
                    ld_store_bcd(appData->pChip8, instructionData);
                    snprintf(debugBuf, sizeof(debugBuf), "Executed: Store BCD Representation (LD_BCD)");
                    break;
                case 0x55:
                    ld_store_v0_to_vx(appData->pChip8, instructionData);
                    snprintf(debugBuf, sizeof(debugBuf), "Executed: Store Registers V0 to Vx (LD_STORE_VX)");
                    break;
                case 0x65:
                    ld_read_v0_to_vx(appData->pChip8, instructionData);
                    snprintf(debugBuf, sizeof(debugBuf), "Executed: Read Registers V0 to Vx (LD_READ_VX)");
                    break;
                default:
                    snprintf(debugBuf, sizeof(debugBuf), "Error: Invalid Fx Command");
                    break;
            }
            break;
        default:
            snprintf(debugBuf, sizeof(debugBuf), "Error: Invalid Command");
            break;
    }

    //SDL_Log("%s", debugBuf);
    free(instructionData);
}

void fetchDecodeCycle(AppData_t *appData) {
    decode(appData, fetch(appData->pChip8));
}
