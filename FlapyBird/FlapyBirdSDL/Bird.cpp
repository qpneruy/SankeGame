#include "GLOBAL_DATA.h"
#include "Bird.h"
SDL_Rect gSpriteClips[4];

void Bird::BirdUpdate() {
    Bird_Y     += Velocity_Y;
    Velocity_Y += Gravity;
    Bird_Angel      += Velocity_Angel;
    Velocity_Angel  += Angel_Gravity;
    if (Bird_Angel > 33) {
        Bird_Angel = 33;
    }
    if (Bird_Angel < -33) {
        Bird_Angel = -32;
    }
    if (Bird_Y >= 628) {
        Bird_Y = 628;
    }
    if (Bird_Y <= 5) {
        Bird_Y = 300;
    }
}

void Bird::BirdFlap() {
    Velocity_Y = Flap_Velocity;
    Velocity_Angel = AngelFlap_velocity;
}
LoadTexture gSpriteSheetTexture;
Bird::Bird() {
    Hitbox.x = 2;
    Hitbox.y = 0;
    Hitbox.h = 24;
    Hitbox.w = 34;
    gSpriteClips[0].x = 2;
    gSpriteClips[0].y = 0;
    gSpriteClips[0].h = 24;
    gSpriteClips[0].w = 34;

    gSpriteClips[1].x = 39;
    gSpriteClips[1].y = 0;
    gSpriteClips[1].h = 24;
    gSpriteClips[1].w = 34;

    gSpriteClips[2].x = 76;
    gSpriteClips[2].y = 0;
    gSpriteClips[2].h = 24;
    gSpriteClips[2].w = 34;

    gSpriteClips[3].x = 110;
    gSpriteClips[3].y = 0;
    gSpriteClips[3].h = 24;
    gSpriteClips[3].w = 34;
}