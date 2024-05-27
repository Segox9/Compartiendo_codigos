#pragma once
#include <stdint.h>

void show_bin8 (uint8_t val);
void show_bin32(uint32_t val);
uint32_t set_bit32(uint32_t data, uint8_t bit_pos, bool bit_value);
uint32_t toogle_bit32(uint32_t data, uint8_t bit_pos);
uint32_t carry_rotate32(uint32_t data, int8_t N);
uint32_t exxtract_segment(uint32_t data, uint8_t startBit, uint8_t endBit);