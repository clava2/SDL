#ifndef SDL_LINE_H
#define SDL_LINE_H

#define _SDL_DEBUG

#include <SDL2/SDL.h>
#include <vector>

using std::vector;

#ifdef _SDL_DEBUG
#include <iostream>

using std::cout;
using std::endl;
#endif

#pragma comment(lib,"SDL2.lib")

class CLine
{
private:
	vector<SDL_Point> m_Points;															//构成直线的点

	SDL_Color m_Color;																			//画线的颜色

	bool m_Dragging;																			//是否在拖动

	int m_Width;																					//线宽

public:
//构造函数与析构函数块

	/**构造函数
	*无参数
	*无返回值
	*测试标记									:0
	*/
	CLine();

	/**析构函数
	*无参数
	*无返回值
	*测试标记									:0
	*/
	~CLine();

//变量控制块

	/**向曲线中添加点
	*参数SDL_Point point						:想要添加的点
	*无返回值
	*测试标记											:0
	*/
	void AddPoint(SDL_Point point)
	{
		m_Points.push_back(point);
	}

	/**设置线的颜色
	*参数SDL_Color color						:线的颜色
	*无返回值
	*测试标记											:0
	*/
	void SetColor(SDL_Color color)
	{
		m_Color = color;
	}

	/**设置线宽
	*参数int Width									:线的宽度
	*无返回值
	*测试标记											:0
	*/
	void SetWidth(int Width)
	{
		m_Width = Width;
	}

//绘图块

	/**绘制曲线
	*参数SDL_Renderer* Renderer			:渲染器
	*无返回值
	*/
	void Render(SDL_Renderer* Renderer);
};

#endif
