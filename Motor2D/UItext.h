#ifndef _UI_TEXT_
#define _UI_TEXT_

#include "UIelement.h"
#include "p2SString.h"
class UIText :public UIelement {
public:
	UIText(int, SDL_Rect,p2SString,p2Point<int>, bool);
	~UIText();

	const char* getText()const;

	bool update();
	bool draw();
	bool handle_intro();
	void setText(const char*);
	void SetNewSCoods(const int&, const int&);
	void move();
	SDL_Rect getrect();
private:
	p2SString* text;
	SDL_Texture* texture;
};

#endif // !_UI_IMAGE_