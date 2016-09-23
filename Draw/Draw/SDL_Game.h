#ifndef CGAME_H
#define CGAME_H

#define _SDL_DEBUG

#include <string>
#include <SDL2/SDl.h>
#include "SDL_Line.h"

#ifdef _SDL_DEBUG

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

#endif

using std::string;


#pragma comment(lib,"SDL2main.lib")
#pragma comment(lib,"SDL2.lib")

namespace SDL
{
	class CGame
	{
	private:
		//窗口数据块
		int m_Width;																				//当前窗口的宽度
		int m_Height;																				//当前窗口的高度

		//游戏控制块
		bool m_Quit;																				//是否推出本局游戏
		bool m_QuitGame;																		//是否推出这个游戏

		//窗口和渲染器
		SDL_Window* m_Window;															//游戏的主要窗口
		SDL_Renderer* m_Renderer;														//窗口的渲染器

		//其他变量
		
		bool m_Redraw;																			//判断当前窗口是否需要重绘

		CLine m_Line;

		bool m_Dragging;

	public:
		//构造函数和析构函数

		/**构造函数
		*参数string Title = ""			:创建窗口时的标题，默认为空标题
		*参数int X = 100					:创建窗口时的横坐标，默认为100
		*参数int Y = 100					:创建窗口时的纵坐标，默认为100
		*参数int Width = 500			:创建窗口时的宽度，默认为500
		*参数int Height = 500			:创建窗口时的高度，默认为500
		*参数SDL_WindowFlags Flag = SDL_WINDOW_SHOWN	:创建窗口时的属性，默认以显示状态创建，可以为以下之一：
		*											SDL_WINDOW_ALLOW_HIGHDPI			:创建允许高DPI的窗口
		*											SDL_WINDOW_BORDERLESS					:创建无边框的窗口
		*											SDL_WINDOW_FOREIGN							:创建外部窗口
		*											SDL_WINDOW_FULLSCREEN					:以全屏模式创建窗口（真全屏，会减小屏幕的分辨率）
		*											SDL_WINDOW_FULLSCREEN_DESKTOP	:以全屏模式创建窗口（假全屏，不会减小屏幕分辨率）
		*											SDL_WINDOW_HIDDEN							:创建时隐藏窗口
		*											SDL_WINDOW_INPUT_FOCUS					:创建时输入聚焦
		*											SDL_WINDOW_INPUT_GRABBED			:创建时抓取输入
		*											SDL_WINDOW_MAXIMIZED					:创建时最大化窗口
		*											SDL_WINDOW_MINIMIZED						:创建时最小化窗口
		*											SDL_WINDOW_MOUSE_CAPTURE			:创建捕获鼠标
		*											SDL_WINDOW_OPENGL							:创建可用于OpenGL的窗口
		*											SDL_WINDOW_SHOWN							:创建时显示窗口
		*											SDL_WINDOW_RESIZABLE						:创建可调整大小的窗口
		*											SDL_WINDOW_MOUSE_FOCUS				:创建时鼠标聚焦于此窗口
		*无返回值
		*功能									:如果创建窗口成功，就将窗口指针指向窗口，并自动将渲染器指针指向该窗口对应的渲染器
		*副作用									:让窗口指针指向一个窗口，让渲染器指针指向窗口对应的渲染器
		*测试标记								:未测试
		*/
		CGame(string Title = "", int X = 100, int Y = 100, int Width = 500, int Height = 500, SDL_WindowFlags Flag = SDL_WINDOW_SHOWN);

		/**析构函数
		*无参数
		*无返回值
		*功能									:如果窗口指针不为空，就销毁窗口，如果渲染器指针不为空，就销毁渲染器
		*副作用									:销毁窗口，并让其指针指向空，销毁渲染器，并让其指针指向空
		*测试标记								:未测试
		*/
		~CGame();


		//开始前准备块

		/**初始化窗口函数
		*参数									:同构造函数
		*返回值									:创建成功返回true,一旦出现错误，返回false;
		*功能									:同构造函数
		*副作用									:同构造函数
		*测试标记								:未测试
		*/
		bool InitWindow(string title = "", int X = 0, int Y = 0, int Width = 100, int Height = 100, SDL_WindowFlags Flag = SDL_WINDOW_SHOWN);

		/**从文件加载媒体文件
		*无参数
		*返回值									:加载成功返回true,否则返回false;
		*功能									:从文件加载媒体,视具体情况而定
		*副作用									:视具体文件而定
		*测试标记								:未测试
		*/
		bool LoadMedia();


		//循环块

		/**事件处理循环
		*无参数
		*无返回值								:进入时间循环，只有当m_QuitGame和m_Quit同时为true时才推出
		*无返回值
		*功能									:循环处理时间，直至条件满足是退出循环
		*副作用									:占用一个程序的大多数时间
		*测试标记								:未测试
		*/
		void MainLoop();


		/**渲染背景专用函数
		*无参数
		*无返回值
		*功能									:渲染一桩图片或者其他作为背景
		*注意									:由于需要保证其做为背景，所以会在渲染的尾部暂停5毫秒
		*测试标记								:未测试
		*/
		void RenderBackground();


		/**在窗口中渲染
		*无参数
		*无返回值
		*功能									:在窗口中绘图
		*副作用									:绘图
		*测试标记								:未测试
		*/
		void Render();

		/**开始页
		*无参数
		*无返回值
		*功能									:进入起始页，直至时间达到，或者其他条件（是具体情况）
		*副作用									:视具体情况
		*测试标记								:未测试
		*/
		void BeginPage();

		/**角色死亡时进入的页面
		*无参数
		*无返回值
		*功能									:进入结束页面一段时间，时间到达后自动退出
		*副作用									:视具体情况
		*测试标记								:未测试
		*/
		void EndPage();

		/**当玩家选择暂停时的页面
		*无参数
		*无返回值
		*功能									:进入菜单页面，直至按下某个键或者点击某个按钮(视具体情况）
		*副作用									:是具体情况
		*测试标记								:未测试
		*/
		void Menu();

		/**判断当前游戏是否应该结束
		*无参数
		*返回值									:应该结束返回true,否则返回false
		*功能									:判断当前游戏是否该结束
		*副作用									:无
		*测试标记								:未测试
		*/
		bool CheckEnd() const;
	};

}

#endif