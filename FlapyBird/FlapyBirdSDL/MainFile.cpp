#include <SDL_mixer.h>
#include <iostream>
#include <stdlib.h>
#include "GLOBAL_DATA.h"
#include "Texture_Module.h"
#include "Bird.h"
#include "Pipe.h"
#include "BackGround.h"
using namespace std;
const int Screen_ngang = 500;
const int Screen_cao = 760;
extern SDL_Window* Sceen;
extern SDL_Renderer* GRenderer;
extern SDL_Rect gSpriteClips[4];
const int ANIMATION_SPEED = 100;
int currentFrame = 0;
Uint32 frameTime = 0;

Background   Score[10];
void ShowScore(int n) {
    int so = 0, x = 280;
    while (n > 0) {
        x = x - 25;
        so = n % 10;
        Score[so].render(x, 100, 24, 44);
        n = n / 10;
    }
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
SDL_Rect MouseHitBox;
int main(int agrc, char* args[]) {
    string StrPath = {};
    MouseHitBox.h = 10;
    MouseHitBox.w = 10;
    init("Flapy Bird", Screen_ngang, Screen_cao);
    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Bird         Bird;
    Background   BG, Ground, Text2, Menu, Prompt_Mess;
    Mix_Chunk* score = Mix_LoadWAV("D:\\Project\\FlapyBirdSDL-Git\\asset\\Sound\\point.wav");
    Mix_Chunk* flap = Mix_LoadWAV("D:\\Project\\FlapyBirdSDL-Git\\asset\\Sound\\Wing.wav");
    Mix_Chunk* Die = Mix_LoadWAV("D:\\Project\\FlapyBirdSDL-Git\\asset\\Sound\\die.wav");
    Mix_Chunk* hit = Mix_LoadWAV("D:\\Project\\FlapyBirdSDL-Git\\asset\\Sound\\hit.wav");

    Menu.Loadformfile("D:\\Project\\FlapyBirdSDL-Git\\asset\\Mess\\menu.png");
    Text2.Loadformfile("D:\\Project\\FlapyBirdSDL-Git\\asset\\Mess\\gameover.png");
    Ground.Loadformfile("D:\\Project\\FlapyBirdSDL-Git\\asset\\Background\\Ground.png");
    BG.Loadformfile("D:\\Project\\FlapyBirdSDL-Git\\asset\\Background\\bg.png");
    Bird.Loadformfile("D:\\Project\\FlapyBirdSDL-Git\\asset\\Bird\\BirdSpite.png");
    Prompt_Mess.Loadformfile("D:\\Project\\FlapyBirdSDL-Git\\asset\\Mess\\prompt.png");
    Pipe  Cot1, Cot1up,
          Cot2, Cot2up,
          Cot3, Cot3up;
    double frequency = 0.09,
           x = 0,
           amplitude = 1.8;
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
    int    diem = 0;
         
    bool   End = false,
           lose = false,
          _lose = false,
          PressedSpace = false;

    SDL_Event e;
    while (!End) {
        while (!_lose) {
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_KEYDOWN) {
                    if (e.key.keysym.sym == SDLK_SPACE && !_lose) {
                        Mix_PlayChannel(-1, flap, 0);
                        Bird.BirdFlap();
                        Bird.render(Bird.Bird_X, Bird.Bird_Y, gSpriteClips[0].w, gSpriteClips[0].h, &gSpriteClips[0]);
                        PressedSpace = true;
                    }
                }
                if (e.type == SDL_QUIT) {
                    SDL_Quit();
                }
            }
            cout << Bird.Bird_Y << "\n";
            if (PressedSpace && !_lose) {
                Bird.BirdUpdate();  Cot1.PipeUpdate();
                Cot2.PipeUpdate();  Cot3.PipeUpdate();
            }
            else {

                SDL_RenderPresent(GRenderer);
            }
            SDL_RenderClear(GRenderer);
            Ground.BackGround_Update();
            BG.render(0, 0, Screen_ngang, 636);   Ground.render(0, 636, Screen_ngang, 174);
            Cot1.render(Cot1.Background_PosX, Cot1.old_y - 300, 52, 600);  Cot1up.render(Cot1.Background_PosX, Cot1.old_y + 400, 52, 485);
            Cot2.render(Cot2.Background_PosX, Cot2.old_y - 300, 52, 600);  Cot2up.render(Cot2.Background_PosX, Cot2.old_y + 400, 52, 485);
            Cot3.render(Cot3.Background_PosX, Cot3.old_y - 300, 52, 600);  Cot3up.render(Cot3.Background_PosX, Cot3.old_y + 400, 52, 485);
            Ground.render(Ground.Background_PosX, 636, Screen_ngang, 174);
            Ground.render(Ground.Background_PosX - Screen_ngang, 636, Screen_ngang, 174);
            
           
            if (ColisionCheck(Bird.Bird_X, Bird.Bird_Y, &Bird.Hitbox, Cot1.Background_PosX + 5, Cot1.old_y + 64, &Cot1.Hitbox) || ColisionCheck(Bird.Bird_X, Bird.Bird_Y, &Bird.Hitbox, Cot2.Background_PosX + 5, Cot2.old_y + 64, &Cot2.Hitbox) || ColisionCheck(Bird.Bird_X, Bird.Bird_Y, &Bird.Hitbox, Cot3.Background_PosX + 5, Cot3.old_y + 64, &Cot3.Hitbox) || ColisionCheck(Bird.Bird_X, Bird.Bird_Y, &Bird.Hitbox, Cot1.Background_PosX, Cot1.old_y + 400, &Cot1up.Hitbox) || ColisionCheck(Bird.Bird_X, Bird.Bird_Y, &Bird.Hitbox, Cot2.Background_PosX, Cot2.old_y + 400, &Cot2up.Hitbox) || ColisionCheck(Bird.Bird_X, Bird.Bird_Y, &Bird.Hitbox, Cot3.Background_PosX, Cot3.old_y + 400, &Cot3up.Hitbox)) {
                 _lose = true;
                 Mix_PlayChannel(-1, hit, 0);
            }
            if (Cot1.Background_PosX == Bird.Bird_X || Cot2.Background_PosX == Bird.Bird_X || Cot3.Background_PosX == Bird.Bird_X) {
                diem++;
                Mix_PlayChannel(-1, score, 0);

            }
            if (SDL_GetTicks() - frameTime >= 150) {
                currentFrame++;
                if (currentFrame >= 3) {
                    currentFrame = 0;
                }
                frameTime = SDL_GetTicks();
            }
            ShowScore(diem);
            if (Bird.Bird_Y >= 600) {
                _lose = true;
                Mix_PlayChannel(-1, Die, 0);
             
            }
            if (PressedSpace && !_lose) {
                Bird.render(Bird.Bird_X, Bird.Bird_Y, gSpriteClips[currentFrame].w, gSpriteClips[currentFrame].h, &gSpriteClips[currentFrame], Bird.Bird_Angel);


            }
            else if (!_lose) {
                Menu.render(110, 100, 300, 500);
                Prompt_Mess.render(200, 200, 250, 100);
                Bird.Bird_Y = Bird.Bird_Y + amplitude * sin(x);
                x += frequency;
                Bird.render(Bird.Bird_X, Bird.Bird_Y, gSpriteClips[currentFrame].w, gSpriteClips[currentFrame].h, &gSpriteClips[currentFrame], Bird.Bird_Angel);
            }

            SDL_RenderPresent(GRenderer);

        }
        if (_lose) {
            Cot1.PipeMovingSpeed = 0;
            Ground.Background_MovingSpeed = 0;
            Bird.Gravity = 0.6;
            Bird.BirdUpdate();
            BG.render(0, 0, Screen_ngang, 636); 
            Cot1.render(Cot1.Background_PosX, Cot1.old_y - 300, 52, 600);  Cot1up.render(Cot1.Background_PosX, Cot1.old_y + 400, 52, 485);
            Cot2.render(Cot2.Background_PosX, Cot2.old_y - 300, 52, 600);  Cot2up.render(Cot2.Background_PosX, Cot2.old_y + 400, 52, 485);
            Cot3.render(Cot3.Background_PosX, Cot3.old_y - 300, 52, 600);  Cot3up.render(Cot3.Background_PosX, Cot3.old_y + 400, 52, 485);
           
            Ground.render(Ground.Background_PosX, 636, Screen_ngang, 174);   Ground.render(Ground.Background_PosX - Screen_ngang, 636, Screen_ngang, 174);
            Bird.render(Bird.Bird_X, Bird.Bird_Y, gSpriteClips[3].w, gSpriteClips[3].h, &gSpriteClips[3], Bird.Bird_Angel);
            Text2.render(155, 130, 204, 52);
        }
        SDL_RenderPresent(GRenderer);
    }
    return 0;
}