#include"position.h"

const char ascii_pieces[12] = {'P','N','B','R','Q','K','p','n','b','r','q','k'};

//TODO: switch back colour codes after, this just looks nicer in the terminal. correct even.
const char *unicode_pieces[12] = {
    "♟", "♞", "♝", "♜", "♛", "♚",
    "♙", "♘", "♗", "♖", "♕", "♔"
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
    ['k'] = k,
    ['q'] = q,
};

const char * starting_position = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

// save a position from a fen string into the position object.
int parse_fen(const char * fen, Position * pos){
    Position temp_pos = {0};
    char buffer[strlen(fen) + 1];
    temp_pos.side_to_move = white;
    temp_pos.enpassant_square = no_sq;
    temp_pos.castling_rights = 0;
    strcpy(buffer,fen);
    char * token = strtok(buffer , " ");
    for (int row = 7; row >= 0; row--){
            for (int column = 0; column < 8; column++){
                int square = row * 8 + column;
                int piece_type = -1;
                for (int board_piece = P ; board_piece <= k ; board_piece++){
                    if (get_bit(pos->bitboards[board_piece],square)){
                        piece_type = board_piece;
                        break;
                    }
                }

            }
    }
}

void print_position(Position * pos){
    U64 bitboards[12];
    memcpy(bitboards , pos->bitboards , sizeof(bitboards));
    for (int row = 7; row >= 0; row--){
        printf("%d   ", row + 1);
        for (int column = 0; column < 8; column++){
            int square = row * 8 + column;
            int piece_type = -1;
            for (int board_piece = P ; board_piece <= k ; board_piece++){
                if (get_bit(bitboards[board_piece],square)){
                    piece_type = board_piece;
                    break;
                }
            }
            printf("%s " , (piece_type == -1) ? "." : unicode_pieces[piece_type]);
        }
        printf("\n");
    }
    printf("\n");
    printf("    a b c d e f g h\n");
    printf("\n");
    printf("    To play: %s\n" , (pos->side_to_move == white) ? "white" : "black");
    printf("\n");
    printf("    En passant: %s\n" , square_to_coordinates[pos->enpassant_square]);
    printf("\n");
    printf("    Who can castle?: %c%c%c%c\n",(pos->castling_rights & wk) ? 'K' : '-',
                                             (pos->castling_rights & wq) ? 'Q' : '-',
                                             (pos->castling_rights & bk) ? 'k' : '-',
                                             (pos->castling_rights & bq) ? 'q' : '-');
}

void init_position(Position * pos){
    parse_fen(starting_position ,pos);
    print_position(pos);
}
