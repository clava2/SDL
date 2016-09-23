#ifndef SDL_BOMB_H
#define SDL_BOMB_H

#include "SDL_CommonInclude.h"
#include "SDL_Object.h"
#include "SDL_Map.h"

class CBomb:public CObject
{
private:

//绘图相关
	SDL_Texture* m_Fire;																				//储存炸弹爆炸后的火焰的纹理；

//基本信息变量

	Uint32 m_BombTime;																				//保存炸弹放置到爆炸的时间；

	int m_Level;																								//记录炸弹的级数；

	bool m_ShouldDraw;																				//当前是否应该显示？

	int m_BombState;																							//爆炸已经进行到哪一步
public:

//构造函数与析构函数块；
	/**构造构造
	*/
	CBomb(SDL_Window* Window = NULL,string BombPath = "resources/Bomb.png",string FirePath = "resources/Fire.png");

	/**析构函数
	*/
	~CBomb();

	/**设置炸弹的级数
	*参数int Level							:炸弹的级数，或者说炸弹在每一边波及的范围
	*/
	void SetLevel(int Level);

	/**设置防止到爆炸的时间
	*参数int InternalTime				:炸弹从放置到爆炸的时间
	*/
	void SetTime(int BombTime);

	/**在某个位置设置一个炸弹
	*参数char X									:设置地的瓦块横坐标(即不乘瓦块的宽度)
	*参数char Y									:设置地的瓦块纵坐标(即不乘瓦块的高度)
	*测试标记									:0
	*/
	void SetBomb(char X, char Y);

	/**渲染炸弹
	*参数const CMap& Map			:需要渲染在哪幅地图上
	*返回值										:爆炸已经完成返回true,否则返回false
	*测试标记									:0
	*/
	bool Render(CMap& Map);
};

#endif
