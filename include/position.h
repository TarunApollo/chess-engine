#ifndef POSITION_H_INCLUDED
#define POSITION_H_INCLUDED

#include"board_essentials.h"

// TYPE OF CASTLING ALLOWED
/*
wk white king king side
wq white king queen side
*/
enum CastlingRights{ no_castling = 0, wk = 1, wq = 2 , bk = 4 , bq = 8 };

//encode pieces as characters
enum NumericPieceEncoding{ P , N , B  , R , Q ,K  , p , n , b , r , q , k};

extern const char ascii_pieces[13];

extern const char *unicode_pieces[12];

extern const int char_pieces[];

//TODO: 50 move draw rule to be added, as a boolean atleast. maybe gonna track it.
typedef struct{
// one bitboard representation for each piece type (white pawn,black knight,etc)
    U64 bitboards[12];
//occupancy bitboard. 1 to track the white side, another to track black side, and another to track all 2 together.
    U64 occupancies[3];
    enum Squares enpassant_square;
    enum Colour side_to_move;
    enum CastlingRights castling_rights;
}Position;

void init_position(Position * pos);
#endif