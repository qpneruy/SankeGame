#pragma once
#include "GLOBAL_DATA.h"
#include "Texture_Module.h"
class Pipe : public LoadTexture {
public:
    Pipe();
    static int PipeMovingSpeed;
    int Background_PosX = -50,
        old_y = 0,
        Spacing = 0,
        pipePosX = 0,
        pipePosY = 0,
        randomnumber = {};
    SDL_Rect Hitbox;
    SDL_Rect SpriteClipsPipe;
    void PipeUpdate();
    int PGenerator(int old_y);
};

