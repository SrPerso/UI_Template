#include "UItext.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Gui.h"
#include "j1Input.h"
#include "j1Scene.h"
#include "j1Fonts.h"
#include "j1Textures.h"

//label -> cant be modificable

UIlabel::UIlabel() : UIelement() {
	elementType = UILABEL;
	texture = NULL;
}
UIlabel::UIlabel(const char* text) : UIelement()
{
	SetText(text);
	elementType = UILABEL;
}

UIlabel::UIlabel(const char * text, p2Point<int>pos)
{
	SetText(text);
	elementType = UILABEL;
	Position = pos;
}

// --------------------------
UIlabel::~UIlabel()
{
	if (texture != nullptr && texture != App->gui->GetAtlas())
		App->tex->UnLoad(texture);
}

// --------------------------
void UIlabel::SetText(const char* text)
{
	if (texture != nullptr)
		SDL_DestroyTexture(texture);
	texture = App->font->Print(text, { (255),(160),(0),(0) }, App->font->default);

	int w, h;
	App->tex->GetSize(texture, (uint&)w, (uint&)h);
	SetSize(w, h);
}

// --------------------------
const SDL_Texture* UIlabel::GetTexture() const
{

	return texture;
}

// --------------------------

bool UIlabel::draw()
{
	App->render->Blit(texture, Position.x, Position.y);
	return true;
}


void UIlabel::Draw()
{
	iPoint p = GetScreenPos();
	App->render->Blit(texture, p.x, p.y);
}

//modificable text
UIText::UIText(SDL_Rect section, p2SString defaultText, uint width, p2Point<int>Position, bool move, type typeelemtn,bool Password, int Max_quantity)
	:UIelement(), input(defaultText), max_quantity(Max_quantity), backgro(ELEMENT, section, Position, move), text(defaultText.GetString(), Position)
{
	elementType = TXTTYPER;
	SetSize(width, text.GetScreenRect().h);
	text.Parent = this;
	backgro.Parent = this;

	backgro.SetLocalPos(Position.x-20, Position.y-25);
	max_quantity = Max_quantity;
	password = Password;

	Deftext = defaultText.GetString();

	show_def_text = true;


	App->font->CalcSize("A", cursor_coords.x, cursor_coords.y);
	if (this->max_quantity == 0)
		this->max_quantity = width / cursor_coords.x;
		cursor_coords.x = 0;
	
}

UIText::~UIText()
{
}

const char* UIText::getText() const
{	
	return Deftext;
}

bool UIText::update(const UIelement* mouse_hover, const UIelement* focus)
{

//	CheckInput(mouse_hover, focus);

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


	//------------------------------------------------------------------------------------------------

	if (interactive == false)
		return false;

	bool inside = (mouse_hover == this);
	bool have_focus = (focus == this);

	if (had_focus != have_focus)
	{
		if (have_focus == true)
		{
			if (show_def_text == true)
			{
				input.Clear();
				show_def_text = false;
			}
			App->input->StartTyping(nullptr, input);
		}
		else
		{
			if (input.Length() == 0)
			{
				input = Deftext;
				show_def_text = true;
				text.SetText(input.GetString());
			}
			if (focus->GetType() != TXTTYPER)
				App->input->StopTyping();
		}

		had_focus = have_focus;
	}

	static p2SString selected(100);
	if (have_focus == true)
	{

		int cursor, selection;
		p2SString user_input = App->input->GetText(cursor, selection);

		if (input != user_input || cursor != last_cursor)
		{
			if (input != user_input)
			{
				if (user_input.Length() > this->max_quantity)
				{
					user_input = input;
					cursor = last_cursor;
					App->input->TextInputTooLong();
				}

				input = user_input;
				if (password == true)
				{
					p2SString pass_hided;
					for (int x = input.Length(); x > 0; x--)
						pass_hided.Insert(0, "*");
					text.SetText(pass_hided.GetString());
				}
				else
					text.SetText(user_input.GetString());

				if (listener != nullptr)
					listener->behaviour(this, input_changed);
			}

			last_cursor = cursor;

			if (cursor > 0)
			{
				if (input.Length() >= selected.GetCapacity())
					selected.Reserve(input.Length() * 2);
				if (password == true)
				{
					p2SString pass_hided;
					for (int x = input.Length(); x > 0; x--)
						pass_hided.Insert(0, "*");
					pass_hided.SubString(0, cursor, selected);
					App->font->CalcSize(selected.GetString(), cursor_coords.x, cursor_coords.y);
				}
				else
				{
					input.SubString(0, cursor, selected);
					App->font->CalcSize(selected.GetString(), cursor_coords.x, cursor_coords.y);
				}
			}
			else
			{
				cursor_coords.x = 0;
			}
			//
		}
		if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
		{
			if (listener)
				listener->behaviour(this, return_down);
		}

		if (selection != 0 && listener != nullptr)
		{
			listener->behaviour(this, input_submit);
		}
	}
	return true;
}


bool UIText::draw()
{	
	backgro.draw();

	// render text
	if (input.Length() > 0)
		text.draw();

	// // render cursor
	if (have_focus == true)
	{
		iPoint pos = GetScreenPos();
		App->render->DrawQuad({ pos.x + (cursor_coords.x - (CURSOR_WIDTH / 2)), pos.y, CURSOR_WIDTH, cursor_coords.y }, 255, 255, 255, 255, true, false);
	}

	return true;
}

void UIText::move()
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
