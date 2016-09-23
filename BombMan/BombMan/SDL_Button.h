#ifndef SDL_BUTTON_H
#define SDL_BUTTON_H

#include "SDL_CommonInclude.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <string>


#ifdef _SDL_DEBUG
#include <iostream>
#endif


using std::string;
using std::cout;
using std::endl;

enum BUTTON_STATE
{
	BUTTON_STATE_UP,
	BUTTON_STATE_DOWN,
	BUTTON_STATE_OVER,
	BUTTON_STATE_DISABLE
};

class CButton
{
private:

	SDL_Window* m_Window;															//按钮所在窗口的指针
	SDL_Renderer* m_Renderer;														//按钮所在窗口的渲染器

	SDL_Texture* m_DownImage;														//按钮按下时的图片
	SDL_Texture* m_UpImage;															//按钮弹起是的图片
	SDL_Texture* m_DisableImage;													//按钮不可用是的图片
	SDL_Texture* m_Text;																	//按钮上显示的文字


	SDL_Rect m_Area;																	    //储存按钮显示的区域
	BUTTON_STATE m_State;															//按钮当前的状态

	Uint32 m_Key;																				//储存于按钮作用相同的键盘按键
	bool m_KeyOn;																			//控制键盘按钮是否可用


	void* m_DownResult;																	//指向按钮按下时处理函数的返回值
	void* m_UpResult;																		//指向按钮弹起是处理函数的返回值
	void* m_DownParam;																	//指向按钮按下处理函数参数的指针
	void* m_UpParam;																		//指向按钮弹起处理函数参数的指针
	void (*m_DownCallBack)(void* param, void* Result);					//按钮按下的消息处理函数
	void (*m_UpCallBack)(void * Param, void * Result);					//按钮抬起的消息处理函数


public:
	CButton(SDL_Window* Window = NULL,string String = "按钮",string down_path = "Button_Down.png", string up_path = "Button_Up.png", void (DownCallBack)(void* param, void* Result) = NULL, void (UpCallBack)(void* Param, void* Result) = NULL, void* DownParam = NULL, void* DownResult = NULL, void* UpParam = NULL, void* UpResult = NULL);

	~CButton();											
	void Render();

	void SetWindow(SDL_Window* Window);


	bool LoadMedia(string Text = "按钮", string DownPath = "Button_Down.png", string UpPath = "Button_Up.png");

	bool HandleEvent(SDL_Event *event);	

	void Locate(int x, int y);


	void SetSize(int Width, int Height);


};


#endif