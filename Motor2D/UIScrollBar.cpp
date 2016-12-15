#include "UIScrollBar.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Gui.h"
#include "j1Input.h"


UIVscrollBar::UIVscrollBar(SDL_Rect box, p2Point<int>Position, bool move, const SDL_Rect& bar_sect, const SDL_Rect& thumb_sect, const SDL_Rect& offset, iPoint margins, float value)
	:UIelement( VSCROLL, box, Position, move), bar(bar_sect, Position,false), thumb( thumb_sect, Position, false), margins(margins), slider_value(value)
{
	this->bar.SetParent(this);
	this->thumb.SetParent(this);

	this->bar.SetLocalPos(offset.x, offset.y);
	this->thumb.SetLocalPos(margins.x, margins.y);

	min_y = margins.y;
	max_y = bar.GetBox().h + offset.h - margins.y - thumb.GetBox().h;
}

UIVscrollBar::~UIVscrollBar()
{

}

float UIVscrollBar::GetValue() const
{
	iPoint p = thumb.GetLocalPos();

	return float((p.y * slider_value) / max_y);
}

bool UIVscrollBar::draw(){

	bar.draw();
	thumb.draw();

	return true;
}

bool UIVscrollBar::update(const UIelement* mouse_hover, const UIelement* focus)
{

	int requested_change = 0;


	if (focus == this)
	{
		if (App->input->GetKey(SDL_SCANCODE_UP) == j1KeyState::KEY_REPEAT)
		{
			requested_change = -1;
		}
		if (App->input->GetKey(SDL_SCANCODE_DOWN) == j1KeyState::KEY_REPEAT)
		{
			requested_change = 1;
		}

	}

	if (mouse_hover == this)
	{
		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == j1KeyState::KEY_REPEAT)
		{
			iPoint mouse;
			App->input->GetMousePosition(mouse.x, mouse.y);
			if (thumb.GetScreenRect().Contains(mouse.x, mouse.y))
			{
				iPoint motion;
				App->input->GetMouseMotion(motion.x, motion.y);
				requested_change = motion.y;
			}
			else
			{
				iPoint pos = thumb.GetScreenPos();
				if (mouse.y < pos.y)
					requested_change = -1;
				else
					requested_change = 1;
			}
		}
	}

	if (requested_change != 0)
	{
		iPoint p = thumb.getPosition();
		int y = MIN(max_y, p.y + requested_change);
		if (y < min_y)
			y = min_y;

		if (y != p.y)
		{
			if (listener != NULL)
				listener->behaviour(this, value_changed);
			thumb.SetLocalPos(p.x, y);
		}
	}




















	bool ret = false;

	iPoint MousePos, MousePos2;

	App->input->GetMousePosition(MousePos.x, MousePos.y);

	if (Sons.count() != 0) {

		p2List_item<UIelement*>*ite = Sons.start;

		while (ite != nullptr) {
			if (ite->data->isMoving == true)
				canUpdate = true;

			ite = ite->next;
		}
	}
	if (canUpdate == false) {

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
			isMoving = false;
		}
	}
	canUpdate = false;

	LastPos.x = MousePos.x;
	LastPos.y = MousePos.y;

	draw();

	return ret;
}
  
void UIVscrollBar::move()
{
	int Mx, My, Rx, Ry;

	App->input->GetMousePosition(Mx, My);

	Position.x += (Mx - LastPos.x);
	Position.y += (My - LastPos.y);

	isMoving = true;


	if (Sons.count() != 0) {

		p2List_item<UIelement*>*ite = Sons.start;

		while (ite != nullptr) {

			ite->data->move();

			ite = ite->next;
		}
	}
}