#include "UItext.h"

UIText::UIText(int id,SDL_Rect box, p2SString text, p2Point<int>Position, bool move):UIelement(id,TEXT,box,Position, move),text(text)
{

}



UIText::~UIText()
{
}

p2SString UIText::getText() const
{
	return p2SString(text);
}

bool UIText::Update()
{
	return true;
}

bool UIText::Draw()
{	
	return true;
}

bool UIText::handle_intro()
{
	return true;
}
