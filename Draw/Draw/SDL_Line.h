#ifndef SDL_LINE_H
#define SDL_LINE_H

#define _SDL_DEBUG

#include <SDL2/SDL.h>
#include <vector>

using std::vector;

#ifdef _SDL_DEBUG
#include <iostream>

using std::cout;
using std::endl;
#endif

#pragma comment(lib,"SDL2.lib")

class CLine
{
private:
	vector<SDL_Point> m_Points;															//����ֱ�ߵĵ�

	SDL_Color m_Color;																			//���ߵ���ɫ

	bool m_Dragging;																			//�Ƿ����϶�

	int m_Width;																					//�߿�

public:
//���캯��������������

	/**���캯��
	*�޲���
	*�޷���ֵ
	*���Ա��									:0
	*/
	CLine();

	/**��������
	*�޲���
	*�޷���ֵ
	*���Ա��									:0
	*/
	~CLine();

//�������ƿ�

	/**����������ӵ�
	*����SDL_Point point						:��Ҫ��ӵĵ�
	*�޷���ֵ
	*���Ա��											:0
	*/
	void AddPoint(SDL_Point point)
	{
		m_Points.push_back(point);
	}

	/**�����ߵ���ɫ
	*����SDL_Color color						:�ߵ���ɫ
	*�޷���ֵ
	*���Ա��											:0
	*/
	void SetColor(SDL_Color color)
	{
		m_Color = color;
	}

	/**�����߿�
	*����int Width									:�ߵĿ��
	*�޷���ֵ
	*���Ա��											:0
	*/
	void SetWidth(int Width)
	{
		m_Width = Width;
	}

//��ͼ��

	/**��������
	*����SDL_Renderer* Renderer			:��Ⱦ��
	*�޷���ֵ
	*/
	void Render(SDL_Renderer* Renderer);
};

#endif
