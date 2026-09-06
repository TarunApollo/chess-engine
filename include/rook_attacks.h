#ifndef ROOK_ATTACKS_H_INCLUDED
#define ROOK_ATTACKS_H_INCLUDED
#include "board_essentials.h"

extern U64 rook_attacks_mask[64];

U64 rook_attack_mask(int square);
U64 rook_attack_vector(int square, U64 blockers);
void init_rook_attacks_mask(void);
void init_rook_attacks(void);

#endif
