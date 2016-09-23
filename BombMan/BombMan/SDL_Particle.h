#ifndef SDL_PARTICLE_H
#define SDL_PARTICLE_H


#include <SDL2/SDL.h>
#include <vector>
#include <time.h>

#include "SDL_CommonInclude.h"

#include "SDL_Map.h"
#include "SDL_Timer.h"

using std::vector;

enum PARTICLE_COLOR
{
	PARTICLE_GREEN,
	PARTICLE_RED,
	PARTICLE_BLUE,
	PARTICLE_WHITE,
	PARTICLE_ALL
};

struct Single
{
	int X, Y;
	long long Begin;
	PARTICLE_COLOR Type;
	int RealX;
	int RealY;
};

class CParticle
{
public:

//构造函数与析构函数块；

	/**构造函数
	*参数SDL_Window* Window		:物体依附的窗口；
	*参数int x										:物体的初始位置X坐标；
	*参数int y										:物体的初始位置Y坐标；
	*测试标记										:未测试；
	*/
	CParticle(SDL_Window* Window = NULL,int x = 0, int y = 0,int Speed = 20);

//渲染及时间处理块
	/**渲染函数
	*测试标记										:未测试；
	*/
	void Render();

	/**处理事件
	*测试标记										:未测试；
	*/
	bool HandleEvent(SDL_Event& e);

//内部变量加载块；
	/**加载图片等媒体
	*测试标记										:未测试；
	*/
	void LoadMedia();

	/**设置观察块
	*参数SDL_Rect& Camera				:观察块矩形的引用
	*测试标记										:未测试；
	*/
	void SetCamera(SDL_Rect* Camera);


	/**设置窗口
	*测试标记										:未测试；
	*/
	void SetWindow(SDL_Window* Window);

	/**移动黑点
	*测试标记										:未测试；
	*/
	void Move(CMap& Map);

	/**设置黑点移动的速度
	*参数int Speed								:物体移动的速度的倒数，其大小为物体每移动一个像素点所需要的时间,时间以毫秒计；
	*测试标记										:未测试
	*/
	void SetSpeed(int Speed)
	{
		m_Speed = Speed;
	}

private:
//关于物体
	SDL_Rect m_Area;															//保存物体的位置信息,其中坐标为绝对坐标，即相对于地图而言的坐标；

	SDL_Rect m_RealArea;														//保存物体的位置信息，其中坐标为相对坐标，即相对于窗口而言的坐标；

//关于粒子
	int m_ParticleWidth;														//粒子的宽度；
	int m_ParticleHeight;														//粒子的高度；
	vector<Single> m_All;														//保存粒子的相关信息

//图形相关
	SDL_Texture* m_Particles[PARTICLE_ALL];						//粒子效果；
	SDL_Texture* m_Dot;														//物体

	SDL_Window* m_Window;												//图像依附的窗口；
	SDL_Renderer* m_Renderer;											//该窗口的渲染器；

//其他信息

	int m_Time;																		//粒子保存时间；
	int m_Count;																	//粒子的个数；

	int m_XDirection;																//黑点移动的X方向；
	int m_YDirection;																//黑点移动的Y方向；

	int m_Speed;																	//黑点移动的速度的倒数，此值得意义为黑点每移动一个像素点所用的时间，时间以毫秒计；

	CTimer m_Timer;																//主时钟，记录已过的时间，用来计算物体移动的距离；
};

#endif
