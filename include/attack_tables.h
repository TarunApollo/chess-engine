#ifndef ATTACK_TABLES_H_INCLUDED
#define ATTACK_TABLES_H_INCLUDED

#include "board_essentials.h"

void init_attack_tables(void);

extern const int bishop_relevant_occupancy_counts[64];
extern const int rook_relevant_occupancy_counts[64];

U64 rook_attack_lookup(int square, U64 occupancy);
U64 bishop_attack_lookup(int square, U64 occupancy);
U64 knight_attack_lookup(int square);
U64 king_attack_lookup(int square);
U64 pawn_attack_lookup(int side, int square);

#endif
