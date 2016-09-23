#include "SDL_Object.h"

CObject::CObject(SDL_Window* Window, int x, int y,int Speed)
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
	m_Speed = Speed;
	m_Timer.Start();
}

CObject::~CObject()
{
	for (int i = 0; i != OBJECT_IMAGE_ALL; i++)
	{
		if (m_Image[i])
		{
			SDL_DestroyTexture(m_Image[i]);
		}
	}
}

void CObject::Render()
{
	switch (m_State)
	{
	default:
	case OBJECT_STATE_NORMAL:
	{
		SDL_RenderCopy(m_Renderer, m_Image[OBJECT_IMAGE_NORMAL], NULL, &m_RealArea);
		break;
	}
	}
}

bool CObject::HandleEvent(SDL_Event& e)
{
	bool Handle = false;
	if((e.type == SDL_KEYDOWN)&&(e.key.repeat == 0))
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			m_YDirection = -1;
			Handle = true;
			break;
		case SDLK_DOWN:
			m_YDirection = 1;
			Handle = true;
			break;
		case SDLK_LEFT:
			m_XDirection = -1;
			Handle = true;
			break;
		case SDLK_RIGHT:
			m_XDirection = 1;
			Handle = true;
			break;
		}
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
	m_Speed = Speed;
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

bool CObject::LoadMedia()
{
	SDL_Surface* TempSurface = NULL;
	TempSurface = IMG_Load("dot.bmp");
	if (!TempSurface)
	{
#ifdef _SDL_DEBUG
		cout << "SDL_Particle.cpp     LoadMedia      从文件dot.bmp加载图片失败！SDL_Error:" << SDL_GetError() << endl;
#endif
		return false;
	}
	SDL_SetColorKey(TempSurface, SDL_TRUE, SDL_MapRGB(TempSurface->format, 0x00, 0xff, 0xff));
	m_Area.w = TempSurface->w;
	m_Area.h = TempSurface->h;
	m_RealArea.w = m_Area.w;
	m_RealArea.h = m_Area.h;
	m_Image[OBJECT_IMAGE_NORMAL] = SDL_CreateTextureFromSurface(m_Renderer, TempSurface);
	if (!m_Image[OBJECT_IMAGE_NORMAL])
	{
#ifdef _SDL_DEBUG
		cout << "SDL_Particle.cpp     LoadMedia      从dot.bmp表面加载纹理失败！SDL_Error:" << SDL_GetError() << endl;
#endif
		SDL_FreeSurface(TempSurface);
		return false;
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
	if (m_Timer.GetTicks() > m_Speed)
	{
		float times = m_Timer.GetTicks() / m_Speed;
		if (!(((m_Area.x + times*m_XDirection) < 0 || (m_Area.x + m_Area.w + times*m_XDirection) >= MAP_WIDTH) || Map.TouchWall(m_Area, times*m_XDirection, times*m_YDirection)))
		{
			m_Area.x += times*m_XDirection;
		}
		if (!((m_Area.y + times*m_YDirection) < 0 || ((m_Area.y + m_Area.h + times*m_YDirection) >= MAP_HEIGHT) || Map.TouchWall(m_Area, times*m_XDirection, times*m_YDirection)))
		{
			m_Area.y += times*m_YDirection;
		}
		m_Timer.Start();
	}
	else
	{
		return;
	}
}