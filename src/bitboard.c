/* 
pawn bitboard for the engine
for now focusing on accurate reps
and then we will see what happens
*/
#include <stdio.h>
#include <stdint.h>
///define data type for bitboard

typedef uint64_t U64;

const U64 not_a_column = 18374403900871474942ULL;
const U64 not_h_column = 9187201950435737471ULL;
// const U64 not_h_column = 
enum Squares{
    a1, b1, c1, d1, e1, f1, g1, h1,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a8, b8, c8, d8, e8, f8, g8, h8
};

enum Colour{
    white,
    black
};
/*
"a8"  ,  "b8"  ,  "c8"  ,  "d8"  ,  "e8"  ,  "f8"  ,  "g8"  ,  "h8"  ,

"a7"  ,  "b7"  ,  "c7"  ,  "d7"  ,  "e7"  ,  "f7"  ,  "g7"  ,  "h7"  ,

"a6"  ,  "b6"  ,  "c6"  ,  "d6"  ,  "e6"  ,  "f6"  ,  "g6"  ,  "h6"  ,

"a5"  ,  "b5"  ,  "c5"  ,  "d5"  ,  "e5"  ,  "f5"  ,  "g5"  ,  "h5"  ,

"a4"  ,  "b4"  ,  "c4"  ,  "d4"  ,  "e4"  ,  "f4"  ,  "g4"  ,  "h4"  ,

"a3"  ,  "b3"  ,  "c3"  ,  "d3"  ,  "e3"  ,  "f3"  ,  "g3"  ,  "h3"  ,

"a2"  ,  "b2"  ,  "c2"  ,  "d2"  ,  "e2"  ,  "f2"  ,  "g2"  ,  "h2"  ,

"a1"  ,  "b1"  ,  "c1"  ,  "d1"  ,  "e1"  ,  "f1"  ,  "g1"  ,  "h1"  
*/


// get/set/pop macros 
#define get_bit(bitboard , square) (bitboard & (1ULL << square))
#define set_bit(bitboard , square) (bitboard |= (1ULL << square))
#define pop_bit(bitboard , square) (get_bit(bitboard , square) ? (bitboard ^= (1ULL << square)) : 0)

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


//
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

//main driver.

int main(){
    printf("Bitboard Chess\n");
    // initialise pawn attack table
    for (int colour = 0 ; colour < 2 ; colour++){
        for (int square = 0 ; square < 64 ; square++){
            pawn_attacks[colour][square] = pawn_attack_vector(square, colour);
        }
    }
    print_bitboard(pawn_attacks[white][e5]);
    return 0;
}
