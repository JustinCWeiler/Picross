#include <SDL2/SDL.h>
#include <stdbool.h>

int main(void) {
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* win = SDL_CreateWindow("Picross", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);

	bool quit = false;
	SDL_Event e;
	while (!quit) {
		SDL_WaitEvent(&e);

		switch (e.type) {
			case SDL_QUIT:
				quit = true;
				break;
		}
	}
}
