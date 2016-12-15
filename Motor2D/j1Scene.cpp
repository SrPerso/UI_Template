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
#include "UIScrollBar.h"
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


	//--------------------------UI-----------------------------------------------------------------

	//create Window ----------------------------------------

	window = App->gui->CreateElement(UIELEMENT, SDL_Rect{ 0, 512, 484, 512 }, p2Point<int>{400, 50}, true);
	window->SetAtMiddle();
	window->interactive = true;
	window->cut_childs = false;
	//static text ----------------------------------------
	title = App->gui->CreateLabel("Window Title", p2Point<int>{450, 160});
	title->SetParent(window);

	//button  --------------------------------------------
	button = App->gui->CreateElement(UIELEMENT, SDL_Rect{ 0, 110, 230, 71 }, p2Point<int>{525, 450}, false);
	//button->SetListener(this);
	button->interactive = true;
	button->can_focus = true;
	//text button 
	text = App->gui->CreateLabel("Button", p2Point<int>{620, 470 });
	button->AddSon(text);//tree
	window->AddSon(button);//tree

	//back text typer------------------------------------
	Text_typer_back = App->gui->CreateElement(UIELEMENT, SDL_Rect{ 485, 566, 350, 66 }, p2Point<int>{475, 375}, false);
	Text_typer_back->interactive = true;
	Text_typer_back->can_focus = true;
	window->AddSon(Text_typer_back);//tree

	//typer  -------------------------------------------
	typer  = App->gui->Createtyper(UITXTTYPER, SDL_Rect{ 0, 0, 0, 0 }, "Type Here..", p2Point<int>{500, 400}, false);
	Text_typer_back->AddSon(typer);//tree

	//vertical scroll -.----------------------------------
	Vscroll = App->gui->CreateVScroll(SDL_Rect{ 0, 512, 484, 512 }, p2Point<int>{500, 500}, false, SDL_Rect{ 986, 874, 12, 150 }, SDL_Rect{ 950, 806, 9, 47 }, {50, 50, 0, 95 }, { 51, 58 }, 5);
	

	//------------------------------------------
	//cursor  ------------------------------------------
	//curs = App->gui->CreateElement(UICURSOR, SDL_Rect{ 994,728, 25, 23 }, p2Point<int>{ 0, 0 },true);
	//curs->SetListener(this);
	//curs->interactive = true;
	//curs->can_focus = false;
	//-----------------------------------------------------------------------------------------------

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

	//App->gui->DeleteGui(window);

	LOG("Freeing scene");

	return true;
}

void j1Scene::behaviour(UIelement* ui, UIEvents event)
{

	if (ui == button)
	{
		switch (event)
		{
		case mouse_enters:
		case gain_focus:
			button->SetBox(SDL_Rect{ 0,113,229,69 });

			break;

		case mouse_leaves:
		case lost_focus:
			button->SetBox(SDL_Rect{ 642, 169, 229, 69 });
			break;

		case mouse_lclick_down:
			if(button->Parent->canMove != false)
				button->Parent->canMove = false; 
			else
				button->Parent->canMove = true;

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

	if (ui == &Vscroll->thumb)
	{
		switch (event)
		{
		case pushing_up:
			Vscroll->requested_change = -1;
			break;
		case pushing_down:
			Vscroll->requested_change = +1;
			break;
		case value_changed:
			char n[20];
			sprintf_s(n, "Value: %0.2f", Vscroll->GetValue());
			title->SetText(n);
			break;
		}
	}

	if (ui == curs)
	{
		switch (event)
		{
		case mouse_lclick_down:
			curs->SetBox(SDL_Rect{ 994, 704, 46, 48 });
			break;
		case mouse_lclick_up:
			curs->SetBox(SDL_Rect{ 994, 728, 25, 23 });
			break;
		case mouse_rclick_down:
			curs->SetBox(SDL_Rect{ 994,752, 25, 23 });
			break;
		case mouse_rclick_up:
			curs->SetBox(SDL_Rect{ 994, 728, 25, 23 });
			break;
		}
	}


}