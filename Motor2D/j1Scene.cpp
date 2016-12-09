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
#include "j1Scene.h"

#include "j1Fonts.h"
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
	
	// Create elements
	UIelement* window = App->gui->CreateElement(UIELEMENT, SDL_Rect{ 0, 512, 484, 512 }, p2Point<int>{400, 50},true);
	UIelement* button = App->gui->CreateElement(UIBUT, SDL_Rect{ 0, 110, 230, 71 }, {525,400}, false);
	UIelement* textt = App->gui->CreateElement(UITXT, SDL_Rect{ 0, 0, 0, 0 }, "hELLO", { 525,200 }, true);

	window->AddSon(button);
	window->AddSon(textt);

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


	App->gui->PreUpdate();

	//SDL_Color a{ ((0),(0),(0),(255)) };
	//App->render->Blit(App->font->Print("Hello world", a), 200, 180);

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
	LOG("Freeing scene");

	return true;
}
