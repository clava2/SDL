#ifndef SDL_MAP_H
#define SDL_MAP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <fstream>

#include "SDL_CommonInclude.h"

using std::string;
using std::ifstream;

#ifdef _SDL_DEBUG
#include <iostream>

using std::cout;
using std::endl;

#endif


const int TILE_WIDTH = 80;
const int TILE_HEIGHT = 80;

const int TILE_QUEUE = 4;
const int TILE_ROW = 3;

const int MAP_QUEUE = 20;
const int MAP_ROW = 10;

typedef struct SingleTile
{
	SDL_Rect m_Area;																//单个瓦片的区域
	SDL_Point m_Position;															//包含瓦片的在图片中的位置信息；
}SingleTile;

class CMap
{
private:

	SDL_Texture* m_AllSprites;													//储存源瓦片；
	SDL_Texture* m_Map;															//储存地图纹理；
	SDL_Rect m_SourceRects[TILE_ROW][TILE_QUEUE];			//储存纹理切块；
	SingleTile m_TargetRects[MAP_ROW][MAP_QUEUE];		//储存目标切块；
	SDL_Window* m_Window;													//窗口指针；
	SDL_Renderer* m_Renderer;												//窗口渲染器；
	bool m_Barry[TILE_ROW][TILE_QUEUE];								//障碍物设置；
	SDL_Rect m_Camera;															//观察块；

public:

//基本构造函数与析构函数区域:

	/**
	*构造函数，构造CMap类
	*参数SDL_Window* Window	:设置瓦片纹理的窗口；
	*参数string TilePath					:设置瓦片的文件路径；
	*测试标记									:已测试；
	*/
	CMap(SDL_Window* Window = NULL, string TilePath = "Tile_Default.png", string MapPath = "Map_Default.map");


	/*
	*析构函数
	*处理相关变量；
	*测试标记									:未测试
	*/
	~CMap();

//内部变量设置区域:

	/*设置障碍物
	*参数SDL_Point* Barry				:包含障碍物坐标信息的数对；
	*参数int i									:障碍物的个数:
	*测试标记									:未测试
	*/
	void SetBarry(SDL_Point* Barry, int i = 1);

	/**初始化对象，功能与构造函数相同
	*参数与构造函数相同
	*成功返回true；否则返回false；
	*/
	bool Init(SDL_Window* Window = NULL, string TilePath = "Tile_Default.png", string MapPath = "Map_Default.map");

	/**设置纹理的窗口
	*参数SDL_Window* Window	:窗口指针;
	*测试标记									:已测试；
	*/
	void SetWindow(SDL_Window* Window);

	/**从文件中加载瓦片
	*参数stirng TilePath					:瓦片文件路径；
	*返回值										:加载成功返回true；否则返回false；
	*测试标记									:已测试
	*/
	bool LoadTile(string TilePath);

	/**从文件中记载地图
	*参数string MapPath				:地图文件路径；
	*返回值										:加载成功返回true；否则返回false；
	*测试标记									:已测试；
	*/
	bool LoadMap(string MapPath);

	/**设置观察块
	*参数int Width							:观察块的高度；
	*参数int Height						:观察块的宽度；
	*参数SDL_Point DefaultPosition	:观察块的出事位置；
	*测试标记									:已测试；
	*/
	void SetCamera(int Width = SCREEN_WIDTH, int Height = SCREEN_HEIGHT, SDL_Point DefaultPosition = SDL_Point{ 0,0 });

//相关操作区域:

	/**检测是否碰墙
	*参数SDL_Rect& Object			:被移动的物体；
	*返回值										:没有碰墙返回true；否则返回false；
	*测试标记									:未测试
	*/
	bool TouchWall(const SDL_Rect& Object,int x,int y);

	/**渲染
	*测试标记									:已测试；
	*/
	void Render();

	/**移动观察块
	*参数int x									:x坐标的增加量；
	*参数int y									:y坐标的增加量；
	*返回值										:移动成功返回true；否则返回false；
	*测试标记									:已测试；
	*/
	bool MoveCamera(int x, int y);

//内部变量获得区域:
	/**得到观察块的指针
	*测试标记									:未测试；
	*/
	SDL_Rect* GetCamera()
	{
		return &m_Camera;
	}
};



#endif
