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

const int MAP_QUEUE = 30;
const int MAP_ROW = 17;
const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;

int const MAP_WIDTH = MAP_QUEUE*TILE_WIDTH;
int const MAP_HEIGHT = MAP_ROW*TILE_WIDTH;

const int CORRECT_X_OFFSET = 5;
const int CORRECT_Y_OFFSET = 5;

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
