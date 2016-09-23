#ifndef SDL_PARTICLE_H
#define SDL_PARTICLE_H

#define _SDL_DEBUG

#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <time.h>

using std::cout;
using std::endl;
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
};

class CParticle
{
public:
	CParticle(SDL_Window* Window = NULL,int x = 0, int y = 0);

	/**构造函数
	*/

	void Render();

	/**渲染函数
	*/

	void HandleEvent(SDL_Event& e);

	/**处理事件
	*/

	void SetBorder(int Width, int Height);

	/**设置点运动的边界
	*/

	void LoadMedia();

	/**加载图片等媒体
	*/

	void SetWindow(SDL_Window* Window)
	{
		m_Window = Window;
		m_Renderer = SDL_GetRenderer(m_Window);
		SDL_GetWindowSize(m_Window, &m_ScreenWidth, &m_ScreenHeight);
		cout << m_Renderer << endl;
	}

	/**设置窗口
	*/

	void Move();

	/**移动黑点
	*/

private:
	int m_XPos;										//横坐标
	int m_YPos;										//纵坐标
	int m_ScreenWidth;								//屏幕宽度；
	int m_ScreenHeight;								//屏幕高度；
	int m_DotWidth;									//点的宽度；
	int m_DotHeight;								//点的高度；
	int m_ParticleWidth;							//粒子的宽度；
	int m_ParticleHeight;							//粒子的高度；
	vector<Single> m_All;							//保存粒子的相关信息

	int m_Time;										//保存时间；
	int m_Count;									//粒子的个数；

	int m_XDirection;								//黑点移动的X方向；
	int m_YDirection;								//黑点移动的Y方向；

	SDL_Texture* m_Particles[PARTICLE_ALL];			//粒子效果；
	SDL_Texture* m_Dot;								//点
	SDL_Window* m_Window;							//图像依附的窗口；
	SDL_Renderer* m_Renderer;						//该窗口的渲染器；
};

#endif
