#pragma
#include "SDL_Game.h"

bool CGame::Init(string title, int X, int Y, int Width, int Height, int Flag)
{
	bool success = true;
	m_Window = SDL_CreateWindow(title.c_str(), X, Y, Width, Height, Flag);
	if (m_Window == NULL)
	{
		success = false;
	}
	else
	{
		m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
		if (m_Renderer == NULL)
		{
			success = false;
		}
		else
		{
			SDL_SetRenderDrawColor(m_Renderer, 0xff, 0xff, 0xff, 0xff);
			Particle.SetWindow(m_Window);
			Particle.LoadMedia();
		}
	}
	return success;
}

bool CGame::LoadMedia(string path)
{
	return true;
}

void CGame::HandleEventLoop()
{
	SDL_Event event;
	bool quit = false;
	int count = 0;
	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			Particle.HandleEvent(event);
			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					quit = true;
					break;
				}
				break;




			}
		}
		SDL_SetRenderDrawColor(m_Renderer, 0x00, 0xff, 0xff, 0xff);
		SDL_RenderClear(m_Renderer);
		Particle.Move();
		Particle.Render();



		SDL_RenderPresent(m_Renderer);
	}
}

CGame::CGame()
{
	m_Window = NULL;
	m_Renderer = NULL;
}

CGame::~CGame()
{
	if (m_Window != NULL)
	{
		SDL_DestroyWindow(m_Window);
		m_Window = NULL;
	}
	if (m_Renderer != NULL)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = NULL;
	}
}

void CGame::Free()
{
	if (m_Window != NULL)
	{
		SDL_DestroyWindow(m_Window);
		m_Window = NULL;
	}
	if (m_Renderer != NULL)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = NULL;
	}
}