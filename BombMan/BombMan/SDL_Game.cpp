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
	m_Player.SetWindow(m_Window);
	m_MainTimer.Start();
	return success;
}

bool CGame::LoadMedia()
{
	SDL_Point Barry[] = { {0,1},{0,2} };
	m_MainMap.Init(m_Window, "resources/tiles.png", "resources/map.txt");
	m_MainMap.SetBarry(Barry, 2);
	SDL_Point Soft[] = { {0,1} };
	SDL_Point Background = { 0,0 };
	m_MainMap.SetSoft(Soft, 1, Background);
	m_MainMap.SetCamera();
	m_Player.SetTile(6, 4);
	m_Player.LoadMedia("resources/player.png");
	m_Player.SetStateAmount(5);
	SDL_Point Order[10] = { {0,0}, {0,1},{0,2},{0,3} };
	m_Player.SetPlayOrder(0, Order, 4);
	Order[0] = { 1,0 }, Order[1] = { 1,1 }, Order[2] = { 1,2 }, Order[3] = { 1,3 };
	m_Player.SetPlayOrder(1, Order, 4);
	Order[0] = { 2,0 }, Order[1] = { 2,1 }, Order[2] = { 2,2 }, Order[3] = { 2,3 };
	m_Player.SetPlayOrder(2, Order, 4);
	Order[0] = { 3,0 }, Order[1] = { 3,1 }, Order[2] = { 3,2 }, Order[3] = { 3,3 };
	m_Player.SetPlayOrder(3, Order, 4);
	Order[0] = { 4,0 }, Order[1] = { 4,1 }, Order[2] = { 4,2 }, Order[3] = { 4,3 }, Order[4] = { 5,0 }, Order[5] = { 5,1 }, Order[6] = { 5,2 }, Order[7] = { 5,3 };
	m_Player.SetPlayOrder(4, Order, 8);
	m_Player.SetSpeed(20);
	return true;
}

void CGame::HandleEventLoop()
{
	while (!m_QuitGame)
	{
		BeginPage();
		while (!m_Quit)
		{
			m_Player.Move(m_MainMap);
			m_Player.SetCamera(m_MainMap.GetCamera());
			m_ReDraw = true;
			while (SDL_PollEvent(&m_Event))
			{
				if (m_Player.HandleEvent(m_Event))
				{
					m_ReDraw = true;
				}
				switch (m_Event.type)
				{
				case SDL_QUIT:
					m_Quit = true;
					m_QuitGame = true;
					break;
				case SDL_KEYDOWN:
					switch (m_Event.key.keysym.sym)
					{
					case SDLK_ESCAPE:
						m_Quit = true;
						m_QuitGame = true;
						break;
					}
					break;
				case SDL_WINDOWEVENT:
				{
					switch (m_Event.window.event)
					{
					case SDL_WINDOWEVENT_SIZE_CHANGED:
						SCREEN_WIDTH = m_Event.window.data1;
						SCREEN_HEIGHT = m_Event.window.data2;
						break;
					}
				}
				}
			}

			if (m_ReDraw)
			{
				Render();
			}
			if ((m_MainTimer.GetTicks() >= 2000) && (m_MainTimer.GetTicks() <= 3000))
			{
				m_Player.Die();
				m_MainMap.Destroy(SDL_Point{ 1,1 });
			}
			if (m_MainTimer.GetTicks() > 5000)
			{
				m_Player.Revive();
			}
			if (CheckDie())
			{
				DiePage();
				m_Quit = false;
			}
		}
		if (CheckEnd())
		{
			EndPage();
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

void CGame::Render()
{
	SDL_SetRenderDrawColor(m_Renderer, 0xff, 0x00, 0x00, 0xff);
	SDL_RenderClear(m_Renderer);

	m_MainMap.Render();
	m_Player.Render();

	SDL_RenderPresent(m_Renderer);
	m_ReDraw = false;
}

bool CGame::CheckDie()
{
	return false;
}

/**判断游戏是否结束
*返回值								:如果游戏应该结束，返回true,否则返回false
*/
bool CGame::CheckEnd()
{
	return false;
}

void CGame::DiePage()
{
}

void CGame::EndPage()
{
}

void CGame::BeginPage()
{
}

//相关页面块

/**角色死亡时的页面
*/
void DiePage()
{
}

