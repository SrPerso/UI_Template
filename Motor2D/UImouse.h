
#include "SDL\include\SDL.h"
#include "j1Module.h"
#include "p2Point.h"
#include "UIelement.h"

class UICursor :public UIelement
{
public:
	UICursor( int margin_x, int margin_y);
	UICursor( const SDL_Rect& section, int margin_x, int margin_y);
	~UICursor();

	void SetSection(const SDL_Rect& section);
	SDL_Rect GetSection()const;
	bool draw();
	void Update(const UIelement* mouse_hover, const UIelement* focus);
	SDL_Texture* GetTexture()const;

private:
	SDL_Rect section;
	SDL_Texture* curs = nullptr;
	iPoint margin;
};
