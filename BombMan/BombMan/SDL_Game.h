#ifndef SDL_GAME_H
#define SDL_GAME_H

#include <SDL2/SDL.h>
#include <string>

#include "SDL_Map.h"
#include "SDL_Object.h"
#include "SDL_Timer.h"
#include "SDL_CommonInclude.h"

using std::string;

class CGame
{
private:
	SDL_Window* m_Window;																			//主窗口指针
	SDL_Renderer* m_Renderer;																		//主窗口的渲染器指针

	SDL_Event m_Event;																						//主事件队列
	bool m_QuitGame;																						//退出整个游戏
	bool m_Quit;																								//退出当前内层时间处理循环

	CObject m_Player;																						//主要人物
	CMap m_MainMap;																						//主要地图
	CTimer m_MainTimer;																					//主时钟

	bool m_ReDraw;																							//判断是否重绘窗口

public:

//构造函数与析构函数块


	/**构造函数
	*本构造函数只构造基本类型，并不创建窗口
	*/
	CGame();

	/**析构函数
	*销毁窗口和渲染器等
	*/
	~CGame();

//媒体与渲染块

	/**初始化函数
	*参数string Tile							:主窗口的标题
	*参数int X										:主窗口的X坐标，可以是数值或者以下参数中的一个或几个
	*			SDL_WINDOWPOS_UNDEFINED		:未定义位置
	*			SDL_WINDOWPOS_CENTERED		:屏幕中心
	*参数int Y										:主窗口的Y坐标
	*参数int Width								:主窗口的宽度
	*参数int Height							:主窗口的高度
	*参数int Flag								:创建窗口的模式，可以为以下中的某个或某几个：
	*			SDL_WINDOW_FULLSCREEN					:创建全屏窗口
	*			SDL_WINDOW_FULLSCREEN_DESKTOP	:以当前桌面的像素大小为窗口大小创建窗口
	*			SDL_WINDOW_OPENGL							:创建可用于OpenGL的窗口
	*			SDL_WINDOW_HIDDEN							:创建窗口时，窗口不可见
	*			SDL_WINDOW_BORDERLESS					:创建没有边框的窗口
	*			SDL_WINDOW_RESIZABLE						:创建可调节大小的窗口
	*			SDL_WINDOW_MINIMIZED						:创建窗口时，窗口已最小化
	*			SDL_WINDOW_MAXIMIZED					:创建窗口时，窗口已最大化
	*			SDL_WINDOW_INPUT_GRABBED			:创建窗口时，输入设备聚焦于该窗口
	*			SDL_WINDOW_ALLOW_HIGHDPI			:创建高精度像素坐标的窗口
	*/
	bool Init(string Title = "", int X = SDL_WINDOWPOS_CENTERED, int Y = SDL_WINDOWPOS_CENTERED, int Width = SCREEN_WIDTH, int Height = SCREEN_HEIGHT, int Flag = SDL_WINDOW_SHOWN);

	/**加载媒体
	*返回值												:加载成功返回true,否则返回false;
	*/
	bool LoadMedia();

	/**主渲染函数
	*/
	void Render();


//事件处理块

	/**事件处理循环
	*/
	void HandleEventLoop();

//销毁函数块

	/**销毁窗口，渲染器等
	*/
	void Free();

//逻辑判断块

	/**判断角色是否死亡
	*返回值								:如果角色死亡，返回true,否则返回false;
	*/
	bool CheckDie();

	/**判断游戏是否结束
	*返回值								:如果游戏应该结束，返回true,否则返回false
	*/
	bool CheckEnd();

//相关页面块

	/**角色死亡时的页面
	*/
	void DiePage();

	/**游戏结束时的页面
	*/
	void EndPage();

	/**游戏起始页
	*/
	void BeginPage();
	
};

#endif