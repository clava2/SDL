#include "SDL_Particle.h"

CParticle::CParticle(SDL_Window* Window,int x, int y):
	m_Time(300)
{
	m_Window = Window;
	m_XPos = x;
	m_YPos = y;
	m_Count = 10;
	m_All.clear();
	m_Renderer = SDL_GetRenderer(m_Window);
	cout << m_Renderer << endl;
	cout << SDL_GetError() << endl;
	long long Now = SDL_GetTicks();
	Single Temp;
	for (int i = 0; i != m_Count; i++)
	{
		Temp.Begin = Now+m_Time*i/m_Count;
		Temp.Type = (PARTICLE_COLOR)(rand() % PARTICLE_ALL);
		if (m_DotWidth&&m_DotHeight)
		{
			Temp.X = m_XPos + (rand() % m_DotWidth);
			Temp.Y = m_YPos + (rand() % m_DotHeight);
		}
		m_All.push_back(Temp);
	}
}

void CParticle::Render()
{
	SDL_Rect Area = { m_XPos,m_YPos,m_DotWidth,m_DotHeight };

	SDL_SetRenderDrawColor(m_Renderer, 0x00, 0xff, 0xff, 0xff);
	SDL_RenderClear(m_Renderer);
	SDL_RenderCopy(m_Renderer, m_Dot, NULL, &Area);

	for (int i = 0; i != m_Count; i++)
	{
		if (SDL_GetTicks() > (m_All[i].Begin + m_Time))
		{
			m_All[i].Begin = SDL_GetTicks();
			m_All[i].Type = (PARTICLE_COLOR)(rand() % PARTICLE_ALL);
			m_All[i].X = m_XPos + (rand() % m_DotWidth);
			m_All[i].Y = m_YPos + (rand() % m_DotHeight);
		}
	}
	for (int i = 0; i != m_Count; i++)
	{
		Area = { m_All[i].X,m_All[i].Y,m_ParticleWidth,m_ParticleHeight };
		SDL_RenderCopy(m_Renderer, m_Particles[m_All[i].Type], NULL, &Area);
	}
}

void CParticle::HandleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN&&e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
		{
			m_YDirection = -1;
			break;
		}
		case SDLK_DOWN:
		{
			m_YDirection = 1;
			break;
		}
		case SDLK_LEFT:
		{
			m_XDirection = -1;
			break;
		}
		case SDLK_RIGHT:
		{
			m_XDirection = 1;
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
			break;
		}
		case SDLK_DOWN:
		{
			m_YDirection = 0;
			break;
		}
		case SDLK_LEFT:
		{
			m_XDirection = 0;
			break;
		}
		case SDLK_RIGHT:
		{
			m_XDirection =0;
			break;
		}
		}
	}
}

void CParticle::Move()
{
	m_XPos += m_XDirection;
	m_YPos += m_YDirection;
	if (m_XPos<0 || (m_XPos+m_DotWidth)>m_ScreenWidth)
	{
		m_XPos -= m_XDirection;
	}
	if (m_YPos<0 || (m_YPos + m_DotHeight)>m_ScreenHeight)
	{
		m_YPos -= m_YDirection;
	}
}

void CParticle::SetBorder(int Width, int Height)
{
	m_ScreenHeight = Height;
	m_ScreenWidth = Width;
}

void CParticle::LoadMedia()
{
	SDL_Surface* TempSurface = NULL;								//临时表面

	//加载绿色粒子
	TempSurface = SDL_LoadBMP("green.bmp");
#ifdef _SDL_DEBUG
	if (!TempSurface)
	{
		cout << "SDL_Particle.cpp     LoadMedia      从文件green.bmp加载图片失败！SDL_Error:" << SDL_GetError() << endl;
		return;
	}
#endif
	m_ParticleWidth = TempSurface->w;
	m_ParticleHeight = TempSurface->h;
	SDL_SetColorKey(TempSurface, SDL_TRUE, SDL_MapRGB(TempSurface->format, 0x00, 0xff, 0xff));
	m_Particles[PARTICLE_GREEN] = SDL_CreateTextureFromSurface(m_Renderer,TempSurface);
#ifdef _SDL_DEBUG
	if (!m_Particles[PARTICLE_GREEN])
	{
		cout<< "SDL_Particle.cpp     LoadMedia      从green.bmp表面加载纹理失败！SDL_Error:" << SDL_GetError() << endl;
		return;
	}
#endif
	//释放表面
	if (TempSurface)
	{
		SDL_FreeSurface(TempSurface);
		TempSurface = NULL;
	}

	//加载蓝色粒子
	TempSurface = SDL_LoadBMP("blue.bmp");
#ifdef _SDL_DEBUG
	if (!TempSurface)
	{
		cout << "SDL_Particle.cpp     LoadMedia      从文件blue.bmp加载图片失败！SDL_Error:" << SDL_GetError() << endl;
		return;
	}
#endif
	SDL_SetColorKey(TempSurface, SDL_TRUE, SDL_MapRGB(TempSurface->format, 0x00, 0xff, 0xff));
	m_Particles[PARTICLE_BLUE] = SDL_CreateTextureFromSurface(m_Renderer, TempSurface);
#ifdef _SDL_DEBUG
	if (!m_Particles[PARTICLE_BLUE])
	{
		cout << "SDL_Particle.cpp     LoadMedia      从blue.bmp表面加载纹理失败！SDL_Error:" << SDL_GetError() << endl;
		return;
	}
#endif
	//释放表面
	if (TempSurface)
	{
		SDL_FreeSurface(TempSurface);
		TempSurface = NULL;
	}

	//加载红色粒子
	TempSurface = SDL_LoadBMP("red.bmp");
#ifdef _SDL_DEBUG
	if (!TempSurface)
	{
		cout << "SDL_Particle.cpp     LoadMedia      从文件red.bmp加载图片失败！SDL_Error:" << SDL_GetError() << endl;
		return;
	}
#endif
	SDL_SetColorKey(TempSurface, SDL_TRUE, SDL_MapRGB(TempSurface->format, 0x00, 0xff, 0xff));
	m_Particles[PARTICLE_RED] = SDL_CreateTextureFromSurface(m_Renderer, TempSurface);
#ifdef _SDL_DEBUG
	if (!m_Particles[PARTICLE_RED])
	{
		cout << "SDL_Particle.cpp     LoadMedia      从red.bmp表面加载纹理失败！SDL_Error:" << SDL_GetError() << endl;
		return;
	}
#endif
	//释放表面
	if (TempSurface)
	{
		SDL_FreeSurface(TempSurface);
		TempSurface = NULL;
	}

	//加载白色粒子
	TempSurface = SDL_LoadBMP("shimmer.bmp");
#ifdef _SDL_DEBUG
	if (!TempSurface)
	{
		cout << "SDL_Particle.cpp     LoadMedia      从文件shimmer.bmp加载图片失败！SDL_Error:" << SDL_GetError() << endl;
		return;
	}
#endif
	SDL_SetColorKey(TempSurface, SDL_TRUE, SDL_MapRGB(TempSurface->format, 0x00, 0xff, 0xff));
	m_Particles[PARTICLE_WHITE] = SDL_CreateTextureFromSurface(m_Renderer, TempSurface);
#ifdef _SDL_DEBUG
	if (!m_Particles[PARTICLE_WHITE])
	{
		cout << "SDL_Particle.cpp     LoadMedia      从shimmer.bmp表面加载纹理失败！SDL_Error:" << SDL_GetError() << endl;
		return;
	}
#endif
	//释放表面
	if (TempSurface)
	{
		SDL_FreeSurface(TempSurface);
		TempSurface = NULL;
	}

	//加载黑点
	TempSurface = SDL_LoadBMP("dot.bmp");
#ifdef _SDL_DEBUG
	if (!TempSurface)
	{
		cout << "SDL_Particle.cpp     LoadMedia      从文件dot.bmp加载图片失败！SDL_Error:" << SDL_GetError() << endl;
		return;
	}
#endif
	SDL_SetColorKey(TempSurface, SDL_TRUE, SDL_MapRGB(TempSurface->format, 0x00, 0xff, 0xff));
	m_DotWidth = TempSurface->w;
	m_DotHeight = TempSurface->h;
	cout << "黑点宽度:" << m_DotWidth << "黑点高度:" << m_DotHeight << endl;
	m_Dot = SDL_CreateTextureFromSurface(m_Renderer, TempSurface);
#ifdef _SDL_DEBUG
	if (!m_Dot)
	{
		cout << "SDL_Particle.cpp     LoadMedia      从dot.bmp表面加载纹理失败！SDL_Error:" << SDL_GetError() << endl;
		return;
	}
#endif

	//释放表面
	if (TempSurface)
	{
		SDL_FreeSurface(TempSurface);
	}
}