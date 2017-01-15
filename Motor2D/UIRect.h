#ifndef _UI_RECT_
#define _UI_RECT_

#include "UIelement.h"

class UIRect : public UIelement
{
public:
	UIRect(const SDL_Rect& _rect, p2Point<int>Position, SDL_Color _color, bool move);
	~UIRect();
	
	void SetRectColor(SDL_Color color);
	bool draw();

private:

	SDL_Color Color;
};
#endif // !_UI_RECT_