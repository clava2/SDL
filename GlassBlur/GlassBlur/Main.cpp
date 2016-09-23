#include <SDL2/SDL_image.h>
#include <iostream>

using std::cout;
using std::endl;

#pragma comment(lib,"SDL2.lib")
#pragma comment(lib,"SDL2main.lib")
#pragma comment(lib,"SDL2_image.lib")

const int BlurR = 3;

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Surface* Image = IMG_Load("image.jpg");
	SDL_Window* Window = SDL_CreateWindow("Blur", 100, 100, Image->w, Image->h, SDL_WINDOW_SHOWN);

	SDL_Surface* Target = SDL_CreateRGBSurface(SDL_SWSURFACE, Image->w, Image->h, Image->format->BitsPerPixel, Image->format->Rmask, Image->format->Gmask, Image->format->Bmask, Image->format->Amask);
	SDL_LockSurface(Image);

	int r = 0, g = 0, b = 0;
	
	int Amount = 0;

	for (int i = -BlurR; i != BlurR; i++)
	{
		for (int j = -BlurR; j != BlurR; j++)
		{
			Amount++;
		}
	}

	for (int i = 0; i != 3*Image->h; i ++)
	{
		for (int j = 0; j != 3*Image->w; j += 3)
		{
			for (int y = i - BlurR; y != i + BlurR; y++)
			{
				if ((y < 0) || (y > 3*Image->h))
				{
					continue;
				}
				for (int x = j - BlurR; x != j + BlurR; x++)
				{
					if ((x < 0) || (x > 3*Image->w))
					{
						continue;
					}
					r += ((unsigned char*)(Image->pixels))[y*Image->w + x];
					g += ((unsigned char*)(Image->pixels))[y*Image->w + x + 1];
					b += ((unsigned char*)(Image->pixels))[y*Image->w + x + 2];
				}
			}
			((char*)(Target->pixels))[i*Image->w + j] = r / Amount;//((char*)(Image->pixels))[i*Image->w + j    ];
			((char*)(Target->pixels))[i*Image->w + j + 1] = g / Amount;//((char*)(Image->pixels))[i*Image->w + j + 1];
			((char*)(Target->pixels))[i*Image->w + j + 2] = b / Amount;//((char*)(Image->pixels))[i*Image->w + j + 2];
			r = g = b = 0;
		}
	}

	SDL_UnlockSurface(Image);


	SDL_Surface* Screen = SDL_GetWindowSurface(Window);
	SDL_BlitSurface(Target, NULL, Screen, NULL);
	SDL_UpdateWindowSurface(Window);

	SDL_Event e;
	bool quit = false;
	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			}
		}
	}

	SDL_FreeSurface(Image);
	SDL_DestroyWindow(Window);
	SDL_Quit();
	return 0;
}