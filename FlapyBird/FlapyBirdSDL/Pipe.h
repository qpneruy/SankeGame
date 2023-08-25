#pragma once
#include "GLOBAL_DATA.h"
class Pipe : public LoadTexture {
public:
    Pipe();
    int bgX = -50,
        old_y = 0,
        Spacing = 0,
        pipePosX = 0,
        pipePosY = 0,
        bgSpeed = 3,
        randomnumber = {};
    SDL_Rect Hitbox;
    SDL_Rect SpriteClipsPipe;
    void PipeUpdate();
    int PGenerator(int old_y);
};

