#pragma once
#ifndef LOADTEXTURE_H
#define LOADTEXTURE_H
#include <string>
#include <SDL_image.h>


class LoadTexture {
public:
    ~LoadTexture();
    bool Loadformfile(std::string path);
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setBlendMode(SDL_BlendMode blending);
    void setAlpha(Uint8 alpha);
    int getWidth();
    int getHeight();
    bool render(int x, int y, int w, int h, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
private:
    SDL_Texture* Texture = NULL;
    int mWidth;
    int mHeight;
};
bool init(int SCREEN_WIDTH, int SCREEN_HEIGHT);
SDL_Window* getScreen();
SDL_Renderer* getGRenderer();
void close();
#endif