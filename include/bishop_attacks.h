#ifndef BISHOP_ATTACKS_H_INCLUDED
#define BISHOP_ATTACKS_H_INCLUDED

#include "board_essentials.h"

extern U64 bishop_attacks_mask[64];

U64 bishop_attack_mask(int square);
U64 bishop_attack_vector(int square, U64 blockers);
void init_bishop_attacks_mask(void);
void init_bishop_attacks(void);

#endif
