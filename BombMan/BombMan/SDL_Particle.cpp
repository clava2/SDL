#include "SDL_Particle.h"

CParticle::CParticle(SDL_Window* Window,int x, int y,int Speed):
	m_Time(300),
	m_Speed(Speed)
{
	m_Window = Window;
	m_Area.x = x;
	m_Area.y = y;
	m_All.clear();
	m_Count = 10;
	m_Renderer = SDL_GetRenderer(m_Window);
	long long Now = SDL_GetTicks();
	Single Temp;
	for (int i = 0; i != m_Count; i++)
	{
		Temp.Begin = Now + m_Time*i / m_Count;
		Temp.Type = (PARTICLE_COLOR)(rand() % PARTICLE_ALL);
		if (m_Area.w&&m_Area.h)
		{
			Temp.X = m_Area.x + (rand() % m_Area.w);
			Temp.Y = m_Area.y + (rand() % m_Area.h);
			Temp.RealX = Temp.X;
			Temp.RealY = Temp.Y;
		}
		m_All.push_back(Temp);
	}
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
	m_Timer.Start();
}

void CParticle::Render()
{

	SDL_SetRenderDrawColor(m_Renderer, 0x00, 0x00, 0xff, 0xff);
	SDL_RenderCopy(m_Renderer, m_Dot, NULL, &m_RealArea);

	for (int i = 0; i != m_Count; i++)
	{
		if (SDL_GetTicks() > (m_All[i].Begin + m_Time))
		{
			m_All[i].Begin = SDL_GetTicks();
			m_All[i].Type = (PARTICLE_COLOR)(rand() % PARTICLE_ALL);
			m_All[i].X = m_Area.x + (rand() % m_Area.w);
			m_All[i].Y = m_Area.y + (rand() % m_Area.h);
		}
	}
	for (int i = 0; i != m_Count; i++)
	{
		SDL_Rect Temp = { m_All[i].RealX,m_All[i].RealY,m_ParticleWidth,m_ParticleHeight };
		SDL_RenderCopy(m_Renderer, m_Particles[m_All[i].Type], NULL, &Temp);
	}
}

bool CParticle::HandleEvent(SDL_Event& e)
{
	bool Handle = false;
	if (e.type == SDL_KEYDOWN&&e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
		{
			m_YDirection = -1;
			Handle = true;
			break;
		}
		case SDLK_DOWN:
		{
			m_YDirection = 1;
			Handle = true;
			break;
		}
		case SDLK_LEFT:
		{
			m_XDirection = -1;
			Handle = true;
			break;
		}
		case SDLK_RIGHT:
		{
			m_XDirection = 1;
			Handle = true;
			break;
		}
		}
	}
	if (e.type == SDL_KEYUP&&e.key.repeat == 0)
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
			m_XDirection =0;
			Handle = true;
			break;
		}
		}
	}
	return Handle;
}

void CParticle::Move(CMap& Map)
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

void CParticle::SetCamera(SDL_Rect* Camera)
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
	for (int i = 0; i != m_Count; i++)
	{
		m_All[i].RealX = m_All[i].X - Camera->x;
		m_All[i].RealY = m_All[i].Y - Camera->y;
	}
}

void CParticle::LoadMedia()
{
	SDL_Surface* TempSurface = NULL;								//临时表面

//加载绿色粒子
	TempSurface = SDL_LoadBMP("green.bmp");
	if (!TempSurface)
	{
#ifdef _SDL_DEBUG
		cout << "SDL_Particle.cpp     LoadMedia      从文件green.bmp加载图片失败！SDL_Error:" << SDL_GetError() << endl;
#endif
		return;
	}

	m_ParticleWidth = TempSurface->w;
	m_ParticleHeight = TempSurface->h;
	SDL_SetColorKey(TempSurface, SDL_TRUE, SDL_MapRGB(TempSurface->format, 0x00, 0xff, 0xff));
	m_Particles[PARTICLE_GREEN] = SDL_CreateTextureFromSurface(m_Renderer,TempSurface);
	if (!m_Particles[PARTICLE_GREEN])
	{
#ifdef _SDL_DEBUG
		cout<< "SDL_Particle.cpp     LoadMedia      从green.bmp表面加载纹理失败！SDL_Error:" << SDL_GetError() << endl;
#endif
		SDL_FreeSurface(TempSurface);
		return;
	}

	//释放表面
	SDL_FreeSurface(TempSurface);
	TempSurface = NULL;

//加载蓝色粒子
	TempSurface = SDL_LoadBMP("blue.bmp");
	if (!TempSurface)
	{
#ifdef _SDL_DEBUG
		cout << "SDL_Particle.cpp     LoadMedia      从文件blue.bmp加载图片失败！SDL_Error:" << SDL_GetError() << endl;
#endif
		return;
	}
	SDL_SetColorKey(TempSurface, SDL_TRUE, SDL_MapRGB(TempSurface->format, 0x00, 0xff, 0xff));
	m_Particles[PARTICLE_BLUE] = SDL_CreateTextureFromSurface(m_Renderer, TempSurface);
	if (!m_Particles[PARTICLE_BLUE])
	{
#ifdef _SDL_DEBUG
		cout << "SDL_Particle.cpp     LoadMedia      从blue.bmp表面加载纹理失败！SDL_Error:" << SDL_GetError() << endl;
#endif
		SDL_FreeSurface(TempSurface);
		return;
	}
//释放表面
	SDL_FreeSurface(TempSurface);
	TempSurface = NULL;

	//加载红色粒子
	TempSurface = SDL_LoadBMP("red.bmp");
	if (!TempSurface)
	{
#ifdef _SDL_DEBUG
		cout << "SDL_Particle.cpp     LoadMedia      从文件red.bmp加载图片失败！SDL_Error:" << SDL_GetError() << endl;
#endif
		return;
	}
	SDL_SetColorKey(TempSurface, SDL_TRUE, SDL_MapRGB(TempSurface->format, 0x00, 0xff, 0xff));
	m_Particles[PARTICLE_RED] = SDL_CreateTextureFromSurface(m_Renderer, TempSurface);
	if (!m_Particles[PARTICLE_RED])
	{
#ifdef _SDL_DEBUG
		cout << "SDL_Particle.cpp     LoadMedia      从red.bmp表面加载纹理失败！SDL_Error:" << SDL_GetError() << endl;
#endif
		SDL_FreeSurface(TempSurface);
		return;
	}
//释放表面
	SDL_FreeSurface(TempSurface);
	TempSurface = NULL;

	//加载白色粒子
	TempSurface = SDL_LoadBMP("shimmer.bmp");
	if (!TempSurface)
	{
#ifdef _SDL_DEBUG
		cout << "SDL_Particle.cpp     LoadMedia      从文件shimmer.bmp加载图片失败！SDL_Error:" << SDL_GetError() << endl;
#endif
		return;
	}
	SDL_SetColorKey(TempSurface, SDL_TRUE, SDL_MapRGB(TempSurface->format, 0x00, 0xff, 0xff));
	m_Particles[PARTICLE_WHITE] = SDL_CreateTextureFromSurface(m_Renderer, TempSurface);
	if (!m_Particles[PARTICLE_WHITE])
	{
#ifdef _SDL_DEBUG
		cout << "SDL_Particle.cpp     LoadMedia      从shimmer.bmp表面加载纹理失败！SDL_Error:" << SDL_GetError() << endl;
#endif
		SDL_FreeSurface(TempSurface);
		return;
	}
	//释放表面
	SDL_FreeSurface(TempSurface);
	TempSurface = NULL;

//加载黑点
	TempSurface = SDL_LoadBMP("dot.bmp");
	if (!TempSurface)
	{
#ifdef _SDL_DEBUG
		cout << "SDL_Particle.cpp     LoadMedia      从文件dot.bmp加载图片失败！SDL_Error:" << SDL_GetError() << endl;
#endif
		return;
	}
	SDL_SetColorKey(TempSurface, SDL_TRUE, SDL_MapRGB(TempSurface->format, 0x00, 0xff, 0xff));
	m_Area.w = TempSurface->w;
	m_Area.h = TempSurface->h;
	m_RealArea.w = m_Area.w;
	m_RealArea.h = m_Area.h;
	m_Dot = SDL_CreateTextureFromSurface(m_Renderer, TempSurface);
	if (!m_Dot)
	{
#ifdef _SDL_DEBUG
		cout << "SDL_Particle.cpp     LoadMedia      从dot.bmp表面加载纹理失败！SDL_Error:" << SDL_GetError() << endl;
#endif
		SDL_FreeSurface(TempSurface);
		return;
	}

//释放表面
		SDL_FreeSurface(TempSurface);
}

void CParticle::SetWindow(SDL_Window* Window)
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