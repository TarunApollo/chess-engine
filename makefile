all:
	gcc -O3 src/rook_attacks/bitboard.c -o src/rook_attacks/bitboard -Wall -Wextra
	./src/rook_attacks/bitboard