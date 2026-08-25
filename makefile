all:
	gcc -O3 src/king_attacks/bitboard.c -o src/king_attacks/bitboard -Wall -Wextra
	./src/king_attacks/bitboard