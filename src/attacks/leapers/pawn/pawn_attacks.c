#include "board_essentials.h"
#include "pawn_attacks.h"
U64 pawn_attack_vector(int square , int side){
    U64 bitboard = 0ULL;
    U64 attacks = 0ULL;

    set_bit(bitboard , square);
    if (side == white){
        if(bitboard & not_a_column) attacks |= (bitboard << 7);
        if(bitboard & not_h_column) attacks |= (bitboard << 9);
    } else {
        if(bitboard & not_a_column) attacks |= (bitboard >> 9);
        if(bitboard & not_h_column) attacks |= (bitboard >> 7);
    }
    return attacks;
}
