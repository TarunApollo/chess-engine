#include "bishop_attacks.h"
#include "king_attacks.h"
#include "knight_attacks.h"
#include "pawn_attacks.h"
#include "rook_attacks.h"


int main(void){
    init_rook_attacks();
    init_bishop_attacks();
    init_king_attacks();
    init_knight_attacks();
    init_pawn_attacks();
    return 0;
}
