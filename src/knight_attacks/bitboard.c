#include "../board_essentials.h"

U64 knight_attacks[64];

U64 knight_attack_vector(int square){
    U64 bitboard = 0ULL;
    U64 attacks = 0ULL;
    set_bit(bitboard , square);
    // possible refactor : use compile time insta-struct that captures shift and direction of shift
    // run a loop to iterate and return the attack vector.
    const struct {
        int offset;
        U64 bitmask;
        int direction;
    } knight_moves[] = {
        {17, not_h_column, 1},
        {15, not_a_column, 1},
        {10, not_gh_column, 1},
        {6, not_ab_column, 1},
        {17, not_a_column, -1},
        {15, not_h_column, -1},
        {10, not_ab_column, -1},
        {6, not_gh_column, -1},
    };
    for(int i = 0 ; i < 8 ; i++){
        if (bitboard & knight_moves[i].bitmask){
            if (knight_moves[i].direction > 0){
                attacks |= (bitboard << knight_moves[i].offset);
            } else {
                attacks |= (bitboard >> knight_moves[i].offset);
            }
        }
    }
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