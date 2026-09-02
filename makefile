all:
	gcc -O3 src/bishop_attacks/bitboard.c -o src/bishop_attacks/bitboard -Wall -Wextra
	gcc -O3 src/rook_attacks/bitboard.c -o src/rook_attacks/bitboard -Wall -Wextra
	./src/bishop_attacks/bitboard
	./src/rook_attacks/bitboard
