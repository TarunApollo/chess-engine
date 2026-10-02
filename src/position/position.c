#include"position.h"

const char ascii_pieces[13] = "PNBRQKpbnrqk";

const char *unicode_pieces[12] = {
    "♙", "♘", "♗", "♖", "♕", "♔",
    "♟", "♞", "♝", "♜", "♛", "♚"
};

const int char_pieces[] = {
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

static U64 set_pieces_on_rank(enum NumericPieceEncoding piece_code , U64 bitboard){
    switch(piece_code){
        case P:
            for(int square = 8 ; square < 16 ; square++){
                set_bit(bitboard,square);
            };
            break;
        case N:
            set_bit(bitboard , b1);
            set_bit(bitboard, g1);
            break;
        case B:
            set_bit(bitboard , c1);
            set_bit(bitboard , f1);
            break;
        case R:
            set_bit(bitboard , a1);
            set_bit(bitboard , h1);;
            break;
        case Q:
            set_bit(bitboard , d1);
            break;
        case K:
            set_bit(bitboard , e1);
            break;
        case p:
            for(int square = 48 ; square < 56 ; square++){
                set_bit(bitboard,square);
            };
            break;
        case n:
            set_bit(bitboard , b8);
            set_bit(bitboard, g8);
            break;
        case b:
            set_bit(bitboard , c8);
            set_bit(bitboard, f8);
            break;
        case r:
            set_bit(bitboard , a8);
            set_bit(bitboard, h8);
            break;
        case q:
            set_bit(bitboard ,d8);
            break;
        case k:
            set_bit(bitboard, e8);
            break;
    }
    return bitboard;
};

void init_position(Position * pos){
    *pos = (Position){0};
    for (int piece_code = 0 ; piece_code < 12 ; piece_code++){
        pos->bitboards[piece_code] = set_pieces_on_rank(piece_code , pos->bitboards[piece_code]);
    }
    U64 white_occs = 0ULL;
    for(int white_piece_occupancy = 0 ; white_piece_occupancy < 6 ; white_piece_occupancy++){
        white_occs |= pos->bitboards[white_piece_occupancy];
    }
    pos->occupancies[white] = white_occs;
    U64 black_occs = 0ULL;
    for(int black_piece_occupancy = 6 ; black_piece_occupancy < 12 ; black_piece_occupancy++){
        black_occs |= pos->bitboards[black_piece_occupancy];
    }
    pos->occupancies[black] = black_occs;
    pos->occupancies[both] = white_occs | black_occs;
    pos->enpassant_square = no_sq;
    pos->side_to_move = white;
    pos->castling_rights = wk | wq | bk | bq;
    return;
}