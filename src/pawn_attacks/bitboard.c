#include "../board_essentials.h"

U64 pawn_attacks[2][64];

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

void init_pawn_attacks(){
    for (int square = 0 ; square < 64 ; square++){
        pawn_attacks[white][square] = pawn_attack_vector(square, white);
        pawn_attacks[black][square] = pawn_attack_vector(square, black);
    }
}

//main driver.
int main(void){
    printf("Bitboard Chess\n");
    init_pawn_attacks();
    return 0;
}
