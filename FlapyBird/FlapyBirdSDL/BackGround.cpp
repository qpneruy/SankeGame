#include "BackGround.h"
void Background::BackGround_Update() {
    Background_PosX -= Background_MovingSpeed;
    if (Background_PosX <= 0) {
        Background_PosX = 500;
    }
}
