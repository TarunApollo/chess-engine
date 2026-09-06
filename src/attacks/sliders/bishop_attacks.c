#include "board_essentials.h"
#include "bishop_attacks.h"
#include "magic_search.h"
#include "slider_helpers.h"

U64 bishop_attacks_mask[64];
U64 bishop_attacks[64][512];

// pre calculated
U64 bishop_attack_mask(int square){
    U64 attacks = 0ULL;
    int r , f;
    int tr = square / 8;
    int tf = square % 8;
    for (r = tr + 1 , f = tf + 1 ; r <= 6 & f <= 6 ; r++ , f++) attacks |= (1ULL << ((r * 8) + f));
    for (r = tr - 1 , f = tf - 1 ; r >= 1 & f >= 1 ; r-- , f--) attacks |= (1ULL << ((r * 8) + f));
    for (r = tr - 1 , f = tf + 1 ; r >= 1 & f <= 6 ; r-- , f++) attacks |= (1ULL << ((r * 8) + f));
    for (r = tr + 1 , f = tf - 1 ; r <= 6 & f >= 1 ; r++ , f--) attacks |= (1ULL << ((r * 8) + f));
    return attacks; 

}

// on the fly
U64 bishop_attack_vector(int square , U64 blocker){
    U64 attacks = 0ULL;
    int r , f;
    int tr = square / 8;
    int tf = square % 8;
    for (r = tr + 1 , f = tf + 1 ; r <= 7 & f <= 7 ; r++ , f++){
        attacks |= (1ULL << ((r * 8) + f));
        if ((1ULL << ((r * 8) + f)) & blocker) break;
    }
    for (r = tr - 1 , f = tf - 1 ; r >= 0 & f >= 0 ; r-- , f--){
        attacks |= (1ULL << ((r * 8) + f));
        if ((1ULL << ((r * 8) + f)) & blocker) break;
    }
    for (r = tr - 1 , f = tf + 1 ; r >= 0 & f <= 7 ; r-- , f++){
        attacks |= (1ULL << ((r * 8) + f));
        if ((1ULL << ((r * 8) + f)) & blocker) break;
    }
    for (r = tr + 1 , f = tf - 1 ; r <= 7 & f >= 0 ; r++ , f--){
        attacks |= (1ULL << ((r * 8) + f));
        if ((1ULL << ((r * 8) + f)) & blocker) break;
    }
    return attacks; 
}


void init_bishop_attacks_mask(){
    for(int square = 0 ; square < 64 ; square ++){
        bishop_attacks_mask[square] = bishop_attack_mask(square);
    }
}

void init_bishop_attacks(){
    init_bishop_attacks_mask();
    for(int square = 0 ; square <= 63 ; square++){
        U64 mask = bishop_attacks_mask[square];
        int bits = bishop_relevant_occupancy_counts[square];
        int occ_indices = 1 << bits;
        for (int index = 0 ; index < occ_indices ; index++){
            U64 occupancy = set_occupancy(index , bits , mask);
            int magic_index = (int)((occupancy * bishop_magics[square]) >> (64 - bits));
            bishop_attacks[square][magic_index] = bishop_attack_vector(square , occupancy);
        }
    }
}
