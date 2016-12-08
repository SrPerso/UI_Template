#include "UIbutton.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Gui.h"
#include "j1Input.h"


UIbutton::UIbutton(int id, SDL_Rect box, p2Point<int>Position,bool move) :UIelement(id, BUTTON, box, Position,move)
{
}

UIbutton::~UIbutton()
{
}

bool UIbutton::draw()
{

	if (elementState == MouseIn) {
		SetNewSCoods(411, 166);
	}
	else if (elementState == Mouseb1 || elementState == Mouseb2) {
		SetNewSCoods(642,166);
	}
	else if (elementState == MouseOut) {
		SetNewSCoods(0, 110);
	}

	App->render->Blit(App->gui->GetAtlas(), Position.x, Position.y, &GetBox());	

	return true;
}

bool UIbutton::update()
{
	bool ret = false;



	iPoint MousePos, MousePos2;

	App->input->GetMousePosition(MousePos.x, MousePos.y);

	if (isMouseRect(MousePos.x, MousePos.y) == true) {
		elementState = MouseIn;

		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT)) {
			elementState = Mouseb1;

			if (canMove == true) {
				move();
			}
		}
		else if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT)) {
			elementState = Mouseb2;
		}
	}
	else {
		elementState = MouseOut;
	}

	LastPos.x = MousePos.x;
	LastPos.y = MousePos.y;


	ret = PositionOParent();
	draw();

	return ret;
}

void UIbutton::SetNewSCoods(const int& x,const int& y)
{
	box.x = x;
	box.y = y;
}
