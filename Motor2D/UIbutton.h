#ifndef _UI_BUTTON_
#define _UI_BUTTON_
#include "UIelement.h"

class UIbutton:public UIelement {
public:
	UIbutton(int,SDL_Rect, p2Point<int>,bool);
	~UIbutton();
	bool draw();
	bool update();
	void SetNewSCoods(const int&, const int&);
	void move();
public:
	bool isMoving = false;
	bool canUpdate = false;

};



#endif // !_UI_IMAGE_
