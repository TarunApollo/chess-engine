#include "../board_essentials.h"

U64 knight_attacks[64];

U64 knight_attack_vector(int square){
    U64 bitboard = 0ULL;
    U64 attacks = 0ULL;
    set_bit(bitboard , square);
    if (bitboard & not_a_column) attacks |= (bitboard >> 17);
    if (bitboard & not_a_column) attacks |= (bitboard << 15);
    if (bitboard & not_ab_column) attacks |= (bitboard >> 10);
    if (bitboard & not_ab_column) attacks |= (bitboard << 6);
    if (bitboard & not_h_column) attacks |= (bitboard << 17);
    if (bitboard & not_h_column) attacks |= (bitboard >> 15);
    if (bitboard & not_gh_column) attacks |= (bitboard << 10);
    if (bitboard & not_gh_column) attacks |= (bitboard >> 6);
    return attacks;
}

void init_knight_attacks(){
    for (int square = 0 ; square < 64 ; square++){
        knight_attacks[square] = knight_attack_vector(square);
    }
}

int main(void){
    init_knight_attacks();
    return 0;
}