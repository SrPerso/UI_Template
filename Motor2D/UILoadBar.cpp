//
//#include "UILoadBar.h"
//#include "j1App.h"
//#include "j1Render.h"
//#include "j1Gui.h"
//#include "j1Input.h"
//#include "j1Scene.h"
//
//
//UILoadBar::UILoadBar(int value, const SDL_Texture* texture, const SDL_Rect& bar_sect, const SDL_Rect& cover_sect, bool show_text) :
//	value(value), bar(texture, bar_sect), cover(texture, cover_sect), show_text(show_text), bar_section(bar_sect)
//{
//	sprintf_s(values, "%d", (int)actual_value_percentage);
//	percentage.SetText(values);
////	type = GuiTypes::load_bar;
//	cover.SetParent(this);
//	bar.SetParent(&cover);
//	bar_size.x = bar.GetBox().w;
//	bar_size.y = bar.GetBox().h;
//	SetSize(cover_sect.w, cover_sect.h);
//	percentage.SetParent(this);
//	percentage.SetAtMiddle();
//}
//
//UILoadBar::~UILoadBar()
//{
//}
//
//void UILoadBar::Grow(int percentage)
//{
//	if (actual_value_percentage + percentage >= 100)
//	{
//		actual_value_percentage = 100;
//	}
//	else
//		actual_value_percentage += percentage;
//}
//
//void UILoadBar::Decrease(int percentage)
//{
//	if (actual_value_percentage - percentage <= 0)
//	{
//		actual_value_percentage = 0;
//	}
//	else
//		actual_value_percentage -= percentage;
//}
//
//void UILoadBar::Update(const UIelement* mouse_hover, const UIelement* focus)
//{
//	bar_section.w = (bar_size.x * (actual_value_percentage / 100.0f));
//	bar_section.h = bar_size.y;
//	bar.SetBox(bar_section);
//
//	int v = ((actual_value_percentage * value) / 100.0f);
//
//	sprintf_s(values, "%d", (int)v);
//	percentage.SetText(values);
//}
//
//void UILoadBar::Draw()const
//{
//	cover.draw();
//	bar.draw();
//
//	if (show_text == true)
//	{
//		percentage.draw();
//	}
//}