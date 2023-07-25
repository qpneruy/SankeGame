#include <SDL.h>
#include <iostream>
SDL_Window* Screen = NULL;
SDL_Surface* Surface = NULL;
SDL_Surface* _Surface = NULL;
bool init()
{
	int screen_dai = 720;
	int screen_rong = 480;
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		Screen = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_dai, screen_rong, SDL_WINDOW_SHOWN);
		if (Screen == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Get window surface
			Surface = SDL_GetWindowSurface(Screen);
		}
	}

	return success;
}
bool loadMedia()
{
	//Loading success flag
	bool success = true;
	//Load splash image
	_Surface = SDL_LoadBMP("D:/Project/F0p4Ri_aAAETXzd.bmp");
	if (_Surface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError());
		success = false;
	}

	return success;
}
void close()
{
	//Deallocate surface
	SDL_FreeSurface(_Surface);
	_Surface = NULL;
	//Destroy window
	SDL_DestroyWindow(Screen);
	Screen = NULL;
	//Quit SDL subsystems
	SDL_Quit();
}
int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Apply the image
			SDL_BlitSurface(_Surface, NULL, Surface, NULL);
			//Update the surface
			SDL_UpdateWindowSurface(Screen);
			//Hack to get window to stay up
			SDL_Event e; bool quit = false; while (quit == false) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } }
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}