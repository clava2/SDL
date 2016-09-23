#ifndef SDL_GAME_H
#define SDL_GAME_H

#include <SDL2/SDL.h>
#include <string>

#include "SDL_Map.h"
#include "SDL_Object.h"
#include "SDL_CommonInclude.h"

using namespace std;

class CGame
{
public:

	bool Init(string title = "", int X = 200, int Y = 200, int Width = SCREEN_WIDTH, int Height = SCREEN_HEIGHT, int Flag = SDL_WINDOW_SHOWN);
	bool LoadMedia();
	void HandleEventLoop();
	void Free();
	CGame();
	~CGame();

private:
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;

	CObject m_Player;
	CMap m_MainMap;

	bool m_ReDraw;


};

#endif