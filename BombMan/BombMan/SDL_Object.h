#ifndef SDL_OBJECT_H
#define SDL_OBJECT_H

#include "SDL_CommonInclude.h"
#include "SDL_Timer.h"
#include "SDL_Map.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <vector>

using std::string;
using std::vector;

#ifdef _SDL_DEBUG
#include <iostream>

using std::cout;
using std::endl;

#endif

class CObject
{
protected:
//基本信息
	SDL_Rect m_Area;															//保存物体的位置信息,其中坐标为绝对坐标，即相对于地图而言的坐标；
	SDL_Rect m_RealArea;														//保存物体的位置信息，其中坐标为相对坐标，即相对于窗口而言的坐标；

//绘图相关
	SDL_Window* m_Window;												//图像依附的窗口；
	SDL_Renderer* m_Renderer;											//该窗口的渲染器；

	SDL_Rect m_SourceRect;													//绘图时的源矩形；
	
	SDL_Texture* m_Image;													//物体的图像；
	SDL_Rect m_ImageInfo;													//储存瓦块的宽度和高度；

	int m_LastDraw;																//储存上次绘制的图形序号；
	vector< vector<SDL_Point> > m_Orders;						//储存每种状态图形的瓦块位置；

	int m_ChangeInternal;														//储存物体渲染不同图像的间隔时间；
	Uint32 m_LastChangeTime;												//储存上次转换图像的时间点；

//其他信息

	int m_XDirection;																//物体移动的X方向；
	int m_YDirection;																//物体移动的Y方向；

	bool m_Listening;															//物体当前是否监听事件；

	int  m_State;																		//物体当前状态;

	CTimer m_Timer;																//主时钟，用来计算移动路程；

	int m_MoveSpeed;															//物体移动速度的倒数，数值上表示物体移动一个像素点所用的时间；
	Uint32 m_LastMoveTime;												//储存上次移动的时间点；

	Mix_Music* m_DieSound;												//储存物体被销毁是的声音；

public:

//构造函数与析构函数块

	/**构造函数
	*参数SDL_Window* Window				:物体所依附的窗口
	*参数int x												:物体起始X坐标
	*参数int y												:物体起始Y坐标
	*测试标记												:未测试
	*/
	CObject(SDL_Window* Window = NULL,int AllState = 1, int x = 0, int y = 0,int Speed = 5);

	/**析构函数
	*测试标记												:未测试
	*/
	~CObject();

//绘图函数及消息处理函数

	void Render();

	bool HandleEvent(SDL_Event& e);

//变量状态设置函数

	bool Init(SDL_Window* Window = NULL, int x = 0, int y = 0,int Speed = 5);

	bool LoadMedia(string ImagePath,string SoundPath = "");

	void SetCamera(SDL_Rect* Camera);

	void SetWindow(SDL_Window* Window);

	void Move(CMap& Map);

	void SetPlayOrder(int StateIndex, SDL_Point* Order, int Length);

	void SetTile(int Row, int Queue);

	void SetStateAmount(int Amount);

	void Die();

	void Revive()
	{
		if (m_State == (m_Orders.size() - 1))
		{
			m_State = 0;
			m_LastDraw = 0;
			m_Listening = true;
		}
	}

	void Stop()
	{
		m_XDirection = 0;
		m_YDirection = 0;
	}

	void SetSpeed(int Speed)
	{
		m_MoveSpeed = Speed;
	}

	SDL_Rect GetArea()
	{
		return m_Area;
	}

	SDL_Rect GetRealArea()
	{
		return m_RealArea;
	}
};


#endif