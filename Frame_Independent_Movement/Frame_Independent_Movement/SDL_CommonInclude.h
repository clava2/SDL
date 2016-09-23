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

const int MAP_WIDTH = 1600;
const int MAP_HEIGHT = 800;

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
