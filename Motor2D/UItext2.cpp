#include "UItext2.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Gui.h"
#include "j1Input.h"
#include "j1Fonts.h"

UItext::UItext(SDL_Rect box, p2SString text, p2Point<int>Position, bool move) :UIelement(TXTTYPER, box, Position, move)
{
	this->text = new p2SString(text);
	texture = App->font->Print(getText(), { (255),(160),(0),(0) }, App->font->default);

}

UItext::~UItext()
{
}

const char* UItext::getText() const
{
	return text->GetString();
}

bool UItext::update(const UIelement* mouse_hover, const UIelement* focus)
{
	bool ret = true;

	int w = 0, h = 0;

	App->font->CalcSize(text->GetString(), w, h);

	box = { Position.x,Position.y,w + Position.x,h + Position.y };

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
				if (TXTTYPER) {
					App->input->StartTyping2();
					istyping = true;
				}
				if (canMove == true)
					move();
			}
			else if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT)) 
				elementState = Mouseb2;
			
	
		}
		else {
			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) && TXTTYPER) {
				App->input->StopTyping();
				istyping = false;
			}

			elementState = MouseOut;
			isMoving = false;
		}
	}
	canUpdate = false;

	LastPos.x = MousePos.x;
	LastPos.y = MousePos.y;



	if (istyping == true && TXTTYPER) {
		texture = App->font->Print(App->input->GetText2(), { (255),(160),(0),(0) }, App->font->default);
	}


	return ret;
}

bool UItext::draw()
{

	App->render->Blit(texture, Position.x, Position.y);

	return true;
}



bool UItext::handle_intro()
{
	return true;
}
void UItext::setText(const char *txt)
{
	delete text;
	text = new p2SString(txt);
	texture = App->font->Print(getText(), { (255),(160),(0),(0) }, App->font->default);
}

void UItext::SetNewSCoods(const int& x, const int& y)
{
	box.x = x;
	box.y = y;
}

SDL_Rect UItext::getrect()
{
	SDL_Rect ret;
	int x = 0, y = 0;

	ret.x = Position.x + App->render->camera.x;
	ret.y = Position.y + App->render->camera.y;

	App->font->CalcSize(getText(), x, y, App->font->default);

	ret.w = Position.x + x + App->render->camera.x;
	ret.h = Position.y + y + App->render->camera.y;

	return SDL_Rect(ret);
}

void UItext::move()
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