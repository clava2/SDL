#include "SDL_Game.h"

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

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
	if (SDL_Init(SDL_INIT_TIMER) < 0)
	{
#ifdef _SDL_DEBUG
		cout << "Main.cpp   main   SDL��ʱ����ϵͳ��ʼ��ʧ�ܣ�SDL_Error:" << SDL_GetError() << endl;
#endif
		return -1;
	}
	CGame Game;
	Game.Init("Test");
	Game.LoadMedia();
	Game.HandleEventLoop();
	Game.Free();
	SDL_Quit();
	return 0;
}