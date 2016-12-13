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

bool UIelement::update()
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
				ite->data->update();
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

UIelement * UIelement::IsTheGrandParent()
{	
	if (Parent == nullptr) {
		return this;
	}
	
}
