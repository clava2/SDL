#ifndef SDL_COMMONINCLUDE_H
#define SDL_COMMONINCLUDE_H


#define _SDL_DEBUG

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

using std::string;

//调试用头文件块
#ifdef _SDL_DEBUG

#include <iostream>
using std::cout;
using std::endl;
#endif


//通用变量块

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

const int MAP_WIDTH = 1600;
const int MAP_HEIGHT = 800;

//通用函数块

/**检测碰撞
*参数const SDL_Rect& Cbject	:被检测的物体；
*参数const SDL_Rect& Area	:检测区域；
*参数bool Border			:是否只有在碰到边框时才算碰撞；
*返回值							:检测到碰撞返回true；否则返回false；
*测试标记						:已测试；
*/
bool CheckCollision(const SDL_Rect& Object, const SDL_Rect& Area,bool Border = false);


#endif
