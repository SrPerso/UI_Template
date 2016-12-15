#ifndef _UI_ELEMENT_
#define _UI_ELEMENT_
#include "p2Point.h"
#include "p2List.h"
#include "SDL\include\SDL.h"
#include "j1Module.h"

enum type { TEXT, IMAGE, ELEMENT, BUTTON,MOUSE_CURSOR, UNKNOWN , TXTTYPER, VSCROLL,HSCROLL };
enum ElementsState { MouseIn, Mouseb1, Mouseb2, MouseOut, sUnknown };

class UIelement {
	friend class j1Gui;
public:

	UIelement() { elementType = UNKNOWN;	}
	UIelement(int, SDL_Rect, p2Point<int>,bool);
	UIelement(int,type, SDL_Rect, p2Point<int>, bool);
	~UIelement();

	virtual bool update(const UIelement* mouse_hover, const UIelement* focus);
	virtual bool draw();
	virtual bool handle_intro();
	virtual void move();

	void SetAtMiddle();
	void SetLocalPos(int x, int y);
	void SetListener(j1Module* module);
	void SetBox(SDL_Rect newBox) { box = newBox; }
	void SetSize(int x, int y){}
	void SetParent(UIelement*);

	virtual p2Point<int> getPosition();
	SDL_Rect GetBox()const { return box; }
	SDL_Rect GetScreenRect()const;
	iPoint GetScreenPos() const;
	iPoint GetLocalPos() const;
	
	void CheckInput(const UIelement* mouse_hover, const UIelement* focus);
	bool isMouseRect(int, int);
	virtual UIelement* IsTheGrandParent();
	virtual void AddSon(UIelement*);

public:

	bool can_focus = false;
	bool active = true;
	bool interactive = false;
	bool mouse_inside = false;
	bool canMove = false;
	bool isMoving = false;
	bool canUpdate = false;

	p2Point<int>LastPos = { 0,0 };
protected:

	int id;
	bool have_focus = false;

	type elementType;
	p2Point<int> Position;
	SDL_Rect box;

protected:
	UIelement* Parent=nullptr;
	j1Module* listener = nullptr;
	p2List<UIelement*> Sons;

public:	
	ElementsState elementState = sUnknown;//
	UIEvents elementState2;


};


#endif // !_UI_ELEMENT_