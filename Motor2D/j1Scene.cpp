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
bool j1Scene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;

	for (label = config.child("ui_label"); label; label = label.next_sibling("ui_label"))
		labels.add({ label.child_value(), label.attribute("x").as_uint(0), label.attribute("y").as_uint(0), label.attribute("drag").as_bool(false) });

	label2 = config;
	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{


	debug_tex = App->tex->Load("maps/path.png");

	if (App->map->Load("iso_walk.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;
		if (App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}




	// Load textures
	background = App->tex->Load("textures/login_background.png");


		p2List_item<ui_label>* item = labels.start;
	while(item)
	{
		UIlabel* l = App->gui->CreateLabel(item->data.text.GetString(), { (int)item->data.x,(int)item->data.y });

		if(item->data.draggable == true)
		{
			l->interactive = true;
			l->canMove = true;
		}

		item = item->next;
	}



	//--------------------------UI-----------------------------------------------------------------

	//create Window ----------------------------------------

	//window = App->gui->CreateElement(UIELEMENT, SDL_Rect{ 0, 512, 484, 512 }, p2Point<int>{400, 50}, true);
	//window->SetAtMiddle();
	//window->interactive = true;
	//window->cut_childs = false;
	//static text ----------------------------------------
	//title = App->gui->CreateLabel("Window Title", p2Point<int>{450, 160});
	//title->SetParent(window);

	////button  --------------------------------------------
	//button = App->gui->CreateElement(UIELEMENT, SDL_Rect{ 0, 110, 230, 71 }, p2Point<int>{525, 450}, false);
	////button->SetListener(this);
	//button->interactive = true;
	//button->can_focus = true;
	////text button 
	//text = App->gui->CreateLabel("Button", p2Point<int>{620, 470 });
	//button->AddSon(text);//tree
	//window->AddSon(button);//tree

	////back text typer------------------------------------
	//Text_typer_back = App->gui->CreateElement(UIELEMENT, SDL_Rect{ 485, 566, 350, 66 }, p2Point<int>{475, 375}, false);
	//Text_typer_back->interactive = true;
	//Text_typer_back->can_focus = true;
	//window->AddSon(Text_typer_back);//tree

	////typer  -------------------------------------------
	//typer  = App->gui->Createtyper(UITXTTYPER, SDL_Rect{ 0, 0, 0, 0 }, "Type Here..", p2Point<int>{500, 400}, false);
	//Text_typer_back->AddSon(typer);//tree

	////vertical scroll -.----------------------------------
	//Vscroll = App->gui->CreateVScroll(SDL_Rect{ 0, 512, 484, 512 }, p2Point<int>{500, 500}, false, SDL_Rect{ 986, 874, 12, 150 }, SDL_Rect{ 950, 806, 9, 47 }, {50, 50, 0, 95 }, { 51, 58 }, 5);
	//

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
	static iPoint origin;
	static bool origin_selected = false;

	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);

	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		if (origin_selected == true)
		{
			App->pathfinding->CreatePath(origin, p);
			origin_selected = false;
		}
		else
		{
			origin = p;
			origin_selected = true;
		}
	}


	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	
	//// -------
	//if(App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
	////App->LoadGame("save_game.xml");

	//if(App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
	////App->SaveGame("save_game.xml");

	//if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	//App->render->camera.y += (int) floor(200.0f * dt);

	//if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	//App->render->camera.y -= (int) floor(200.0f * dt);

	//if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	//App->render->camera.x += (int) floor(200.0f * dt);

	//if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	//App->render->camera.x -= (int)floor(200.0f * dt);
	
	App->map->Draw();

	int x, y;
	App->input->GetMousePosition(x, y);

	// Debug pathfinding ------------------------------
	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);
	p = App->map->MapToWorld(p.x, p.y);

	App->render->Blit(debug_tex, p.x, p.y);

	const p2DynArray<iPoint>* path = App->pathfinding->GetLastPath();

	for(uint i = 0; i < path->Count(); ++i)
	{
	iPoint pos = App->map->MapToWorld(path->At(i)->x, path->At(i)->y);
	App->render->Blit(debug_tex, pos.x, pos.y);
	}
	

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
