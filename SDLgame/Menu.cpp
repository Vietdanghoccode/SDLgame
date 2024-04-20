#include "Menu.h"

Menu::Menu() {
	menuEvent = new SDL_Event();
	console = new LogStatus();
	button[0].x = 30;
	button[0].y = 130;

	button[1].x = 30;
	button[1].y = 170;

	text_menu[0].SetText("New game");
	text_menu[0].SetColor(TextObject::BLACK_TEXT); // renderText?

	
	text_menu[1].SetText("Quit");
	text_menu[1].SetColor(TextObject::BLACK_TEXT);




}

Menu::~Menu() {
	menuEvent = NULL;
	delete menuEvent;
}

bool Menu::checkFocusOnButton(int x, int y, SDL_Rect& rect) {
	if (x >= rect.x && x <= rect.x + rect.w &&
		y >= rect.y && y <= rect.y + rect.h) {
		return true;
	}
	return false;
}

int Menu::MenuLoop(SDL_Renderer* renderer) {
	SDL_Surface* Image = IMG_Load("gfx/theme.png");
	SDL_Texture* theme = NULL;
	if (Image == NULL) {
		console->Status(IMG_GetError());

	}
	else {
		theme = SDL_CreateTextureFromSurface(renderer, Image);
	}
	SDL_FreeSurface(Image);
	Image = NULL;
	
	
	int x_m, y_m; // position of mouse
	while (true) {		
		SDL_RenderCopy(renderer, theme, 0, 0);
		SDL_Rect buttonrect[2];

		for (int i = 0; i < 2; i++) {
			text_menu[i].LoadFromRenderText(text_menu[i].fontMenu, renderer);
			buttonrect[i] = text_menu[i].RenderText(renderer, button[i].x, button[i].y);
		}
		while (SDL_PollEvent(menuEvent)) {
			switch (menuEvent->type) {
			case SDL_QUIT:
				return 1;// quit
				break;
			case SDL_MOUSEMOTION:
				{
					x_m = menuEvent->motion.x;
					y_m = menuEvent->motion.y;
					for (int i = 0; i < 2; i++) {
						if (checkFocusOnButton(x_m, y_m, buttonrect[i])) {
							if (selected[i] == false) {
								selected[i] = 1;
								text_menu[i].SetColor(TextObject::RED_TEXT);
							}
						}
						else {
							selected[i] = 0;
							text_menu[i].SetColor(TextObject::BLACK_TEXT);
						}
					}
					break;
				}
			case SDL_MOUSEBUTTONDOWN:
			{
				x_m = menuEvent->motion.x;
				y_m = menuEvent->motion.y;
				for (int i = 0; i < 2; i++) {
					if (selected[i]) {
						return i;
					}
				}
				break;
			}
			case SDL_KEYDOWN:
				if (menuEvent->key.keysym.sym == SDLK_ESCAPE) {
					return 1;
				}

			default:
				break;
			}
		}
		
		SDL_RenderPresent(renderer);
	}

}