#include "Texture_Module.h"
#include <SDL_mixer.h>
#include "GLOBAL_DATA.h"
#include <iostream>
#include <stdlib.h>
#define GRAVITY 0.6
#define JUMP_VELOCITY -7
#define On_Ground 610
#define Angel_Velocity 0.3
using namespace std;
const int Sngang = 530;
const int Scao = 800;
extern SDL_Window* Sceen;
extern SDL_Renderer* GRenderer;
class Bird: public LoadTexture {
public:
    Bird();
    double x = 120, y, angel, Angel;
    double vel_y, angel_Vel;
    SDL_Rect Hitbox;
    void BirdUpdate();
    void BirdFlap();
private:
    int DOT_Y = 684;
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
        cout << "da reset";
       angel_Vel = 33;
       Angel = 33;
    }
    if (angel_Vel <-33 || Angel < -33) {
        cout << "da resetlloal>>";
        angel_Vel = 0;
        Angel = -32;
    }
}
void Bird::BirdFlap() {
        vel_y = JUMP_VELOCITY;
        angel_Vel = -10;
  
}
const int ANIMATION_SPEED = 100;
int currentFrame = 0;
Uint32 frameTime = 0;

SDL_Rect gSpriteClips[3];
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

}

class Pipe: public LoadTexture {
public:
    int randomnumber;
    int Spacing = 0;
    int old_y = 0;
    int bgX = 0;
    Pipe();
    SDL_Rect Hitbox;
    SDL_Rect SpriteClipsPipe;
    void PipeUpdate();
    int PGenerator(int old_y);
    int pipePosX = 0, pipePosY = 0;
private:
    int bgSpeed = 4;
};
Pipe::Pipe() {
    SpriteClipsPipe.h = 235;
    SpriteClipsPipe.w = 52;
    Hitbox.h = 235;
    Hitbox.w = 52;
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
    if (bgX <= Spacing-50) {
        bgX = Sngang+10;
        Spacing = 0;
        old_y = PGenerator(old_y);

    }
}
class Background: public LoadTexture {
public:
    int bgX = 0;
    void BGUpdate();
private:
   int bgSpeed = 5;
};
void Background::BGUpdate() {
    bgX -= bgSpeed;
    
    if (bgX <= 0) {
        bgX = Sngang;
    }
}
bool ColisionCheck(int A_x, int A_y, SDL_Rect* RectA, int B_x, int B_y, SDL_Rect* RectB) {
    SDL_Rect rectA = { A_x, A_y, RectA->w, RectA->h };
    SDL_Rect rectB = { B_x, B_y, RectB->w, RectB->h };
    if (SDL_HasIntersection(&rectA, &rectB)) {
        return true;
    }
    else {
        return false; 
    }
}

int main(int agrc, char* args[]) {
 init(Sngang, Scao);
 SDL_Init(SDL_INIT_AUDIO);
 Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
 //Mix_Music* score = Mix_LoadMUS("D:\\Project\\flappy_bird asset\\score.mp3");
 Mix_Chunk* score = Mix_LoadWAV("D:\\Project\\flappy_bird asset\\score.mp3");
 Mix_Chunk* flap = Mix_LoadWAV("D:\\Project\\flappy_bird asset\\fly.mp3");
 Bird Bird; Background BG; Background Ground;
 Ground.Loadformfile("D:\\Project\\flappy_bird asset\\Ground.png");
 BG.Loadformfile("D:\\Project\\flappy_bird asset\\bg.png");
 Bird.Loadformfile("D:\\Project\\flappy_bird asset\\bird.png");
 Pipe Cot1; Pipe Cot2; Pipe Cot3;
 Pipe Cot1up; Pipe Cot2up; Pipe Cot3up;
 string PipePath = "D:\\Project\\flappy_bird asset\\cot.png";
 Cot1.Loadformfile(PipePath);
 Cot2.Loadformfile(PipePath);
 Cot3.Loadformfile(PipePath);
 string PipePath2 = "D:\\Project\\flappy_bird asset\\cot2.png";
 Cot1up.Loadformfile(PipePath2);
 Cot2up.Loadformfile(PipePath2);
 Cot3up.Loadformfile(PipePath2);
 Ground.render(0, 636, 479, 174);
 BG.render(0, 0, Sngang, 636);
 Cot1.Spacing = -50; Cot2.Spacing = -250; Cot3.Spacing = -415;
 SDL_Event e;
 int diem = 0;
 bool quit = false;
 while (!quit) {
     while (SDL_PollEvent(&e) != 0) {
         if (e.type == SDL_QUIT) {
             quit = true;
         }
         else if (e.type == SDL_KEYDOWN) {
             if (e.key.keysym.sym == SDLK_SPACE) {
                 Mix_PlayChannel(-1, flap, 0);
                 Bird.BirdFlap();
             }
         }
     }
     Bird.BirdUpdate();
     Cot1.PipeUpdate();
     Ground.BGUpdate();
     Cot2.PipeUpdate();
    Cot3.PipeUpdate();
     SDL_RenderClear(GRenderer);
     BG.render(0, 0, Sngang, 636);
     Ground.render(0, 636, Sngang, 174);
     Ground.render(Ground.bgX, 636, Sngang, 174);
     Ground.render(Ground.bgX - Sngang, 636, Sngang, 174);
         Cot1.render(Cot1.bgX, Cot1.old_y-300, 52, 600);
         Cot2.render(Cot2.bgX, Cot2.old_y-300, 52, 600);
         Cot3.render(Cot3.bgX, Cot3.old_y-300, 52, 600);
         if (ColisionCheck(Bird.x, Bird.y, &Bird.Hitbox, Cot1.bgX, Cot1.old_y, &Cot1.Hitbox) || ColisionCheck(Bird.x, Bird.y, &Bird.Hitbox, Cot2.bgX, Cot2.old_y, &Cot2.Hitbox) || ColisionCheck(Bird.x, Bird.y, &Bird.Hitbox, Cot3.bgX, Cot3.old_y, &Cot3.Hitbox) || ColisionCheck(Bird.x, Bird.y, &Bird.Hitbox, Cot1.bgX, Cot1.old_y + 400, &Cot1up.Hitbox) || ColisionCheck(Bird.x, Bird.y, &Bird.Hitbox, Cot2.bgX, Cot2.old_y + 400, &Cot2up.Hitbox) || ColisionCheck(Bird.x, Bird.y, &Bird.Hitbox, Cot3.bgX, Cot3.old_y + 400, &Cot3up.Hitbox)) {
      //       std::cout << "va cham ";
        }
         if (Cot1.bgX == Bird.x || Cot2.bgX == Bird.x || Cot3.bgX == Bird.x) {
             diem++;
             Mix_PlayChannel(-1, score, 0);
             cout << diem << " ";
         }
         Cot1up.render(Cot1.bgX, Cot1.old_y+400 , 52, Cot1up.SpriteClipsPipe.h-Cot1.old_y, &Cot1up.SpriteClipsPipe);
         Cot2up.render(Cot2.bgX, Cot2.old_y+400 , 52, Cot2up.SpriteClipsPipe.h-Cot2.old_y, &Cot2up.SpriteClipsPipe);
         Cot3up.render(Cot3.bgX, Cot3.old_y+400, 52, Cot3up.SpriteClipsPipe.h-Cot3.old_y, &Cot3up.SpriteClipsPipe);
     Bird.render(Bird.x, Bird.y, gSpriteClips[currentFrame].w, gSpriteClips[currentFrame].h, &gSpriteClips[currentFrame], Bird.Angel);
     if (SDL_GetTicks() - frameTime >= ANIMATION_SPEED) {
        currentFrame++;
        if (currentFrame >= 3) {
             currentFrame = 0;
        }
         frameTime = SDL_GetTicks();
     }

     SDL_RenderPresent(GRenderer);
 }
    return 0;
}