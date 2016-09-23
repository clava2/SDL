#include "SDL_Timer.h"

CTimer::CTimer()
{
	if (SDL_WasInit(SDL_INIT_TIMER))
	{
		m_Paused = false;
		m_Started = false;
		
		m_StartTicks = 0;
		m_PauseTicks = 0;
	}
	else
	{
#ifdef _SDL_DEBUG
		cout << "定时器子系统为初始化！SDL_Error:" << SDL_GetError() << endl;
		return;
#endif
	}
}

void CTimer::Start()
{
	if (SDL_WasInit(SDL_INIT_TIMER))
	{
		m_Paused = false;
		m_Started = true;
		m_StartTicks = SDL_GetTicks();
		m_PauseTicks = 0;
	}
	else
	{
#ifdef _SDL_DEBUG
		cout << "计时器子系统为初始化。SDL_Error:" << SDL_GetError() << endl;
		return;
#endif
	}
}

void CTimer::Pause()
{
	if (!m_Paused&&m_Started)
	{
		m_Paused = true;
		m_PauseTicks = SDL_GetTicks() - m_StartTicks;
		m_Started = true;
	}
#ifdef _SDL_DEBUG
	else
	{
		cout << "定时器还没有开启或者已经暂停." << endl;
	}
#endif
}

void CTimer::Stop()
{
	if (m_Started)
	{
		m_Started = false;
		m_Paused = false;
		m_PauseTicks = 0;
		m_StartTicks = 0;
	}

#ifdef _SDL_DEBUG
	else
	{
		cout << "计时器还没有开始计时，无法停止！" << endl;
	}
#endif
}

void CTimer::Unpause()
{
	if (m_Paused)
	{
		m_Paused = false;
		m_Started = true;
		m_PauseTicks = 0;
	}
#ifdef _SDL_DEBUG
	else
	{
		cout << "定时器还没有暂停！" << endl;
	}
#endif
}

Uint32 CTimer::GetTicks()
{
	if (m_Started && !m_Paused)
	{
		return SDL_GetTicks() - m_StartTicks;
	}
	else if (m_Started)
	{
#ifdef _SDL_DEBUG
		cout << "计时器已经暂停，返回值为暂停时间！" << endl;
#endif
		return m_PauseTicks;
	}
#ifdef _SDL_DEBUG
	else
	{
		cout << "定时器还未开启或已暂停！" << endl;
	}
#endif
	return 0;
}

