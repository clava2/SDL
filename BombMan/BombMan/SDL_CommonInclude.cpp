#include "SDL_CommonInclude.h"

bool CheckCollision(const SDL_Rect& Object, const SDL_Rect& Area, bool Border)
{
	if (Border)
	{
		if ((Object.x + Object.w > (Area.x+CORRECT_X_OFFSET)) && (Object.x < (Area.x + CORRECT_X_OFFSET))
			&& ((Object.y + Object.h) > (Area.y+CORRECT_Y_OFFSET)) && (Object.y < (Area.y - CORRECT_Y_OFFSET + Area.h)))
		{
			return true;
		}
		else if ((Object.y + Object.h > (Area.y+ CORRECT_Y_OFFSET)) && (Object.y < (Area.y+ CORRECT_Y_OFFSET)) 
			&& ((Object.x + Object.w) > (Area.x+ CORRECT_X_OFFSET)) && (Object.x < (Area.x- CORRECT_X_OFFSET + Area.w)))
		{
			return true;
		}
		else if(((Object.x+Object.w)>(Area.x - CORRECT_X_OFFSET +Area.w))&&(Object.x <(Area.x - CORRECT_X_OFFSET +Area.w)) 
			&& ((Object.y + Object.h) > (Area.y+ CORRECT_Y_OFFSET)) && (Object.y < (Area.y - CORRECT_Y_OFFSET + Area.h)))
		{
			return true;
		}
		else if (((Object.y + Object.h) > (Area.y - CORRECT_Y_OFFSET + Area.h)) && (Object.y  < (Area.y- CORRECT_Y_OFFSET +Area.h)) 
			&& ((Object.x + Object.w) > (Area.x+ CORRECT_X_OFFSET)) && (Object.x < (Area.x  - CORRECT_X_OFFSET + Area.w)))
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
		if ((Object.x + Object.w) <= (Area.x+ CORRECT_X_OFFSET))
		{
			return false;
		}
		else if ((Object.y + Object.h) <= (Area.y+ CORRECT_Y_OFFSET))
		{
			return false;
		}
		else if (Object.x >= (Area.x - CORRECT_X_OFFSET + Area.w))
		{
			return false;
		}
		else if (Object.y>= (Area.y - CORRECT_Y_OFFSET + Area.h))
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}