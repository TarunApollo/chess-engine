#include "board_essentials.h"


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

void print_bitboard(U64 bitboard){
    for (int row = 7; row >= 0; row--){
        printf("%d   ", row + 1);
        for (int column = 0; column < 8; column++){
            int square = row * 8 + column;
            printf("%d ", get_bit(bitboard, square) ? 1 : 0);
        }
        printf("\n");
    }
    printf("\n");
    printf("    a b c d e f g h\n");
    printf("    Bitboard: %lluULL\n", bitboard);
}

int count_bits(U64 bitboard){
    return __builtin_popcountll(bitboard);
}

int lsb_index(U64 bitboard){
    return __builtin_ctzll(bitboard);
}
