#include "SDL_Button.h"

CButton::CButton(SDL_Window* Window, string String, string down_path, string up_path, void (DownCallBack)(void* param, void* Result), void (UpCallBack)(void* Param, void* Result), void* DownParam, void* DownResult, void* UpParam, void* UpResult)
{
	if (!Window)
	{
		m_Window = NULL;
		m_Renderer = NULL;
	}
	m_Window = Window;
	m_Renderer = SDL_GetRenderer(m_Window);
	if (!m_Renderer)
	{
#ifdef _SDL_DEBUG
		cout << "SDL_Button.cpp	CButtotn::CButton	获取窗口渲染器失败！SDL Error:" << SDL_GetError() << endl;
#endif
		return;
	}


	m_Area.x = 0;
	m_Area.y = 0;


	m_DownCallBack = DownCallBack;
	m_UpCallBack = UpCallBack;

	m_DownParam = DownParam;
	m_DownResult = DownResult;

	m_UpParam = UpParam;
	m_UpResult = UpResult;

	m_KeyOn = true;
}



bool CButton::HandleEvent(SDL_Event* event)
{
	bool Handle = false;
	switch (event->type)
	{
	case SDL_MOUSEBUTTONDOWN:
	{
		if ((event->button.x <= (m_Area.x + m_Area.w)) && (event->button.x >= m_Area.x) && (event->button.y >= m_Area.y) && (event->button.y <= m_Area.y + m_Area.h))
		{
			Handle = true;
			m_State = BUTTON_STATE_DOWN;
			if (m_DownCallBack)
			{
				m_DownCallBack(m_DownParam, m_DownResult);
			}
		}
		break;
	}
	case SDL_KEYDOWN:
	{
		if (m_KeyOn && (event->key.keysym.sym == m_Key))
		{
			Handle = true;
			m_State = BUTTON_STATE_DOWN;
			if (m_DownCallBack)
			{
				m_DownCallBack(m_DownParam, m_DownResult);
			}
		}
		break;
	}
	case SDL_FINGERDOWN:
	{
		if (((event->tfinger.x)*SCREEN_WIDTH <= (m_Area.x + m_Area.w)) && ((event->tfinger).x*SCREEN_WIDTH) >= m_Area.x && ((event->tfinger.y*SCREEN_HEIGHT) >= m_Area.y && ((event->tfinger.y*SCREEN_HEIGHT) <= (m_Area.y + m_Area.h))))
		{
			Handle = true;
			m_State = BUTTON_STATE_DOWN;
			Handle = true;
			if (m_DownCallBack)
			{
				m_DownCallBack(m_DownParam, m_DownResult);
			}
		}
		break;
	}
	case SDL_MOUSEBUTTONUP:
	{
		m_State = BUTTON_STATE_UP;
		Handle = true;
		if ((event->button.x <= (m_Area.x + m_Area.w)) && (event->button.x >= m_Area.x) && (event->button.y >= m_Area.y) && (event->button.y <= m_Area.y + m_Area.h))
		{
			if (m_UpCallBack)
			{
				m_UpCallBack(m_UpParam, m_UpResult);
			}
		}
		break;
	}
	case SDL_KEYUP:
	{
		if (m_KeyOn && (event->key.keysym.sym == m_Key))
		{
			m_State = BUTTON_STATE_UP;
			Handle = true;
			if (m_UpCallBack)
			{
				m_UpCallBack(m_UpParam, m_UpResult);
			}
		}
		break;
	}
	case SDL_FINGERUP:
	{
		m_State = BUTTON_STATE_UP;
		Handle = true;
		if (m_UpCallBack)
		{
			m_UpCallBack(m_UpParam, m_UpResult);
		}
		
		break;
	}
	}
	return Handle;
}


void CButton::Locate(int x, int y)
{
	m_Area.x= x;
	m_Area.y = y;
}

void CButton::SetSize(int Width, int Height)
{
	m_Area.w = Width;
	m_Area.h = Height; 
}

CButton::~CButton()
{
	if (m_DownImage)
	{
		SDL_DestroyTexture(m_DownImage);
	}
	if (m_UpImage)
	{
		SDL_DestroyTexture(m_UpImage);
	}
	if (m_Text)
	{
		SDL_DestroyTexture(m_Text);
	}
}

void CButton::Render()
{
	if (m_State == BUTTON_STATE_DOWN)
	{
		SDL_RenderCopy(m_Renderer, m_DownImage, NULL, &m_Area);
	}
	if (m_State == BUTTON_STATE_UP)
	{
		SDL_RenderCopy(m_Renderer, m_UpImage, NULL, &m_Area);
	}
	if (m_State == BUTTON_STATE_DISABLE)
	{
		SDL_RenderCopy(m_Renderer, m_DisableImage, NULL, &m_Area);
	}
}

void CButton::SetWindow(SDL_Window* Window)
{
	m_Window = Window;
	m_Renderer = SDL_GetRenderer(m_Window);
	if (!m_Renderer)
	{
#ifdef _SDL_DEBUG
		cout << "SDL_Button.cpp	SetWindow	无法获得窗口渲染器指针!SDL Error:" << SDL_GetError() << endl;
#endif
	}
}


bool CButton::LoadMedia(string DownPath, string UpPath, string Text)
{
	SDL_Surface* TempSurface = NULL;
	TempSurface = IMG_Load(DownPath.c_str());
	if (!TempSurface)
	{
#ifdef _SDL_DEBUG
		cout << "SDL_Button.cpp	LoadMedia	从文件加载图片表面失败!SDL Error:" << SDL_GetError() << endl;
#endif
		return false;
	}
	
	m_DownImage = SDL_CreateTextureFromSurface(m_Renderer, TempSurface);

	if (!m_DownImage)
	{
#ifdef _SDL_DEBUG
		cout << "SDL_Button.cpp	LoadMedia	从表面加载纹理失败！SDL Error:" << SDL_GetError() << endl;
#endif
		return false;
	}
	
	SDL_FreeSurface(TempSurface);
	TempSurface = NULL;
	TempSurface = IMG_Load(UpPath.c_str());
	if (!TempSurface)
	{
#ifdef _SDL_DEBUG
		cout << "SDL_Button.cpp	LoadMedia	从文件加载图片表面失败!SDL Error:" << SDL_GetError() << endl;
#endif
		return false;
	}

	m_UpImage = SDL_CreateTextureFromSurface(m_Renderer, TempSurface);

	if (!m_UpImage)
	{
#ifdef _SDL_DEBUG
		cout << "SDL_Button.cpp	LoadMedia	从表面加载纹理失败！SDL Error:" << SDL_GetError() << endl;
#endif
		return false;
	}

	SDL_FreeSurface(TempSurface);
	TempSurface = NULL;



}