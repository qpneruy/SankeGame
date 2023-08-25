#include "Texture_Module.h"
#include <SDL_mixer.h>
#include "GLOBAL_DATA.h"
#include <iostream>
#include <stdlib.h>
#include "Bird.h"
#include "Pipe.h"
using namespace std;
const int Sngang = 500;
const int Scao = 760;
extern SDL_Window* Sceen;
extern SDL_Renderer* GRenderer;
extern SDL_Rect gSpriteClips[4];
const int ANIMATION_SPEED = 100;
int currentFrame = 0;
Uint32 frameTime = 0;
class Background : public LoadTexture {
public:
    Background();
    int bgX = 0,
        bgSpeed = 3;
    SDL_Rect HitBox;
    void BGUpdate();
};
void Background::BGUpdate() {
    bgX -= bgSpeed;
    if (bgX <= 0) {
        bgX = Sngang;
    }
}
Background::Background() {
    //cout << "a";
}
bool ColisionCheck(double A_x, double A_y, SDL_Rect* RectA, double B_x, double B_y, SDL_Rect* RectB) {
    SDL_Rect rectA = { static_cast<int>(A_x), static_cast<int>(A_y), RectA->w, RectA->h };
    SDL_Rect rectB = { static_cast<int>(B_x), static_cast<int>(B_y), RectB->w, RectB->h };

    if (SDL_HasIntersection(&rectA, &rectB)) {
        return true;
    }
    else {
        return false;
    }
}
Background   Score[10];
string StrPath = {};
void UpdateDiem(int n) {
    int so = 0, x = 280;
    while (n > 0) {
        x = x - 25;
        so = n % 10;
        Score[so].render(x, 100, 24, 44);
        n = n / 10;
    }
}
SDL_Rect MouseHitBox;
int main(int agrc, char* args[]) {
    MouseHitBox.h = 10;
    MouseHitBox.w = 10;
    init("Flapy Bird", Sngang, Scao);
    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Bird         Bird;
    Background   BG, Ground, Text2, Menu, Caidat[2], Prompt_Mess;
    Mix_Chunk* score = Mix_LoadWAV("D:\\Project\\FlapyBirdSDL-Git\\asset\\Sound\\point.wav");
    Mix_Chunk* flap = Mix_LoadWAV("D:\\Project\\FlapyBirdSDL-Git\\asset\\Sound\\Wing.wav");
    Mix_Chunk* Die = Mix_LoadWAV("D:\\Project\\FlapyBirdSDL-Git\\asset\\Sound\\die.wav");
    Mix_Chunk* hit = Mix_LoadWAV("D:\\Project\\FlapyBirdSDL-Git\\asset\\Sound\\hit.wav");

    Menu.Loadformfile("D:\\Project\\FlapyBirdSDL-Git\\asset\\Mess\\menu.png");
    Text2.Loadformfile("D:\\Project\\FlapyBirdSDL-Git\\asset\\Mess\\gameover.png");
    Ground.Loadformfile("D:\\Project\\FlapyBirdSDL-Git\\asset\\Background\\Ground.png");
    BG.Loadformfile("D:\\Project\\FlapyBirdSDL-Git\\asset\\Background\\bg.png");
    Bird.Loadformfile("D:\\Project\\FlapyBirdSDL-Git\\asset\\Bird\\BirdSpite.png");
    Caidat[0].Loadformfile("D:\\Project\\FlapyBirdSDL-Git\\asset\\Caidat.png");
    Caidat[1].Loadformfile("D:\\Project\\FlapyBirdSDL-Git\\asset\\Caidat2.png");
    Prompt_Mess.Loadformfile("D:\\Project\\FlapyBirdSDL-Git\\asset\\Mess\\prompt.png");
    Caidat[0].HitBox.h = 50;
    Caidat[0].HitBox.w = 50;
    Caidat[1].HitBox.h = 50;
    Caidat[1].HitBox.w = 50;
    Pipe   Cot1, Cot1up,
        Cot2, Cot2up,
        Cot3, Cot3up;
    double frequency = 0.1,
        x = 0;
    string PipePath = "D:\\Project\\FlapyBirdSDL-Git\\asset\\pipe\\cot1.png";
    string PipePath2 = "D:\\Project\\FlapyBirdSDL-Git\\asset\\pipe\\cot2.png";
    Cot1.Loadformfile(PipePath);  Cot1up.Loadformfile(PipePath2);
    Cot2.Loadformfile(PipePath);  Cot2up.Loadformfile(PipePath2);
    Cot3.Loadformfile(PipePath);  Cot3up.Loadformfile(PipePath2);

    for (int i = 0; i < 10; i++) {
        StrPath = "D:\\Project\\FlapyBirdSDL-Git\\asset\\Num\\" + std::to_string(i) + ".png";
        Score[i].Loadformfile(StrPath);
    }
    Cot1.Spacing = -50;
    Cot2.Spacing = -250;
    Cot3.Spacing = -415;
    int    diem = 0,
        amplitude = 3;
    int Mousex = 0, Mousey = 0;
    bool   End = false,
        lose = false,
        _lose = false,
        PressedSpace = false;
    SDL_Event e;
    while (!End) {
        while (!_lose) {
            while (SDL_PollEvent(&e) != 0 && !_lose) {
                if (e.type == SDL_KEYDOWN) {
                    if (e.key.keysym.sym == SDLK_SPACE) {
                        Mix_PlayChannel(-1, flap, 0);
                        Bird.BirdFlap();
                        Bird.render(Bird.x, Bird.y, gSpriteClips[1].w, gSpriteClips[1].h, &gSpriteClips[1], 38);
                        PressedSpace = true;
                    }
                }
            }
            if (e.type == SDL_QUIT) {
                SDL_Quit();
            }
            cout << Bird.y << "\n";
            if (PressedSpace && !_lose) {
                Bird.BirdUpdate();  Cot1.PipeUpdate();
                Cot2.PipeUpdate();  Cot3.PipeUpdate();

            }
            else {
                if (SDL_GetTicks() - frameTime >= 150) {
                    currentFrame++;
                    if (currentFrame >= 3) {
                        currentFrame = 0;
                    }
                    frameTime = SDL_GetTicks();
                }
                SDL_RenderPresent(GRenderer);
            }
             SDL_RenderClear(GRenderer);
            Ground.BGUpdate();
            SDL_GetMouseState(&Mousex, &Mousey);
            BG.render(0, 0, Sngang, 636);   Ground.render(0, 636, Sngang, 174);
            Cot1.render(Cot1.bgX, Cot1.old_y - 300, 52, 600);  Cot1up.render(Cot1.bgX, Cot1.old_y + 400, 52, 485);
            Cot2.render(Cot2.bgX, Cot2.old_y - 300, 52, 600);  Cot2up.render(Cot2.bgX, Cot2.old_y + 400, 52, 485);
            Cot3.render(Cot3.bgX, Cot3.old_y - 300, 52, 600);  Cot3up.render(Cot3.bgX, Cot3.old_y + 400, 52, 485);
            Ground.render(Ground.bgX, 636, Sngang, 174);
            Ground.render(Ground.bgX - Sngang, 636, Sngang, 174);
            
            if (ColisionCheck(Bird.x, Bird.y, &Bird.Hitbox, Cot1.bgX + 5, Cot1.old_y + 64, &Cot1.Hitbox) || ColisionCheck(Bird.x, Bird.y, &Bird.Hitbox, Cot2.bgX + 5, Cot2.old_y + 64, &Cot2.Hitbox) || ColisionCheck(Bird.x, Bird.y, &Bird.Hitbox, Cot3.bgX + 5, Cot3.old_y + 64, &Cot3.Hitbox) || ColisionCheck(Bird.x, Bird.y, &Bird.Hitbox, Cot1.bgX, Cot1.old_y + 400, &Cot1up.Hitbox) || ColisionCheck(Bird.x, Bird.y, &Bird.Hitbox, Cot2.bgX, Cot2.old_y + 400, &Cot2up.Hitbox) || ColisionCheck(Bird.x, Bird.y, &Bird.Hitbox, Cot3.bgX, Cot3.old_y + 400, &Cot3up.Hitbox)) {
                 _lose = true;
                    Mix_PlayChannel(-1, Die, 0);
                }
            if (Bird.y >= 600) {
                _lose = true;
                if (_lose) {
                    Mix_PlayChannel(-1, Die, 0);
                }
            }
            if (Cot1.bgX == Bird.x || Cot2.bgX == Bird.x || Cot3.bgX == Bird.x) {
                diem++;
                cout << diem;
                if (!_lose) {
                    Mix_PlayChannel(-1, score, 0);
                }

            }
            UpdateDiem(diem);
            if (PressedSpace && !_lose) {
                Bird.render(Bird.x, Bird.y, gSpriteClips[currentFrame].w, gSpriteClips[currentFrame].h, &gSpriteClips[currentFrame], Bird.Angel);

                if (SDL_GetTicks() - frameTime >= ANIMATION_SPEED) {
                    currentFrame++;
                    if (currentFrame >= 3) {
                        currentFrame = 0;
                    }
                    frameTime = SDL_GetTicks();
                }
            }
            else if (!_lose) {
                Menu.render(110, 100, 300, 500);
                Prompt_Mess.render(200, 200, 250, 100);
                if (ColisionCheck(Mousex, Mousey, &MouseHitBox, 15, 15, &Caidat[0].HitBox)) {
                    Caidat[1].render(15, 15, 50, 50);
                }
                else {
                    Caidat[0].render(15, 15, 50, 50);
                }

                Bird.y = Bird.y + amplitude * sin(x);
                x += frequency;
                Bird.render(Bird.x, Bird.y, gSpriteClips[currentFrame].w, gSpriteClips[currentFrame].h, &gSpriteClips[currentFrame], Bird.Angel);
            }

            SDL_RenderPresent(GRenderer);

        }
        if (_lose) {
            Cot1.bgSpeed = 0;
            Cot2.bgSpeed = 0;
            Cot3.bgSpeed = 0;
            Ground.bgSpeed = 0;
            Bird.JUMP_VELOCITY = 0;
            Bird.Angel_Velocity = 0;
            Bird.GRAVITY = 1.6;
            Bird.BirdUpdate();
            SDL_RenderClear(GRenderer);
            BG.render(0, 0, Sngang, 636); 
            Cot1.render(Cot1.bgX, Cot1.old_y - 300, 52, 600);  Cot1up.render(Cot1.bgX, Cot1.old_y + 400, 52, 485);
            Cot2.render(Cot2.bgX, Cot2.old_y - 300, 52, 600);  Cot2up.render(Cot2.bgX, Cot2.old_y + 400, 52, 485);
            Cot3.render(Cot3.bgX, Cot3.old_y - 300, 52, 600);  Cot3up.render(Cot3.bgX, Cot3.old_y + 400, 52, 485);
           
            Ground.render(Ground.bgX, 636, Sngang, 174);   Ground.render(Ground.bgX - Sngang, 636, Sngang, 174);
            Bird.render(Bird.x, Bird.y, gSpriteClips[3].w, gSpriteClips[3].h, &gSpriteClips[3], Bird.angel);
            Text2.render(155, 130, 204, 52);
            SDL_RenderPresent(GRenderer);
        }
        SDL_RenderPresent(GRenderer);
    }
    return 0;
}