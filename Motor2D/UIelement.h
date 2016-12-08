#ifndef _UI_ELEMENT_
#define _UI_ELEMENT_
#include "p2Point.h"
#include "p2List.h"
#include "SDL\include\SDL.h"

enum type { TEXT, IMAGE, ELEMENT, BUTTON, UNKNOWN };
enum ElementsState { MouseIn, Mouseb1, Mouseb2, MouseOut, sUnknown };

class UIelement {
public:

	UIelement(int, SDL_Rect, p2Point<int>,bool);
	UIelement(int,type, SDL_Rect, p2Point<int>, bool);
	~UIelement();

	virtual bool update();
	virtual bool draw();
	virtual bool handle_intro();
	virtual void move();

	virtual p2Point<int> getPosition();

	bool isMouseRect(int, int);
	SDL_Rect GetBox()const{	return box;	}

	virtual UIelement* IsTheGrandParent();
	virtual void AddSon(UIelement*);

protected:

	int id;
	type elementType;
	p2Point<int> Position;
	SDL_Rect box;
	bool canMove;
	UIelement* Parent=nullptr;
	p2List<UIelement*> Sons;

public:
	bool isMoving = false;
	bool canUpdate = false;
	p2Point<int>LastPos = {0,0};
	ElementsState elementState = sUnknown;
};


#endif // !_UI_ELEMENT_