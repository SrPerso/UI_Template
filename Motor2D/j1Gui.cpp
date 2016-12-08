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

	while (iterator != nullptr) {
		if(iterator->data->IsTheGrandParent() != nullptr)
		iterator->data->update();
		iterator = iterator->next;
	}


	/*
	p2List_item<UIelement*>*iterator;
	p2List<UIelement*>* queue =  nullptr;

	iterator = elementlist.start;	

	while (iterator != nullptr){
		if (iterator->data->IsTheGrandParent() != nullptr) {
			queue->add(iterator->data->IsTheGrandParent());
		}		 
		iterator = iterator->next;
	}//while	

	iterator = queue->start;
	
	while (iterator != nullptr) {
		ret = iterator->data->update();
		ret = iterator->data->draw();
		iterator = iterator->next;
	}*/
	
	return ret;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
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

UIelement * j1Gui::CreateElement(const typegui elementType, SDL_Rect box,p2Point<int>Position, bool move)
{
	assert(elementType == UIBUT || elementType== UIELEMENT);

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
	assert( elementType == UITXT);

	UIelement* created = nullptr;
	
	switch (elementType)
	{
	case UITXT:

		created = new UIText(id, box, text, Position, move);
		break;
		
	}//switch

	if (created != nullptr)
	{
		elementlist.add(created);
		id++;
	}

		return created;
}//create element

// const getter for atlas
SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

// class Gui ---------------------------------------------------

