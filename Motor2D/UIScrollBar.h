#ifndef _SCROLLBAR_
#define _SCROLLBAR_


#include "UIelement.h"
#include "UItext.h"
class UIscrollBar :public UIelement {
public:
	UIscrollBar(int, SDL_Rect, p2Point<int>, bool);
	~UIscrollBar();
	bool draw();
	bool update();
	void SetNewSCoods(const int&, const int&);
	void move();

};
#endif // !_SCROLLBAR_
