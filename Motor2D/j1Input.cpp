#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Window.h"
#include "SDL/include/SDL.h"
#define _CRT_SECURE_NO_WARNINGS
#define MAX_KEYS 300

j1Input::j1Input() : j1Module()
{
	name.create("input");

	keyboard = new j1KeyState[MAX_KEYS];
	memset(keyboard, KEY_IDLE, sizeof(j1KeyState) * MAX_KEYS);
	memset(mouse_buttons, KEY_IDLE, sizeof(j1KeyState) * NUM_MOUSE_BUTTONS);
}

// Destructor
j1Input::~j1Input()
{
	delete[] keyboard;
}

// Called before render is available
bool j1Input::Awake(pugi::xml_node& config)
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called before the first frame
bool j1Input::Start()
{
	SDL_StopTextInput();
	return true;
}

// Called each loop iteration
bool j1Input::PreUpdate()
{
	static SDL_Event event;
	
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for(int i = 0; i < MAX_KEYS; ++i)
	{
		if(keys[i] == 1)
		{
			if(keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if(keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	for(int i = 0; i < NUM_MOUSE_BUTTONS; ++i)
	{
		if(mouse_buttons[i] == KEY_DOWN)
			mouse_buttons[i] = KEY_REPEAT;

		if(mouse_buttons[i] == KEY_UP)
			mouse_buttons[i] = KEY_IDLE;
	}

	while(SDL_PollEvent(&event) != 0)
	{
		switch(event.type)
		{
			case SDL_QUIT:
				windowEvents[WE_QUIT] = true;
			break;

			case SDL_WINDOWEVENT:
				switch(event.window.event)
				{
					//case SDL_WINDOWEVENT_LEAVE:
					case SDL_WINDOWEVENT_HIDDEN:
					case SDL_WINDOWEVENT_MINIMIZED:
					case SDL_WINDOWEVENT_FOCUS_LOST:
					windowEvents[WE_HIDE] = true;
					break;

					//case SDL_WINDOWEVENT_ENTER:
					case SDL_WINDOWEVENT_SHOWN:
					case SDL_WINDOWEVENT_FOCUS_GAINED:
					case SDL_WINDOWEVENT_MAXIMIZED:
					case SDL_WINDOWEVENT_RESTORED:
					windowEvents[WE_SHOW] = true;
					break;
				}
			break;
	

			case SDL_KEYDOWN:
			{
				// Special case of micro controlling text input
				if (text_input == true)
				{
					switch (event.key.keysym.sym)
					{
					case SDLK_BACKSPACE:
						last_textinput.Cut(cursor - 1, cursor - 1);
						if (cursor > 0)
							cursor--;
						break;
					case SDLK_DELETE:
						if (cursor < last_textinput.Length())
							last_textinput.Cut(cursor, cursor);
						break;
					case SDLK_KP_ENTER:
					case SDLK_RETURN2:
					case SDLK_RETURN:
						selection_len = 1;
						break;
					case SDLK_LEFT:
						if (cursor > 0)
							cursor--;
						break;
					case SDLK_RIGHT:
						if (cursor < last_textinput.Length())
							cursor++;
						break;
					case SDLK_HOME:
						cursor = 0;
						break;
					case SDLK_END:
						cursor = last_textinput.Length();
						break;
					}
				}

				//LOG("Key %d changes state to %d", code, state);
			}

			case SDL_KEYUP:

				// Special case of micro controlling text input

				if (text_input)

				{

					switch (event.key.keysym.sym)

					{

					case SDLK_BACKSPACE:

						lastText.Cut(cursor - 1);

						if (cursor > 0)

							cursor--;

						break;

					case SDLK_DELETE:

						if (cursor < lastText.Length())

							lastText.Cut(cursor);

						break;

					case SDLK_KP_ENTER:

					case SDLK_RETURN2:

					case SDLK_RETURN:

						selection_len = 1;

						break;

					case SDLK_LEFT:

						if (cursor > 0)

							cursor--;

						break;

					case SDLK_RIGHT:

						if (cursor < lastText.Length())

							cursor++;

						break;

					case SDLK_HOME:

						cursor = 0;

						break;

					case SDLK_END:

						cursor = lastText.Length();

						break;

					}
				}
				break;

			case SDL_TEXTINPUT:

				lastText.operator+=(event.text.text);

				cursor += strlen(event.text.text);

				LOG("Input event: %s", event.edit.text);

				break;

			case SDL_MOUSEBUTTONDOWN:
				mouse_buttons[event.button.button - 1] = KEY_DOWN;
				//LOG("Mouse button %d down", event.button.button-1);
			break;

			case SDL_MOUSEBUTTONUP:
				mouse_buttons[event.button.button - 1] = KEY_UP;
				//LOG("Mouse button %d up", event.button.button-1);
			break;

			case SDL_MOUSEMOTION:
				int scale = App->win->GetScale();
				mouse_motion_x = event.motion.xrel / scale;
				mouse_motion_y = event.motion.yrel / scale;
				mouse_x = event.motion.x / scale;
				mouse_y = event.motion.y / scale;
				//LOG("Mouse motion x %d y %d", mouse_motion_x, mouse_motion_y);
			break;
		}
	}

	return true;
}

// Called before quitting
bool j1Input::CleanUp()
{
	LOG("Quitting SDL event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}

// ---------
bool j1Input::GetWindowEvent(j1EventWindow ev)
{
	return windowEvents[ev];
}

void j1Input::GetMousePosition(int& x, int& y)
{
	x = mouse_x;
	y = mouse_y;
}

void j1Input::GetMouseMotion(int& x, int& y)
{
	x = mouse_motion_x;
	y = mouse_motion_y;
}


void j1Input::StartTyping(SDL_Rect* rect, p2SString input) {

	text_input = true;
	SDL_StartTextInput();
	lastText = input;
	cursor = lastText.Length();

	if (rect != NULL)
		SDL_SetTextInputRect(rect);
}

void j1Input::StopTyping() {
	SDL_StopTextInput();
	text_input = false;
}

const char* j1Input::GetText(int& cursor, int& selection)const {
	cursor = this->cursor;
	selection = this->selection_len;

	return lastText.GetString();
}

void j1Input::TextInputTooLong()
{
	lastText = last_textinput;
	cursor = last_cursor;
}


void j1Input::StartTyping2() {
	if (!text_input) {
		text_input = true;
		SDL_StartTextInput();
	}
}
void j1Input::StopTyping2() {
	if (text_input) {
		text_input = false;
		SDL_StopTextInput();
	}
}
const char* j1Input::GetText2() {
	return lastText.GetString();
}

void j1Input::ClearTyping()
{
	cursor = selection_len = 0;
	last_textinput.Clear();

}
