#ifndef MAGIC_SEARCH_H_INCLUDED
#define MAGIC_SEARCH_H_INCLUDED
#include "board_essentials.h"

extern const U64 rook_magics[64];
extern const U64 bishop_magics[64];

U64 find_magic(int square , int mask , int is_bishop);

void init_magic_numbers();
#endif

