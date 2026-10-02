all:
	gcc -std=c11 -O3 -Wall -Wextra -Iinclude \
		src/main.c src/board_essentials.c \
		src/attacks/sliders/slider_helpers.c \
		src/attacks/attack_tables.c \
		src/position/position.c \
		src/attacks/sliders/rook_attacks.c \
		src/attacks/sliders/bishop_attacks.c \
		src/attacks/leapers/king/king_attacks.c \
		src/attacks/leapers/knight/knight_attacks.c \
		src/attacks/leapers/pawn/pawn_attacks.c \
		src/magic/magic_random.c \
		src/magic/magic_search.c \
		-o bin/chess_engine
	./bin/chess_engine
