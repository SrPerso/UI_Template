#include "UIelement.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Gui.h"
#include "j1Input.h"

UIelement::UIelement(int id, SDL_Rect box, p2Point<int>Position,bool canMove)
	:elementType(ELEMENT), box(box), id(id), Position(Position),canMove(canMove)
{
}
UIelement::UIelement(int id,type elementType, SDL_Rect box, p2Point<int>Position, bool canMove)
	:elementType(elementType),box(box),id(id), Position(Position), canMove(canMove)
{
}

UIelement::~UIelement()
{
}

bool UIelement::update(const UIelement* mouse_hover, const UIelement* focus)
{
	bool ret = true;

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
			//isMoving = false;
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

	

		if (Sons.count() != 0) {
			p2List_item<UIelement*>*ite = Sons.start;

			while (ite != nullptr) {
				ite->data->update(mouse_hover,focus);
				ite = ite->next;
			}
		}
	
	return ret;
}

bool UIelement::draw()
{
	bool ret = false;

	if (elementType ==ELEMENT){
		App->render->Blit(App->gui->GetAtlas(), Position.x, Position.y, &GetBox());
		ret = true;
	}

	return ret;
}

bool UIelement::handle_intro()
{
	return true;
}

SDL_Rect UIelement::GetScreenRect() const
{
	if (Parent != nullptr)
	{
		iPoint p = GetScreenPos();
		return{ p.x, p.y, box.w, box.h };
	}
	return box;
}
iPoint UIelement::GetScreenPos() const
{
	if (Parent != nullptr)
		return Parent->GetScreenPos() + iPoint(box.x, box.y);
	else
		return iPoint(box.x, box.y);
}

iPoint UIelement::GetLocalPos() const
{
	return iPoint(box.x, box.y);
}

void UIelement::move()
{
	int Mx, My,Rx,Ry;	

	App->input->GetMousePosition(Mx, My);
	
	
	Position.x += (Mx - LastPos.x );
	Position.y += (My - LastPos.y);

	if (Sons.count() != 0) {

		p2List_item<UIelement*>*ite = Sons.start;

		while (ite != nullptr) {

			ite->data->move();
			
			ite = ite->next;
		}
	}

	isMoving = true;
}

void UIelement::SetAtMiddle()
{
	int frame_w = (Parent) ? Parent->GetBox().w : App->render->camera.w;
	int frame_h = (Parent) ? Parent->GetBox().h : App->render->camera.h;

	SetLocalPos(frame_w / 2 - box.w / 2, frame_h / 2 - box.h / 2);
}

void UIelement::SetLocalPos(int x, int y)
{
	Position.x = x;
	Position.y = y;
}

void UIelement::AddSon(UIelement*son)
{
	Sons.add(son);

	if (son->Parent != this)
		son->Parent = this;
}

p2Point<int> UIelement::getPosition()
{
	return p2Point<int>(Position);
}

bool UIelement::isMouseRect(int MouseX, int MouseY)
{
	return (MouseX>=Position.x  && MouseX<=(Position.x+box.w)&&MouseY>= Position.y&&MouseY<=(Position.y+box.h));
}

void UIelement::SetParent(UIelement *dad)
{
	this->Parent = dad;
	dad->Sons.add(this);
}

UIelement * UIelement::IsTheGrandParent()
{	
	if (Parent == nullptr) {
		return this;
	}
	
}

void UIelement::CheckInput(const UIelement* mouse_hover, const UIelement* focus)
{
	bool inside = (mouse_hover == this);

	if (mouse_inside != inside)
	{
		mouse_inside = inside;
		if (listener != nullptr)
			listener->OnGui(this, (inside) ? mouse_enters :mouse_leaves);
	}

	if (inside == true)
	{
		if (listener != nullptr)
		{
			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
				listener->OnGui(this, mouse_lclick_down);

			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP)
				listener->OnGui(this, mouse_lclick_up);

			if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN)
				listener->OnGui(this, mouse_rclick_down);

			if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_UP)
				listener->OnGui(this,mouse_lclick_up);
		}

		if (drag == true && App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
		{
			iPoint p = GetLocalPos();
			iPoint motion;
			App->input->GetMouseMotion(motion.x, motion.y);
			SetLocalPos(p.x + motion.x, p.y + motion.y);
		}
	}

	if (have_focus != (focus == this))
	{
		if (listener != nullptr)
		{
			if (focus == this)
				listener->OnGui(this,gain_focus);
			else
				listener->OnGui(this,lost_focus);
		}
		have_focus = (focus == this);
	}

	if (have_focus == true && listener != nullptr)
	{
		if (App->input->GetKey(SDL_SCANCODE_RETURN) == j1KeyState::KEY_DOWN)
			listener->OnGui(this, mouse_lclick_down);

		if (App->input->GetKey(SDL_SCANCODE_RETURN) == j1KeyState::KEY_UP)
			listener->OnGui(this, mouse_lclick_up);
	}
}
