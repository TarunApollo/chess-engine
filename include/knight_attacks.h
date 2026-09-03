#ifndef KNIGHT_ATTACKS_H_INCLUDED
#define KNIGHT_ATTACKS_H_INCLUDED

#include "board_essentials.h"

extern U64 knight_attacks[64];

U64 knight_attack_vector(int square);
void init_knight_attacks(void);

#endif
