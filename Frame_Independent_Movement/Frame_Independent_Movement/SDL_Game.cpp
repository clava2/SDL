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
		m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_TARGETTEXTURE);
		if (m_Renderer == NULL)
		{
			success = false;
		}
		else
		{
			SDL_SetRenderDrawColor(m_Renderer, 0xff, 0xff, 0xff, 0xff);
		}
	}
	m_Particle.SetWindow(m_Window);
	m_Particle.SetSpeed(2);
	return success;
}

bool CGame::LoadMedia()
{
	SDL_Point Barry[] = { {0,1},{0,2},{0,3},{1,1}, {1,2},{1,3},{2,1},{2,2},{2,3} };
	m_MainMap.Init(m_Window, "tiles.png", "map.txt");
	m_MainMap.SetBarry(Barry, 9);
	m_Particle.LoadMedia();
	return true;
}

void CGame::HandleEventLoop()
{
	SDL_Event event;
	bool quit = false;
	while (!quit)
	{
		m_Particle.Move(m_MainMap);
		m_Particle.SetCamera(m_MainMap.GetCamera());
		m_ReDraw = true;
		while (SDL_PollEvent(&event))
		{
			if (m_Particle.HandleEvent(event))
			{
				m_ReDraw = true;
			}
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
			case SDL_WINDOWEVENT:
			{
				switch (event.window.event)
				{
				case SDL_WINDOWEVENT_SIZE_CHANGED:
					SCREEN_WIDTH = event.window.data1;
					SCREEN_HEIGHT = event.window.data2;
					break;
				}
			}



			}
		}
		if (m_ReDraw)
		{
			SDL_SetRenderDrawColor(m_Renderer, 0x00, 0x00, 0x00, 0xff);
			SDL_RenderClear(m_Renderer);

			m_MainMap.Render();
			m_Particle.Render();

			SDL_RenderPresent(m_Renderer);
			m_ReDraw = false;
		}
	}
}

CGame::CGame()
{
	m_Window = NULL;
	m_Renderer = NULL;
	m_ReDraw = true;
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
