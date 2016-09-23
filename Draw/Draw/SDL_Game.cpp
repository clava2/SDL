#include "SDL_Game.h"

SDL::CGame::CGame(string Title, int X, int Y, int Width, int Height, SDL_WindowFlags Flag)
{
	m_Quit = false;
	m_QuitGame = false;
	m_Redraw = true;
	m_Dragging = false;


	m_Window = NULL;
	m_Renderer = NULL;
	
	InitWindow(Title,X, Y, Width, Height, Flag);													//初始化窗口

	//成员变量设置串口块
}

bool SDL::CGame::InitWindow(string title, int X, int Y, int Width, int Height, SDL_WindowFlags Flag)
{
	if ((SDL_Init(SDL_INIT_VIDEO)) < 0)
	{
#ifdef _SDL_DEBUG
		cout << "初始化SDL_INIT_VIDEO子系统失败！SDL_Error:" << SDL_GetError() << endl;
#endif
		return false;
	}

	m_Window = SDL_CreateWindow(title.c_str(), X, Y, Width, Height, Flag);

	if (m_Window == NULL)
	{
#ifdef _SDL_DEBUG
		cout << "SDL创建窗口失败！SDL_Error:" << SDL_GetError() << endl;
#endif
		return false;
	}

	SDL_GetWindowSize(m_Window, &m_Width, &m_Height);

	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);

	if (m_Renderer == NULL)
	{
#ifdef _SDL_DEBUG
		cout << "创建渲染器失败！SDL_Error:" << SDL_GetError() << endl;
#endif
		return false;
	}

	//成员变量设置窗口

	return true;
}

bool SDL::CGame::LoadMedia ()
{
	m_Line.SetColor(SDL_Color{ 0xff,0x00,0xff,0xff });
	m_Line.SetWidth(10);
	return true;
}

void SDL::CGame::MainLoop()
{
	BeginPage();
	SDL_Event Event;
	while (!m_QuitGame)
	{
		while (!m_Quit)
		{

			//内存泄漏测试块


			while (SDL_PollEvent(&Event))
			{
				switch (Event.type)
				{
				case SDL_QUIT:
					m_Quit = true;
					m_QuitGame = true;
					m_Redraw = true;
					break;
				case SDL_KEYDOWN:
				{
					switch (Event.key.keysym.sym)
					{
					case SDLK_ESCAPE:
						m_Quit = true;
						m_QuitGame = true;
						cout << "你好！" << endl;
						break;
					}
					m_Redraw = true;
					break;
				}
				case SDL_WINDOWEVENT:
				{
					switch (Event.window.type)
					{
					case SDL_WINDOWEVENT_EXPOSED:
						m_Redraw = true;
						break;
					}
				}
				case SDL_MOUSEBUTTONDOWN:
				{
					if (Event.button.button == SDL_BUTTON_LEFT)
					{
						m_Dragging = true;
						m_Line.AddPoint(SDL_Point{ Event.button.x,Event.button.y });
					}
					break;
				}
				case SDL_MOUSEMOTION:
				{
					if (m_Dragging)
					{
						m_Line.AddPoint(SDL_Point{ Event.motion.x,Event.motion.y });
					}
					break;
				}
				case SDL_MOUSEBUTTONUP:
				{
					if (Event.button.button == SDL_BUTTON_LEFT)
					{
						m_Dragging = false;
						m_Line.AddPoint(SDL_Point{ Event.motion.x,Event.motion.y });
					}
					break;
				}
				}
			}
			m_Redraw = true;
			SDL_SetRenderDrawColor(m_Renderer, 0x00, 0x00, 0xff, 0xff);
			SDL_RenderClear(m_Renderer);
			if (m_Redraw)
			{
				Render();
			}
			SDL_RenderPresent(m_Renderer);
		}
	}
}

void SDL::CGame::Render()
{
	m_Line.Render(m_Renderer);
}

SDL::CGame::~CGame ()
{
  if (m_Window)
    {
      SDL_DestroyWindow (m_Window);
    }
  if (m_Renderer)
    {
      SDL_DestroyRenderer (m_Renderer);
    }
}

void SDL::CGame::BeginPage()
{
	SDL_SetRenderDrawColor(m_Renderer,0xff, 0xff, 0xff, 0xff);
	SDL_RenderPresent(m_Renderer);
	SDL_Delay(2000);
}


bool SDL::CGame::CheckEnd() const
{
	return true;
}

void SDL::CGame::Menu()
{
	SDL_Event e;
	bool quit = false;
	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_ESCAPE)
				{
					m_QuitGame = true;
					quit = true;
					m_Quit = true;
				}
			}
			if (e.type == SDL_QUIT)
			{
				m_QuitGame = true;
				quit = true;
				m_Quit = true;
			}
		}
		SDL_RenderPresent(m_Renderer);
	}
}