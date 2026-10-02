#include "board_essentials.h"

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


// one bitboard representation for each piece type (white pawn,black knight,etc
U64 bitboards[12];

//occupancy bitboard. 1 to track the white side, another to track 
//black side, and another to track all 2.
U64 occupancies[3];


//what side to move
int side = -1;

//enpassant square to be tracked
int enpassant_sq = no_sq;

//castling rights
int castle;


// TYPE OF CASTLING ALLOWED
/*
wk white king king side
wq white king queen side
*/
enum { wk = 1, wq = 2 , bk = 4 , bq = 8 };

//encode pieces as characters
enum { P , N , B  , R , Q ,K  , p , n , b , r , q , k};

// sides to move
enum {WHITE , BLACK , BOTH};


//bishop and rook 
enum {rook  , bishop};

//ASCII pieces
char ascii_pieces[12] = "PNBRQKpnbrqk";

//unicode pieces
char *unicode_pieces[12] = {
    "♙", "♘", "♗", "♖", "♕", "♔", 
    "♟︎", "♞", "♝", "♜", "♛", "♚"
};

// character to piece constants
int char_pieces[] = {
    ['P'] = P,
    ['N'] = N,
    ['B'] = B,
    ['R'] = R,
    ['Q'] = Q,
    ['K'] = K,
    ['p'] = p,
    ['n'] = n,
    ['b'] = b,
    ['r'] = r,
    ['q'] = q,
    ['k'] = k
};
