#ifndef BOARD_H
#define BOARD_H

#include <stddef.h>
#include <stdbool.h>

typedef size_t row_t;

typedef struct {
	int width, height;
	int num_on;
	int** pixels;

	int** hints_rows;
	int** hints_cols;
} board_t;

// generates random board
board_t* board_create(int width, int height, int num_on);
void board_destroy(board_t* board);
void board_clear(board_t* board);

void draw_pixel(board_t* board, int row, int col);
void clear_pixel(board_t* board, int row, int col);
void cross_pixel(board_t* board, int row, int col);

// return whether row, col, or whole board is valid given hints
bool validate_row(board_t* board, int row);
bool validate_col(board_t* board, int col);
bool validate(board_t* board);

#endif
