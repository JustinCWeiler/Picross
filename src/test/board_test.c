#include "board.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	srand(12345);

	board_t* b = board_create(10, 10, 50);

	/*
	if (!validate(b))
		printf("Generated board is invalid\n");
	*/

	board_destroy(b);

	return 0;
}
