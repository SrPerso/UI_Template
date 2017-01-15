#include "UIRect.h"
#include "j1Module.h"
#include "j1Render.h"
#include "j1App.h"
#include "UIelement.h"
UIRect::UIRect(const SDL_Rect& box, p2Point<int>Position, SDL_Color color, bool move) :UIelement(UIRECT, box, Position, move), Color(color)
{
	SetSize(box.w, box.h);
}

UIRect::~UIRect()
{}


void UIRect::SetRectColor(SDL_Color color)
{
	Color = color;
}

bool UIRect::draw()
{
	App->render->DrawQuad({ box.x, box.y, box.w, box.h }, Color.r, Color.g, Color.b, Color.a);
	
	return true;
}