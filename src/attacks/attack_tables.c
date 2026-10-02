#include "attack_tables.h"
#include "bishop_attacks.h"
#include "king_attacks.h"
#include "knight_attacks.h"
#include "pawn_attacks.h"
#include "rook_attacks.h"
#include "slider_helpers.h"
#include "magic_search.h"

static U64 rook_attacks[64][4096];
static U64 bishop_attacks[64][512];
static U64 king_attacks[64];
static U64 knight_attacks[64];
static U64 pawn_attacks[2][64];

const int bishop_relevant_occupancy_counts[64] = {
    6, 5, 5, 5, 5, 5, 5, 6, 
    5, 5, 5, 5, 5, 5, 5, 5, 
    5, 5, 7, 7, 7, 7, 5, 5, 
    5, 5, 7, 9, 9, 7, 5, 5, 
    5, 5, 7, 9, 9, 7, 5, 5, 
    5, 5, 7, 7, 7, 7, 5, 5, 
    5, 5, 5, 5, 5, 5, 5, 5, 
    6, 5, 5, 5, 5, 5, 5, 6
};

const int rook_relevant_occupancy_counts[64] = {
    12, 11, 11, 11, 11, 11, 11, 12,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    12, 11, 11, 11, 11, 11, 11, 12
};

static void init_rook_attack_table(void){
    init_rook_attacks_mask();
    for (int square = 0; square < 64; square++){
        U64 mask = rook_attacks_mask[square];
        int bits = rook_relevant_occupancy_counts[square];
        int occupancy_count = 1 << bits;

        for (int index = 0; index < occupancy_count; index++){
            U64 occupancy = set_occupancy(index, bits, mask);
            int magic_index = (int)((occupancy * rook_magics[square]) >> (64 - bits));
            rook_attacks[square][magic_index] = rook_attack_vector(square, occupancy);
        }
    }
}

static void init_bishop_attack_table(void){
    init_bishop_attacks_mask();
    for (int square = 0; square < 64; square++){
        U64 mask = bishop_attacks_mask[square];
        int bits = bishop_relevant_occupancy_counts[square];
        int occupancy_count = 1 << bits;

        for (int index = 0; index < occupancy_count; index++){
            U64 occupancy = set_occupancy(index, bits, mask);
            int magic_index = (int)((occupancy * bishop_magics[square]) >> (64 - bits));
            bishop_attacks[square][magic_index] = bishop_attack_vector(square, occupancy);
        }
    }
}

static void init_king_attack_table(void){
    for (int square = 0; square < 64; square++){
        king_attacks[square] = king_attack_vector(square);
    }
}

static void init_knight_attack_table(void){
    for (int square = 0; square < 64; square++){
        knight_attacks[square] = knight_attack_vector(square);
    }
}

static void init_pawn_attack_table(void){
    for (int square = 0; square < 64; square++){
        pawn_attacks[white][square] = pawn_attack_vector(square, white);
        pawn_attacks[black][square] = pawn_attack_vector(square, black);
    }
}

void init_attack_tables(void){
    init_rook_attack_table();
    init_bishop_attack_table();
    init_king_attack_table();
    init_knight_attack_table();
    init_pawn_attack_table();
}

U64 rook_attack_lookup(int square, U64 occupancy){
    int bits = rook_relevant_occupancy_counts[square];
    occupancy &= rook_attacks_mask[square];
    int magic_index = (int)((occupancy * rook_magics[square]) >> (64 - bits));
    return rook_attacks[square][magic_index];
}

U64 bishop_attack_lookup(int square, U64 occupancy){
    int bits = bishop_relevant_occupancy_counts[square];
    occupancy &= bishop_attacks_mask[square];
    int magic_index = (int)((occupancy * bishop_magics[square]) >> (64 - bits));
    return bishop_attacks[square][magic_index];
}

U64 knight_attack_lookup(int square){
    return knight_attacks[square];
}

U64 king_attack_lookup(int square){
    return king_attacks[square];
}

U64 pawn_attack_lookup(int side , int square){
    return pawn_attacks[side][square];
}
