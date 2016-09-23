#include "SDL_Game.h"

using SDL::CGame;

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_AUDIO)<0)
	{
		cout << "初始化声音子系统失败！SDL_Error:" << SDL_GetError() << endl;
		return 0;
	}
	if (SDL_Init(SDL_INIT_TIMER)<0)
	{
		return 0;
	}
	CGame game("SDL_Window1",100,100,244,180,SDL_WINDOW_SHOWN);
	game.LoadMedia();
	game.MainLoop();
	SDL_Quit();
	return 0;
}
