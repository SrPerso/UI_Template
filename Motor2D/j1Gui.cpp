#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "UIbutton.h"
#include "UIelement.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");
	
	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());	
	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	bool ret=true;
	p2List_item<UIelement*>*iterator;
	iterator = elementlist.start;

	const UIelement* mouse_hover = FindMouseHover();
	while (iterator != nullptr) {
		if(iterator->data->IsTheGrandParent() != nullptr)
		iterator->data->update(mouse_hover, focus);
		iterator = iterator->next;
	}
	p2List_item<UIelement*>* item;

	// if TAB find the next item and give it the focus
	if (App->input->GetKey(SDL_SCANCODE_TAB) == j1KeyState::KEY_DOWN)
	{
		int pos = elementlist.find((UIelement*)focus);
		if (pos > 0)
		{
			focus = nullptr;
			item = elementlist.At(pos);
			if (item)
				item = item->next;
			for (item; item; item = item->next)
				if (item->data->can_focus == true && item->data->active == true)
				{
					focus = item->data;
					break;
				}
		}
		if (focus == nullptr)
		{
			for (item = elementlist.start; item; item = item->next)
				if (item->data->can_focus == true && item->data->active == true)
				{
					focus = item->data;
					break;
				}
		}
	}

	// Now the iteration for input and update
	for (item = elementlist.start; item; item = item->next)
		if (item->data->interactive == true && item->data->active == true)
			item->data->CheckInput(mouse_hover, focus);

	for (item = elementlist.start; item; item = item->next)
		if (item->data->active == true)
		{
			item->data->update(mouse_hover, focus);
		}


	return ret;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{

	p2List_item<UIelement*>* item;

	for (item = elementlist.start; item; item = item->next)
	{
		if (item->data->active == true)
		{
			item->data->draw();
		}
	}
	
	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");


	for (int i = 0; i < elementlist.count(); i++)
		delete elementlist[i];


	elementlist.clear();

	return true;
}


// const getter for atlas
SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

const UIelement* j1Gui::FindMouseHover()const
{
	iPoint mouse;
	App->input->GetMousePosition(mouse.x, mouse.y);

	for (p2List_item<UIelement*>* item = elementlist.end; item; item = item->prev)
	{
		if (item->data->interactive == true)
		{
			if (item->data->GetScreenRect().Contains(mouse.x, mouse.y))
				return item->data;
		}
	}

	return nullptr;
}

//enable

void j1Gui::EnableGui(UIelement* elem)
{
	if (elem != NULL)
	{
		if (elem->Sons.count() > 0)
		{
			for (p2List_item<UIelement*>* i = elem->Sons.end; i; i = i->prev)
			{
				EnableGui(i->data);
			}
		}
		elem->active = true;
	}
}

// class Gui ---------------------------------------------------

UIelement * j1Gui::CreateElement(const typegui elementType, SDL_Rect box, p2Point<int>Position, bool move)
{
	assert(elementType == UIBUT || elementType == UIELEMENT);

	UIelement* created = nullptr;

	switch (elementType)
	{
	case UIBUT:

		created = new UIbutton(id, box, Position, move);
		break;

	case UIELEMENT:

		created = new UIelement(id, box, Position, move);
		break;

	}//switch

	if (created != nullptr)
	{
		elementlist.add(created);
		id++;
	}

	return created;
}

UIelement* j1Gui::CreateElement(const typegui elementType, SDL_Rect box, p2SString text, p2Point<int>Position, bool move)
{
	assert(elementType == UITXT || elementType == UITXTTYPER);

	UIelement* created = nullptr;

	switch (elementType)
	{
	case UITXT:

		created = new UIText(id, box, text, Position, move, TEXT);
		break;
	case UITXTTYPER:

		created = new UIText(id, box, text, Position, move, TXTTYPER);
		break;

	}//switch

	if (created != nullptr)
	{
		elementlist.add(created);
		id++;
	}

	return created;
}//create element
