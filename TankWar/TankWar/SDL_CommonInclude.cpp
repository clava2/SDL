#include "SDL_CommonInclude.h"

bool CheckCollision(const SDL_Rect& Object, const SDL_Rect& Area, bool Border)
{
	if (Border)
	{
		if ((Object.x + Object.w > Area.x) && (Object.x < Area.x) && ((Object.y + Object.h) > Area.y) && (Object.y < (Area.y + Area.h)))
		{
			return true;
		}
		else if ((Object.y + Object.h > Area.y) && (Object.y < Area.y) && ((Object.x + Object.w) > Area.x) && (Object.x < (Area.x + Area.w)))
		{
			return true;
		}
		else if(((Object.x+Object.w)>(Area.x+Area.w))&&(Object.x <(Area.x+Area.w)) && ((Object.y + Object.h) > Area.y) && (Object.y < (Area.y + Area.h)))
		{
			return true;
		}
		else if (((Object.y + Object.h) > (Area.y + Area.h)) && (Object.y  < (Area.y+Area.h)) && ((Object.x + Object.w) > Area.x) && (Object.x < (Area.x + Area.w)))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if ((Object.x + Object.w) <= Area.x)
		{
			return false;
		}
		else if ((Object.y + Object.h) <= Area.y)
		{
			return false;
		}
		else if (Object.x >= (Area.x + Area.w))
		{
			return false;
		}
		else if (Object.y>= (Area.y + Area.h))
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}