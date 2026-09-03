all:
	gcc -O3 src/sliders_attacks/rook_attacks/bitboard.c src/sliders_attacks/slider_helpers.c -o src/sliders_attacks/rook_attacks/bitboard -Wall -Wextra
	./src/sliders_attacks/rook_attacks/bitboard
