#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "SDL_Game.h"

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
	{
#ifdef _SDL_DEBUG
		cout << "main.cpp int min(int argc,char* argv[])" << endl;
		cout << "初始化SDL失败！" << endl;
		cout << "SDL_GetError() = " << SDL_GetError() << endl << endl << endl;
#endif
		return 1;
	}

	if (TTF_Init() < 0)
	{
#ifdef _SDL_DEBUG
		cout << "main.cpp	int main(int argc,char* argv[])" << endl;
		cout << "TTF初始化失败！" << endl;
		cout << "TTF_GetError() = " << TTF_GetError() << endl << endl << endl;
#endif
		return 2;
	}
	if (Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG) <= 0)
	{
#ifdef _SDL_DEBUG
		cout << "main.cpp	int main(int argc,char* argv[])" << endl;
		cout << "Mix初始化失败！" << endl;
		cout << "Mix_GetError() = " << Mix_GetError() << endl << endl << endl;
#endif
		return 3;
	}

	CGame game;
	game.InitWindow("SDL_Window",100,100,1000,1200,SDL_WINDOW_FULLSCREEN_DESKTOP);
	game.LoadMedia();
	game.MainLoop();
	return 0;
	SDL_Quit();
}