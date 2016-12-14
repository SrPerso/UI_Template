#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "UIelement.h"
#include "UItext.h"
#define CURSOR_WIDTH 2


enum typegui { UITXT, UIBUT, UIELEMENT, UIUNKNOWN, UITXTTYPER};
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
	return_down
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
	UIelement* CreateElement(const typegui, SDL_Rect, p2SString, p2Point<int>, bool);

	void EnableGui(UIelement* elem);

	SDL_Texture* GetAtlas() const;

	p2List<UIelement*> GetElementlist() {	return elementlist;	}
	p2List<UIelement*> elementlist;



private:

	int id = 0;
	const UIelement *focus = nullptr;
	SDL_Texture* atlas;

	p2SString atlas_file_name;
	//p2SString wow_file_font;
	

};

#endif // __j1GUI_H__