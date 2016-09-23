#ifndef SDL_PROCESS_BAR_H
#define SDL_PROCESS_BAR_H

										//��������˵��ע��λ�ñ��
																//��Ա����ע�ͱ��

#include <SDL2/SDL.h>
#include <string>
#include <SDL2/SDL_image.h>

#define _SDL_DEBUG

#ifdef _SDL_DEBUG

#include <iostream>

using std::cout;
using std::endl;

#endif

using std::string;

class CProcessBar
{
private:

	typedef void (*SDL_ProcessBarCallBack)(void* Param, void* Result);

	int m_MaxLength;											//����������󳤶�
	int m_CurrentPosition;										//��������ǰ����
	bool m_ShowPercent;											//�����������Ƿ���ʾ�ٷֱ�
	SDL_Window* m_Window;										//���������ڵĴ���
	SDL_Renderer* m_Renderer;									//������Ⱦ��
	bool m_Vertical;											//�Ƿ�ֱ��ʾ������
	bool m_Direction;											//�������ķ��򣬶���ˮƽ���������ԣ�Ϊtrueʱ�������ң�
																//������ֱ���������ԣ�Ϊtrueʱ���µ��ϡ�

	SDL_Rect m_MainArea;										//��������ʾ������
	SDL_Rect m_GoArea;											//�������ƶ�ʱ������

	SDL_Texture* m_Border;										//�������߽�ͼ��
	SDL_Color m_BorderKey;										//�������߽��͸��ɫ
	bool m_BorderKeyOpen;										//͸��ɫ�Ƿ��

	SDL_Texture* m_Slider;										//�������α��ͼ��
	SDL_Color m_SliderKey;										//����������͸��ɫ
	bool m_SliderKeyOpen;										//����������͸��ɫ�Ƿ��

	int m_SliderWidth;											//�������Ŀ��
	int m_SliderHeight;											//�������ĸ߶�

	SDL_Color m_Color;											//�������ƶ�ʱ��������ɫ

	SDL_ProcessBarCallBack m_CallBack;							//��������ֵ���������ֵ�󣬵��øú���
	bool m_Called;												//�����Ƿ񱻵��ù�

	void* m_Param;												//�ص���������ʱʹ�õĲ���
	void* m_Result;												//�ص���������ʱ��ʹ�ô�ָ�봫�ط���ֵ

public:
	
	/*
	*���캯��
	*����SDL_Window* Window = NULL		:���������ڴ��ڵ�ָ��
	*����int MaxLength = 100			:��������󳤶�
	*�޷���ֵ
	*/
	CProcessBar(SDL_Window* Window = NULL, int MaxLength = 100);

	/*
	*��������
	*�޲���
	*�޷���ֵ
	*/
	~CProcessBar();

	/*
	*���ý������ĳ���
	*����int Length						:�������ĳ���
	*�޷���ֵ
	*/
	void SetPosition(int Position = 1);

	/*
	*���ƽ�����
	*�޲���
	*�޷���ֵ
	*/
	void Render();

	/*
	*������ɫ
	*����SDL_Color Color				:���ý������ѵ����������ɫ
	*�޷���ֵ
	*/
	void SetColor(SDL_Color Color)
	{
		m_Color = Color;
	}

	/*
	*������ɫ
	*����int r							:�������ѵ���������ɫ��rֵ
	*����int g							:�������ѵ���������ɫ��gֵ
	*����int b							:�������ѵ���������ɫ��bֵ
	*����int a							:�������ѵ���������ɫ��aֵ
	*�޷���ֵ
	*/
	void SetColor(int r, int g, int b, int a)
	{
		m_Color.r = r;
		m_Color.g = g;
		m_Color.b = b;
		m_Color.a = a;
	}

	/*
	*���õ�ǰ��������λ��
	*����SDL_Point Position				:��������λ��
	*�޷���ֵ
	*/
	void Locate(SDL_Point Position);

	/*
	*���õ�ǰ��������λ��
	*����int x							:��������X����
	*����int y							:��������Y����
	*�޷���ֵ
	*/
	void Locate(int x, int y);

	/*
	*���ý��������ܳ���
	*����int MaxLength					:���������ܳ���
	*�޷���ֵ
	*˵��								:�˴��ܳ���ָ��ֵ�ܳ��ȣ������ǽ����������س���
	*/
	void SetMaxLength(int MaxLength)
	{
		m_MaxLength = MaxLength;
	}

	/*
	*�ý������ĳ�������ĳ������
	*����int Offset						:ƫ������Ϊ�����Ľ���
	*�޷���ֵ
	*˵��								:ƫ������ָ�ӵ�ǰλ�ÿ�ʼƫ��
	*/
	void Offset(int Offset);

	/*
	*���ý��������ڵĴ���
	*����SDL_Window* Window				:����ָ��
	*�޷���ֵ
	*/
	void SetWindow(SDL_Window* Window);

	/*
	*���ý������ı߽���ʽ
	*����string ImagePath				:�߽�ͼƬ
	*����SDL_Rect GoArea				:���������ȷ����仯ʱ���������,������������ָ�����ͼ�������
	*����ֵbool success					:������óɹ�����true,���򷵻�false;
	*ע��								:һ�����øú�������������С�����Զ�����δ�߽�ͼƬ��ԭʼ��С��
	*/
	bool SetBorderImage(string ImagePath,SDL_Rect GoArea);

	/*
	*���þ������ı߽���ʽ
	*����string ImagePath				:�߽�ͼƬ
	*����int x							:���ͼƬ���ԣ��������˶������X����
	*����int y							:���ͼƬ���ԣ��������˶������Y���
	*����int w							:���ͼƬ���ԣ��������˶�����Ŀ��
	*����int h							:���ͼƬ���ԣ��������˶�����ĸ߶�
	*����ֵbool success					:�ɹ�����true,���򷵻�false;
	*ע��								:һ�����øú�������������С�����Զ�����δ�߽�ͼƬ��ԭʼ��С��
	*/
	bool SetBorderImage(string ImagePath, int x, int y, int w, int h);

	/*
	*���õ�ǰ�������߽�͸��ɫ
	*����SDL_Color ColorKey				:������͸��ɫ
	*�޷���ֵ
	*ע��								:ֻ���ڵ��ô˺�����͸��ɫ�Ż�򿪣�
										 ���ṩĬ�ϱ���ɫ,�˺������������ñ߽�ͼ��ֻǰ����
	*/
	void SetBorderKey(SDL_Color ColorKey)
	{

	}

	/*
	*���õ�ǰ�������߽�͸��ɫ
	*����char r							:������͸��ɫ�ĺ�ɫ����
	*����char g							:������͸��ɫ����ɫ����
	*����char b							:������͸��ɫ����ɫ����
	*����char a							:������͸��ɫ��alpha����
	*�޷���ֵ
	*ע��								:ֻ���ڵ��ô˺�����͸��ɫ�Ż�򿪣�
										 ���ṩĬ�ϱ���ɫ,�˺������������ñ߽�ͼ��ֻǰ����
	*/
	void SetBorderKey(char r, char g, char b, char a)
	{
		m_BorderKeyOpen = true;
		m_BorderKey.r = r;
		m_BorderKey.g = g;
		m_BorderKey.b = b;
		m_BorderKey.a = a;
	}

	/*
	*���ý������˶�ʱ��������ʽ
	*����string ImagePath				:������ʾ��Ӧ��ͼƬ·��
	*����int Width = -1					:����Ŀ�ȣ�-1��ʾԭʼ��С
	*����int Height = -1				:����ĸ߶ȣ�-1��ʾԭʼ��С
	*����ֵbool success					:���سɹ�����true,ʧ�ܷ���false
	*˵��								
	*/
	bool SetSliderImage(string ImagePath, int Width = -1, int Height = -1);

	/*
	*���ý�������͸��ɫ
	*����SDL_Color ColorKey				:͸��ɫ
	*�޷���ֵ
	*ע��								:ֻ���ڵ��ô˺�����͸��ɫ�Ż�򿪣�
										 ���ṩĬ�ϱ���ɫ,�˺������������ñ߽�ͼ��ֻǰ����
	*/
	void SetSliderColorKey(SDL_Color ColorKey)
	{
		m_SliderKeyOpen = true;
		m_SliderKey = ColorKey;
	}

	/*
	*���ý�������͸��ɫ
	*����char r							:����͸��ɫ�ĺ�ɫ����
	*����char g							:����͸��ɫ����ɫ����
	*����char b							:����͸��ɫ����ɫ����
	*����char a							:����͸��ɫ��alpha����
	*�޷���ֵ
	*ע��								:ֻ���ڵ��ô˺�����͸��ɫ�Ż�򿪣�
	���ṩĬ�ϱ���ɫ,�˺������������ñ߽�ͼ��ֻǰ����
	*/
	void SetSliderColorKey(char r,char g,char b,char a)
	{
		m_SliderKeyOpen = true;
		m_SliderKey.r = r;
		m_SliderKey.g = g;
		m_SliderKey.b = b;
		m_SliderKey.a = a;
	}

	/*
	*���ý������ص�����
	*����SDL_ProcessBarCallBack Functin	:�ص�����
	*����void* Param = NULL				:���ûص�����ʱ����Ĳ���
	*����void* Result = NULL			:���ûٵ�����ʱ��ʹ�ô�ָ�봫�ؽ��
	*�޷���ֵ
	*˵��
	*/
	void SetFunction(SDL_ProcessBarCallBack Function, void* Param = NULL, void* Result = NULL)
	{
		m_CallBack = Function;
		m_Param = Param;
		m_Result = Result;
	}

	/*
	*���ó��ȺͿ��
	*����int Width						:���������¿�ȣ�-1��ʾ���ֲ���
	*����int Height						:���������¸߶ȣ�-1��ʾ���ֲ���
	*�޷���ֵ
	*˵��								:����ڴ˺���֮ǰ���ù����ȱ仯���������Զ��仯��������������
	*/
	void SetSize(int Width, int Height)
	{
		m_GoArea.x = m_MainArea.x + (m_GoArea.x - m_MainArea.x)*Width / m_MainArea.w + 1;
		m_GoArea.y = m_MainArea.y + (m_GoArea.y - m_MainArea.y)*Height / m_MainArea.h + 1;
		m_GoArea.w = m_GoArea.w*Width / m_MainArea.w;
		m_GoArea.h = m_GoArea.h*Height / m_MainArea.h;

		m_MainArea.w = Width;
		m_MainArea.h = Height;
	}
};



#endif