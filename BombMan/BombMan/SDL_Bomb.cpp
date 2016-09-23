#include "SDL_Bomb.h"

CBomb::CBomb(SDL_Window* Window,string BombPath,string FirePath):
	CObject(Window,1),
	m_Level(1),
	m_ShouldDraw(false),
	m_BombState(0)
{
	m_ChangeInternal = 200;
	SDL_Surface* TempSurface(NULL);
	TempSurface = IMG_Load(FirePath.c_str());
	if (!TempSurface)
	{
#ifdef _SDL_DEBUG
		cout << "SDL_Bomb.cpp\tCBomb::CBomb(SDL_Window* Window,string BombPath,string FirePath)\t�ܱ�Ǹ�����Ǵ��ļ�" << FirePath << "���ر���ʧ���ˡ�����-_-\\" << endl;
		cout << "SDL˵������������:" << SDL_GetError() << endl;
		cout << "�����������:FirePath = " << FirePath << "\t\tTempSurface = " << TempSurface << endl << endl << endl;
#endif
		return;
	}
	m_Fire = SDL_CreateTextureFromSurface(m_Renderer, TempSurface);
	if (!m_Fire)
	{
#ifdef _SDL_DEBUG
		cout << "SDL_Bomb.cpp\tCBomb::CBomb(SDL_Window* Window,string BombPath,string FirePath)\t�ܱ�Ǹ�����Ǵӱ����������ʧ����..." << endl;
		cout << "SDL˵�Ĵ�����������:" << SDL_GetError() << endl;
		cout << "���ǿ��ܳ��������:m_Renderer = " << m_Renderer << "\t\tTempSurface = " << TempSurface << endl << endl << endl;
#endif
		return;
	}
}

CBomb::~CBomb()
{
	if (m_Fire)
	{
		SDL_DestroyTexture(m_Fire);
		m_Fire = NULL;
	}
}

void CBomb::SetLevel(int Level)
{
	m_Level = Level;
}

void CBomb::SetTime(int BombTime)
{
	m_BombTime = BombTime;
}

void CBomb::SetBomb(char X, char Y)
{
	m_Area.x = X*TILE_WIDTH;
	m_Area.y = Y*TILE_HEIGHT;
	m_Area.w = TILE_WIDTH;
	m_Area.h = TILE_HEIGHT;
	m_ShouldDraw = true;
	m_Timer.Start();
}

bool CBomb::Render(CMap& Map)
{
	if (m_ShouldDraw)
	{
		if (m_Timer.GetTicks() >= m_BombTime)
		{
			if (m_Timer.GetTicks() >= m_BombTime + 200 * m_BombState + 200)
			{
				m_BombState++;
			}
			SDL_Rect SourceRect = { 0,TILE_WIDTH * (3-m_BombState),TILE_WIDTH,TILE_HEIGHT };
			SDL_Rect TargetRect = m_Area;
			Map.MapToScreen(TargetRect);
			SDL_RenderCopy(m_Renderer, m_Fire, &SourceRect, &TargetRect);
			for (int i = 0; i != m_Level; i++)
			{
				if (Map.IsSoft(m_Area.x / TILE_WIDTH-i, m_Area.y / TILE_HEIGHT))
				{
					Map.Destroy(SDL_Point{ m_Area.x / TILE_WIDTH - i, m_Area.y / TILE_HEIGHT });
					if (i < m_Level - 1)
					{
						SourceRect.x = 3 * TILE_WIDTH;
						SDL_RenderCopy(m_Renderer, m_Fire, &SourceRect, &TargetRect);
					}
				}
				SourceRect.x = 0;

				if (Map.IsSoft(m_Area.x / TILE_WIDTH + i, m_Area.y / TILE_HEIGHT))
				{
					Map.Destroy(SDL_Point{ m_Area.x / TILE_WIDTH + i, m_Area.y / TILE_HEIGHT });
					if (i < m_Level - 1)
					{
						SourceRect.x = 4 * TILE_WIDTH;
						TargetRect.x = m_Area.x + i*TILE_WIDTH;
					}
				}
				if (Map.IsSoft(m_Area.x / TILE_WIDTH, m_Area.y / TILE_HEIGHT-i))
				{
					Map.Destroy(SDL_Point{ m_Area.x / TILE_WIDTH, m_Area.y / TILE_HEIGHT-i });
					if (i < m_Level - 1)
					{
						SourceRect.x = 3 * TILE_WIDTH;
						TargetRect.x = m_Area.x - i*TILE_WIDTH;
					}
				}
			}
		}
		else
		{
			CObject::Render();
		}
	}
	return false;
}
