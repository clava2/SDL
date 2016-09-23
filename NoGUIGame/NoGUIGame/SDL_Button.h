/*****************************************************************
****������CButton											******
****����ļ�				:SDL_Button.h,SDL_Button.cpp	******
****���ܣ�����һ����ť										******
****������;��												******
****��󹹽�����			:2016��9��9��14:24:07			******
****�汾��					:ver 0.1						******
****������					:֣��							******
****														******
****														******
****														******
****														******
****														******
******************************************************************/


									//��Ա����˵��ע��λ�ñ��
														//����������˵��λ�ñ��



#ifndef SDL_BUTTON_H
#define SDL_BUTTON_H

#define _SDL_DEBUG										//���Ա��

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <SDL2/SDL_Image.h>
#include <SDL2/SDL_ttf.h>


#ifdef _SDL_DEBUG
#include <iostream>										//������ͷ�ļ�
using std::string;
using std::cout;
using std::endl;
#endif


const int TEXT_HEIGHT_RATE = 75;						//�ڰ�ť����ʾ����ʱ��������ռ��ť�ܸ߶ȵİٷֱ�
const int TEXT_WIDTH_RATE = 75;							//�ڰ�ť����ʾ����ʱ��������ռ��ť�ܸ߶ȵİٷֱ�


enum BUTTON_STATE
{
	BUTTON_OUT,
	BUTTON_IN,
	BUTTON_DOWN,
	BUTTON_DISABLED,
	BUTTON_STATE_ALL,
	BUTTON_UP = 5								//��ֵ�����ڻص�������
};

enum ALIGN_STATE
{
	ALIGN_OVER,
	ALIGN_LEFT,
	ALIGN_RIGHT,
	ALIGN_TOP,
	ALIGN_BOTTOM
};

class CButton
{

private:

	//״̬ͼ��
	SDL_Texture* m_ButtonImage[BUTTON_STATE_ALL];		//��ť����״̬��ͼƬ

	//�ص�����
	typedef void(*SDL_ButtonCallBack)(void* param, void* Result);

	SDL_ButtonCallBack m_CallBack[BUTTON_STATE_ALL+1];			//�ص�����������ͼƬ�����ڵ���ʱ��ͼƬ�����Ը����ֱ�ͼƬ�Ĵ�һ��

	void* m_Param[BUTTON_STATE_ALL+1];					//���ֺ����Ĳ���
	void* m_Result[BUTTON_STATE_ALL+1];					//���ֺ�����������

	int m_DefaultWidth[BUTTON_STATE_ALL];				//ͼƬĬ�Ͽ��
	int m_DefaultHeight[BUTTON_STATE_ALL];				//ͼƬĬ�ϸ߶�

	//����
	string m_ButtonText;								//��ť����ʾ������
	SDL_Texture* m_TextTexture;							//��������
	SDL_Rect m_TextArea;								//����������ʾ��λ�õ�λ��
	TTF_Font* m_TextFont;								//�������õ�����
	//ALIGN_STATE m_AlignState;							//��ť���ֵ���ʾ״̬
	string m_FontPath;									//��Ⱦ������ʹ�õ������·��
	int m_FontSize;										//��Ⱦ����ʱʹ�õ������С
	SDL_Color m_TextColor;								//���ֵ���ɫ
	int m_TextWidth;									//��������Ŀ��
	int m_TextHeight;									//��������ĸ߶�

	//״̬����
	SDL_Rect m_ButtonArea;							    //���水ť��ʾ������
	BUTTON_STATE m_ButtonState;							//���水ť��ǰ״̬
	Uint32 m_Key;										//�����ڰ�ť������ͬ�ļ��̰���
	int m_WindowWidth;									//���ڿ��
	int m_WindowHeight;									//���ڸ߶�

	//�ⲿ���
	SDL_Renderer* m_Renderer;
	SDL_Window* m_Window;

public:

	/*
	*���캯��1
	*����SDL_Window* Window = NULL	:��ť�������Ǹ�������Ⱦ
	*����string String				:��ť�Ͻ�����ʾ������
	*�޷���ֵ
	*˵��							:����򵥵ķ�ʽ����һ����ť
	*/
	CButton(SDL_Window* Window = NULL, string String = "Button");

	/*
	*��������
	*�޲���
	*�޷���ֵ
	*˵��							:�˺��������ͷŵ�����ͼƬռ�õ��ڴ棬���ǲ����ͷŴ��ں���Ⱦ��
	*/
	~CButton();

	/*
	*��Ⱦ��ť
	*
	*/
	void Render();

	void SetWindow(SDL_Window* Window)
	{
		m_Window = Window;
		m_Renderer = SDL_GetRenderer(m_Window);
		if (!m_Renderer)
		{
#ifdef _SDL_DEBUG
			cout << "SDL_Button.h	CButton	void SetWindow(SDL_Window* Window)	"
				"�Ӵ��ڻ����Ⱦ��ʧ�ܣ����鴫��Ĵ���ָ���Ƿ�Ϸ�!" << endl << endl << endl;
#endif
			return;
		}
	}

	/*
	*������굥���¼�
	*����const SDL_Event& Event		:�������Ļ�ϵ�����λ��
	*����ֵ							:����õ��ٰ�ť���ڵ������ڲ�������true,���򷵻�false;
	*˵��							:
	*/
	bool HandleEvent(const SDL_Event& Event);

	/*
	*���ð�ť��λ��
	*����int x						:��λ�����Ͻǵĺ�����
	*����int y						:��λ�����Ͻǵ�������
	*�޷���ֵ
	*/
	void Locate(int x, int y);

	/*
	*���ð�ť��λ��
	*����SDL_Point Position			:��λ�����Ͻǵ�λ��
	*�޷���ֵ
	*/
	void Locate(SDL_Point Position);

	/*
	*���ð�ť�Ĵ�С
	*����int Width					:��ť���¿��,-1ʹ��ԭʼ��С
	*����int Height					:��ť���¸߶ȣ�-1ʹ��ԭʼ��С
	*/
	void SetSize(int Width, int Height);

	/*
	*Ϊ��ť��ĳ��״̬����ͼƬ
	*����BUTTON_STATE State			:�����õ�״̬
	*����string Path				:ͼƬ��·��
	*����ֵ							:�ɹ�����true,���򷵻�false;
	*/
	bool SetImage(BUTTON_STATE State,string Path);

	/*
	*���ú����Ĳ����ͷ���ֵָ��
	*����BUTTON_STATE State			:����ť�����״̬ʱ������ô˺������ûص�����
	*����SDL_ButtonCallBack CallBackFunction	:�ص�������������ʽΪvoid (*p)(void* Param,void* Result);
	*����void* pParam = NULL		:�ص���������ʱ�����뺯���Ĳ���
	*����void* pResult = NULL		:�ص���������ʱ��ͨ����ָ�봫�������
	*˵��							:��������ƺ�����������ͷ���ֵ�ĸ�ʽ
	*/
	void SetFunction(BUTTON_STATE State, SDL_ButtonCallBack CallBackFunction, void* pParam = NULL, void* pResult = NULL);

	/*
	*���ð�ť����
	*����string Text				:�����õ�����
	*����string FontPath			:����·��
	*����int Size					:����Ĵ�С
	*����ALIGN_STATE Align			:�������ʾ״̬
	*����ֵ							:�ɹ�����true�����򷵻�false
	*˵��
	*/
	bool SetText(string Text, string FontPath = "", int Size = -1,ALIGN_STATE Align = ALIGN_OVER);

	/*
	*ǿ�Ƹ��İ�ť��������ʾ����
	*����SDL_Rect TextArea		:ָ��������
	*�޷���ֵ
	*˵��						:�˺�����SetText����֮�����
	*/
	void SetTextArea(SDL_Rect TextArea)
	{
		m_TextArea = TextArea;
	}
	
	/*
	*ǿ�Ƹ��İ�ť��������ʾ����
	*����int x = -1				:ָ�������X���꣬-1��ʾ����ԭX����
	*����int y = -1				:ָ�������Y���꣬-1��ʾ����ԭY����
	*����int Width = -1			:ָ������Ŀ��,-1��ʾ����ԭ���
	*����int Height = -1		:ָ������ĸ߶ȣ�-1��ʾ����ԭ���
	*�޷���ֵ
	*˵��						:�˺�����SetText����֮�����
	*/
	void SetTextArea(int x, int y, int Width, int Height)
	{
		if (x != -1)
		{
			m_TextArea.x = x;
		}
		if (y != -1)
		{
			m_TextArea.y = y;
		}
		if (Width != -1)
		{
			m_TextArea.w = Width;
		}
		if (Height != -1)
		{
			m_TextArea.h = Height;
		}
	}

	/*
	*�����밴ť������ͬ�İ�ť
	*����Uint32 Key					:��ť���
	*�޷���ֵ
	*/
	void SetKey(Uint32 Key)
	{
		m_Key = Key;
	}

	/*
	*ǿ�Ƹı䵱ǰ��ť��״̬
	*����BUTTON_STATE State			:��Ҫ�ı䵽��״̬
	*/
	void ChangeState(BUTTON_STATE State);
};

#endif