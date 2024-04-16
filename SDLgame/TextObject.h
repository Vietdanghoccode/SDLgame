#pragma once

#include "SDL.h"
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include "LogStatus.h"

class TextObject 
{
private:
	LogStatus* TextConsole = new LogStatus();
	std::string text;
	SDL_Color text_color;
	SDL_Texture* texture;
	int width;
	int height;
public:
	TTF_Font* fontTime;

	TextObject();
	~TextObject();

	enum TextColor
	{
		RED_TEXT = 0,
		WHITE_TEXT = 1,
		BLACK_TEXT = 2,
	};

	bool LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen);
	void Free();

	void SetColor(Uint8 red, Uint8 green, Uint8 blue);
	void SetColor(int type);
	void RenderText(SDL_Renderer* renderer, int posX, int posY,
		SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL,
		SDL_RendererFlip flip = SDL_FLIP_NONE);

	int getWidth() {
		return this->width;
	}
	int getHeight() {
		return this->height;
	}
	void SetText(std::string text_) {
		this->text = text_;
	}
	std::string GetText() {
		return this->text;
	}
 

};