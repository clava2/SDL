#ifndef SDL_BUTTON_H
#define SDL_BUTTON_H

#include "SDL_CommonInclude.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <string>


#ifdef _SDL_DEBUG
#include <iostream>
#endif


using std::string;
using std::cout;
using std::endl;

enum BUTTON_STATE
{
	BUTTON_STATE_UP,
	BUTTON_STATE_DOWN,
	BUTTON_STATE_OVER,
	BUTTON_STATE_DISABLE
};

class CButton
{
private:

	SDL_Window* m_Window;															//��ť���ڴ��ڵ�ָ��
	SDL_Renderer* m_Renderer;														//��ť���ڴ��ڵ���Ⱦ��

	SDL_Texture* m_DownImage;														//��ť����ʱ��ͼƬ
	SDL_Texture* m_UpImage;															//��ť�����ǵ�ͼƬ
	SDL_Texture* m_DisableImage;													//��ť�������ǵ�ͼƬ
	SDL_Texture* m_Text;																	//��ť����ʾ������


	SDL_Rect m_Area;																	    //���水ť��ʾ������
	BUTTON_STATE m_State;															//��ť��ǰ��״̬

	Uint32 m_Key;																				//�����ڰ�ť������ͬ�ļ��̰���
	bool m_KeyOn;																			//���Ƽ��̰�ť�Ƿ����


	void* m_DownResult;																	//ָ��ť����ʱ�������ķ���ֵ
	void* m_UpResult;																		//ָ��ť�����Ǵ������ķ���ֵ
	void* m_DownParam;																	//ָ��ť���´�����������ָ��
	void* m_UpParam;																		//ָ��ť��������������ָ��
	void (*m_DownCallBack)(void* param, void* Result);					//��ť���µ���Ϣ������
	void (*m_UpCallBack)(void * Param, void * Result);					//��ţ̌�����Ϣ������


public:
	CButton(SDL_Window* Window = NULL,string String = "��ť",string down_path = "Button_Down.png", string up_path = "Button_Up.png", void (DownCallBack)(void* param, void* Result) = NULL, void (UpCallBack)(void* Param, void* Result) = NULL, void* DownParam = NULL, void* DownResult = NULL, void* UpParam = NULL, void* UpResult = NULL);

	~CButton();											
	void Render();

	void SetWindow(SDL_Window* Window);


	bool LoadMedia(string Text = "��ť", string DownPath = "Button_Down.png", string UpPath = "Button_Up.png");

	bool HandleEvent(SDL_Event *event);	

	void Locate(int x, int y);


	void SetSize(int Width, int Height);


};


#endif