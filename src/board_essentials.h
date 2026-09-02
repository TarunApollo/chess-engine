#ifndef BOARD_ESSENTIALS_H_INCLUDED
#define BOARD_ESSENTIALS_H_INCLUDED

#include <stdio.h>
#include <stdint.h>

typedef uint64_t U64;


#define not_a_column 18374403900871474942ULL
#define not_ab_column 18229723555195321596ULL
#define not_h_column 9187201950435737471ULL
#define not_gh_column 4557430888798830399ULL


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

// get/set/pop macros 
#define get_bit(bitboard , square) (bitboard & (1ULL << square))
#define set_bit(bitboard , square) (bitboard |= (1ULL << square))
#define pop_bit(bitboard , square) (get_bit(bitboard , square) ? (bitboard ^= (1ULL << square)) : 0)


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


static inline void print_bitboard(U64 bitboard){
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
//TODO: optimise with 
static inline int count_bits(U64 bitboard){
    // int count = 0;
    // while (bitboard) {
    //     bitboard &= (bitboard - 1); subtracting 1 leads to bits flipping all the way until the set bit we are counting
                                    // &ing keeps all else the same except for the bits that got flipped which become 0.
    //     count++;
    // }
    // return count;
    return __builtin_popcountll(bitboard);
}

static inline int lsb_index(U64 bitboard){
    // if (!bitboard) return -1;
    // U64 lsb = bitboard & -bitboard;
    // return count_bits(bitboard);
    return __builtin_ctzll(bitboard);
}


#endif