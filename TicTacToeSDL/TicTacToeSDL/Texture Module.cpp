#include <SDL_image.h>
#include <iostream>
#include <string>
#include "GLOBAL_DATA.h"
/*
- Loadformfile: load any img type .png, .jpg... 
- Render: Show img on screen / texture
- ~LoadTexture(): Free resouce
Khai Bao:
- extern SDL_Window* Sceen;
- extern SDL_Renderer* GRenderer;
o file can lay du lieu

can 1 file dinh nghia:
- extern SDL_Window* Sceen;
- extern SDL_Renderer* GRenderer;*/
SDL_Renderer* GRenderer;
SDL_Window* Screen;

class LoadTexture {
public:
    ~LoadTexture();
    bool Loadformfile(std::string path);
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setBlendMode(SDL_BlendMode blending);
    void setAlpha(Uint8 alpha);
    int getWidth();
    int getHeight();
    bool render(double x, double y, double w, double h, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
private:
    SDL_Texture* Texture = NULL;
    int mWidth = 0;
    int mHeight = 0;
};
void close() {
    SDL_DestroyRenderer(GRenderer);
    SDL_DestroyWindow(Screen);
    Screen = NULL;
    GRenderer = NULL;
    IMG_Quit();
    SDL_Quit();
}
LoadTexture::~LoadTexture() {
    close();
}

bool LoadTexture::Loadformfile(std::string path) {
    SDL_Surface* Temp = IMG_Load(path.c_str());
    if (Temp == NULL) {
        std::cout << "unable to load img" << path.c_str() << " " << IMG_GetError();
    }
    else {
        SDL_SetColorKey(Temp, SDL_TRUE, SDL_MapRGB(Temp->format, 0, 0xFF, 0xFF));
        Texture = SDL_CreateTextureFromSurface(GRenderer, Temp);
        mWidth = Temp->w;
        mHeight = Temp->h;
        SDL_FreeSurface(Temp);
    }
    if (Texture == NULL) {
        std::cout << "unable to create texture from" << " " << path.c_str() << " Error:  " << SDL_GetError();
    }

    return Texture != NULL;
}

void LoadTexture::setColor(Uint8 red, Uint8 green, Uint8 blue){
    SDL_SetTextureColorMod(Texture, red, green, blue);
}

void LoadTexture::setBlendMode(SDL_BlendMode blending){
    SDL_SetTextureBlendMode(Texture, blending);
}

void LoadTexture::setAlpha(Uint8 alpha){
    SDL_SetTextureAlphaMod(Texture, alpha);
}

bool LoadTexture::render(double x, double y, double w, double h, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
    int _x = static_cast<int>(x);  int _w = static_cast<int>(w);
    int _y = static_cast<int>(y);  int _h = static_cast<int>(h);
    SDL_Rect renderquad = { _x, _y, _w, _h };
    SDL_RenderCopyEx(GRenderer, Texture, clip, &renderquad, angle, center, flip);
    return true;
}
int LoadTexture::getWidth(){ return mWidth; }
int LoadTexture::getHeight(){ return mHeight; }
bool init(const char* ProgramName, int SCREEN_WIDTH, int SCREEN_HEIGHT) {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            printf("Warning: Linear texture filtering not enabled!");
        }
        Screen = SDL_CreateWindow(ProgramName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (Screen == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else {
            GRenderer = SDL_CreateRenderer(Screen, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (GRenderer == NULL) {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else {
                SDL_SetRenderDrawColor(GRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }

    return success;
}

SDL_Renderer* getGRenderer() {
    return GRenderer;
}

SDL_Window* getScreen() {
    return Screen;
}