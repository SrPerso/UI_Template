#pragma once

#include "UIelement.h"
#include "UItext.h"

class UILoadBar : public UIelement
{
public:
	UILoadBar(int value, const SDL_Texture* texture, const SDL_Rect& bar_sect, const SDL_Rect& cover_sect, bool show_text);
	~UILoadBar();

	void Update(const UIelement* mouse_hover, const UIelement* focus);
	void Draw()const;
	void Grow(int percentage);
	void Decrease(int percentage);

public:
	UIelement bar;
	UIelement cover;
	UIlabel percentage;
private:
	iPoint bar_size;
	int value;	//How much the hole bar represents
	char values[100];
	float actual_value_percentage = 100;		//How much the bar each iteration must represent
	SDL_Rect bar_section;
	bool show_text;
};