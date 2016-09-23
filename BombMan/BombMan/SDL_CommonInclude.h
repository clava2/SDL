#ifndef SDL_COMMONINCLUDE_H
#define SDL_COMMONINCLUDE_H


#define _SDL_DEBUG

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

using std::string;

//������ͷ�ļ���
#ifdef _SDL_DEBUG

#include <iostream>
using std::cout;
using std::endl;

#endif


//ͨ�ñ�����

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

//ͨ�ú�����

/**�����ײ
*����const SDL_Rect& Cbject	:���������壻
*����const SDL_Rect& Area	:�������
*����bool Border			:�Ƿ�ֻ���������߿�ʱ������ײ��
*����ֵ							:��⵽��ײ����true�����򷵻�false��
*���Ա��						:�Ѳ��ԣ�
*/
bool CheckCollision(const SDL_Rect& Object, const SDL_Rect& Area,bool Border = false);


#endif
