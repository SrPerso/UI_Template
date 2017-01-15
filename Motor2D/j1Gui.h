#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "UIelement.h"
#include "UItext.h"
#include "UIScrollBar.h"
#include "UIRect.h"

#define CURSOR_WIDTH 2


enum typegui { 
	UITXT,
	UIBUT, 
	UIELEMENT,
	UITXTTYPER,
	UICURSOR,
	UIVSCRO,
	UIHSCRO,
	UIUNKNOWN,
	CONSOLE
};
enum UIEvents
{
	listening_ends,
	mouse_enters,
	mouse_leaves,
	mouse_lclick_down,
	mouse_lclick_up,
	mouse_rclick_down,
	mouse_rclick_up,
	gain_focus,
	lost_focus,
	input_changed,
	input_submit,
	value_changed,
	mouse_lclick_repeat,
	mouse_rclick_repeat,
	return_down,
	pushing_up,
	pushing_down,
	pushing_right,
	pushing_left,
};



// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	const UIelement* FindMouseHover()const;

public:
	// Gui creation functions
	UIelement* CreateElement(const typegui, SDL_Rect, p2Point<int>,bool);
	//UIelement* CreateElement(const typegui, SDL_Rect, p2SString,uint, p2Point<int>, bool, bool,int);
	UIlabel* CreateLabel( const char* text, p2Point<int> = {0,0}, typegui type = UITXT);
	UIVscrollBar* j1Gui::CreateVScroll(SDL_Rect box, p2Point<int>Position, bool move, const SDL_Rect& bar_sect, const SDL_Rect& thumb_sect, const SDL_Rect& offset, iPoint margins, float value);
	UIelement* Createtyper(const typegui elementType, SDL_Rect box, p2SString text, p2Point<int>Position, bool move);
	UIText* j1Gui::CreateInput(const SDL_Rect& section, const char* default_text, uint width, const iPoint& offset, bool password, int max_quantity, bool move = false);
	void EnableGui(UIelement* elem);
	bool DeleteGui(UIelement* elem);
	SDL_Texture* GetAtlas() const;
	p2List<UIelement*> GetElementlist() {	return elementlist;	}
	UIRect* CreateRect(const SDL_Rect& box, SDL_Color color, bool move = false);
	

	bool Load(pugi::xml_node& data);
	bool Save(pugi::xml_node& data) const;

	void SetFocus(const UIelement* ui);
	const UIelement* GetFocus() const;
private:

	p2List<UIelement*> elementlist;
	UIelement *focus = nullptr;
	SDL_Texture* atlas=nullptr;
	p2SString atlas_file_name;

};

#endif // __j1GUI_H__