#include "GLOBAL_DATA.h"
#include "Texture_Module.h"
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

Pipe::Pipe() {
    SpriteClipsPipe.h = 235;
    SpriteClipsPipe.w = 52;
    Hitbox.h = 235;
    Hitbox.w = 50;
}

int Pipe::PGenerator(int old_y) {
    int b = old_y + 40; int a = old_y - 40;
    while (randomnumber < old_y + 40 && randomnumber > old_y - 40) {
        randomnumber = rand() % b - a;
        if (randomnumber >= 680) {
            randomnumber = 680;

        }
    }
    return  randomnumber;
}

void Pipe::PipeUpdate() {
    bgX -= bgSpeed;
    if (bgX <= Spacing - 50) {
        bgX = 500 + 10;
        Spacing = 0;
        old_y = PGenerator(old_y);
    }
}
