#ifndef _UI_TEXTT_
#define _UI_TEXTT_

#include "UIelement.h"
#include "p2SString.h"


class UIlabel :public UIelement {
public:

	UIlabel();
	UIlabel(const char* text);
	UIlabel(const char* text, p2Point<int>);
	~UIlabel();

	void SetText(const char* text);
	const SDL_Texture* GetTexture() const;
	bool draw();
	void Draw();
public:

	SDL_Texture* texture = nullptr;
};


class UIText :public UIelement {
public:
	UIText(const SDL_Rect section,p2SString, uint, p2Point<int>, bool, type, bool, int);
	~UIText();

	const char* getText()const;

	bool update(const UIelement* mouse_hover, const UIelement* focus);
	bool draw();

	//bool handle_intro();
	//void setText(const char*);
	void SetNewSCoods(const int&, const int&);
	void move();
//	SDL_Rect getrect();

private:
	int max_quantity=10;
	int last_cursor = 0;
	iPoint cursor_coords = { 0, 0 };
	const char* Deftext;
	p2SString input;
	SDL_Texture* texture;

private:
	UIelement backgro;
	UIlabel text;

private:
	bool password= false;
	bool istyping = false;
	bool had_focus = false;
	bool show_def_text;
};

#endif // !_UI_TEXT_