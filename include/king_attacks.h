#ifndef KING_ATTACKS_H_INCLUDED
#define KING_ATTACKS_H_INCLUDED

#include "board_essentials.h"

extern U64 king_attacks[64];

U64 king_attack_vector(int square);
void init_king_attacks(void);

#endif
