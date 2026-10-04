#ifndef BOARD_ESSENTIALS_H_INCLUDED
#define BOARD_ESSENTIALS_H_INCLUDED

#include <stdint.h>
#include <stdio.h>
#include <string.h>

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
    a8, b8, c8, d8, e8, f8, g8, h8 , no_sq
};


enum Colour{
    white,
    black,
    both
};



// get/set/pop macros 
#define get_bit(bitboard , square) ((bitboard) & (1ULL << square))
#define set_bit(bitboard , square) ((bitboard) |= (1ULL << square))
#define pop_bit(bitboard , square) (get_bit(bitboard , square) ? (bitboard ^= (1ULL << square)) : 0)


extern const char *square_to_coordinates[65];


extern void print_bitboard(U64 bitboard);
extern int count_bits(U64 bitboard);
extern int lsb_index(U64 bitboard);


#endif
