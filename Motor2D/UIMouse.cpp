#include "UIMouse.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Gui.h"
#include "j1Input.h"
#include "j1Textures.h"





// class GuiMCursor ---------------------------------------------------
GuiMCursor::GuiMCursor( SDL_Texture* texture, int margin_x, int margin_y) : UIelement(), curs(texture), margin(margin_x, margin_y)
{
	section.x = section.y = 0;
	App->tex->GetSize(texture, (uint&)section.w, (uint&)section.h);

	SetSize(section.w, section.h);
	iPoint p;
	App->input->GetMousePosition(p.x, p.y);
	SetLocalPos(p.x - margin.x, p.y - margin.y);
	elementType = MOUSE_CURSOR;
}

// --------------------------
GuiMCursor::GuiMCursor( SDL_Texture* texture, const SDL_Rect& section, int margin_x, int margin_y) : UIelement(), curs(texture), section(section), margin(margin_x, margin_y)
{
	SetSize(section.w, section.h);
	iPoint p;
	App->input->GetMousePosition(p.x, p.y);
	SetLocalPos(p.x - margin.x, p.y - margin.y);
	elementType = MOUSE_CURSOR;
}

// --------------------------
GuiMCursor::~GuiMCursor()
{}

//---------------------------
SDL_Rect GuiMCursor::GetSection()const
{
	return section;
}

// --------------------------
void GuiMCursor::SetSection(const SDL_Rect& section)
{
	this->section = section;
}

// --------------------------
void GuiMCursor::Draw() const
{
	SDL_ShowCursor(SDL_DISABLE);

	iPoint p;
	App->input->GetMousePosition(p.x, p.y);
	App->render->Blit(curs, p.x - margin.x, p.y - margin.y, (SDL_Rect*)&section, 0.0f);
}

//----------------------------

SDL_Texture* GuiMCursor::GetTexture()const
{
	return curs;
}

//----------------------------

void GuiMCursor::Update(const UIelement* mouse_hover, const UIelement* focus)
{
	if (listener != nullptr)
	{
		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == j1KeyState::KEY_DOWN)
			listener->behaviour(this, UIEvents::mouse_lclick_down);

		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == j1KeyState::KEY_UP)
			listener->behaviour(this, UIEvents::mouse_lclick_up);

		if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == j1KeyState::KEY_DOWN)
			listener->behaviour(this, UIEvents::mouse_rclick_down);

		if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == j1KeyState::KEY_UP)
			listener->behaviour(this, UIEvents::mouse_lclick_up);
	}
}
