all:
	gcc -O3 src/bitboard.c -o src/bitboard -Wall -Wextra
	./src/bitboard