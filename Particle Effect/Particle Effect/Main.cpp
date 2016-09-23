#include "SDL_Game.h"

int  main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
#ifdef _SDL_DEBUG
		cout << "Main.cpp   main   SDL视屏子系统初始化失败！SDL_Error:" << SDL_GetError() << endl;
#endif
		return -1;
	}
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
#ifdef _SDL_DEBUG
		cout << "Main.cpp   main   SDL音频子系统初始化失败！SDL_Error:" << SDL_GetError() << endl;
#endif
		return -1;
	}
	CGame Game;
	Game.Init("Test", 10, 10, 500, 500,SDL_WINDOW_FULLSCREEN_DESKTOP);
	Game.HandleEventLoop();
	Game.Free();
	SDL_Quit();
}