#ifndef SDL_OBJECT_H
#define SDL_OBJECT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "SDL_CommonInclude.h"
#include "SDL_Timer.h"
#include "SDL_Map.h"

using std::string;

#ifdef _SDL_DEBUG
#include <iostream>

using std::cout;
using std::endl;

#endif

enum OBJECT_STATE
{
	OBJECT_STATE_NORMAL,
	OBJECT_STATE_ALL
};

enum OBJECT_IMAGE
{
	OBJECT_IMAGE_NORMAL,
	OBJECT_IMAGE_ALL
};


class CObject
{
private:
//基本信息
	SDL_Rect m_Area;															//保存物体的位置信息,其中坐标为绝对坐标，即相对于地图而言的坐标；
	SDL_Rect m_RealArea;														//保存物体的位置信息，其中坐标为相对坐标，即相对于窗口而言的坐标；

//绘图相关
	SDL_Window* m_Window;												//图像依附的窗口；
	SDL_Renderer* m_Renderer;											//该窗口的渲染器；
	
	SDL_Texture* m_Image[OBJECT_IMAGE_ALL];					//物体的图像

//其他信息
	int m_XDirection;																//物体移动的X方向；
	int m_YDirection;																//物体移动的Y方向；

	OBJECT_STATE m_State;													//物体当前状态;

	CTimer m_Timer;																//主时钟，用来计算移动路程；

	int m_Speed;																		//物体移动速度的倒数，数值上表示物体移动一个像素点所用的时间；

public:

//构造函数与析构函数块

	/**构造函数
	*参数SDL_Window* Window				:物体所依附的窗口
	*参数int x												:物体起始X坐标
	*参数int y												:物体起始Y坐标
	*测试标记												:未测试
	*/
	CObject(SDL_Window* Window = NULL, int x = 0, int y = 0,int Speed = 5);

	/**析构函数
	*测试标记												:未测试
	*/
	~CObject();

//绘图函数及消息处理函数

	void Render();

	bool HandleEvent(SDL_Event& e);

//变量状态设置函数

	bool Init(SDL_Window* Window = NULL, int x = 0, int y = 0,int Speed = 5);

	bool LoadMedia();

	void SetCamera(SDL_Rect* Camera);

	void SetWindow(SDL_Window* Window);

	void Move(CMap& Map);

	void SetSpeed(int Speed)
	{
		m_Speed = Speed;
	}

};


#endif