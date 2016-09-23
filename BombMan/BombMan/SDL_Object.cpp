#include "SDL_Object.h"

CObject::CObject(SDL_Window* Window,  int AllState, int x, int y, int Speed) :
	m_LastDraw(0),
	m_ChangeInternal(200),
	m_State(0),
	m_LastChangeTime(0),
	m_Listening(true)
{
	m_Window = Window;
	m_Area.x = x;
	m_Area.y = y;
	m_Renderer = SDL_GetRenderer(m_Window);
	if (!m_Renderer)
	{
#ifdef _SDL_DEBUG
		cout << "SDL_Particle	CParticle	无法获取窗口的渲染器	SDL Error:" << SDL_GetError() << endl;
#endif
	}
	m_RealArea.x = x;
	m_RealArea.y = y;
	m_RealArea.w = m_Area.w;
	m_RealArea.h = m_Area.h;
	m_MoveSpeed = Speed;
	m_SourceRect.x = 0;
	m_SourceRect, y = 0;
	m_SourceRect.w = m_ImageInfo.w;
	m_SourceRect.h = m_ImageInfo.h;
	m_Timer.Start();
	for (int i = 0; i != AllState; i++)
	{
		vector<SDL_Point> Temp(0);
		m_Orders.push_back(Temp);
	}
}

CObject::~CObject()
{
	if (m_Image)
	{
		SDL_DestroyTexture(m_Image);
	}
	if (m_DieSound)
	{
		Mix_FreeMusic(m_DieSound);
	}
}

bool CObject::HandleEvent(SDL_Event& e)
{
	bool Handle = false;
	if (m_Listening)
	{
		if ((e.type == SDL_KEYDOWN) && (e.key.repeat == 0))
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
				m_YDirection = -1;
				Handle = true;
				m_State = 1;
				break;
			case SDLK_DOWN:
				m_YDirection = 1;
				Handle = true;
				m_State = 0;
				break;
			case SDLK_LEFT:
				m_XDirection = -1;
				Handle = true;
				m_State = 2;
				break;
			case SDLK_RIGHT:
				m_XDirection = 1;
				Handle = true;
				m_State = 3;
				break;
			}
			m_LastDraw = 0;
		}
		if ((e.type == SDL_KEYUP) && (e.key.repeat == 0))
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
			{
				m_YDirection = 0;
				Handle = true;
				break;
			}
			case SDLK_DOWN:
			{
				m_YDirection = 0;
				Handle = true;
				break;
			}
			case SDLK_LEFT:
			{
				m_XDirection = 0;
				Handle = true;
				break;
			}
			case SDLK_RIGHT:
			{
				m_XDirection = 0;
				Handle = true;
				break;
			}
			}
			m_LastDraw = 0;
		}
		if (!(m_XDirection || m_YDirection))
		{
			m_State = 0;
			m_LastDraw = 0;
		}
	}
	if (Handle)
	{
		m_LastDraw = 0;
	}
	return Handle;
}

bool CObject::Init(SDL_Window* Window, int x, int y,int Speed)
{
	m_Window = Window;
	m_Area.x = x;
	m_Area.y = y;
	m_Renderer = SDL_GetRenderer(m_Window);
	m_RealArea.x = x;
	m_RealArea.y = y;
	m_RealArea.w = m_Area.w;
	m_RealArea.h = m_Area.h;
	m_MoveSpeed = Speed;
	m_Timer.Start();
	if (!m_Renderer)
	{
#ifdef _SDL_DEBUG
		cout << "SDL_Particle	CParticle	无法获取窗口的渲染器	SDL Error:" << SDL_GetError() << endl;
		return false;
#endif
	}
	return true;
}

bool CObject::LoadMedia(string ImagePath,string SoundPath)
{
	SDL_Surface* TempSurface = NULL;
	TempSurface = IMG_Load(ImagePath.c_str());
	if (!TempSurface)
	{
#ifdef _SDL_DEBUG
		cout << "SDL_Particle.cpp     LoadMedia      从文件加载图片失败！SDL_Error:" << SDL_GetError() << endl;
#endif
		return false;
	}
	SDL_SetColorKey(TempSurface, SDL_TRUE, SDL_MapRGB(TempSurface->format, 0x00, 0xff, 0xff));
	m_ImageInfo.w = TempSurface->w / m_ImageInfo.y;
	m_ImageInfo.h = TempSurface->h / m_ImageInfo.x;
	m_Area.w = m_ImageInfo.w;
	m_Area.h = m_ImageInfo.h;
	m_SourceRect.w = m_ImageInfo.w;
	m_SourceRect.h = m_ImageInfo.h;
	m_RealArea.w = m_Area.w;
	m_RealArea.h = m_Area.h;
	m_Image = SDL_CreateTextureFromSurface(m_Renderer, TempSurface);

	if (!m_Image)
	{
#ifdef _SDL_DEBUG
		cout << "SDL_Particle.cpp     LoadMedia      从表面加载纹理失败！SDL_Error:" << SDL_GetError() << endl;
#endif
		SDL_FreeSurface(TempSurface);
		return false;
	}

	if (SoundPath.empty())
	{
		if (!SDL_WasInit(SDL_INIT_AUDIO))
		{
#ifdef _SDL_DEBUG
			cout << "SDL_Object.cpp	LoadMedia	音频子系统没有初始化！SDL Error:" << SDL_GetError() << endl;
#endif
			return false;
		}
		Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, -1, 1024);
		m_DieSound = Mix_LoadMUS(SoundPath.c_str());
		if (!m_DieSound)
		{
#ifdef _SDL_DEBUG
			cout << "SDL_Object.cpp	LoadMedia	加载音频失败！SDL Error:" << Mix_GetError() << endl;
#endif
			return false;
		}
	}
	else
	{
		m_DieSound = NULL;
	}
}

void CObject::SetCamera(SDL_Rect* Camera)
{
	Camera->x = m_Area.x + m_Area.w / 2 - Camera->w / 2;
	Camera->y = m_Area.y + m_Area.h / 2 - Camera->h / 2;

	if (Camera->x < 0)
	{
		Camera->x = 0;
	}
	if (Camera->y < 0)
	{
		Camera->y = 0;
	}
	if ((Camera->x + Camera->w) > MAP_WIDTH)
	{
		Camera->x = MAP_WIDTH - Camera->w;
	}
	if ((Camera->y + Camera->h) > MAP_HEIGHT)
	{
		Camera->y = MAP_HEIGHT - Camera->h;
	}
	m_RealArea.x = m_Area.x - Camera->x;
	m_RealArea.y = m_Area.y - Camera->y;
}

void CObject::SetWindow(SDL_Window* Window)
{
	m_Window = Window;
	m_Renderer = SDL_GetRenderer(m_Window);
	if (!m_Renderer)
	{
#ifdef _SDL_DEBUG
		cout << "SDL_Particle.cpp	CParticle	获取窗口渲染器失败!SDL Error:" << SDL_GetError() << endl;
#endif
		return;
	}
}

void CObject::Move(CMap& Map)
{
	if ((m_Timer.GetTicks() - m_LastMoveTime) > m_MoveSpeed)
	{
		float times = (m_Timer.GetTicks()-m_LastMoveTime) / m_MoveSpeed;
		if (!(((m_Area.x + times*m_XDirection) < 0 || (m_Area.x + m_Area.w + times*m_XDirection) >= MAP_WIDTH) || Map.TouchWall(m_Area, times*m_XDirection, times*m_YDirection)))
		{
			m_Area.x += times*m_XDirection;
		}
		if (!((m_Area.y + times*m_YDirection) < 0 || ((m_Area.y + m_Area.h + times*m_YDirection) >= MAP_HEIGHT) || Map.TouchWall(m_Area, times*m_XDirection, times*m_YDirection)))
		{
			m_Area.y += times*m_YDirection;
		}
		m_LastMoveTime = m_Timer.GetTicks();
	}
}

void CObject::Render()
{
	if ((m_Timer.GetTicks() - m_LastChangeTime) > m_ChangeInternal)
	{
		if (m_State >= m_Orders.size())
		{
#ifdef _SDL_DEBUG
			cout << "SDL_Object.cpp	Render	状态值过大或瓦块长度过小！" << endl;
#endif
			return;
		}
		if (m_LastDraw < (m_Orders[m_State].size() - 1))
		{
			m_LastDraw++;
		}
		else
		{
			m_LastDraw = 0;
		}
		m_LastChangeTime = m_Timer.GetTicks();
	}
	cout << m_State << endl;
	cout << m_LastDraw << endl;
	m_SourceRect.x = m_Orders[m_State][m_LastDraw].y*m_ImageInfo.w;
	m_SourceRect.y = m_Orders[m_State][m_LastDraw].x*m_ImageInfo.h;
	SDL_RenderCopy(m_Renderer, m_Image, &m_SourceRect, &m_RealArea);
}

void CObject::SetTile( int Row, int Queue)
{
	m_ImageInfo.x = Row;
	m_ImageInfo.y = Queue;
}

void CObject::SetPlayOrder(int StateIndex, SDL_Point* Order, int Length)
{
	if (StateIndex >= m_Orders.size())
	{
#ifdef _SDL_DEBUG
		cout << "SDL_Object.cpp	SetPlayOrder	输入的状态值过大！" << endl;
#endif
		return;
	}
	for (int i = 0; i != Length; i++)
	{
		m_Orders[StateIndex].push_back(Order[i]);
	}
}

void CObject::SetStateAmount(int Amount)
{
	m_Orders.clear();
	for (int i = 0; i != Amount; i++)
	{
		vector<SDL_Point> Temp(0);
		m_Orders.push_back(Temp);
	}
}

void CObject::Die()
{
	if (m_State != m_Orders.size() - 1)
	{
		Stop();
		m_State = m_Orders.size() - 1;
		m_Listening = false;
	}
}