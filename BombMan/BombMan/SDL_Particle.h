#ifndef SDL_PARTICLE_H
#define SDL_PARTICLE_H


#include <SDL2/SDL.h>
#include <vector>
#include <time.h>

#include "SDL_CommonInclude.h"

#include "SDL_Map.h"
#include "SDL_Timer.h"

using std::vector;

enum PARTICLE_COLOR
{
	PARTICLE_GREEN,
	PARTICLE_RED,
	PARTICLE_BLUE,
	PARTICLE_WHITE,
	PARTICLE_ALL
};

struct Single
{
	int X, Y;
	long long Begin;
	PARTICLE_COLOR Type;
	int RealX;
	int RealY;
};

class CParticle
{
public:

//���캯�������������飻

	/**���캯��
	*����SDL_Window* Window		:���������Ĵ��ڣ�
	*����int x										:����ĳ�ʼλ��X���ꣻ
	*����int y										:����ĳ�ʼλ��Y���ꣻ
	*���Ա��										:δ���ԣ�
	*/
	CParticle(SDL_Window* Window = NULL,int x = 0, int y = 0,int Speed = 20);

//��Ⱦ��ʱ�䴦���
	/**��Ⱦ����
	*���Ա��										:δ���ԣ�
	*/
	void Render();

	/**�����¼�
	*���Ա��										:δ���ԣ�
	*/
	bool HandleEvent(SDL_Event& e);

//�ڲ��������ؿ飻
	/**����ͼƬ��ý��
	*���Ա��										:δ���ԣ�
	*/
	void LoadMedia();

	/**���ù۲��
	*����SDL_Rect& Camera				:�۲����ε�����
	*���Ա��										:δ���ԣ�
	*/
	void SetCamera(SDL_Rect* Camera);


	/**���ô���
	*���Ա��										:δ���ԣ�
	*/
	void SetWindow(SDL_Window* Window);

	/**�ƶ��ڵ�
	*���Ա��										:δ���ԣ�
	*/
	void Move(CMap& Map);

	/**���úڵ��ƶ����ٶ�
	*����int Speed								:�����ƶ����ٶȵĵ��������СΪ����ÿ�ƶ�һ�����ص�����Ҫ��ʱ��,ʱ���Ժ���ƣ�
	*���Ա��										:δ����
	*/
	void SetSpeed(int Speed)
	{
		m_Speed = Speed;
	}

private:
//��������
	SDL_Rect m_Area;															//���������λ����Ϣ,��������Ϊ�������꣬������ڵ�ͼ���Ե����ꣻ

	SDL_Rect m_RealArea;														//���������λ����Ϣ����������Ϊ������꣬������ڴ��ڶ��Ե����ꣻ

//��������
	int m_ParticleWidth;														//���ӵĿ�ȣ�
	int m_ParticleHeight;														//���ӵĸ߶ȣ�
	vector<Single> m_All;														//�������ӵ������Ϣ

//ͼ�����
	SDL_Texture* m_Particles[PARTICLE_ALL];						//����Ч����
	SDL_Texture* m_Dot;														//����

	SDL_Window* m_Window;												//ͼ�������Ĵ��ڣ�
	SDL_Renderer* m_Renderer;											//�ô��ڵ���Ⱦ����

//������Ϣ

	int m_Time;																		//���ӱ���ʱ�䣻
	int m_Count;																	//���ӵĸ�����

	int m_XDirection;																//�ڵ��ƶ���X����
	int m_YDirection;																//�ڵ��ƶ���Y����

	int m_Speed;																	//�ڵ��ƶ����ٶȵĵ�������ֵ������Ϊ�ڵ�ÿ�ƶ�һ�����ص����õ�ʱ�䣬ʱ���Ժ���ƣ�

	CTimer m_Timer;																//��ʱ�ӣ���¼�ѹ���ʱ�䣬�������������ƶ��ľ��룻
};

#endif
