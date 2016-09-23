/*****************************************************************
****类名：CButton											******
****相关文件				:SDL_Button.h,SDL_Button.cpp	******
****功能：构造一个按钮										******
****函数用途：												******
****最后构建日期			:2016年9月9日14:24:07			******
****版本号					:ver 0.1						******
****构建人					:郑聪							******
****														******
****														******
****														******
****														******
****														******
******************************************************************/


									//成员函数说明注释位置标记
														//变量及其他说明位置标记



#ifndef SDL_BUTTON_H
#define SDL_BUTTON_H

#define _SDL_DEBUG										//调试标记

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <SDL2/SDL_Image.h>
#include <SDL2/SDL_ttf.h>


#ifdef _SDL_DEBUG
#include <iostream>										//调试用头文件
using std::string;
using std::cout;
using std::endl;
#endif


const int TEXT_HEIGHT_RATE = 75;						//在按钮上显示文字时，文字所占按钮总高度的百分比
const int TEXT_WIDTH_RATE = 75;							//在按钮上显示文字时，文字所占按钮总高度的百分比


enum BUTTON_STATE
{
	BUTTON_OUT,
	BUTTON_IN,
	BUTTON_DOWN,
	BUTTON_DISABLED,
	BUTTON_STATE_ALL,
	BUTTON_UP = 5								//此值仅用于回调函数中
};

enum ALIGN_STATE
{
	ALIGN_OVER,
	ALIGN_LEFT,
	ALIGN_RIGHT,
	ALIGN_TOP,
	ALIGN_BOTTOM
};

class CButton
{

private:

	//状态图像
	SDL_Texture* m_ButtonImage[BUTTON_STATE_ALL];		//按钮各个状态的图片

	//回掉函数
	typedef void(*SDL_ButtonCallBack)(void* param, void* Result);

	SDL_ButtonCallBack m_CallBack[BUTTON_STATE_ALL+1];			//回调函数，由于图片不存在弹起时的图片，所以该数字比图片的大一。

	void* m_Param[BUTTON_STATE_ALL+1];					//各种函数的参数
	void* m_Result[BUTTON_STATE_ALL+1];					//各种函数的输出结果

	int m_DefaultWidth[BUTTON_STATE_ALL];				//图片默认宽度
	int m_DefaultHeight[BUTTON_STATE_ALL];				//图片默认高度

	//文字
	string m_ButtonText;								//按钮上显示的文字
	SDL_Texture* m_TextTexture;							//文字纹理
	SDL_Rect m_TextArea;								//文字纹理显示的位置的位置
	TTF_Font* m_TextFont;								//文字所用的字体
	//ALIGN_STATE m_AlignState;							//按钮文字的显示状态
	string m_FontPath;									//渲染文字是使用的字体的路径
	int m_FontSize;										//渲染文字时使用的字体大小
	SDL_Color m_TextColor;								//文字的颜色
	int m_TextWidth;									//文字纹理的宽度
	int m_TextHeight;									//文字纹理的高度

	//状态参数
	SDL_Rect m_ButtonArea;							    //储存按钮显示的区域
	BUTTON_STATE m_ButtonState;							//储存按钮当前状态
	Uint32 m_Key;										//储存于按钮作用相同的键盘按键
	int m_WindowWidth;									//窗口宽度
	int m_WindowHeight;									//窗口高度

	//外部相关
	SDL_Renderer* m_Renderer;
	SDL_Window* m_Window;

public:

	/*
	*构造函数1
	*参数SDL_Window* Window = NULL	:按钮将会在那个窗口渲染
	*参数string String				:按钮上将会显示的文字
	*无返回值
	*说明							:以最简单的方式构造一个按钮
	*/
	CButton(SDL_Window* Window = NULL, string String = "Button");

	/*
	*析构函数
	*无参数
	*无返回值
	*说明							:此函数将会释放掉所有图片占用的内存，但是不会释放窗口和渲染器
	*/
	~CButton();

	/*
	*渲染按钮
	*
	*/
	void Render();

	void SetWindow(SDL_Window* Window)
	{
		m_Window = Window;
		m_Renderer = SDL_GetRenderer(m_Window);
		if (!m_Renderer)
		{
#ifdef _SDL_DEBUG
			cout << "SDL_Button.h	CButton	void SetWindow(SDL_Window* Window)	"
				"从窗口获得渲染器失败，请检查传入的窗口指针是否合法!" << endl << endl << endl;
#endif
			return;
		}
	}

	/*
	*处理鼠标单击事件
	*参数const SDL_Event& Event		:鼠标在屏幕上单击的位置
	*返回值							:如果该点再按钮所在的区域内部，返回true,否则返回false;
	*说明							:
	*/
	bool HandleEvent(const SDL_Event& Event);

	/*
	*设置按钮的位置
	*参数int x						:新位置左上角的横坐标
	*参数int y						:新位置左上角的纵坐标
	*无返回值
	*/
	void Locate(int x, int y);

	/*
	*设置按钮的位置
	*参数SDL_Point Position			:新位置左上角的位置
	*无返回值
	*/
	void Locate(SDL_Point Position);

	/*
	*设置按钮的大小
	*参数int Width					:按钮的新宽度,-1使用原始大小
	*参数int Height					:按钮的新高度，-1使用原始大小
	*/
	void SetSize(int Width, int Height);

	/*
	*为按钮的某个状态设置图片
	*参数BUTTON_STATE State			:被设置的状态
	*参数string Path				:图片的路径
	*返回值							:成功返回true,否则返回false;
	*/
	bool SetImage(BUTTON_STATE State,string Path);

	/*
	*设置函数的参数和返回值指针
	*参数BUTTON_STATE State			:当按钮进入此状态时，会调用此函数设置回调函数
	*参数SDL_ButtonCallBack CallBackFunction	:回调函数，函数格式为void (*p)(void* Param,void* Result);
	*参数void* pParam = NULL		:回调函数调用时，传入函数的参数
	*参数void* pResult = NULL		:回调函数调用时，通过此指针传出结果。
	*说明							:请自行设计函数传入参数和返回值的格式
	*/
	void SetFunction(BUTTON_STATE State, SDL_ButtonCallBack CallBackFunction, void* pParam = NULL, void* pResult = NULL);

	/*
	*设置按钮文字
	*参数string Text				:被设置的文字
	*参数string FontPath			:字体路径
	*参数int Size					:字体的大小
	*参数ALIGN_STATE Align			:字体的显示状态
	*返回值							:成功返回true，否则返回false
	*说明
	*/
	bool SetText(string Text, string FontPath = "", int Size = -1,ALIGN_STATE Align = ALIGN_OVER);

	/*
	*强制更改按钮上文字显示区域
	*参数SDL_Rect TextArea		:指定的区域
	*无返回值
	*说明						:此函数在SetText函数之后调用
	*/
	void SetTextArea(SDL_Rect TextArea)
	{
		m_TextArea = TextArea;
	}
	
	/*
	*强制更改按钮上文字显示区域
	*参数int x = -1				:指定区域的X坐标，-1表示沿用原X坐标
	*参数int y = -1				:指定区域的Y坐标，-1表示沿用原Y坐标
	*参数int Width = -1			:指定区域的宽度,-1表示沿用原宽度
	*参数int Height = -1		:指定区域的高度，-1表示沿用原宽度
	*无返回值
	*说明						:此函数在SetText函数之后调用
	*/
	void SetTextArea(int x, int y, int Width, int Height)
	{
		if (x != -1)
		{
			m_TextArea.x = x;
		}
		if (y != -1)
		{
			m_TextArea.y = y;
		}
		if (Width != -1)
		{
			m_TextArea.w = Width;
		}
		if (Height != -1)
		{
			m_TextArea.h = Height;
		}
	}

	/*
	*设置与按钮功能相同的按钮
	*参数Uint32 Key					:按钮标号
	*无返回值
	*/
	void SetKey(Uint32 Key)
	{
		m_Key = Key;
	}

	/*
	*强制改变当前按钮的状态
	*参数BUTTON_STATE State			:需要改变到的状态
	*/
	void ChangeState(BUTTON_STATE State);
};

#endif