#ifndef _UI_ELEMENT_
#define _UI_ELEMENT_
#include "p2Point.h"
#include "p2List.h"
#include "SDL\include\SDL.h"
#include "j1Module.h"

enum type { TEXT, IMAGE, ELEMENT, BUTTON,MOUSE_CURSOR, UNKNOWN , UILABEL, TXTTYPER,UIRECT, VSCROLL,HSCROLL };
enum ElementsState { MouseIn, Mouseb1, Mouseb2, MouseOut, sUnknown };

class UIelement {
	friend class j1Gui;
public:

	UIelement() { elementType = UNKNOWN;	}
	UIelement(SDL_Rect, p2Point<int>,bool);
	UIelement(type, SDL_Rect, p2Point<int>, bool);
	~UIelement();

	virtual bool update(const UIelement* mouse_hover, const UIelement* focus);
	virtual bool draw();
	virtual bool handle_intro();
	virtual void move();

	void SetAtMiddle();
	void SetLocalPos(int x, int y);
	void SetListener(j1Module* module);
	void SetBox(SDL_Rect newBox) { box = newBox; }
	void SetSize(int w, int h){
		Rect.w = w;
		Rect.h = h;
	}
	void SetParent(UIelement*);

	virtual p2Point<int> getPosition();
	SDL_Rect GetBox()const { return box; }
	SDL_Rect GetScreenRect()const;
	SDL_Rect GetLocalRect() const;
	iPoint GetScreenPos() const;
	iPoint GetLocalPos() const;
	type GetType()const { return elementType; }

	void Clear();

	void CheckInput(const UIelement* mouse_hover, const UIelement* focus);
	bool isMouseRect(int, int);
	virtual UIelement* IsTheGrandParent();
	virtual void AddSon(UIelement*);

public:
	bool cut_childs = false;
	bool can_focus = false;
	bool active = true;
	bool interactive = false;
	bool mouse_inside = false;
	bool canMove = false;
	bool isClicked = false;
	bool isMoving = false;
	bool canUpdate = false;
	UIelement* Parent = nullptr;

protected:

	bool have_focus = false;

protected:

	j1Module* listener = nullptr;
	p2List<UIelement*> Sons;
	type elementType;
	p2Point<int> Position;
	SDL_Rect box;

public:	
		const SDL_Texture* texture = nullptr;
	ElementsState elementState = sUnknown;//
	UIEvents elementState2;

	p2Point<int>LastPos = { 0,0 };

private:
	SDL_Rect Rect;
	SDL_Texture* textu = nullptr;
};


#endif // !_UI_ELEMENT_