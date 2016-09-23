#ifndef SDL_OBJECT_H
#define SDL_OBJECT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "SDL_CommonInclude.h"
#include "SDL_Timer.h"
#include "SDL_Map.h"

using std::string;

#ifdef _SDL_DEBUG
#include <iostream>

using std::cout;
using std::endl;

#endif

enum OBJECT_STATE
{
	OBJECT_STATE_NORMAL,
	OBJECT_STATE_ALL
};

enum OBJECT_IMAGE
{
	OBJECT_IMAGE_NORMAL,
	OBJECT_IMAGE_ALL
};


class CObject
{
private:
//������Ϣ
	SDL_Rect m_Area;															//���������λ����Ϣ,��������Ϊ�������꣬������ڵ�ͼ���Ե����ꣻ
	SDL_Rect m_RealArea;														//���������λ����Ϣ����������Ϊ������꣬������ڴ��ڶ��Ե����ꣻ

//��ͼ���
	SDL_Window* m_Window;												//ͼ�������Ĵ��ڣ�
	SDL_Renderer* m_Renderer;											//�ô��ڵ���Ⱦ����
	
	SDL_Texture* m_Image[OBJECT_IMAGE_ALL];					//�����ͼ��

//������Ϣ
	int m_XDirection;																//�����ƶ���X����
	int m_YDirection;																//�����ƶ���Y����

	OBJECT_STATE m_State;													//���嵱ǰ״̬;

	CTimer m_Timer;																//��ʱ�ӣ����������ƶ�·�̣�

	int m_Speed;																		//�����ƶ��ٶȵĵ�������ֵ�ϱ�ʾ�����ƶ�һ�����ص����õ�ʱ�䣻

public:

//���캯��������������

	/**���캯��
	*����SDL_Window* Window				:�����������Ĵ���
	*����int x												:������ʼX����
	*����int y												:������ʼY����
	*���Ա��												:δ����
	*/
	CObject(SDL_Window* Window = NULL, int x = 0, int y = 0,int Speed = 5);

	/**��������
	*���Ա��												:δ����
	*/
	~CObject();

//��ͼ��������Ϣ������

	void Render();

	bool HandleEvent(SDL_Event& e);

//����״̬���ú���

	bool Init(SDL_Window* Window = NULL, int x = 0, int y = 0,int Speed = 5);

	bool LoadMedia();

	void SetCamera(SDL_Rect* Camera);

	void SetWindow(SDL_Window* Window);

	void Move(CMap& Map);

	void SetSpeed(int Speed)
	{
		m_Speed = Speed;
	}

};


#endif