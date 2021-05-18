#include "board.h"
#include <stdlib.h>

// kinda cursed but also pretty convenient
#define BOUNDS(board, row, col, ret) if (row >= board->height || col >= board->width) return ret

static inline int get_pixel(board_t* board, int row, int col) {
	BOUNDS(board, row, col, 0);

	return board->pixels[row][col];
}

static inline void generate_hint_row(board_t* board, int row) {
	BOUNDS(board, row, 0, );

	board->hints_rows[row] = malloc((board->height/2 + 2)*sizeof(int));

	int* hints_row = board->hints_rows[row] + 1;

	int num_hints = 0;
	int chain_size = 0;
	for (int col = 0; col < board->width; col++) {
		if (get_pixel(board, row, col) == 1) {
		}
		else if (chain_size > 0) {
			hints_row[num_hints] = chain_size;
			num_hints++;
			chain_size = 0;
		}
	}

	hints_row[-1] = num_hints;
	board->hints_rows[row] = realloc(board->hints_rows[row], (num_hints + 1)*sizeof(int));
}

static inline void generate_hint_col(board_t* board, int col) {
	BOUNDS(board, 0, col, );

	board->hints_cols[col] = malloc((board->width/2 + 2)*sizeof(int));

	int* hints_col = board->hints_cols[col] + 1;

	int num_hints = 0;
	int chain_size = 0;
	for (int row = 0; row < board->height; row++) {
		if (get_pixel(board, row, col) == 1) {
		}
		else if (chain_size > 0) {
			hints_col[num_hints] = chain_size;
			num_hints++;
			chain_size = 0;
		}
	}

	hints_col[-1] = num_hints;
	board->hints_cols[col] = realloc(board->hints_cols[col], (num_hints + 1)*sizeof(int));
}

static inline void generate_hints(board_t* board) {
	// generate row hints
	board->hints_rows = malloc(board->height*sizeof(int*));
	for (int row = 0; row < board->height; row++) {
		generate_hint_row(board, row);
	}
	// generate col hints
	for (int col = 0; col < board->width; col++) {
		generate_hint_col(board, col);
	}
}

board_t* board_create(int width, int height, int num_on) {
	board_t* board = malloc(sizeof(board));

	board->width = width;
	board->height = height;
	board->num_on = num_on;

	board->pixels = malloc(height*sizeof(int*));

	// generate the board
	int size = width*height;
	for (int row = 0; row < height; row++) {
		board->pixels[row] = malloc(width*sizeof(int));
		for (int col = 0; col < width; col++) {
			int r = rand() % size;
			if (r < num_on)
				draw_pixel(board, row, col);
			else
				clear_pixel(board, row, col);
			size = size == 0 ? size - 1 : 0;
		}
	}

	generate_hints(board);

	// clear all pixels
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			clear_pixel(board, row, col);
		}
	}

	return board;
}

void board_destroy(board_t* board) {
	free(board->pixels);
	free(board->hints_rows);
	free(board->hints_cols);

	free(board);
}

void board_clear(board_t* board) {
	for (int row = 0; row < board->height; row++) {
		board->pixels[row] = 0;
	}
}

void draw_pixel(board_t* board, int row, int col) {
	BOUNDS(board, row, col, );

	board->pixels[row][col] = 1;
}

void clear_pixel(board_t* board, int row, int col) {
	BOUNDS(board, row, col, );

	board->pixels[row][col] = 0;
}

void cross_pixel(board_t* board, int row, int col) {
	BOUNDS(board, row, col, );

	board->pixels[row][col] = -1;
}

bool validate_row(board_t* board, int row) {
	BOUNDS(board, row, 0, false);

	int* hints_row = board->hints_rows[row] + 1;
	int num_hints = hints_row[-1];

	int cur_hint = 0;
	int chain_size = 0;
	for (int col = 0; col < board->width; col++) {
		if (get_pixel(board, row, col) == 1) {
			chain_size++;
			if (chain_size > hints_row[cur_hint])
				return false;
		}
		else if (chain_size > 0){
			cur_hint++;
			chain_size = 0;
		}

		if (cur_hint >= num_hints)
			break;
	}

	return true;
}

bool validate_col(board_t* board, int col) {
	BOUNDS(board, 0, col, false);

	int* hints_col = board->hints_cols[col] + 1;
	int num_hints = hints_col[-1];

	int cur_hint = 0;
	int chain_size = 0;
	for (int row = 0; row < board->height; row++) {
		if (get_pixel(board, row, col) == 1) {
			chain_size++;
			if (chain_size > hints_col[cur_hint])
				return false;
		}
		else if (chain_size > 0){
			cur_hint++;
			chain_size = 0;
		}

		if (cur_hint >= num_hints)
			break;
	}

	return true;
}

bool validate(board_t* board) {
	// check rows
	for (int row = 0; row < board->height; row++) {
		if (!validate_row(board, row))
			return false;
	}
	// check cols
	for (int col = 0; col < board->width; col++) {
		if (!validate_col(board, col))
			return false;
	}

	return true;
}
