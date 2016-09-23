#include "SDL_Map.h"

CMap::CMap(SDL_Window* Window, string TilePath, string MapPath)
{
	m_Camera.w = SCREEN_WIDTH;
	m_Camera.h = SCREEN_HEIGHT;
	m_Camera.x = 0;
	m_Camera.y = 0;
	if (Window)
	{
		m_Window = Window;
		m_Renderer = SDL_GetRenderer(m_Window);
#ifdef _SDL_DEBUG
		if (!m_Renderer)
		{
			cout << "SDL_Tile.cpp	CMap	获取窗口渲染器失败！SDL Error:" << SDL_GetError() << endl;
			cout << "SDL_Tile.cpp	CMap	获取窗口渲染器失败！m_Window = " << m_Window << endl;
			cout << "SDL_Tile.cpp	CMap	获取窗口渲染器失败！m_Renderer = " << m_Renderer << endl;
			cout << endl << endl << endl;
			return;
		}
#endif

		SDL_Surface* TempSurface = NULL;

		TempSurface = IMG_Load(TilePath.c_str());
#ifdef _SDL_DEBUG
		if (!TempSurface)
		{
			cout << "SDL_Tile.cpp	CMap	从文件读取表面失败！SDL Error:" << SDL_GetError() << endl;
			cout << "SDL_Tile.cpp	CMap	TilePath = " << TilePath << endl;
			cout << endl << endl << endl;
			return;
		}
#endif
		m_AllSprites = SDL_CreateTextureFromSurface(m_Renderer, TempSurface);
#ifdef _SDL_DEBUG
		if (!m_AllSprites)
		{
			cout << "SDL_Tile.cpp	CMap	从表面创建纹理失败！SDL Error:" << SDL_GetError() << endl;
			cout << "SDL_Tile.cpp	CMap	m_Surface = " << TempSurface << endl;
			cout << "SDL_Tile.cpp	CMap	m_AllSprites = " << m_AllSprites << endl;
			cout << endl << endl << endl;
			return;
		}
#endif

		if (TempSurface)
		{
			SDL_FreeSurface(TempSurface);
		}
	}
	else
	{
		m_Window = Window;
	}

	ifstream In(MapPath.c_str());

#ifdef _SDL_DEBUG
	if (!In)
	{
		cout << "SDL_Tile.cpp	CMap	打开地图文件失败！" << endl;
		cout << endl << endl << endl;
		return;
	}
#endif

	for (int i = 0; i != TILE_ROW; i++)
	{
		for (int j = 0; j != TILE_QUEUE; j++)
		{
			m_SourceRects[i][j].x = j*TILE_WIDTH;
			m_SourceRects[i][j].y = i*TILE_HEIGHT;
			m_SourceRects[i][j].w = TILE_WIDTH;
			m_SourceRects[i][j].h = TILE_HEIGHT;
		}
	}

	SDL_Point TempPosition;

	for (int i = 0; i != MAP_ROW; i++)
	{
		for (int j = 0; j != MAP_QUEUE; j++)
		{
			m_TargetRects[i][j].m_Area.x = j*TILE_WIDTH;
			m_TargetRects[i][j].m_Area.y = i*TILE_HEIGHT;
			m_TargetRects[i][j].m_Area.w = TILE_WIDTH;
			m_TargetRects[i][j].m_Area.h = TILE_HEIGHT;
			In >> TempPosition.x;
			In >> TempPosition.y;
			m_TargetRects[i][j].m_Position = TempPosition;
		}
	}

	for (int i = 0; i != TILE_ROW; i++)
	{
		for (int j = 0; j != TILE_QUEUE; j++)
		{
			m_Barry[i][j] = false;
		}
	}

	m_Map = SDL_CreateTexture(m_Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, TILE_WIDTH*MAP_QUEUE, TILE_HEIGHT*MAP_ROW);
	if (!m_Map)
	{
#ifdef _SDL_DEBUG
		cout << "SDL_Map.cpp	CMap	创建地图纹理失败！SDL Error:" << SDL_GetError() << endl;
#endif
		return;
	}
	SDL_SetRenderTarget(m_Renderer, m_Map);
	SDL_SetRenderDrawBlendMode(m_Renderer, SDL_BLENDMODE_NONE);
	SDL_RenderClear(m_Renderer);
	for (int i = 0; i != MAP_ROW; i++)
	{
		for (int j = 0; j != MAP_QUEUE; j++)
		{
			SDL_RenderCopy(m_Renderer, m_AllSprites, &m_SourceRects[m_TargetRects[i][j].m_Position.x][m_TargetRects[i][j].m_Position.y], &m_TargetRects[i][j].m_Area);
		}
	}
	SDL_SetRenderTarget(m_Renderer, NULL);
}

bool CMap::Init(SDL_Window* Window, string TilePath, string MapPath)
{
	m_Camera.w = SCREEN_WIDTH;
	m_Camera.h = SCREEN_HEIGHT;
	m_Camera.x = 0;
	m_Camera.y = 0;
	if (Window)
	{
		m_Window = Window;
		m_Renderer = SDL_GetRenderer(m_Window);
#ifdef _SDL_DEBUG
		if (!m_Renderer)
		{
			cout << "SDL_Tile.cpp	CMap	获取窗口渲染器失败！SDL Error:" << SDL_GetError() << endl;
			cout << "SDL_Tile.cpp	CMap	获取窗口渲染器失败！m_Window = " << m_Window << endl;
			cout << "SDL_Tile.cpp	CMap	获取窗口渲染器失败！m_Renderer = " << m_Renderer << endl;
			cout << endl << endl << endl;
			return false;
		}
#endif

		SDL_Surface* TempSurface = NULL;

		TempSurface = IMG_Load(TilePath.c_str());
#ifdef _SDL_DEBUG
		if (!TempSurface)
		{
			cout << "SDL_Tile.cpp	CMap	从文件读取表面失败！SDL Error:" << SDL_GetError() << endl;
			cout << "SDL_Tile.cpp	CMap	TilePath = " << TilePath << endl;
			cout << endl << endl << endl;
			return false;
		}
#endif
		if (m_AllSprites)
		{
			SDL_DestroyTexture(m_AllSprites);
			m_AllSprites = NULL;
		}
		m_AllSprites = SDL_CreateTextureFromSurface(m_Renderer, TempSurface);
#ifdef _SDL_DEBUG
		if (!m_AllSprites)
		{
			cout << "SDL_Tile.cpp	CMap	从表面创建纹理失败！SDL Error:" << SDL_GetError() << endl;
			cout << "SDL_Tile.cpp	CMap	m_Surface = " << TempSurface << endl;
			cout << "SDL_Tile.cpp	CMap	m_AllSprites = " << m_AllSprites << endl;
			cout << endl << endl << endl;
			return false;
		}
#endif

		if (TempSurface)
		{
			SDL_FreeSurface(TempSurface);
			TempSurface = NULL;
		}
	}
	else
	{
		m_Window = Window;
	}

	ifstream In(MapPath.c_str());

#ifdef _SDL_DEBUG
	if (!In)
	{
		cout << "SDL_Tile.cpp	CMap	打开地图文件失败！" << endl;
		cout << endl << endl << endl;
		return false;
	}
#endif

	for (int i = 0; i != TILE_ROW; i++)
	{
		for (int j = 0; j != TILE_QUEUE; j++)
		{
			m_SourceRects[i][j].x = j*TILE_WIDTH;
			m_SourceRects[i][j].y = i*TILE_HEIGHT;
			m_SourceRects[i][j].w = TILE_WIDTH;
			m_SourceRects[i][j].h = TILE_HEIGHT;
		}
	}

	SDL_Point TempPosition;

	for (int i = 0; i != MAP_ROW; i++)
	{
		for (int j = 0; j != MAP_QUEUE; j++)
		{
			m_TargetRects[i][j].m_Area.x = j*TILE_WIDTH;
			m_TargetRects[i][j].m_Area.y = i*TILE_HEIGHT;
			m_TargetRects[i][j].m_Area.w = TILE_WIDTH;
			m_TargetRects[i][j].m_Area.h = TILE_HEIGHT;
			In >> TempPosition.x;
			In >> TempPosition.y;
			m_TargetRects[i][j].m_Position = TempPosition;
		}
	}

	for (int i = 0; i != TILE_ROW; i++)
	{
		for (int j = 0; j != TILE_QUEUE; j++)
		{
			m_Barry[i][j] = false;
		}
	}
	if (!m_Map)
	{
		m_Map = SDL_CreateTexture(m_Renderer, 0, SDL_TEXTUREACCESS_TARGET, MAP_WIDTH, MAP_HEIGHT);
	}
	if (!m_Map)
	{
#ifdef _SDL_DEBUG
		cout << "SDL_Map.cpp	CMap	创建地图纹理失败！SDL Error:" << SDL_GetError() << endl;
#endif
		return false;
	}
	SDL_SetRenderTarget(m_Renderer, m_Map);
	SDL_SetRenderDrawBlendMode(m_Renderer, SDL_BLENDMODE_NONE);
	SDL_RenderClear(m_Renderer);
	for (int i = 0; i != MAP_ROW; i++)
	{
		for (int j = 0; j != MAP_QUEUE; j++)
		{
			SDL_RenderCopy(m_Renderer, m_AllSprites, &m_SourceRects[m_TargetRects[i][j].m_Position.x][m_TargetRects[i][j].m_Position.y], &m_TargetRects[i][j].m_Area);
		}
	}
	SDL_SetRenderTarget(m_Renderer, NULL);
	return true;
}

CMap::~CMap()
{
	SDL_DestroyTexture(m_AllSprites);
	SDL_DestroyTexture(m_Map);
	m_AllSprites = NULL;
	m_Map = NULL;
}

void CMap::SetBarry(SDL_Point* Barry, int i)
{
	for (int m = 0; m != TILE_ROW; m++)
	{
		for (int n = 0; n != TILE_QUEUE; n++)
		{
			for (int k = 0; k != i; k++)
			{
				if ((Barry[k].x == m) && (Barry[k].y == n))
				{
					m_Barry[m][n] = true;
				}
			}
		}
	}


	cout << endl << endl << endl;
	for (int i = 0; i != TILE_ROW; i++)
	{
		for (int j = 0; j != TILE_QUEUE; j++)
		{
			cout << m_Barry[i][j] << "    ";
		}
		cout << endl;
	}
	cout << endl << endl << endl;
	for (int i = 0; i != MAP_ROW; i++)
	{
		for (int j = 0; j != MAP_QUEUE; j++)
		{
			//cout << "位置：" << m_TargetRects[i][j].m_Position.x << "   " << m_TargetRects[i][j].m_Position.y<<"       ";
			cout << m_Barry[m_TargetRects[i][j].m_Position.x][m_TargetRects[i][j].m_Position.y] << "    ";
		}
		cout << endl;
	}
}

void CMap::SetWindow(SDL_Window* Window)
{
	m_Window = Window;
	if (m_Window)
	{
		m_Renderer = SDL_GetRenderer(m_Window);
#ifdef _SDL_DEBUG
		if (!m_Renderer)
		{
			cout << "SDL_Tile.cpp	CMap::SetWindow	设置窗口失败！SDL Error:" << SDL_GetError() << endl;
			cout << "SDL_Tile.cpp	CMap::SetWindow	m_Window = " << m_Window << endl;
			cout << "SDL_Tile.cpp	CMap::SetWindow	m_Renderer = " << m_Renderer << endl;
			cout << endl << endl << endl;
			return;
		}
#endif
	}
	else
	{
		return;
	}
}

bool CMap::LoadTile(string TilePath)
{
	SDL_Surface* TempSurface = NULL;

	TempSurface = IMG_Load(TilePath.c_str());
#ifdef _SDL_DEBUG
	if (!TempSurface)
	{
		cout << "SDL_Tile.cpp	LoadTile	从文件读取表面失败！SDL Error:" << SDL_GetError() << endl;
		cout << "SDL_Tile.cpp	LoadTile	TilePath = " << TilePath << endl;
		cout << endl << endl << endl;
		return false;
	}
#endif

	if (m_AllSprites)
	{
		SDL_DestroyTexture(m_AllSprites);
		m_AllSprites = NULL;
	}
	m_AllSprites = SDL_CreateTextureFromSurface(m_Renderer, TempSurface);
#ifdef _SDL_DEBUG
	if (!m_AllSprites)
	{
		cout << "SDL_Tile.cpp	LoadTile	从表面创建纹理失败！SDL Error:" << SDL_GetError() << endl;
		cout << "SDL_Tile.cpp	LoadTile	m_Surface = " << TempSurface << endl;
		cout << "SDL_Tile.cpp	LoadTile	m_AllSprites = " << m_AllSprites << endl;
		cout << endl << endl << endl;
		return false;
	}
#endif

	if (TempSurface)
	{
		SDL_FreeSurface(TempSurface);
	}

	for (int i = 0; i != TILE_ROW; i++)
	{
		for (int j = 0; j != TILE_QUEUE; j++)
		{
			m_SourceRects[i][j].x = j*TILE_WIDTH;
			m_SourceRects[i][j].y = i*TILE_HEIGHT;
			m_SourceRects[i][j].w = TILE_WIDTH;
			m_SourceRects[i][j].h = TILE_HEIGHT;
		}
	}
	return false;
}

bool CMap::LoadMap(string MapPath)
{
	ifstream In(MapPath.c_str());

#ifdef _SDL_DEBUG
	if (!In)
	{
		cout << "SDL_Tile.cpp	LoadMap	打开地图文件失败！" << endl;
		cout << endl << endl << endl;
		return false;
	}
#endif

	SDL_Point TempPosition;

	for (int i = 0; i != MAP_ROW; i++)
	{
		for (int j = 0; j != MAP_QUEUE; j++)
		{
			m_TargetRects[i][j].m_Area.x = j*TILE_WIDTH;
			m_TargetRects[i][j].m_Area.y = i*TILE_HEIGHT;
			m_TargetRects[i][j].m_Area.w = TILE_WIDTH;
			m_TargetRects[i][j].m_Area.h = TILE_HEIGHT;
			In >> TempPosition.x;
			In >> TempPosition.y;
			m_TargetRects[i][j].m_Position = TempPosition;
		}
	}

	for (int i = 0; i != TILE_ROW; i++)
	{
		for (int j = 0; j != TILE_QUEUE; j++)
		{
			m_Barry[i][j] = false;
		}
	}
	SDL_SetRenderTarget(m_Renderer, m_Map);
	SDL_SetRenderDrawBlendMode(m_Renderer, SDL_BLENDMODE_NONE);
	SDL_RenderClear(m_Renderer);
	for (int i = 0; i != MAP_ROW; i++)
	{
		for (int j = 0; j != MAP_QUEUE; j++)
		{
			SDL_RenderCopy(m_Renderer, m_AllSprites, &m_SourceRects[m_TargetRects[i][j].m_Position.x][m_TargetRects[i][j].m_Position.y], &m_TargetRects[i][j].m_Area);
		}
	}
	SDL_SetRenderTarget(m_Renderer, NULL);
	return true;
}

bool CMap::TouchWall(const SDL_Rect& Object,int x,int y)
{
	SDL_Rect Temp = { Object.x + x,Object.y + y,Object.w,Object.h };
	int j = Temp.x / TILE_WIDTH;
	int i = Temp.y / TILE_HEIGHT;
	for (int x = i; x != i + 2; x++)
	{
		if (x == MAP_ROW)
		{
			break;
		}
		for (int y = j; y != j + 2; y++)

		{
			if (y == MAP_QUEUE)
			{

				break;
			}
			else if (CheckCollision(Temp, m_TargetRects[x][y].m_Area) && m_Barry[m_TargetRects[x][y].m_Position.x][m_TargetRects[x][y].m_Position.y])
			{
					return true;
			}
		}
	}
	return false;
}

bool CMap::MoveCamera(int x, int y)
{
	m_Camera.x += x;
	m_Camera.y += y;
	if (m_Camera.x < 0)
	{
		m_Camera.x = 0;
		return false;
	}
	else if ((m_Camera.x+m_Camera.w) > TILE_WIDTH*MAP_QUEUE)
	{
		m_Camera.x = TILE_WIDTH*MAP_QUEUE - m_Camera.w;
		return false;
	}
	if (m_Camera.y < 0)
	{
		m_Camera.y = 0;
		return false;
	}
	else if ((m_Camera.y+m_Camera.h) > TILE_HEIGHT*MAP_ROW)
	{
		m_Camera.y = TILE_HEIGHT*MAP_ROW - m_Camera.h;
		return false;
	}
	return true;
}

void CMap::Render()
{
	SDL_RenderCopy(m_Renderer, m_Map, &m_Camera, NULL);
}

void CMap::SetCamera(int Width, int Height, SDL_Point DefaultPosition)
{
	if (Width > 0)
	{
		m_Camera.w = Width;
	}
	if (Height > 0)
	{
		m_Camera.h = Height;
	}
	m_Camera.x = DefaultPosition.x;
	m_Camera.y = DefaultPosition.y;
}