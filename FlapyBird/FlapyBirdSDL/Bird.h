#pragma once
#include "GLOBAL_DATA.h"
class Bird : public LoadTexture {
    public:
        Bird();
        int DOT_Y = 684;
        double x = 120,
            y = 350,
            angel = {},
            Angel = 0,
            vel_y = 0,
            GRAVITY = 0.6,
            angel_Vel = {},
            JUMP_VELOCITY = -7,
            Angel_Velocity = 0.3;

        SDL_Rect Hitbox;
        void BirdUpdate();
        void BirdFlap();
    };

