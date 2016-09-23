#include "SDL_Game.h"
#include "SDL_Button.h"

CGame::CGame(string Title, int X, int Y, int Width, int Height)
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

	SDL_Surface* TempSurface = IMG_Load("Start.jpg");
	if (!TempSurface)
	{
#ifdef _SDL_DEBUG
		cout << "SDL_Game.cpp	CGame	bool CGame::LoadMedia()" << endl;
		cout << "从文件加载开始页面的图片失败！" << endl;
		cout << "Path = " << "Start.jpg" << endl;
		cout << "TempSurface" << TempSurface << endl;
		cout << "SDL_GetError() = " << SDL_GetError() << endl << endl << endl;
#endif
		return false;
	}
	m_StartImage = SDL_CreateTextureFromSurface(m_Renderer, TempSurface);
	SDL_FreeSurface(TempSurface);
	if (!m_StartImage)
	{
#ifdef _SDL_DEBUG
		cout << "SDL_Game.cpp	CGame	bool CGame::LoadMedia()" << endl;
		cout << "从表面创建纹理失败！" << endl;
		cout << "m_Renderer = " << m_Renderer << endl;
		cout << "TempSurface = " << TempSurface << endl;
		cout << "SDL_GetError() = " << SDL_GetError() << endl;
#endif
		return false;
	}

	return true;
}

void CGame::MainLoop()
{
	BeginPage();
	SDL_Event event;

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

			Render();

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
  if (m_StartImage)
  {
	  SDL_DestroyTexture(m_StartImage);
  }
}

void CGame::BeginPage()
{
	SDL_SetRenderDrawColor(m_Renderer,0xff, 0xff, 0xff, 0xff);

	SDL_RenderCopy(m_Renderer, m_StartImage, NULL, NULL);

	SDL_RenderPresent(m_Renderer);
	SDL_Delay(5000);
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