/* 
pawn bitboard for the engine
for now focusing on accurate reps
and then we will see what happens
*/
#include <stdio.h>
#include <stdint.h>
#include "../board_essentials.h"


void print_bitboard(U64 bitboard){
    for (int row = 7 ; row >= 0 ; row--){
        printf("%d   " , row + 1 );
        for (int column = 0 ; column < 8 ; column++){
            int square = row * 8 + column; 
            printf("%d ", get_bit(bitboard , square) ? 1 : 0);
        }
        printf("\n");
    }
    printf("\n");
    printf("    a b c d e f g h\n");
    printf("    Bitboard: %lluULL\n" , bitboard);
}

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
