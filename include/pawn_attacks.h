#ifndef PAWN_ATTACKS_H_INCLUDED
#define PAWN_ATTACKS_H_INCLUDED

#include "board_essentials.h"

extern U64 pawn_attacks[2][64];

U64 pawn_attack_vector(int square, int side);
void init_pawn_attacks(void);

#endif
