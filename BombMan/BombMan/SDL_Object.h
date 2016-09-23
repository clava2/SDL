#ifndef SDL_OBJECT_H
#define SDL_OBJECT_H

#include "SDL_CommonInclude.h"
#include "SDL_Timer.h"
#include "SDL_Map.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <vector>

using std::string;
using std::vector;

#ifdef _SDL_DEBUG
#include <iostream>

using std::cout;
using std::endl;

#endif

class CObject
{
protected:
//������Ϣ
	SDL_Rect m_Area;															//���������λ����Ϣ,��������Ϊ�������꣬������ڵ�ͼ���Ե����ꣻ
	SDL_Rect m_RealArea;														//���������λ����Ϣ����������Ϊ������꣬������ڴ��ڶ��Ե����ꣻ

//��ͼ���
	SDL_Window* m_Window;												//ͼ�������Ĵ��ڣ�
	SDL_Renderer* m_Renderer;											//�ô��ڵ���Ⱦ����

	SDL_Rect m_SourceRect;													//��ͼʱ��Դ���Σ�
	
	SDL_Texture* m_Image;													//�����ͼ��
	SDL_Rect m_ImageInfo;													//�����߿�Ŀ�Ⱥ͸߶ȣ�

	int m_LastDraw;																//�����ϴλ��Ƶ�ͼ����ţ�
	vector< vector<SDL_Point> > m_Orders;						//����ÿ��״̬ͼ�ε��߿�λ�ã�

	int m_ChangeInternal;														//����������Ⱦ��ͬͼ��ļ��ʱ�䣻
	Uint32 m_LastChangeTime;												//�����ϴ�ת��ͼ���ʱ��㣻

//������Ϣ

	int m_XDirection;																//�����ƶ���X����
	int m_YDirection;																//�����ƶ���Y����

	bool m_Listening;															//���嵱ǰ�Ƿ�����¼���

	int  m_State;																		//���嵱ǰ״̬;

	CTimer m_Timer;																//��ʱ�ӣ����������ƶ�·�̣�

	int m_MoveSpeed;															//�����ƶ��ٶȵĵ�������ֵ�ϱ�ʾ�����ƶ�һ�����ص����õ�ʱ�䣻
	Uint32 m_LastMoveTime;												//�����ϴ��ƶ���ʱ��㣻

	Mix_Music* m_DieSound;												//�������屻�����ǵ�������

public:

//���캯��������������

	/**���캯��
	*����SDL_Window* Window				:�����������Ĵ���
	*����int x												:������ʼX����
	*����int y												:������ʼY����
	*���Ա��												:δ����
	*/
	CObject(SDL_Window* Window = NULL,int AllState = 1, int x = 0, int y = 0,int Speed = 5);

	/**��������
	*���Ա��												:δ����
	*/
	~CObject();

//��ͼ��������Ϣ������

	void Render();

	bool HandleEvent(SDL_Event& e);

//����״̬���ú���

	bool Init(SDL_Window* Window = NULL, int x = 0, int y = 0,int Speed = 5);

	bool LoadMedia(string ImagePath,string SoundPath = "");

	void SetCamera(SDL_Rect* Camera);

	void SetWindow(SDL_Window* Window);

	void Move(CMap& Map);

	void SetPlayOrder(int StateIndex, SDL_Point* Order, int Length);

	void SetTile(int Row, int Queue);

	void SetStateAmount(int Amount);

	void Die();

	void Revive()
	{
		if (m_State == (m_Orders.size() - 1))
		{
			m_State = 0;
			m_LastDraw = 0;
			m_Listening = true;
		}
	}

	void Stop()
	{
		m_XDirection = 0;
		m_YDirection = 0;
	}

	void SetSpeed(int Speed)
	{
		m_MoveSpeed = Speed;
	}

	SDL_Rect GetArea()
	{
		return m_Area;
	}

	SDL_Rect GetRealArea()
	{
		return m_RealArea;
	}
};


#endif