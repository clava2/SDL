#include "SDL_Game.h"
#include "SDL_Button.h"
#include "SDL_ProcessBar.h"

CGame::CGame(string Title, int X, int Y, int Width, int Height, SDL_WindowFlags Flag)
{
	m_Quit = false;
	m_QuitGame = false;
	m_Window = NULL;
	m_Renderer = NULL;

	m_MainTimer.Start();
}

bool CGame::InitWindow(string title, int X, int Y, int Width, int Height, SDL_WindowFlags Flag)
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

bool CGame::LoadMedia ()
{
	return true;
}

void CGame::MainLoop()
{
	BeginPage();
	SDL_Event event;


	CProcessBar Process;

	SDL_SetRenderDrawBlendMode(m_Renderer, SDL_BLENDMODE_BLEND);

	Process.SetWindow(m_Window);
	Process.SetColor(0, 255, 255, 255);
	Process.SetMaxLength(1000);


	Process.SetBorderKey('\xff', '\xff', '\xff', '\xff');
	Process.SetSliderColorKey('\xff', '\xff', '\xff', '\xff');
	Process.SetBorderImage("ProcessBar.bmp", 20, 20, 650, 112);
	Process.SetSliderImage("Slider.bmp", -1, -1);

	Process.Locate(100, 100);
	Process.SetSize(500, 50);

	int ProcessPos = 0;



	while (!m_QuitGame)
	{
		while (!m_Quit)
		{

			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
				case SDL_QUIT:
					m_Quit = true;
					m_QuitGame = true;
					break;
				case SDL_KEYDOWN:
				{
					switch (event.key.keysym.sym)
					{
					case SDLK_ESCAPE:
						m_Quit = true;
						m_QuitGame = true;
						break;
					}
					break;
				}
				}
			}

			SDL_SetRenderDrawColor(m_Renderer, 0xff, 0x00, 0xff, 0xff);
			SDL_RenderClear(m_Renderer);

			Process.Offset(1);

			Render();

			Process.Render();

			SDL_RenderPresent(m_Renderer);
		}
	}
}

void CGame::Render()
{
}

CGame::~CGame ()
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

void CGame::BeginPage()
{
	SDL_SetRenderDrawColor(m_Renderer,0xff, 0xff, 0xff, 0xff);
	SDL_RenderPresent(m_Renderer);
	SDL_Delay(2000);
}


bool CGame::CheckEnd() const
{
	return true;
}

void CGame::Menu()
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


void InCallBack(void* Param, void* Result)
{
	cout << "SDL_Game.cpp	void InCallBack(void* Param,void* Reault)" << endl;
	cout << "进入按钮的回调函数调用！" << endl << endl << endl;
}