#ifndef SDL_PROCESS_BAR_H
#define SDL_PROCESS_BAR_H

										//函数参数说明注释位置标记
																//成员变量注释标记

#include <SDL2/SDL.h>
#include <string>
#include <SDL2/SDL_image.h>

#define _SDL_DEBUG

#ifdef _SDL_DEBUG

#include <iostream>

using std::cout;
using std::endl;

#endif

using std::string;

class CProcessBar
{
private:

	typedef void (*SDL_ProcessBarCallBack)(void* Param, void* Result);

	int m_MaxLength;											//进度条的最大长度
	int m_CurrentPosition;										//进度条当前长度
	bool m_ShowPercent;											//进度条后面是否显示百分比
	SDL_Window* m_Window;										//进度条所在的窗口
	SDL_Renderer* m_Renderer;									//窗口渲染器
	bool m_Vertical;											//是否垂直显示进度条
	bool m_Direction;											//进度条的方向，对于水平进度条而言，为true时从左向右，
																//对于竖直进度条而言，为true时从下到上。

	SDL_Rect m_MainArea;										//进度条显示的区域
	SDL_Rect m_GoArea;											//进度条移动时的区域

	SDL_Texture* m_Border;										//进度条边界图像
	SDL_Color m_BorderKey;										//进度条边界的透明色
	bool m_BorderKeyOpen;										//透明色是否打开

	SDL_Texture* m_Slider;										//进度条游标的图像
	SDL_Color m_SliderKey;										//进度条滑块透明色
	bool m_SliderKeyOpen;										//进度条滑块透明色是否打开

	int m_SliderWidth;											//滑动条的宽度
	int m_SliderHeight;											//滑动条的高度

	SDL_Color m_Color;											//进度条移动时，填充的颜色

	SDL_ProcessBarCallBack m_CallBack;							//进度条数值到达最大数值后，调用该函数
	bool m_Called;												//函数是否被调用过

	void* m_Param;												//回调函数调用时使用的参数
	void* m_Result;												//回调函数调用时，使用此指针传回返回值

public:
	
	/*
	*构造函数
	*参数SDL_Window* Window = NULL		:进度条所在窗口的指针
	*参数int MaxLength = 100			:进度条最大长度
	*无返回值
	*/
	CProcessBar(SDL_Window* Window = NULL, int MaxLength = 100);

	/*
	*析构函数
	*无参数
	*无返回值
	*/
	~CProcessBar();

	/*
	*设置进度条的长度
	*参数int Length						:进度条的长度
	*无返回值
	*/
	void SetPosition(int Position = 1);

	/*
	*绘制进度条
	*无参数
	*无返回值
	*/
	void Render();

	/*
	*设置颜色
	*参数SDL_Color Color				:设置进度条已到达区域的颜色
	*无返回值
	*/
	void SetColor(SDL_Color Color)
	{
		m_Color = Color;
	}

	/*
	*设置颜色
	*参数int r							:进度条已到达区域颜色的r值
	*参数int g							:进度条已到达区域颜色的g值
	*参数int b							:进度条已到达区域颜色的b值
	*参数int a							:进度条已到达区域颜色的a值
	*无返回值
	*/
	void SetColor(int r, int g, int b, int a)
	{
		m_Color.r = r;
		m_Color.g = g;
		m_Color.b = b;
		m_Color.a = a;
	}

	/*
	*设置当前进度条的位置
	*参数SDL_Point Position				:进度条的位置
	*无返回值
	*/
	void Locate(SDL_Point Position);

	/*
	*设置当前进度条的位置
	*参数int x							:进度条的X坐标
	*参数int y							:进度条的Y坐标
	*无返回值
	*/
	void Locate(int x, int y);

	/*
	*设置进度条的总长度
	*参数int MaxLength					:进度条的总长度
	*无返回值
	*说明								:此处总长度指数值总长度，而不是进度条的像素长度
	*/
	void SetMaxLength(int MaxLength)
	{
		m_MaxLength = MaxLength;
	}

	/*
	*让进度条的长度增加某个长度
	*参数int Offset						:偏移量，为负数的较少
	*无返回值
	*说明								:偏移量是指从当前位置开始偏移
	*/
	void Offset(int Offset);

	/*
	*设置进度条所在的窗口
	*参数SDL_Window* Window				:窗口指针
	*无返回值
	*/
	void SetWindow(SDL_Window* Window);

	/*
	*设置进度条的边界样式
	*参数string ImagePath				:边界图片
	*参数SDL_Rect GoArea				:进度条进度发生变化时的填充区域,此区域坐标是指相对与图像的坐标
	*返回值bool success					:如果设置成功返回true,否则返回false;
	*注意								:一旦调用该函数，进度条大小将会自动设置未边界图片的原始大小。
	*/
	bool SetBorderImage(string ImagePath,SDL_Rect GoArea);

	/*
	*设置静读条的边界样式
	*参数string ImagePath				:边界图片
	*参数int x							:相对图片而言，进度条运动区域的X坐标
	*参数int y							:相对图片而言，进度条运动区域的Y左边
	*参数int w							:相对图片而言，进度条运动区域的宽度
	*参数int h							:相对图片而言，进度条运动区域的高度
	*返回值bool success					:成功返回true,否则返回false;
	*注意								:一旦调用该函数，进度条大小将会自动设置未边界图片的原始大小。
	*/
	bool SetBorderImage(string ImagePath, int x, int y, int w, int h);

	/*
	*设置当前进度条边界透明色
	*参数SDL_Color ColorKey				:进度条透明色
	*无返回值
	*注意								:只有在调用此函数后，透明色才会打开，
										 不提供默认背景色,此函数必须在设置边界图像只前调用
	*/
	void SetBorderKey(SDL_Color ColorKey)
	{

	}

	/*
	*设置当前进度条边界透明色
	*参数char r							:进度条透明色的红色分量
	*参数char g							:进度条透明色的绿色分量
	*参数char b							:进度条透明色的蓝色分量
	*参数char a							:进度条透明色的alpha分量
	*无返回值
	*注意								:只有在调用此函数后，透明色才会打开，
										 不提供默认背景色,此函数必须在设置边界图像只前调用
	*/
	void SetBorderKey(char r, char g, char b, char a)
	{
		m_BorderKeyOpen = true;
		m_BorderKey.r = r;
		m_BorderKey.g = g;
		m_BorderKey.b = b;
		m_BorderKey.a = a;
	}

	/*
	*设置进度条运动时，滑块样式
	*参数string ImagePath				:滑块演示对应的图片路径
	*参数int Width = -1					:滑块的宽度，-1表示原始大小
	*参数int Height = -1				:滑块的高度，-1表示原始大小
	*返回值bool success					:加载成功返回true,失败返回false
	*说明								
	*/
	bool SetSliderImage(string ImagePath, int Width = -1, int Height = -1);

	/*
	*设置进度条的透明色
	*参数SDL_Color ColorKey				:透明色
	*无返回值
	*注意								:只有在调用此函数后，透明色才会打开，
										 不提供默认背景色,此函数必须在设置边界图像只前调用
	*/
	void SetSliderColorKey(SDL_Color ColorKey)
	{
		m_SliderKeyOpen = true;
		m_SliderKey = ColorKey;
	}

	/*
	*设置进度条的透明色
	*参数char r							:滑块透明色的红色分量
	*参数char g							:滑块透明色的绿色分量
	*参数char b							:滑块透明色的蓝色分量
	*参数char a							:滑块透明色的alpha分量
	*无返回值
	*注意								:只有在调用此函数后，透明色才会打开，
	不提供默认背景色,此函数必须在设置边界图像只前调用
	*/
	void SetSliderColorKey(char r,char g,char b,char a)
	{
		m_SliderKeyOpen = true;
		m_SliderKey.r = r;
		m_SliderKey.g = g;
		m_SliderKey.b = b;
		m_SliderKey.a = a;
	}

	/*
	*设置进度条回调函数
	*参数SDL_ProcessBarCallBack Functin	:回调函数
	*参数void* Param = NULL				:调用回调函数时传入的参数
	*参数void* Result = NULL			:调用毁掉函数时，使用此指针传回结果
	*无返回值
	*说明
	*/
	void SetFunction(SDL_ProcessBarCallBack Function, void* Param = NULL, void* Result = NULL)
	{
		m_CallBack = Function;
		m_Param = Param;
		m_Result = Result;
	}

	/*
	*设置长度和宽度
	*参数int Width						:进度条的新宽度，-1表示保持不变
	*参数int Height						:进度条的新高度，-1表示保持不变
	*无返回值
	*说明								:如果在此函数之前设置过进度变化区域，它会自动变化，不必重新设置
	*/
	void SetSize(int Width, int Height)
	{
		m_GoArea.x = m_MainArea.x + (m_GoArea.x - m_MainArea.x)*Width / m_MainArea.w + 1;
		m_GoArea.y = m_MainArea.y + (m_GoArea.y - m_MainArea.y)*Height / m_MainArea.h + 1;
		m_GoArea.w = m_GoArea.w*Width / m_MainArea.w;
		m_GoArea.h = m_GoArea.h*Height / m_MainArea.h;

		m_MainArea.w = Width;
		m_MainArea.h = Height;
	}
};



#endif