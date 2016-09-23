#ifndef SDL_GAME_H
#define SDL_GAME_H

#include <SDL2/SDL.h>
#include <string>

#include "SDL_Map.h"
#include "SDL_Object.h"
#include "SDL_Timer.h"
#include "SDL_CommonInclude.h"

using std::string;

class CGame
{
private:
	SDL_Window* m_Window;																			//������ָ��
	SDL_Renderer* m_Renderer;																		//�����ڵ���Ⱦ��ָ��

	SDL_Event m_Event;																						//���¼�����
	bool m_QuitGame;																						//�˳�������Ϸ
	bool m_Quit;																								//�˳���ǰ�ڲ�ʱ�䴦��ѭ��

	CObject m_Player;																						//��Ҫ����
	CMap m_MainMap;																						//��Ҫ��ͼ
	CTimer m_MainTimer;																					//��ʱ��

	bool m_ReDraw;																							//�ж��Ƿ��ػ洰��

public:

//���캯��������������


	/**���캯��
	*�����캯��ֻ����������ͣ�������������
	*/
	CGame();

	/**��������
	*���ٴ��ں���Ⱦ����
	*/
	~CGame();

//ý������Ⱦ��

	/**��ʼ������
	*����string Tile							:�����ڵı���
	*����int X										:�����ڵ�X���꣬��������ֵ�������²����е�һ���򼸸�
	*			SDL_WINDOWPOS_UNDEFINED		:δ����λ��
	*			SDL_WINDOWPOS_CENTERED		:��Ļ����
	*����int Y										:�����ڵ�Y����
	*����int Width								:�����ڵĿ��
	*����int Height							:�����ڵĸ߶�
	*����int Flag								:�������ڵ�ģʽ������Ϊ�����е�ĳ����ĳ������
	*			SDL_WINDOW_FULLSCREEN					:����ȫ������
	*			SDL_WINDOW_FULLSCREEN_DESKTOP	:�Ե�ǰ��������ش�СΪ���ڴ�С��������
	*			SDL_WINDOW_OPENGL							:����������OpenGL�Ĵ���
	*			SDL_WINDOW_HIDDEN							:��������ʱ�����ڲ��ɼ�
	*			SDL_WINDOW_BORDERLESS					:����û�б߿�Ĵ���
	*			SDL_WINDOW_RESIZABLE						:�����ɵ��ڴ�С�Ĵ���
	*			SDL_WINDOW_MINIMIZED						:��������ʱ����������С��
	*			SDL_WINDOW_MAXIMIZED					:��������ʱ�����������
	*			SDL_WINDOW_INPUT_GRABBED			:��������ʱ�������豸�۽��ڸô���
	*			SDL_WINDOW_ALLOW_HIGHDPI			:�����߾�����������Ĵ���
	*/
	bool Init(string Title = "", int X = SDL_WINDOWPOS_CENTERED, int Y = SDL_WINDOWPOS_CENTERED, int Width = SCREEN_WIDTH, int Height = SCREEN_HEIGHT, int Flag = SDL_WINDOW_SHOWN);

	/**����ý��
	*����ֵ												:���سɹ�����true,���򷵻�false;
	*/
	bool LoadMedia();

	/**����Ⱦ����
	*/
	void Render();


//�¼������

	/**�¼�����ѭ��
	*/
	void HandleEventLoop();

//���ٺ�����

	/**���ٴ��ڣ���Ⱦ����
	*/
	void Free();

//�߼��жϿ�

	/**�жϽ�ɫ�Ƿ�����
	*����ֵ								:�����ɫ����������true,���򷵻�false;
	*/
	bool CheckDie();

	/**�ж���Ϸ�Ƿ����
	*����ֵ								:�����ϷӦ�ý���������true,���򷵻�false
	*/
	bool CheckEnd();

//���ҳ���

	/**��ɫ����ʱ��ҳ��
	*/
	void DiePage();

	/**��Ϸ����ʱ��ҳ��
	*/
	void EndPage();

	/**��Ϸ��ʼҳ
	*/
	void BeginPage();
	
};

#endif