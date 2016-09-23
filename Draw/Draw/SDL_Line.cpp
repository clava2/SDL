#include "SDL_Line.h"

CLine::CLine():
	m_Points(0),
	m_Dragging(false),
	m_Width(1)
{
}

CLine::~CLine()
{
}

void CLine::Render(SDL_Renderer* Renderer)
{
	if (m_Points.size() <= 1)
	{
		return;
	}
	vector<SDL_Point>::iterator ite = m_Points.begin();
	SDL_Color Old;
	SDL_GetRenderDrawColor(Renderer, &Old.r, &Old.g, &Old.b, &Old.a);
	SDL_SetRenderDrawColor(Renderer, m_Color.r, m_Color.g, m_Color.b, m_Color.a);
	while (ite != (m_Points.end()-1))
	{
		SDL_Rect Temp = {};
		SDL_RenderDrawLines(Renderer, &m_Points[0], m_Points.size());
		ite++;
	}
	SDL_SetRenderDrawColor(Renderer, m_Color.r, m_Color.g, m_Color.b, m_Color.a);
}
