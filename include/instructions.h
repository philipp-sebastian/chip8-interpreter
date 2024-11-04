#ifndef CHIP8_INTERPRETER_INSTRUCTIONS_H
#define CHIP8_INTERPRETER_INSTRUCTIONS_H

#include "common.h"

int sys_jump_to_addr(Chip8_t* pChip8, InstructionData_t* instructionData);
int cls_clear_display(Chip8_t* pChip8, InstructionData_t* instructionData);
int ret_return_subroutine(Chip8_t* pChip8, InstructionData_t* instructionData);
int jp_jump_to_addr(Chip8_t* pChip8, InstructionData_t* instructionData);
int call_subroutine(Chip8_t* pChip8, InstructionData_t* instructionData);
int se_skip_if_equal(Chip8_t* pChip8, InstructionData_t* instructionData);
int sne_skip_if_not_equal(Chip8_t* pChip8, InstructionData_t* instructionData);
int se_skip_if_vx_equals_vy(Chip8_t* pChip8, InstructionData_t* instructionData);
int ld_set_vx(Chip8_t* pChip8, InstructionData_t* instructionData);
int add_add_to_vx(Chip8_t* pChip8, InstructionData_t* instructionData);
int ld_set_vx_to_vy(Chip8_t* pChip8, InstructionData_t* instructionData);
int or_set_vx_or_vy(Chip8_t* pChip8, InstructionData_t* instructionData);
int and_set_vx_and_vy(Chip8_t* pChip8, InstructionData_t* instructionData);
int xor_set_vx_xor_vy(Chip8_t* pChip8, InstructionData_t* instructionData);
int add_add_vx_vy(Chip8_t* pChip8, InstructionData_t* instructionData);
int sub_vx_minus_vy(Chip8_t* pChip8, InstructionData_t* instructionData);
int shr_shift_right_vx(Chip8_t* pChip8, InstructionData_t* instructionData);
int subn_vy_minus_vx(Chip8_t* pChip8, InstructionData_t* instructionData);
int shl_shift_left_vx(Chip8_t* pChip8, InstructionData_t* instructionData);
int sne_skip_if_vx_not_equal_vy(Chip8_t* pChip8, InstructionData_t* instructionData);
int ld_set_i(Chip8_t* pChip8, InstructionData_t* instructionData);
int jp_v0_plus_addr(Chip8_t* pChip8, InstructionData_t* instructionData);
int rnd_vx_random_and_byte(Chip8_t* pChip8, InstructionData_t* instructionData);
int drw_draw_sprite(Chip8_t* pChip8, InstructionData_t* instructionData);
int skp_skip_if_key_pressed(Chip8_t* pChip8, InstructionData_t* instructionData);
int sknp_skip_if_key_not_pressed(Chip8_t* pChip8, InstructionData_t* instructionData);
int ld_set_vx_to_delay_timer(Chip8_t* pChip8, InstructionData_t* instructionData);
int ld_wait_for_key_press(Chip8_t* pChip8, InstructionData_t* instructionData);
int ld_set_delay_timer(Chip8_t* pChip8, InstructionData_t* instructionData);
int ld_set_sound_timer(Chip8_t* pChip8, InstructionData_t* instructionData);
int add_add_i_and_vx(Chip8_t* pChip8, InstructionData_t* instructionData);
int ld_set_i_to_sprite_addr(Chip8_t* pChip8, InstructionData_t* instructionData);
int ld_store_bcd(Chip8_t* pChip8, InstructionData_t* instructionData);
int ld_store_v0_to_vx(Chip8_t* pChip8, InstructionData_t* instructionData);
int ld_read_v0_to_vx(Chip8_t* pChip8, InstructionData_t* instructionData);

#endif //CHIP8_INTERPRETER_INSTRUCTIONS_H
