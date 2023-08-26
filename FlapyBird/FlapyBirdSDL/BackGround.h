#pragma once
#include "Texture_Module.h"
class Background: public LoadTexture {
public:
    int Background_PosX = 0,
        Background_MovingSpeed = 3;
    SDL_Rect HitBox;
    void BackGround_Update();
};

