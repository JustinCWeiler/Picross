#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "board_hints_15_10_12345.c"

int test_row_hints(board_t* board) {
	for (int row = 0; row < ROWS; row++) {
		if (board->hints_rows[row][0] != num_hints_rows[row])
			return row;
		for (int i = 0; i < num_hints_rows[row]; i++) {
			if (board->hints_rows[row][1 + i] != hints_rows[row][i])
				return row;
		}
	}

	return 0;
}

int test_col_hints(board_t* board) {
	for (int col = 0; col < COLS; col++) {
		if (board->hints_cols[col][0] != num_hints_cols[col])
			return col;
		for (int i = 0; i < num_hints_cols[col]; i++) {
			if (board->hints_cols[col][1 + i] != hints_cols[col][i])
				return col;
		}
	}

	return 0;
}

int main(void) {
	srand(12345);

	board_t* board = board_create(ROWS, COLS, 50);

	int ret;
	if ((ret = test_row_hints(board))) {
		printf("Row %d\n", ret);
	}
	if ((ret = test_col_hints(board))) {
		printf("Col %d\n", ret);
	}

	if (!validate(board))
		printf("Generated board is invalid\n");

	board_print_basic(board);

	board_destroy(board);

	return 0;
}
