#include "TextObject.h"

TextObject::TextObject() {
	text_color.r = 255;
	text_color.g = 255;
	text_color.b = 255;
	texture = NULL;
	if (TTF_Init() == -1) {
		TextConsole->Status("Failed to load time font");
	}
	fontTime = TTF_OpenFont("gfx//Roboto-Black.ttf", 15);
	if (fontTime == NULL) {
		TextConsole->Status("Can't load font time");
	}

}
TextObject::~TextObject() {

}

bool TextObject::LoadFromRenderText(TTF_Font* font, SDL_Renderer* renderer) 
{

	SDL_Surface* text_surface = TTF_RenderText_Solid(font, text.c_str(), text_color);
	if (text_surface) {
		texture = SDL_CreateTextureFromSurface(renderer, text_surface);
		this->width = text_surface->w;
		this->height = text_surface->h;
		SDL_FreeSurface(text_surface);
	}
	else {
		TextConsole->Status("Can't load the text from surface");
	}
	return texture != NULL;
}

void TextObject::Free() {
	if (texture != NULL) {
		SDL_DestroyTexture(texture);
		texture = NULL;

	}
}

void TextObject::SetColor(int type) {
	if (type == RED_TEXT) {
		SDL_Color color = { 255, 0, 0 };
		text_color = color;
	}
	else if (type == WHITE_TEXT) {
		SDL_Color color = { 255, 255, 255 };
		text_color = color;
	} else {
		SDL_Color color = { 0, 0, 0 };
		text_color = color;
	}
}

void TextObject::RenderText(SDL_Renderer* renderer, int posX, int posY,
	SDL_Rect* clip, double angle, SDL_Point* center,
	SDL_RendererFlip flip) 
{
	SDL_Rect renderQuad = { posX, posY, width, height };
	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);

}
