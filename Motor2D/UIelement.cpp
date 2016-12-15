#include "UIelement.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Gui.h"
#include "j1Input.h"
#include "p2Log.h"
#include "j1Scene.h"

#include <stdio.h>
UIelement::UIelement( SDL_Rect box, p2Point<int>Position,bool canMove)
	:elementType(ELEMENT), box(box),  Position(Position),canMove(canMove)
{
	SetSize(box.w, box.h);

	textu = App->gui->GetAtlas();
}
UIelement::UIelement(type elementType, SDL_Rect box, p2Point<int>Position, bool canMove)
	:elementType(elementType),box(box),Position(Position), canMove(canMove)
{
}

UIelement::~UIelement()
{
}

bool UIelement::update(const UIelement* mouse_hover, const UIelement* focus)
{
	CheckInput(mouse_hover, focus);

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
					//behaviourr
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


	return ret;
}


bool UIelement::draw()
{

	bool ret= false;
	if (elementType == ELEMENT) {
		ret = true;
		if (Parent && Parent->cut_childs)
		{
			SDL_Rect rec = Parent->GetScreenRect();
			App->render->SetViewPort(rec);
		}

		App->render->Blit(App->gui->GetAtlas(), Position.x, Position.y, (SDL_Rect*)&box, 0.0f);
		if (Parent && Parent->cut_childs)
			App->render->ResetViewPort();
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
SDL_Rect UIelement::GetLocalRect() const
{
	return Rect;
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

void UIelement::SetAtMiddle()
{
	int frame_w = (Parent) ? Parent->GetLocalRect().w : App->render->camera.w;
	int frame_h = (Parent) ? Parent->GetLocalRect().h : App->render->camera.h;

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

void UIelement::SetListener(j1Module * module)
{
	if (listener != nullptr)
		listener->behaviour(this, listening_ends);

	listener = module;
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
	iPoint MousePos, MousePos2;

	App->input->GetMousePosition(MousePos.x, MousePos.y);

	if (isMouseRect(MousePos.x, MousePos.y) == true) {


		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN){
			App->scene->behaviour(this, mouse_lclick_down);
			isClicked = true;
		}
		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP){
			App->scene->behaviour(this, mouse_lclick_up);
			isClicked = true;
		}
		if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN){
			App->scene->behaviour(this, mouse_rclick_down);
			isClicked = true;
		}
		if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_UP) {
			App->scene->behaviour(this, mouse_lclick_up);
			isClicked = true;
		}


		if (canMove == true && App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
			App->scene->behaviour(this, mouse_lclick_repeat);

		if (canMove == true && App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_REPEAT)
			App->scene->behaviour(this, mouse_rclick_repeat);

		else if(isClicked != true)
			App->scene->behaviour(this, gain_focus);
		
	}



	else if(isMouseRect(MousePos.x, MousePos.y) == false&&isClicked==false)
		App->scene->behaviour(this, lost_focus);

	//keys ARROWWWWWWWW
	if (App->input->GetKey(	SDLK_DOWN) == KEY_DOWN)
		App->scene->behaviour(this, pushing_down);

	if (App->input->GetKey(SDLK_UP) == KEY_DOWN)
		App->scene->behaviour(this, pushing_up);

	if (App->input->GetKey(SDLK_LEFT) == KEY_DOWN)
		App->scene->behaviour(this, pushing_left);

	if (App->input->GetKey(SDLK_RIGHT) == KEY_DOWN)
		App->scene->behaviour(this, pushing_right);



	if (have_focus != (focus == this)){
	
			if (focus == this)
				App->scene->behaviour(this,gain_focus);
			else
				App->scene->behaviour(this,lost_focus);
		
		have_focus = (focus == this);
	}

	if (have_focus == true && listener != nullptr)
	{
		if (App->input->GetKey(SDL_SCANCODE_RETURN) == j1KeyState::KEY_DOWN)
			App->scene->behaviour(this, mouse_lclick_down);

		if (App->input->GetKey(SDL_SCANCODE_RETURN) == j1KeyState::KEY_UP)
			App->scene->behaviour(this, mouse_lclick_up);
	}
}
