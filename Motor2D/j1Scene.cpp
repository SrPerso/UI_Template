#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1PathFinding.h"
#include "j1Gui.h"
#include "UIelement.h"
#include "j1Scene.h"
#include "j1FileSystem.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;



	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{

	// Load textures
	background = App->tex->Load("textures/login_background.png");
	
	
	//create Window ->id==0;
	
	window = App->gui->CreateElement(UIELEMENT,	SDL_Rect{ 0, 512, 484, 512 },p2Point<int>{400, 50},	true);
	window->SetAtMiddle();
	window->interactive = true;

	// Create elements

	button = App->gui->CreateElement(UIELEMENT, SDL_Rect{ 0, 110, 230, 71 },p2Point<int>{525, 400}, false);
	//button->SetListener(this);
	button->interactive = true;
	button->can_focus = true;
	
	button->SetParent(window);
	//window->AddSon(button);
	textt = App->gui->CreateElement(UITXT, SDL_Rect{ 0, 0, 0, 0 }, "hELLO", p2Point<int>{ 525, 200 }, true);
	button->interactive = false;
	button->can_focus = false;
	window->AddSon(textt);



	//UIelement* button = App->gui->CreateElement(		UIBUT,		SDL_Rect{ 0, 110, 230, 71 },					p2Point<int>{525,400},	false);
	
	//UIelement* Text_typer_back = App->gui->CreateElement(UIBUT, SDL_Rect{ 485, 566, 350, 66 },					p2Point<int>{475, 300}, true);
	//UIelement* Text_typer = App->gui->CreateElement(	UITXTTYPER,		SDL_Rect{ 0, 0, 0, 0 },			"Type Here",	p2Point<int>{500, 325}, false);	

	//window->AddSon(button); 
	//
	//window->AddSon(Text_typer_back);
	//Text_typer_back->AddSon(Text_typer);
	 
	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{

	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	//--------------------------UI-----------------------------------------------------------------

		if (window)
			App->gui->EnableGui(window);

	//-----------------------------------------------------------------------------------------------
	
	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{

	App->gui->DeleteGui(window);

	LOG("Freeing scene");

	return true;
}




void j1Scene::behaviour(UIelement* ui, UIEvents event)
{
	/*Normal Button coords are {0,111,229,69} - hover state
	Bright Button coords are {410,169,229,69} - click state
	Dark Button coords are {645,165,229,69} - normal state
	*/

	if (ui == button)
	{
		switch (event)
		{
		case mouse_enters:
		case gain_focus:
			button->SetBox(SDL_Rect{ 0,113,229,69 });

			break;
		case mouse_lclick_repeat:
			ui->move();
			break;
		case mouse_leaves:
		case lost_focus:
			button->SetBox(SDL_Rect{ 642, 169, 229, 69 });
			break;

		case mouse_lclick_down:
			button->SetBox(SDL_Rect{ 411, 169, 229, 69 });
			break;

		case mouse_lclick_up:
			button->SetBox(SDL_Rect{ 0, 113, 229, 69 });
			break;

		case mouse_rclick_down:
			button->SetBox(SDL_Rect{ 411, 169, 229, 69 });
			break;

		case UIEvents::mouse_rclick_up:
			button->SetBox(SDL_Rect{ 0, 113, 229, 69 });
			break;
		}
	}
	/*
	if (ui == sliderH)
	{
		switch (event)
		{
		case value_changed:
			char n[20];
			sprintf_s(n, "Value: %0.2f", sliderH->GetValue());
			title->SetText(n);
			break;
		}
	}*/
	/*
	if (ui == image)
	{
		switch (event)
		{
		case UIEvents::mouse_enters:
			help->active = true;
			break;
		case UIEvents::mouse_leaves:
			help->active = false;
			break;
		}
	}
	*/

	/*
	if (ui->type == GuiTypes::mouse_cursor)
	{
		switch (event)
		{
		case mouse_lclick_down:
			curs->SetSection(rectangle{ 48, 1, 46, 48 });
			break;
		case mouse_lclick_up:
			curs->SetSection(rectangle{ 0, 1, 46, 48 });
			break;
		case mouse_rclick_down:
			curs->SetSection(rectangle{ 96, 1, 46, 48 });
			break;
		case mouse_rclick_up:
			curs->SetSection(rectangle{ 0, 1, 46, 48 });
			break;
		}
	}*/


}