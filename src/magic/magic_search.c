#include "magic_search.h"
#include "magic_random.h"
#include "bishop_attacks.h" 
#include "rook_attacks.h"
#include "slider_helpers.h"


U64 find_magic(int square , int relevant_bits , int is_bishop){
    U64 occupancies[4096] , attacks[4096] , used_attacks[4096];
    U64 attack_mask = is_bishop ? bishop_attack_mask(square) : rook_attack_mask(square);
    int occ_indices = 1 << relevant_bits;
    for (int index = 0 ; index < occ_indices ; index++){
        occupancies[index] = set_occupancy(index , relevant_bits , attack_mask);
        attacks[index] = is_bishop ? bishop_attack_vector(square , occupancies[index]) : rook_attack_vector(square , occupancies[index]);
    }
    // TODO: finish after understanding.
    return 0ULL;
}