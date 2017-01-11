#include "UIScrollBar.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Gui.h"
#include "j1Input.h"
#include "j1Scene.h"

UIVscrollBar::UIVscrollBar(SDL_Rect box, p2Point<int>Position, bool move, const SDL_Rect& bar_sect, const SDL_Rect& thumb_sect, const SDL_Rect& offset, iPoint margins, float value)
	:UIelement( VSCROLL, box, Position, move), bar(ELEMENT,bar_sect, Position,false), thumb(ELEMENT, thumb_sect, Position, false), margins(margins), slider_value(value)
{

	SetSize(bar.GetBox().w + offset.w, bar.GetBox().h + offset.h);

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


	thumb.CheckInput( mouse_hover,focus);

	iPoint MousePos, MousePos2;

	App->input->GetMousePosition(MousePos.x, MousePos.y);


	if (thumb.isMouseRect(MousePos.x, MousePos.y) == true) {
	
		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
		{

			int Mx, My, Rx, Ry;

			App->input->GetMousePosition(Mx, My);

			Position.y += (My - LastPos.y);

		}

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

	if (isMouseRect(MousePos.x, MousePos.y) == true) {

		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == j1KeyState::KEY_REPEAT)
		{

			iPoint p = thumb.getPosition();

			int y = MIN(max_y, p.y);

			if (y < min_y)
				y = min_y;

			if (y != p.y)
			{
				App->scene->behaviour(this, value_changed);
				thumb.SetLocalPos(p.x, y);
			}
		}
	}

	return true;
}
  
void UIVscrollBar::move()
{
	int Mx, My;

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


//--------------------------
//
//
//GuiHScroll::GuiHScroll(const SDL_Rect& bar_sect, const SDL_Rect& thumb_sect, const SDL_Rect& offset, iPoint margins, float value)
//	: bar(App->gui->GetAtlas(), bar_sect), thumb(App->gui->GetAtlas(), thumb_sect), margins(margins), slider_value(value)
//{
//
//	SetSize(bar.GetBox().w + offset.w, bar.GetBox().h + offset.h);
//	this->bar.SetParent(this);
//	this->thumb.SetParent(this);
//	this->bar.SetLocalPos(offset.x, offset.y);
//	this->thumb.SetLocalPos(margins.x, margins.y);
//
//	min_x = margins.x;
//	max_x = bar.GetBox().w + offset.w - margins.x - thumb.GetBox().w;
//}
//
//GuiHScroll::~GuiHScroll()
//{
//}
//
//void GuiHScroll::Update(const UIelement* mouse_hover, const UIelement* focus)
//{
//	int requested_change = 0;
//
//	if (focus == this)
//	{
//		if (App->input->GetKey(SDL_SCANCODE_LEFT) == j1KeyState::KEY_REPEAT)
//		{
//			requested_change = -1;
//		}
//		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == j1KeyState::KEY_REPEAT)
//		{
//			requested_change = 1;
//		}
//	}
//
//	if (mouse_hover == this)
//	{
//		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == j1KeyState::KEY_REPEAT)
//		{
//			iPoint mouse;
//			App->input->GetMousePosition(mouse.x, mouse.y);
//			if (thumb.GetScreenRect().Contains(mouse.x, mouse.y))
//			{
//				iPoint motion;
//				App->input->GetMouseMotion(motion.x, motion.y);
//				requested_change = motion.x;
//			}
//			else
//			{
//				iPoint pos = thumb.GetScreenPos();
//				if (mouse.x < pos.x)
//					requested_change = -1;
//				else
//					requested_change = 1;
//			}
//		}
//	}
//
//	if (requested_change != 0)
//	{
//		iPoint p = thumb.GetLocalPos();
//		int x = MIN(max_x, p.x + requested_change);
//		if (x < min_x)
//			x = min_x;
//
//		if (x != p.x)
//		{
//			if (listener != NULL)
//				listener->behaviour(this, value_changed);
//			thumb.SetLocalPos(x, p.y);
//		}
//	}
//}
//
//void GuiHScroll::Draw()const
//{
//	bar.draw();
//	thumb.draw();
//}
//
//float GuiHScroll::GetValue() const
//{
//	iPoint p = thumb.GetLocalPos();
//	return float((p.x * slider_value) / max_x);
//}
//
//void GuiHScroll::SetSliderValue(float value)
//{
//	slider_value = value;
//}