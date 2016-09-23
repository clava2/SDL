#ifndef SDL_BOMB_H
#define SDL_BOMB_H

#include "SDL_CommonInclude.h"
#include "SDL_Object.h"
#include "SDL_Map.h"

class CBomb:public CObject
{
private:

//��ͼ���
	SDL_Texture* m_Fire;																				//����ը����ը��Ļ��������

//������Ϣ����

	Uint32 m_BombTime;																				//����ը�����õ���ը��ʱ�䣻

	int m_Level;																								//��¼ը���ļ�����

	bool m_ShouldDraw;																				//��ǰ�Ƿ�Ӧ����ʾ��

	int m_BombState;																							//��ը�Ѿ����е���һ��
public:

//���캯�������������飻
	/**���칹��
	*/
	CBomb(SDL_Window* Window = NULL,string BombPath = "resources/Bomb.png",string FirePath = "resources/Fire.png");

	/**��������
	*/
	~CBomb();

	/**����ը���ļ���
	*����int Level							:ը���ļ���������˵ը����ÿһ�߲����ķ�Χ
	*/
	void SetLevel(int Level);

	/**���÷�ֹ����ը��ʱ��
	*����int InternalTime				:ը���ӷ��õ���ը��ʱ��
	*/
	void SetTime(int BombTime);

	/**��ĳ��λ������һ��ը��
	*����char X									:���õص��߿������(�������߿�Ŀ��)
	*����char Y									:���õص��߿�������(�������߿�ĸ߶�)
	*���Ա��									:0
	*/
	void SetBomb(char X, char Y);

	/**��Ⱦը��
	*����const CMap& Map			:��Ҫ��Ⱦ���ķ���ͼ��
	*����ֵ										:��ը�Ѿ���ɷ���true,���򷵻�false
	*���Ա��									:0
	*/
	bool Render(CMap& Map);
};

#endif
