#ifndef SDL_TIMER_H
#define SDL_TIMER_H

#define _SDL_DEBUG

#include <SDL2/SDL.h>

#ifdef _SDL_DEBUG
#include <iostream>

using std::endl;
using std::cout;

#endif


class CTimer
{
private:

//时间记录变量

	Uint32 m_StartTicks;							//存储开始时间
	Uint32 m_PauseTicks;							//存储暂停时间

//计时器状态变量

	bool m_Paused;									//存储是否暂停
	bool m_Started;									//存储是否开始计时

public:

//构造函数块


	/**构造函数
	*测试标记					:未测试
	*/
	CTimer();


//相关操作



	/**开始计时
	*测试标记					:未测试
	*/
	void Start();

	/**停止计时器
	*测试标记					:未测试
	*/
	void Stop();

	/**暂停计时器
	*测试标记					:未测试
	*/
	void Pause();

	/**暂停后重新开始计时器
	*测试标记					:未测试
	*/
	void Unpause();
	
	/**得到当前时间
	*返回值						:从计时器开始到想在的时间；
	*测试标记					:未测试
	*/
	Uint32 GetTicks();


//内部变量获取块


	/**判断当前计时器是否开始
	*返回值						:开始返回true;否则返回false;
	*/
	bool IsStarted()
	{
		return m_Started;
	}

	/**判断当前计时器是否暂停
	*返回值						:暂停返回true;否则返回false;
	*/
	bool IsPaused()
	{
		return m_Paused;
	}
};




#endif
