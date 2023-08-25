#include "GLOBAL_DATA.h"
#include "Texture_Module.h"
SDL_Rect gSpriteClips[4];
class Bird: public LoadTexture {
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

void Bird::BirdUpdate() {
    y += vel_y;
    Angel += angel_Vel;
    angel_Vel += Angel_Velocity;
    vel_y += GRAVITY;
    if (y > DOT_Y) {
        y = DOT_Y;
        vel_y = 0;
    }
    if (angel_Vel > 33 || Angel > 33) {
        Angel = 33;
        angel_Vel = 33;
    }
    if (angel_Vel < -33 || Angel < -33) {
        Angel = -32;
        angel_Vel = 0;
    }
    if (y >= 628) {
        y = 628;
    }
}

void Bird::BirdFlap() {
    vel_y = JUMP_VELOCITY;
    angel_Vel = -10;
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