#include "GLOBAL_DATA.h"
#include "Pipe.h"

Pipe::Pipe() {
    SpriteClipsPipe.h = 235;
    SpriteClipsPipe.w = 52;
    Hitbox.h = 235;
    Hitbox.w = 50;
}
int Pipe::PipeMovingSpeed = 3;
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
    Background_PosX -= PipeMovingSpeed;
    if (Background_PosX <= Spacing - 50) {
        Background_PosX = 500 + 10;
        Spacing = 0;
        old_y = PGenerator(old_y);
    }
}
