#ifndef _UI_TEXT_
#define _UI_TEXT_

#include "UIelement.h"
#include "p2SString.h"
class UItext :public UIelement {
public:
	UItext( SDL_Rect, p2SString, p2Point<int>, bool);
	~UItext();

	const char* getText()const;

	bool update(const UIelement* mouse_hover, const UIelement* focus);
	bool draw();
	bool handle_intro();
	void setText(const char*);
	void SetNewSCoods(const int&, const int&);
	void move();
	SDL_Rect getrect();
private:
	p2SString* text;
	SDL_Texture* texture;
	bool istyping = false;
};

#endif // !_UI_IMAGE_