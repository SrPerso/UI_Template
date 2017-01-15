#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"

struct SDL_Texture;
class UIlabel;
class UItext;
class UIVscrollBar;
struct Command;

struct ui_label
{
	p2SString text;
	uint x, y;
	bool draggable;
};

class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake(pugi::xml_node& config);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	void behaviour(UIelement* ui, UIEvents event);
	bool OnCommand(const Command* com, const p2DynArray<p2SString>& arguments, p2SString& return_message);
	UIelement* typer = NULL;
	p2List<ui_label> labels;
	pugi::xml_node label;
	pugi::xml_node label2;
private:
	SDL_Texture* background;
	SDL_Texture* debug_tex;
	//ui---------------------------
	UIelement* button = NULL;
	UIelement* window = NULL;
	UIelement* Text_typer = NULL;
	UIelement* textt = NULL;
	UIelement* curs = NULL;
	UIelement* Text_typer_back = NULL;
	UIlabel* text = NULL;
	UIlabel* title = NULL;
	UIVscrollBar* Vscroll = NULL;
	//ui---------------------------

	
	const Command* load = nullptr;
	const Command* save = nullptr;

};

#endif // __j1SCENE_H__