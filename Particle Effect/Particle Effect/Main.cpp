#include "SDL_Game.h"

int  main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
#ifdef _SDL_DEBUG
		cout << "Main.cpp   main   SDL������ϵͳ��ʼ��ʧ�ܣ�SDL_Error:" << SDL_GetError() << endl;
#endif
		return -1;
	}
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
#ifdef _SDL_DEBUG
		cout << "Main.cpp   main   SDL��Ƶ��ϵͳ��ʼ��ʧ�ܣ�SDL_Error:" << SDL_GetError() << endl;
#endif
		return -1;
	}
	CGame Game;
	Game.Init("Test", 10, 10, 500, 500,SDL_WINDOW_FULLSCREEN_DESKTOP);
	Game.HandleEventLoop();
	Game.Free();
	SDL_Quit();
}