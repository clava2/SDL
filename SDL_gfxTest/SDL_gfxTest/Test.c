#include <SDL2/SDL_gfxPrimitives.h>
#include <SDL2/SDL.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	SDL_Event e;
	
	_Bool quit = 0;

	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);

	SDL_Window* Window = SDL_CreateWindow("SDL_gfxTest", 100, 100, 400, 400, SDL_WINDOW_SHOWN);
	SDL_Renderer* Renderer = SDL_CreateRenderer(Window,-1,SDL_RENDERER_ACCELERATED);

	int Time = SDL_GetTicks();

	srand((unsigned int)time(NULL));

	SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
	SDL_RenderClear(Renderer);

	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				quit = 1;
				break;
			}
		}

		if (SDL_GetTicks() - Time >= 100)
		{
			SDL_F(Renderer, rand() % 400, rand() % 400, rand() % 200, rand() % 255, rand() % 255, rand() % 255,rand()%255);
			Time = SDL_GetTicks();
		}

		SDL_RenderPresent(Renderer);
	}
	return 0;
}