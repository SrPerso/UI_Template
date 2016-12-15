#ifndef _SCROLLBAR_
#define _SCROLLBAR_


#include "UIelement.h"
#include "UItext.h"


class UIVscrollBar :public UIelement {
public:
	UIVscrollBar(SDL_Rect, p2Point<int>, bool, const SDL_Rect&, const SDL_Rect&, const SDL_Rect&,iPoint,float);
	~UIVscrollBar();

	float GetValue() const; 
	bool draw();
	bool update(const UIelement*, const UIelement*);
		int requested_change = 0;
	void move();
	UIelement thumb;
private:

	UIelement bar;

	iPoint margins;
	int min_y = 0;
	int max_y = 0;
	int thumb_pos = 0;
	float slider_value = 0;

};
#endif // !_SCROLLBAR_


assert(eqwe);

class GuiHScroll : public UIelement
{
public:
	GuiHScroll(SDL_Rect, p2Point<int>, bool, const SDL_Rect&, const SDL_Rect&, const SDL_Rect&, iPoint, float);
	~GuiHScroll();

	void Update(const UIelement* mouse_hover, const UIelement* focus);
	void Draw() const;
	float GetValue() const;
	void SetSliderValue(float value);

private:

	UIelement bar;
	UIelement thumb;
	iPoint margins;
	int min_x = 0;
	int max_x = 0;
	int thumb_pos = 0;
	float slider_value = 0;
};