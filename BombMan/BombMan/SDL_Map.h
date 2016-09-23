#ifndef SDL_MAP_H
#define SDL_MAP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>
#include <fstream>

#include "SDL_CommonInclude.h"

using std::string;
using std::ifstream;
using std::vector;

#ifdef _SDL_DEBUG
#include <iostream>

using std::cout;
using std::endl;

#endif

const int TILE_QUEUE = 4;
const int TILE_ROW = 2;

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
	SingleTile m_TargetRects[MAP_ROW][MAP_QUEUE];			//����Ŀ���п飻
	SDL_Window* m_Window;													//����ָ�룻
	SDL_Renderer* m_Renderer;												//������Ⱦ����
	bool m_Barry[TILE_ROW][TILE_QUEUE];								//�ϰ������ã�
	bool m_Soft[TILE_ROW][TILE_QUEUE];								//�ܷ�ը������
	SDL_Rect m_Camera;															//�۲�飻

	SDL_Point m_Background;													//����ը�ٿ鵲ס������ͼƬ��
	vector<SingleTile> m_Hide;												//����������ֻ��ը�ٱ���֮����ܻ�õĵ���

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


	/**���ÿ��Ա�ը�ٵ�����
	*����SDL_Point* Soft				:���Ա�ը�ٵĿ���߿����꼯��
	*����int Length						:��������ĳ���
	*����SDL_Point Background				:�����ƻ�֮����ʾ�ڵ�ͼ�е�ͼƬ���߿�ͼ�е�����
	*�޷���ֵ	
	*���Ա��									:δ����
	*/
	void SetSoft(SDL_Point* Soft, int Length,SDL_Point Background);

	/**���ÿ��Ա�ը�ٵ�����ը�ٵ�ͼƬ
	*����SDL_Point Hide				:����ͼƬ
	*����SDL_Point Soft					:���Ա�ը�ٵ����������
	*����ֵ	bool succeed				:���óɹ�����true,���򷵻�false
	*���Ա��									:δ����
	*/
	bool SetHide(SDL_Point Hide, SDL_Point Pos);

	/**ը��ĳ���߿�
	*����SDL_Point Pos					:��ը�ٵ��߿��ڵ�ͼ�е�����
	*����ֵ										:���������ը�ٷ���true,����ը��������򲻻�ը�٣�������false;
	*���Ա��									:δ����
	*/
	bool Destroy(SDL_Point Pos);

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

	/**ѯ��ĳ���ط��Ƿ��ܹ���ը��
	*����char X								:ѯ�ʵط����߿�X����
	*����char Y								:ѯ�ʵط����߿�Y����
	*����ֵ										:�õط����Ա�ը�ٷ���true,���򷵻�false
	���Ա��									:0
	*/
	bool IsSoft(char X, char Y)const
	{
		if ((X < 0) || (X > MAP_QUEUE) || (Y < 0) || (Y > MAP_ROW))
		{
			return false;
		}
		return m_Soft[m_TargetRects[X][Y].m_Position.x][m_TargetRects[X][Y].m_Position.y];
	}

	/**����Ե�ͼ������ת��Ϊ�����Ļ������
	*����SDL_Rect& Area				:��Ҫ��ת��������
	*�޷���ֵ
	*���Ա��									:0
	*/
	bool MapToScreen(SDL_Rect& Area)const
	{
		Area.x = Area.x - m_Camera.x;
		Area.y = Area.y - m_Camera.y;
		return true;
	}
};
#endif
