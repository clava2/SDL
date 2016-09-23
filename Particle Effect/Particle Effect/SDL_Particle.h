#ifndef SDL_PARTICLE_H
#define SDL_PARTICLE_H

#define _SDL_DEBUG

#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <time.h>

using std::cout;
using std::endl;
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
};

class CParticle
{
public:
	CParticle(SDL_Window* Window = NULL,int x = 0, int y = 0);

	/**���캯��
	*/

	void Render();

	/**��Ⱦ����
	*/

	void HandleEvent(SDL_Event& e);

	/**�����¼�
	*/

	void SetBorder(int Width, int Height);

	/**���õ��˶��ı߽�
	*/

	void LoadMedia();

	/**����ͼƬ��ý��
	*/

	void SetWindow(SDL_Window* Window)
	{
		m_Window = Window;
		m_Renderer = SDL_GetRenderer(m_Window);
		SDL_GetWindowSize(m_Window, &m_ScreenWidth, &m_ScreenHeight);
		cout << m_Renderer << endl;
	}

	/**���ô���
	*/

	void Move();

	/**�ƶ��ڵ�
	*/

private:
	int m_XPos;										//������
	int m_YPos;										//������
	int m_ScreenWidth;								//��Ļ��ȣ�
	int m_ScreenHeight;								//��Ļ�߶ȣ�
	int m_DotWidth;									//��Ŀ�ȣ�
	int m_DotHeight;								//��ĸ߶ȣ�
	int m_ParticleWidth;							//���ӵĿ�ȣ�
	int m_ParticleHeight;							//���ӵĸ߶ȣ�
	vector<Single> m_All;							//�������ӵ������Ϣ

	int m_Time;										//����ʱ�䣻
	int m_Count;									//���ӵĸ�����

	int m_XDirection;								//�ڵ��ƶ���X����
	int m_YDirection;								//�ڵ��ƶ���Y����

	SDL_Texture* m_Particles[PARTICLE_ALL];			//����Ч����
	SDL_Texture* m_Dot;								//��
	SDL_Window* m_Window;							//ͼ�������Ĵ��ڣ�
	SDL_Renderer* m_Renderer;						//�ô��ڵ���Ⱦ����
};

#endif
