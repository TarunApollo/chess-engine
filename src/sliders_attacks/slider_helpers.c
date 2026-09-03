#include "slider_helpers.h"

U64 set_occupancy(int index, int bits_in_mask, U64 attack_mask){
    // occupancy map
    U64 occupancy = 0ULL;
    for (int count = 0 ; count < bits_in_mask ; count++){
        int square = lsb_index(attack_mask);
        pop_bit(attack_mask, square);
        if (index & ( 1 << count)) occupancy |= (1ULL << square);
    }
    return occupancy;
}