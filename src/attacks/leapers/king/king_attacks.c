#include "board_essentials.h"
#include "king_attacks.h"
U64 king_attacks[64];

U64 king_attack_vector(int square){
    U64 bitboard = 0ULL;
    U64 attacks = 0ULL;
    set_bit(bitboard , square);
    attacks |= bitboard << 8;
    attacks |= bitboard >> 8;
    const struct{
        int offset;
        U64 bitmask;
        int direction;
    } king_moves[] = {
        { 7 , not_a_column , -1},
        { 9 , not_a_column , 1},
        { 1 , not_a_column , 1},
        { 7 , not_h_column , 1},
        { 9 , not_h_column , -1},
        { 1 , not_h_column , -1}
    };
    for (int moves = 0 ; moves < 6 ; moves++){
        if (bitboard & king_moves[moves].bitmask){
            if (king_moves[moves].direction < 0){
                attacks |= (bitboard << king_moves[moves].offset);
            } else {
                attacks |= (bitboard >> king_moves[moves].offset);
            }
        }
    }
    return attacks;
}

void init_king_attacks(){
    for (int square = 0 ; square < 64 ; square ++){
        king_attacks[square] = king_attack_vector(square);
    }
}
