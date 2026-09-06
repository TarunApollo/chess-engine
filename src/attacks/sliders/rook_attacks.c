#include "board_essentials.h"
#include "rook_attacks.h"
#include "slider_helpers.h"
#include "magic_search.h"


U64 rook_attacks_mask[64];
U64 rook_attacks[64][4096];

// pre calculated relevant occupancy bits, that the magic system must take into account
U64 rook_attack_mask(int square){
    U64 attacks = 0ULL;
    int r , f;
    int tr = square / 8;
    int tf = square % 8;
    for (r = tr + 1 ; r <= 6 ; r++) attacks |= (1ULL << ((r * 8) + tf));
    for (r = tr - 1 ; r >= 1 ; r-- ) attacks |= (1ULL << ((r * 8) + tf));
    for (f = tf + 1 ; f <= 6 ; f++) attacks |= (1ULL << ((tr * 8) + f));
    for (f = tf - 1 ; f >= 1 ; f-- ) attacks |= (1ULL << ((tr * 8) + f));
    return attacks; 

}

//on the fly
U64 rook_attack_vector(int square , U64 blocker){
    U64 attacks = 0ULL;
    int r , f;
    int tr = square / 8;
    int tf = square % 8;
    for (r = tr + 1 ; r <= 7 ; r++){ 
        attacks |= (1ULL << ((r * 8) + tf));
        if ((1ULL << ((r * 8) + tf)) & blocker) break;
    }
    for (r = tr - 1 ; r >= 0 ; r-- ){ 
        attacks |= (1ULL << ((r * 8) + tf));
        if ((1ULL << ((r * 8) + tf)) & blocker) break;
    }
    for (f = tf + 1 ; f <= 7 ; f++){ 
        attacks |= (1ULL << ((tr * 8) + f));
        if ((1ULL << ((tr * 8) + f)) & blocker) break;
    }
    for (f = tf - 1 ; f >= 0 ; f-- ){ 
        attacks |= (1ULL << ((tr * 8) + f));
        if ((1ULL << ((tr * 8) + f)) & blocker) break;
    }
    return attacks; 
}

void init_rook_attacks_mask(){
    for(int square = 0 ; square < 64 ; square ++){
        rook_attacks_mask[square] = rook_attack_mask(square);
    }
}

void init_rook_attacks(){
    init_rook_attacks_mask();
    for(int square = 0 ; square <= 63 ; square++){
        U64 mask = rook_attacks_mask[square];
        int bits = rook_relevant_occupancy_counts[square];
        int occ_indices = 1 << bits;
        for (int index = 0 ; index < occ_indices ; index++){
            U64 occupancy = set_occupancy(index , bits , mask);
            int magic_index = (int)((occupancy * rook_magics[square]) >> (64 - bits));
            rook_attacks[square][magic_index] = rook_attack_vector(square , occupancy);
        }
    }
}
