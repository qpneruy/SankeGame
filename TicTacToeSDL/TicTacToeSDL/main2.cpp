/*#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string.h>
using namespace std;
SDL_Texture* LoadTexture(string path);
void Starup();
void close();
const int ngang = 640;
const int cao = 480;
SDL_Window* Screen = NULL;
SDL_Renderer* Rendered = NULL;
SDL_Texture* Texture = NULL;
void Starup() {
	Screen = SDL_CreateWindow("A window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ngang, cao, SDL_WINDOW_SHOWN);
	Rendered = SDL_CreateRenderer(Screen, -1, SDL_RENDERER_ACCELERATED);
	Texture = LoadTexture("D:/Project/Project_Img/stretch.bmp");
}
SDL_Texture* LoadTexture(string path) {
	SDL_Texture* Ketcau = NULL;
	SDL_Surface* bemat = IMG_Load(path.c_str());
	Ketcau = SDL_CreateTextureFromSurface(Rendered, bemat);
	SDL_FreeSurface(bemat);
	return Ketcau;
}
void close() {
	Rendered = NULL;
	Texture = NULL;
	SDL_Quit;
}
int SDL_main(int argc, char* argv[]) {
	Starup();
	bool quit = false;
	SDL_RenderClear(Rendered);
	SDL_RenderCopy(Rendered, Texture, NULL, NULL);
	SDL_RenderPresent(Rendered);
	SDL_Event e;
	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}
	}

	return 0;
}*/