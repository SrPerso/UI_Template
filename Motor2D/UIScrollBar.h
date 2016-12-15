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
	
	void move();

private:

	UIelement bar;
	UIelement thumb;
	iPoint margins;
	int min_y = 0;
	int max_y = 0;
	int thumb_pos = 0;
	float slider_value = 0;

};
#endif // !_SCROLLBAR_
