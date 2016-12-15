#include "UIMouse.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Gui.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Scene.h"

// class GuiMCursor ---------------------------------------------------
UICursor::UICursor(int margin_x, int margin_y) : UIelement(), margin(margin_x, margin_y)
{
	section.x = section.y = 0;

	curs = App->gui->GetAtlas();
	App->tex->GetSize(curs, (uint&)section.w, (uint&)section.h);

	SetSize(section.w, section.h);
	iPoint p;
	App->input->GetMousePosition(p.x, p.y);
	SetLocalPos(p.x - margin.x, p.y - margin.y);
	elementType = MOUSE_CURSOR;
}

// --------------------------
UICursor::UICursor( const SDL_Rect& section, int margin_x, int margin_y) : UIelement(), section(section), margin(margin_x, margin_y)
{
	curs = App->gui->GetAtlas();
	SetSize(section.w, section.h);
	iPoint p;
	App->input->GetMousePosition(p.x, p.y);
	SetLocalPos(p.x - margin.x, p.y - margin.y);
	elementType = MOUSE_CURSOR;
}

// --------------------------
UICursor::~UICursor()
{}

//---------------------------
SDL_Rect UICursor::GetSection()const
{
	return section;
}

// --------------------------
void UICursor::SetSection(const SDL_Rect& section)
{
	this->section = section;
}

// --------------------------
bool UICursor::draw() 
{
	SDL_ShowCursor(SDL_DISABLE);

	iPoint p;
	App->input->GetMousePosition(p.x, p.y);
	App->render->Blit(curs, p.x - margin.x, p.y - margin.y, (SDL_Rect*)&section, 0.0f);
	return true;
}

//----------------------------

SDL_Texture* UICursor::GetTexture()const
{
	return curs;
}

//----------------------------

void UICursor::Update(const UIelement* mouse_hover, const UIelement* focus)
{
	
		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == j1KeyState::KEY_DOWN)
			App->scene->behaviour(this, UIEvents::mouse_lclick_down);

		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == j1KeyState::KEY_UP)
			App->scene->behaviour(this, UIEvents::mouse_lclick_up);

		if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == j1KeyState::KEY_DOWN)
			App->scene->behaviour(this, UIEvents::mouse_rclick_down);

		if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == j1KeyState::KEY_UP)
			App->scene->behaviour(this, UIEvents::mouse_lclick_up);

}
