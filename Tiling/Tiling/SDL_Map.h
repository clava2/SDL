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
	SDL_Rect m_Area;																//������Ƭ������
	SDL_Point m_Position;															//������Ƭ����ͼƬ�е�λ����Ϣ��
}SingleTile;

class CMap
{
private:

	SDL_Texture* m_AllSprites;													//����Դ��Ƭ��
	SDL_Texture* m_Map;															//�����ͼ����
	SDL_Rect m_SourceRects[TILE_ROW][TILE_QUEUE];			//���������п飻
	SingleTile m_TargetRects[MAP_ROW][MAP_QUEUE];		//����Ŀ���п飻
	SDL_Window* m_Window;													//����ָ�룻
	SDL_Renderer* m_Renderer;												//������Ⱦ����
	bool m_Barry[TILE_ROW][TILE_QUEUE];								//�ϰ������ã�
	SDL_Rect m_Camera;															//�۲�飻

public:

//�������캯����������������:

	/**
	*���캯��������CMap��
	*����SDL_Window* Window	:������Ƭ����Ĵ��ڣ�
	*����string TilePath					:������Ƭ���ļ�·����
	*���Ա��									:�Ѳ��ԣ�
	*/
	CMap(SDL_Window* Window = NULL, string TilePath = "Tile_Default.png", string MapPath = "Map_Default.map");


	/*
	*��������
	*������ر�����
	*���Ա��									:δ����
	*/
	~CMap();

//�ڲ�������������:

	/*�����ϰ���
	*����SDL_Point* Barry				:�����ϰ���������Ϣ�����ԣ�
	*����int i									:�ϰ���ĸ���:
	*���Ա��									:δ����
	*/
	void SetBarry(SDL_Point* Barry, int i = 1);

	/**��ʼ�����󣬹����빹�캯����ͬ
	*�����빹�캯����ͬ
	*�ɹ�����true�����򷵻�false��
	*/
	bool Init(SDL_Window* Window = NULL, string TilePath = "Tile_Default.png", string MapPath = "Map_Default.map");

	/**��������Ĵ���
	*����SDL_Window* Window	:����ָ��;
	*���Ա��									:�Ѳ��ԣ�
	*/
	void SetWindow(SDL_Window* Window);

	/**���ļ��м�����Ƭ
	*����stirng TilePath					:��Ƭ�ļ�·����
	*����ֵ										:���سɹ�����true�����򷵻�false��
	*���Ա��									:�Ѳ���
	*/
	bool LoadTile(string TilePath);

	/**���ļ��м��ص�ͼ
	*����string MapPath				:��ͼ�ļ�·����
	*����ֵ										:���سɹ�����true�����򷵻�false��
	*���Ա��									:�Ѳ��ԣ�
	*/
	bool LoadMap(string MapPath);

	/**���ù۲��
	*����int Width							:�۲��ĸ߶ȣ�
	*����int Height						:�۲��Ŀ�ȣ�
	*����SDL_Point DefaultPosition	:�۲��ĳ���λ�ã�
	*���Ա��									:�Ѳ��ԣ�
	*/
	void SetCamera(int Width = SCREEN_WIDTH, int Height = SCREEN_HEIGHT, SDL_Point DefaultPosition = SDL_Point{ 0,0 });

//��ز�������:

	/**����Ƿ���ǽ
	*����SDL_Rect& Object			:���ƶ������壻
	*����ֵ										:û����ǽ����true�����򷵻�false��
	*���Ա��									:δ����
	*/
	bool TouchWall(const SDL_Rect& Object,int x,int y);

	/**��Ⱦ
	*���Ա��									:�Ѳ��ԣ�
	*/
	void Render();

	/**�ƶ��۲��
	*����int x									:x�������������
	*����int y									:y�������������
	*����ֵ										:�ƶ��ɹ�����true�����򷵻�false��
	*���Ա��									:�Ѳ��ԣ�
	*/
	bool MoveCamera(int x, int y);

//�ڲ������������:
	/**�õ��۲���ָ��
	*���Ա��									:δ���ԣ�
	*/
	SDL_Rect* GetCamera()
	{
		return &m_Camera;
	}
};



#endif
