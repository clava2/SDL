#include "SDL_Button.h"

CButton::CButton(SDL_Window* Window,string String)
{
	m_ButtonArea = { 0,0,100,100 };
	m_FontPath = "default_font.ttf";
	m_ButtonText = String;
	m_FontSize = m_ButtonArea.h;

	if (Window)
	{
		m_Window = Window;
		m_Renderer = SDL_GetRenderer(Window);
		SDL_GetWindowSize(m_Window, &m_WindowWidth, &m_WindowHeight);
		if (!m_Renderer)
		{
#ifdef _SDL_DEBUG
			cout << "SDL_Button.cpp	CButton	CButton::CButton(SDL_Window* Window,string String)"
				"获得窗口渲染器失败，请检查参数是否正确！" << endl << endl << endl;
#endif
		}
	}

	if (m_Renderer)
	{
		m_TextFont = TTF_OpenFont(m_FontPath.c_str(), m_FontSize);
		if (!m_TextFont)
		{
#ifdef _SDL_DEBUG
			cout << "SDL_Button.cpp	CButton	CButton::CButton(SDL_Window* Window,string String)" << endl;
			cout << "从文件加载字体失败！" << endl;
			cout << "m_FontPath = " << m_FontPath << endl;
			cout << "m_FontSize = " << m_FontSize << endl;
			cout << "m_TextFont = " << m_TextFont << endl << endl << endl;
#endif
			return;
		}
		SDL_Surface* TempSurface = TTF_RenderText_Solid(m_TextFont,m_ButtonText.c_str(),m_TextColor);

		if (!TempSurface)
		{
#ifdef _SDL_DEBUG
			cout << "SDL_Button.cpp	CButton	CButton::CButton(SDL_Window* Window,string String)" << endl;
			cout<<"加载文字表面失败!"<<endl;
			cout<<"m_FontPath = "<<m_FontPath<<endl;
			cout<<"m_TextFont = "<<m_TextFont<<endl;
			cout<<"TempSurface = "<<TempSurface<<endl<<endl<<endl;
#endif
			return;
		}
		m_TextTexture = SDL_CreateTextureFromSurface(m_Renderer,TempSurface);
		SDL_FreeSurface(TempSurface);
		TempSurface = NULL;
		
		if(!m_TextTexture)
		{
#ifdef _SDL_DEBUG
			cout<<"SDL_Button.cpp	CButton	CButton::CButton(SDL_Window* Window,string String)"<<endl;
			cout<<"从表面产生纹理失败!"<<endl;
			cout<<"m_TempSurface = "<<TempSurface<<endl;
			cout<<"m_ButtonText = "<<m_ButtonText<<endl<<endl<<endl;
#endif			
			return;
		}
		m_TextWidth = TempSurface->w;
		m_TextHeight = TempSurface->h;
	}
}



bool CButton::HandleEvent(const SDL_Event& event)
{
	if (m_ButtonState == BUTTON_DISABLED)
	{
		return false;
	}
	bool Redraw = false;
	switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
	{
		if ((event.button.x <= (m_ButtonArea.x + m_ButtonArea.w)) && (event.button.x >= m_ButtonArea.x) && (event.button.y >= m_ButtonArea.y) && (event.button.y <= m_ButtonArea.y + m_ButtonArea.h))
		{
#ifdef _SDL_DEBUG
			cout<<"SDL_Button.cpp	CButton	bool CButton::HandleEvent(const SDL_Event&event)"<<endl;
			cout<<"检测到按钮按下了！"<<endl<<endl<<endl;
#endif
			Redraw = true;
			m_ButtonState = BUTTON_DOWN;
			if (m_CallBack[BUTTON_DOWN])
			{
				m_CallBack[BUTTON_DOWN](m_Param[BUTTON_DOWN], m_Result[BUTTON_DOWN]);
			}
		}
		break;
	}
	case SDL_KEYDOWN:
	{
		if ((event.key.keysym.sym == m_Key))
		{
#ifdef _SDL_DEBUG
			cout<<"SDL_Button.cpp	CButton	bool CButton::HandleEvent(const SDL_Event&event)"<<endl;
			cout<<"按钮对应的键盘键按下！"<<endl<<endl<<endl;
#endif
			Redraw = true;
			m_ButtonState = BUTTON_DOWN;
			if (m_CallBack[BUTTON_DOWN])
			{
				m_CallBack[BUTTON_DOWN](m_Param[BUTTON_DOWN], m_Result[BUTTON_DOWN]);
			}
		}
		break;
	}
	case SDL_FINGERDOWN:
	{
		if (((event.tfinger.x)*m_WindowWidth <= (m_ButtonArea.x + m_ButtonArea.w)) && ((event.tfinger).x*m_WindowWidth) >= m_ButtonArea.x && ((event.tfinger.y*m_WindowHeight) >= m_ButtonArea.y && ((event.tfinger.y*m_WindowHeight) <= (m_ButtonArea.y + m_ButtonArea.h))))
		{
#ifdef _SDL_DEBUG
			cout<<"SDL_Button.cpp	CButton	bool CButton::HandleEvent(const SDL_Event&event)"<<endl;
			cout<<"手指触摸！"<<endl<<endl<<endl;
#endif
			Redraw = true;
			m_ButtonState = BUTTON_DOWN;
			Redraw = true;
			if (m_CallBack[BUTTON_DOWN])
			{
				m_CallBack[BUTTON_DOWN](m_Param[BUTTON_DOWN], m_Result[BUTTON_DOWN]);
			}
		}
		break;
	}
	case SDL_MOUSEBUTTONUP:
	{
		if ((event.button.x <= (m_ButtonArea.x + m_ButtonArea.w)) && (event.button.x >= m_ButtonArea.x) && (event.button.y >= m_ButtonArea.y) && (event.button.y <= m_ButtonArea.y + m_ButtonArea.h))
		{
#ifdef _SDL_DEBUG
			cout<<"SDL_Button.cpp	CButton	bool CButton::HandleEvent(const SDL_Event&event)"<<endl;
			cout<<"鼠标弹起，按钮弹起!"<<endl<<endl<<endl;
#endif
			m_ButtonState = BUTTON_IN;
			Redraw = true;
			if (m_CallBack[BUTTON_UP])
			{
				m_CallBack[BUTTON_UP](m_Param[BUTTON_IN], m_Result[BUTTON_IN]);
			}
		}
		break;
	}
	case SDL_KEYUP:
	{
		if ((event.key.keysym.sym == m_Key))
		{
#ifdef _SDL_DEBUG
			cout<<"SDL_Button.cpp	CButton	bool CButton::HandleEvent(const SDL_Event&event)"<<endl;
			cout<<"键盘按键弹起，按钮弹起!"<<endl<<endl<<endl;
#endif
			m_ButtonState = BUTTON_OUT;
			Redraw = true;
			if (m_CallBack[BUTTON_UP])
			{
				m_CallBack[BUTTON_UP](m_Param[BUTTON_OUT], m_Result[BUTTON_OUT]);
			}
		}
		break;
	}
	case SDL_FINGERUP:
	{
		if (((event.tfinger.x)*m_WindowWidth <= (m_ButtonArea.x + m_ButtonArea.w)) && ((event.tfinger).x*m_WindowWidth) >= m_ButtonArea.x && ((event.tfinger.y*m_WindowHeight) >= m_ButtonArea.y && ((event.tfinger.y*m_WindowHeight) <= (m_ButtonArea.y + m_ButtonArea.h))))
		{
#ifdef _SDL_DEBUG
			cout<<"SDL_Button.cpp	CButton	bool CButton::HandleEvent(const SDL_Event&event)"<<endl;
			cout<<"手指抬起，按钮弹起！"<<endl<<endl<<endl;
#endif
			Redraw = true;
			m_ButtonState = BUTTON_IN;
			Redraw = true;
			if (m_CallBack[BUTTON_UP])
			{
				m_CallBack[BUTTON_UP](m_Param[BUTTON_IN], m_Result[BUTTON_IN]);
			}
		}
		break;
	}
	case SDL_MOUSEMOTION:
	{
		if((event.button.x <= (m_ButtonArea.x + m_ButtonArea.w)) && (event.button.x >= m_ButtonArea.x) && (event.button.y >= m_ButtonArea.y) && (event.button.y <= (m_ButtonArea.y + m_ButtonArea.h)))
		{
			if(m_ButtonState == BUTTON_OUT)
			{
				m_ButtonState = BUTTON_IN;
#ifdef _SDL_DEBUG
				cout<<"SDL_Button.cpp	CButton	void HandleEvent(const SDL_Event& event)"<<endl;
				cout<<"鼠标进入按钮!"<<endl<<endl<<endl;
#endif
				if (m_CallBack[BUTTON_IN])
				{
					m_CallBack[BUTTON_IN](m_Param[BUTTON_IN], m_Result[BUTTON_OUT]);
				}
			}
			break;
		}
		if((event.button.x >= (m_ButtonArea.x + m_ButtonArea.w)) || (event.button.x <= m_ButtonArea.x) || (event.button.y <= m_ButtonArea.y) || (event.button.y >= (m_ButtonArea.y + m_ButtonArea.h)))
		{
			if(m_ButtonState == BUTTON_IN)
			{
				m_ButtonState = BUTTON_OUT;
#ifdef _SDL_DEBUG
				cout<<"SDL_Button.cpp	CButton	void HandleEvent(const SDL_Event& event)"<<endl;
				cout<<"鼠标离开按钮!"<<endl<<endl<<endl;
#endif
				if (m_CallBack[BUTTON_OUT])
				{
					m_CallBack[BUTTON_OUT](m_Param[BUTTON_OUT], m_Result[BUTTON_OUT]);
				}
			}
			break;
		}
	}
	}
	return Redraw;
}

void CButton::Render()
{
	if (!m_Renderer)
	{
#ifdef _SDL_DEBUG
		cout << "SDL_Button.h	CButton	void Render()	"
			"错误，当前渲染没有没有设置或者获得失败，请检查参数是否正确！" << endl << endl << endl;
#endif
		return;
	}
	for (int i = 0; i != BUTTON_STATE_ALL; i++)
	{
		if (m_ButtonState == i)
		{
			if (m_Renderer)
			{
				SDL_RenderCopy(m_Renderer, m_ButtonImage[i], NULL, &m_ButtonArea);
				break;
			}
		}
	}
	if (m_TextTexture)
	{
		SDL_RenderCopy(m_Renderer, m_TextTexture, NULL, &m_TextArea);
	}
}

void CButton::Locate(int x,int y)
{
	m_ButtonArea.x = x;
	m_ButtonArea.y = y;
}

void CButton::Locate(SDL_Point Position)
{
	m_ButtonArea.x = Position.x;
	m_ButtonArea.y = Position.y;
}

void CButton::SetSize(int Width, int Height)
{
	if (Width == -1)
	{
		m_ButtonArea.w = m_DefaultWidth[m_ButtonState];
	}
	else
	{
		m_ButtonArea.w = Width;
	}
	if (Height == -1)
	{
		m_ButtonArea.h = m_DefaultHeight[m_ButtonState];
	}
	else
	{
		m_ButtonArea.h = Height;
	}
}

bool CButton::SetImage(BUTTON_STATE State,string Path)
{
	if((State>=BUTTON_STATE_ALL)&&(State<=0))
	{
#ifdef _SDL_DEBUG
		cout<<"SDL_Button.cpp	CButton	void CButton::LoadImage(BUTTON_STATE State,string Path)"<<endl;
		cout<<"设置按钮图片失败，因为状态超出边界！"<<endl;
		cout<<"状态应该在"<<0<<"~"<<BUTTON_STATE_ALL<<"之间"<<endl;
		cout<<"但是传入的参数是:"<<State<<endl<<endl<<endl;
#endif
		return false;
	}
	SDL_Surface* TempSurface = IMG_Load(Path.c_str());
	if(!TempSurface)
	{
#ifdef _SDL_DEBUG
		cout<<"SDL_Button.cpp	CButton	void CButton::LoadImage(BUTTON_STATE State,string Path)"<<endl;
		cout<<"从文件加载按钮纹理失败！"<<endl;
		cout<<"TempSurface = "<<TempSurface<<endl;
		cout<<"SDL_GetError()："<<SDL_GetError()<<endl;
		cout<<"Path = "<<Path<<endl<<endl<<endl;
#endif
		return false;
	}
	if (m_ButtonImage[State])
	{
		SDL_DestroyTexture(m_ButtonImage[State]);
		m_ButtonImage[State] = NULL;
	}
	m_ButtonImage[State] = SDL_CreateTextureFromSurface(m_Renderer,TempSurface);
	m_DefaultWidth[State] = TempSurface->w;
	m_DefaultHeight[State] = TempSurface->h;
	SDL_FreeSurface(TempSurface);
	TempSurface = NULL;
	if(!m_ButtonImage[State])
	{
#ifdef _SDL_DEBUG
		cout<<"SDL_Button.cpp	CButton	void CButton::LoadImage(BUTTON_STATE State,string Path)"<<endl;
		cout<<"从表面加载纹理失败！"<<endl;
		cout<<"TempSurface = "<<endl;
		cout<<"m_Renderer = "<<m_Renderer<<endl;
		cout<<"SDL_GetError():"<<SDL_GetError()<<endl<<endl<<endl;
#endif
		return false;
	}
	return true;
}

void CButton::SetFunction(BUTTON_STATE State, SDL_ButtonCallBack Function, void* Param, void* Result)
{
	m_CallBack[State] = Function;
	m_Param[State] = Param;
	m_Result[State] = Result;
}

bool CButton::SetText(string Text,string FontPath,int Size,ALIGN_STATE Align)
{
	if (Size == -1)
	{
		Size = m_ButtonArea.h;
	}
	if (m_FontPath != "")
	{
		if (m_TextFont)
		{
			TTF_CloseFont(m_TextFont);
			m_TextFont = NULL;
		}
		m_TextFont = TTF_OpenFont(FontPath.c_str(), Size);
	}
	if(!m_TextFont)
	{
#ifdef _SDL_DEBUG
		cout<<"SDL_Button.cpp	CButton	bool CButton::SetText(string Text,string FontPath,int Size,ALIGN_STATE Align)"<<endl;
		cout<<"打开字体失败！"<<endl;
		cout<<"FontPath = "<<FontPath<<endl;
		cout<<"Size = "<<Size<<endl;
		cout<<"SDL_GetError() = "<<SDL_GetError()<<endl<<endl<<endl;
#endif
		return false;
	}
	SDL_Surface* TempSurface = TTF_RenderUTF8_Solid(m_TextFont,Text.c_str(),m_TextColor);
	if(!TempSurface)
	{
#ifdef _SDL_DEBUG
		cout<<"SDL_Button.cpp	CButton	bool CButton::SetText(string Text,string FontPath,int Size,ALIGN_STATE Align)"<<endl;
		cout<<"渲染文字表面失败！"<<endl;
		cout<<"TextFont = "<<m_TextFont<<endl;
		cout<<"Text = "<<Text<<endl;
		cout<<"SDL_GetError() = "<<SDL_GetError()<<endl<<endl<<endl;
#endif
		return false;
	}
	if (m_TextTexture)
	{
		SDL_DestroyTexture(m_TextTexture);
		m_TextTexture = NULL;
	}
	m_TextTexture = SDL_CreateTextureFromSurface(m_Renderer,TempSurface);
	SDL_FreeSurface(TempSurface);
	TempSurface = NULL;
	if(!m_TextTexture)
	{
#ifdef _SDL_DEBUG
		cout<<"SDL_Button.cpp	CButton	bool CButton::SetText(string Text,string FontPath,int Size,ALIGN_STATE Align)"<<endl;
		cout<<"从文字表面渲染纹理失败！"<<endl;
		cout<<"m_Renderer = "<<m_Renderer<<endl;
		cout<<"TempSurface = "<<TempSurface<<endl;
		cout<<"m_TextTexture = "<<m_TextTexture<<endl;
		cout<<"SDL_GetError() = "<<SDL_GetError()<<endl<<endl<<endl;
#endif
		return false;
	}

	switch (Align)
	{
	case ALIGN_BOTTOM:
	{
		m_TextArea = { m_ButtonArea.x + (100 - TEXT_WIDTH_RATE) * m_ButtonArea.w / 200,
			m_ButtonArea.y + m_ButtonArea.h + (100 - TEXT_HEIGHT_RATE) * m_ButtonArea.h / 200,
			TEXT_WIDTH_RATE * m_ButtonArea.w / 100,
			TEXT_HEIGHT_RATE * m_ButtonArea.h / 100 };
		break;
	}
	case ALIGN_LEFT:
	{
		m_TextArea = { m_ButtonArea.x - m_ButtonArea.w + (100 - TEXT_WIDTH_RATE) * m_ButtonArea.w / 200,
			m_ButtonArea.y + (100 - TEXT_HEIGHT_RATE) * m_ButtonArea.h / 200,
			TEXT_WIDTH_RATE * m_ButtonArea.w / 100,
			TEXT_HEIGHT_RATE * m_ButtonArea.h / 100 };
		break;
	}
	case ALIGN_RIGHT:
	{
		m_TextArea = { m_ButtonArea.x + m_ButtonArea.w + (100 - TEXT_WIDTH_RATE) * m_ButtonArea.w / 200,
			m_ButtonArea.y + (100 - TEXT_HEIGHT_RATE) * m_ButtonArea.h / 200,
			TEXT_WIDTH_RATE * m_ButtonArea.w / 100,
			TEXT_HEIGHT_RATE * m_ButtonArea.h / 100 };
		break;
	}
	case ALIGN_TOP:
	{
		m_TextArea = { m_ButtonArea.x + (100 - TEXT_WIDTH_RATE) * m_ButtonArea.w / 200,
			m_ButtonArea.y - m_ButtonArea.h + (100 - TEXT_HEIGHT_RATE) * m_ButtonArea.h / 200,
			TEXT_WIDTH_RATE * m_ButtonArea.w / 100,
			TEXT_HEIGHT_RATE * m_ButtonArea.h / 100 };
		break;
	}
	case ALIGN_OVER:
	{
		m_TextArea = { m_ButtonArea.x + (100 - TEXT_WIDTH_RATE) * m_ButtonArea.w / 200,
			m_ButtonArea.y + (100 - TEXT_HEIGHT_RATE) * m_ButtonArea.h / 200,
			TEXT_WIDTH_RATE * m_ButtonArea.w / 100,
			TEXT_HEIGHT_RATE * m_ButtonArea.h / 100 };
		break;
	}
	}
}

void CButton::ChangeState(BUTTON_STATE State)
{
	m_ButtonState = State;
}

CButton::~CButton()
{
	for(int i = 0;i != BUTTON_STATE_ALL;i++)
	{
		if(m_ButtonImage[i])
		{
			SDL_DestroyTexture(m_ButtonImage[i]);
			m_ButtonImage[i] = NULL;
		}
	}

	if (m_TextTexture)
	{
		SDL_DestroyTexture(m_TextTexture);
		m_TextTexture = NULL;
	}


	SDL_DestroyTexture(m_TextTexture);
	TTF_CloseFont(m_TextFont);
}