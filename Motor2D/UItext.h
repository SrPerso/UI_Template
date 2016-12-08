#ifndef _UI_TEXT_
#define _UI_TEXT_

#include "UIelement.h"
#include "p2SString.h"
class UIText :public UIelement {
public:
	UIText(int, SDL_Rect,p2SString,p2Point<int>, bool);
	~UIText();

	p2SString getText()const;

	bool Update();
	bool Draw();
	bool handle_intro();

private:
	p2SString text;
};

#endif // !_UI_IMAGE_