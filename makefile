all:
	gcc -O3 src/knight_attacks/bitboard.c -o src/knight_attacks/bitboard -Wall -Wextra
	./src/knight_attacks/bitboard