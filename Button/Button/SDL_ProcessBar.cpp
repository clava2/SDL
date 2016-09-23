#include "SDL_ProcessBar.h"

CProcessBar::CProcessBar(SDL_Window * Window, int MaxLength)
{
	m_MaxLength = MaxLength;
	m_Window = Window;;
	if (m_Window)
	{
		m_Renderer = SDL_GetRenderer(m_Window);
	}
	m_CurrentPosition = 0;
	m_ShowPercent = false;
	m_Vertical = false;
	m_Direction = true;
	m_GoArea = m_MainArea = { 0,0,100,20 };
	m_Border = NULL;
	m_Slider = NULL;
	m_Color = { 255,0,0 };
	m_CallBack = NULL;
}

CProcessBar::~CProcessBar()
{
	if (m_Border)
	{
		SDL_DestroyTexture(m_Border);
		m_Border = NULL;
	}
	if (m_Slider)
	{
		SDL_DestroyTexture(m_Slider);
		m_Slider = NULL;
	}
}

void CProcessBar::SetPosition(int Position)
{
	if ((!m_Called) && (m_CallBack))
	{
		m_CallBack(m_Param, m_Result);
		m_Called = true;
	}
	if (Position > m_MaxLength)
	{
#ifdef _SDL_DEBUG
		cout << "SDL_ProcessBar.cpp	CProcessBar	void CProcessBar::SetPosition(int Position)" << endl;
		cout << "设置进度条位置失败！因为位置大于进度条的最大位置！" << endl;
		cout << "Position = " << Position << endl;
		cout << "m_MaxLength = " << m_MaxLength << endl << endl << endl;
#endif
		return;
	}
	m_CurrentPosition = Position;
}

void CProcessBar::Render()
{
	SDL_Rect SlideArea = m_GoArea;
	if (m_Vertical)
	{
		if (m_Direction)
		{
			SlideArea.y = SlideArea.h*(m_MaxLength - m_CurrentPosition*m_GoArea.h / m_MaxLength);
			SlideArea.h = m_CurrentPosition*m_GoArea.h / m_MaxLength;
		}
		else
		{
			SlideArea.h = m_CurrentPosition*m_GoArea.h / m_MaxLength;
		}
	}
	else
	{
		if (m_Direction)
		{
			SlideArea.w = m_CurrentPosition*m_GoArea.w / m_MaxLength;
		}
		else
		{
			SlideArea.x = SlideArea.w*(m_MaxLength - m_CurrentPosition*m_GoArea.w / m_MaxLength);
			SlideArea.w = m_CurrentPosition*m_GoArea.w / m_MaxLength;
		}
	}
	SDL_Color OldColor;
	SDL_GetRenderDrawColor(m_Renderer, &OldColor.r, &OldColor.g, &OldColor.b, &OldColor.a);
	if (m_Border)
	{

		SDL_RenderCopy(m_Renderer, m_Border, NULL, &m_MainArea);
	}
	else
	{
		SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
		SDL_RenderDrawRect(m_Renderer, &m_MainArea);
	}
	SDL_SetRenderDrawColor(m_Renderer, m_Color.r, m_Color.g, m_Color.b, m_Color.a);
	SlideArea.x++; SlideArea.y++; SlideArea.w -= 2; SlideArea.h -= 2;
	SDL_RenderFillRect(m_Renderer, &SlideArea);
	if (m_Slider)
	{
		SDL_Rect SliderArea = { SlideArea.x + SlideArea.w - m_SliderWidth / 2,SlideArea.y +SlideArea.h/2 - m_SliderHeight / 2,m_SliderWidth,m_SliderHeight };
		SDL_RenderCopy(m_Renderer, m_Slider, NULL, &SliderArea);
	}
	SDL_SetRenderDrawColor(m_Renderer, OldColor.r, OldColor.g, OldColor.b, OldColor.a);
}


void CProcessBar::Locate(SDL_Point Position)
{
	m_GoArea.x = m_GoArea.x - m_MainArea.x + Position.x;
	m_GoArea.y = m_GoArea.y - m_MainArea.y + Position.y;

	m_MainArea.x = Position.x;
	m_MainArea.y = Position.y;
}

void CProcessBar::Locate(int x, int y)
{
	m_GoArea.x = m_GoArea.x - m_MainArea.x + x;
	m_GoArea.y = m_GoArea.y - m_MainArea.y + y;


	m_MainArea.x = x;
	m_MainArea.y = y;
}


void CProcessBar::Offset(int Offset)
{
	if ((!m_Called) && (m_CallBack))
	{
		m_CallBack(m_Param, m_Result);
		m_Called = true;
	}
	if (m_CurrentPosition >= m_MaxLength)
	{
#ifdef _SDL_DEBUG
		cout << "SDL_ProcessBar	CProcessBar	void CProcess::Offset(int Offset)" << endl;
		cout << "偏移失败！因为已经达到最大位置，无法偏移！" << endl;
		cout << "m_MaxLength = " << m_MaxLength << endl;
		cout << "m_CurrentPosition = " << m_CurrentPosition << endl << endl << endl;
#endif
		return;
	}
	m_CurrentPosition += Offset;
}

void CProcessBar::SetWindow(SDL_Window* Window)
{
	m_Window = Window;
	m_Renderer = SDL_GetRenderer(m_Window);
}

bool CProcessBar::SetBorderImage(string ImagePath, SDL_Rect GoArea)
{
	if (m_Border)
	{
		SDL_DestroyTexture(m_Border);
		m_Border = NULL;
	}
	SDL_Surface* TempSurface = IMG_Load(ImagePath.c_str());
	if (!TempSurface)
	{
#ifdef _SDL_DEBUG
		cout << "SDL_ProcessBar.cpp	CProcessBar	void CProcessBar::SetBorderImage(string ImagePath,SDL_Rect GoArea)" << endl;
		cout << "从文件加载表面失败!" << endl;
		cout << "ImagePath = " << ImagePath << endl;
		cout << "IMG_GetError() = " << IMG_GetError() << endl << endl << endl;
#endif
		return false;
	}

	if (m_BorderKeyOpen)
	{
		Uint32 Key = SDL_MapRGBA(TempSurface->format, m_BorderKey.r, m_BorderKey.g, m_BorderKey.b, m_BorderKey.a);
		SDL_SetColorKey(TempSurface, 1, Key);
	}

	m_Border = SDL_CreateTextureFromSurface(m_Renderer, TempSurface);
	m_MainArea.w = TempSurface->w;
	m_MainArea.h = TempSurface->h;
	SDL_FreeSurface(TempSurface);
	if (!m_Border)
	{
#ifdef _SDL_DEBUG
		cout << "SDL_ProcessBar.cpp	CProcessBar	bool CProcessBar::SetBorderImage(string ImagePath,SDl_Rect GoArea)" << endl;
		cout << "当前无法加载边界图片！" << endl;
		cout << "ImagePath = " << ImagePath << endl;
		cout << "m_Renderer = " << m_Renderer << endl;
		cout << "TempSurface = " << TempSurface << endl;
		cout << "SDL_GetError() = " << SDL_GetError() << endl;
		TempSurface = NULL;
#endif
		return false;
	}
	m_GoArea = GoArea;
	return true;
}

bool CProcessBar::SetBorderImage(string ImagePath, int x, int y, int w, int h)
{
	if (m_Border)
	{
		SDL_DestroyTexture(m_Border);
		m_Border = NULL;
	}
	SDL_Surface* TempSurface = IMG_Load(ImagePath.c_str());
	if (!TempSurface)
	{
#ifdef _SDL_DEBUG
		cout << "SDL_ProcessBar.cpp	CProcessBar	void CProcessBar::SetBorderImage(string ImagePath,SDL_Rect GoArea)" << endl;
		cout << "从文件加载表面失败!" << endl;
		cout << "ImagePath = " << ImagePath << endl;
		cout << "IMG_GetError() = " << IMG_GetError() << endl << endl << endl;
#endif
		return false;
	}

	if (m_BorderKeyOpen)
	{
		Uint32 Key = SDL_MapRGBA(TempSurface->format, m_BorderKey.r, m_BorderKey.g, m_BorderKey.b, m_BorderKey.a);
		SDL_SetColorKey(TempSurface, 1, Key);
	}

	m_Border = SDL_CreateTextureFromSurface(m_Renderer, TempSurface);
	m_MainArea.w = TempSurface->w;
	m_MainArea.h = TempSurface->h;
	SDL_FreeSurface(TempSurface);
	if (!m_Border)
	{
#ifdef _SDL_DEBUG
		cout << "SDL_ProcessBar.cpp	CProcessBar	bool CProcessBar::SetBorderImage(string ImagePath,SDl_Rect GoArea)" << endl;
		cout << "当前无法加载边界图片！" << endl;
		cout << "ImagePath = " << ImagePath << endl;
		cout << "m_Renderer = " << m_Renderer << endl;
		cout << "TempSurface = " << TempSurface << endl;
		cout << "IMG_GetError() = " << IMG_GetError() << endl << endl << endl;
		TempSurface = NULL;
#endif
		return false;
	}
	m_GoArea.x = x; m_GoArea.y = y; m_GoArea.w = w; m_GoArea.h = h;
	return true;
}

bool CProcessBar::SetSliderImage(string ImagePath, int Width, int Height)
{
	if (m_Slider)
	{
		SDL_DestroyTexture(m_Slider);
		m_Slider = NULL;
	}
	SDL_Surface* TempSurface = IMG_Load(ImagePath.c_str());
	if (!TempSurface)
	{
#ifdef _SDL_DEBUG
		cout << "SDL_ProcessBar.cpp	CProcessBar	void CProcessBar::SetBorderImage(string ImagePath,SDL_Rect GoArea)" << endl;
		cout << "从文件加载表面失败!" << endl;
		cout << "ImagePath = " << ImagePath << endl;
		cout << "IMG_GetError() = " << IMG_GetError() << endl << endl << endl;
#endif
		return false;
	}

	if (m_BorderKeyOpen)
	{
		Uint32 Key = SDL_MapRGBA(TempSurface->format, m_SliderKey.r, m_SliderKey.g, m_SliderKey.b, m_SliderKey.a);
		SDL_SetColorKey(TempSurface, 1, Key);
	}

	m_Slider = SDL_CreateTextureFromSurface(m_Renderer, TempSurface);
	if (Width == -1)
	{
		m_SliderWidth = TempSurface->w;
	}
	else
	{
		m_SliderWidth = Width;
	}
	if (Height == -1)
	{
		m_SliderHeight = TempSurface->h;
	}
	else
	{
		m_SliderHeight = Width;
	}
	SDL_FreeSurface(TempSurface);
	if (!m_Slider)
	{
#ifdef _SDL_DEBUG
		cout << "SDL_ProcessBar.cpp	CProcessBar	bool CProcessBar::SetBorderImage(string ImagePath,SDl_Rect GoArea)" << endl;
		cout << "当前无法加载边界图片！" << endl;
		cout << "ImagePath = " << ImagePath << endl;
		cout << "m_Renderer = " << m_Renderer << endl;
		cout << "TempSurface = " << TempSurface << endl;
		cout << "IMG_GetError() = " << IMG_GetError() << endl << endl << endl;
		TempSurface = NULL;
#endif
		return false;
	}
	return true;
}
