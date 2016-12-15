
#include "SDL\include\SDL.h"
#include "j1Module.h"
#include "p2Point.h"
#include "UIelement.h"

class GuiMCursor :public UIelement
{
public:
	GuiMCursor( SDL_Texture* texture, int margin_x, int margin_y);
	GuiMCursor( SDL_Texture* texture, const SDL_Rect& section, int margin_x, int margin_y);
	~GuiMCursor();

	void SetSection(const SDL_Rect& section);
	SDL_Rect GetSection()const;
	void Draw() const;
	void Update(const UIelement* mouse_hover, const UIelement* focus);
	SDL_Texture* GetTexture()const;

private:
	SDL_Rect section;
	SDL_Texture* curs = nullptr;
	iPoint margin;
};
