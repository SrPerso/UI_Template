#ifndef _UI_ELEMENT_
#define _UI_ELEMENT_
#include "p2Point.h"
#include "p2List.h"
#include "SDL\include\SDL.h"
#include "j1Module.h"

enum type { TEXT, IMAGE, ELEMENT, BUTTON, UNKNOWN , TXTTYPER, VSCROLL,HSCROLL };
enum ElementsState { MouseIn, Mouseb1, Mouseb2, MouseOut, sUnknown };

class UIelement {
	friend class j1Gui;
public:

	UIelement(int, SDL_Rect, p2Point<int>,bool);
	UIelement(int,type, SDL_Rect, p2Point<int>, bool);
	~UIelement();

	void CheckInput(const UIelement* mouse_hover, const UIelement* focus);

	virtual bool update(const UIelement* mouse_hover, const UIelement* focus);
	virtual bool draw();
	virtual bool handle_intro();
	virtual void move();
	void SetAtMiddle();

	void SetLocalPos(int x, int y);
	virtual p2Point<int> getPosition();

	bool isMouseRect(int, int);


	SDL_Rect GetBox()const{	return box;	}
	SDL_Rect GetScreenRect()const;
	iPoint GetScreenPos() const;
	iPoint GetLocalPos() const;
	void SetParent(UIelement*);
	virtual UIelement* IsTheGrandParent();
	virtual void AddSon(UIelement*);

public:
	bool can_focus = false;
	bool active = true;
	bool interactive = false;
	bool mouse_inside = false;
	bool drag = false;
protected:

	int id;
	type elementType;
	p2Point<int> Position;
	bool have_focus = false;
	SDL_Rect box;
	bool canMove;
	UIelement* Parent=nullptr;
	j1Module* listener = nullptr;
	p2List<UIelement*> Sons;

public:
	bool isMoving = false;
	bool canUpdate = false;
	p2Point<int>LastPos = {0,0};
	ElementsState elementState = sUnknown;

};


#endif // !_UI_ELEMENT_