#ifndef SDL_GAME_H
#define SDL_GAME_H

#include <SDL2/SDL.h>
#include <string>
#include "SDL_Particle.h"

using namespace std;

class CGame
{
public:
	bool Init(string title = "", int X = 0, int Y = 0, int Width = 100,
		int Height = 100, int Flag = SDL_WINDOW_SHOWN);
	bool LoadMedia(string path);
	void HandleEventLoop();
	void Free();
	CGame();
	~CGame();
public:
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	CParticle Particle;
};
#endif