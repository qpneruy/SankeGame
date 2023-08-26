#pragma once
#include "GLOBAL_DATA.h"
#include "Texture_Module.h"
class Bird : public LoadTexture {
    public:
        Bird();
        double Bird_X = 120,
            Bird_Y = 350,
            Bird_Angel = 0,

            Velocity_Y = 0,
            Flap_Velocity = -7,
            Gravity = 0.6,

            Velocity_Angel = 0,
            AngelFlap_velocity = -10,
            Angel_Gravity = 0.8;
  
        SDL_Rect Hitbox;
        void BirdUpdate();
        void BirdFlap();
    };

