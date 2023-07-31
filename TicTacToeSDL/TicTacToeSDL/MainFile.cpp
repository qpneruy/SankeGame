#include "Texture_Module.h"

#include "GLOBAL_DATA.h"

using namespace std;
const int Sngang = 530;
const int Scao = 800;
extern SDL_Window* Sceen;
extern SDL_Renderer* GRenderer;

LoadTexture LBird;
class Bird {
public: void HandleEventBird(SDL_Event& e);
      void Move();
      void BirdRender();
private: int DotH = 32;
       int DotW = 32;
public: int DotPosX = 0;
      int DotVelY = 0;
      int DotVelX = 0;
      int DotPosY = 0;
};

const int ANIMATION_SPEED = 100;
int currentFrame = 0;
Uint32 frameTime = 0;

SDL_Rect gSpriteClips[3];
LoadTexture gSpriteSheetTexture;
void Bird::BirdRender() {
    LBird.Loadformfile("D:\\Project\\flappy_bird asset\\bird.png");

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
void Bird::HandleEventBird(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
        case SDLK_UP:
            DotVelY += -5;
            break;
        case SDLK_DOWN:
            DotVelY += 5;
            break;
        case SDLK_LEFT:
            DotVelX += -5;
            break;
        case SDLK_RIGHT:
            DotVelX += 5;
            break;
        };
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
        case SDLK_UP:
            DotVelY += 5;
            break;
        case SDLK_DOWN:
            DotVelY += -5;
            break;
        case SDLK_LEFT:
            DotVelX += +5;
            break;
        case SDLK_RIGHT:
            DotVelX += -5;
            break;
        };
    }
}

int dotX = 0;
int dotY = 0;
void Bird::Move() {

    dotY += DotVelY;
    dotX += DotVelX;

    if (dotY <= -1) {
        dotY = Scao - 16;
    }

    if (dotY >= Scao) {
        dotY = 0;
    }

    if (dotX <= -1) {
        dotX = Sngang - 16;
    }

    if (dotX >= Sngang) {
        dotX = 0;
    }
}

int bgX = 0;
int bgSpeed = 1;
void updateBackground() {
    bgX -= bgSpeed;
    if (bgX <= 0) {
        bgX = Sngang;
    }
}

LoadTexture A_pipe;
LoadTexture B_pipe;
LoadTexture C_pipe;
Pipe pipe_A;
Pipe pipe_B;
Pipe pipe_C;
class Pipe {
public:
    int posX, posY;
    int pW, pH;
    void PGenerator();
    void Moving();
private:
    int PipeMoveSpeed = 1;
    int PipePosX = 0;
};
void Pipe::PGenerator() {
    // tinh toan cac gia tri can thiet nhu se xuat hien o dau vi tri nao lo se o chieu cao nao cho hop li nhat chay ranfom
    // trong pham vi
    // task 1/08/2023: sdl rect, kiem tra va cham voi anh
}
void Pipe::Moving() {
    PipePosX -= PipeMoveSpeed;
    if (PipePosX <= 0) {
        PipePosX = Sngang;
    }
}
int main(int agrc, char* args[]) {
 init(Sngang, Scao);
 A_pipe.Loadformfile("D:\\Project\\flappy_bird asset\\cot.png");
 B_pipe.Loadformfile("D:\\Project\\flappy_bird asset\\cot.png");
 C_pipe.Loadformfile("D:\\Project\\flappy_bird asset\\cot.png");
 LoadTexture Cot;
 LoadTexture bg;
 LoadTexture ground;
 Bird Bird;
 ground.Loadformfile("D:\\Project\\flappy_bird asset\\Ground.png");
 bg.Loadformfile("D:\\Project\\flappy_bird asset\\bg.png");
 Cot.Loadformfile("D:\\Project\\flappy_bird asset\\cot.png");
 ground.render(0, 636, 479, 174);
 Bird.BirdRender();

 SDL_Event e;

 bool quit = false;
 while (!quit) {
  while (SDL_PollEvent(&e) != 0) {
   if (e.type == SDL_QUIT) {
       quit = true;
   }
      Bird.HandleEventBird(e);
  }
     Bird.Move();
     updateBackground();
     SDL_RenderClear(GRenderer);
     bg.render(0, 0, Sngang, 636);
     ground.render(0, 636, Sngang, 174);
     ground.render(bgX, 636, Sngang, 174);
     ground.render(bgX - Sngang, 636, Sngang, 174);
     Cot.render(300, 0, 65, Scao);
     LBird.render(dotX, dotY, gSpriteClips[currentFrame].w, gSpriteClips[currentFrame].h, &gSpriteClips[currentFrame]);
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