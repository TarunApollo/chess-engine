#include "bishop_attacks.h"
#include "king_attacks.h"
#include "knight_attacks.h"
#include "pawn_attacks.h"
#include "rook_attacks.h"
#include "slider_helpers.h"
#include "magic_random.h"
#include "magic_search.h"


int main(void){
    init_rook_attacks_mask();
    init_bishop_attacks_mask();
    init_king_attacks();
    init_knight_attacks();
    init_pawn_attacks();
    init_magic_numbers();
    return 0;
}
