#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "board.h"

void set_seed(void) {
	srand(clock());
}

int main(void) {
	set_seed();

	int num_rows = rand() % 10 + 1;
	int num_cols = rand() % 10 + 1;
	printf("Rows: %d\nCols: %d\n", num_rows, num_cols);
	board_t* board = board_create(num_rows, num_cols, rand() % num_rows*num_cols + 1);

	// manually verify that it's correct
	board_print(board);

	return 0;
}
