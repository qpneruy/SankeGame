/*#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int TOTAL_BUTTONS = 4;
enum LButtonSprite {
    BUTTON_SPRITE_MOUSE_OUT,
    BUTTON_SPRITE_MOUSE_OVER_MOTION,
    BUTTON_SPRITE_MOUSE_DOWN,
    BUTTON_SPRITE_MOUSE_UP,
    BUTTON_SPRITE_TOTAL
};
class LTexture {
public: LTexture();
      ~LTexture();
      bool loadFromFile(std::string path);
      void free();
      void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
      int getWidth();
      int getHeight();
private: SDL_Texture* mTexture;
       int mWidth;  int mHeight;
};
class LButton {
public: LButton();
      void setPosition(int x, int y);
      void handleEvent(SDL_Event* e);
      void render();

private: SDL_Point mPosition;
       LButtonSprite mCurrentSprite;
};
bool init();
bool loadMedia();
void close();
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Rect gSpriteClips[BUTTON_SPRITE_TOTAL];
LTexture gButtonSpriteSheetTexture;
LButton gButtons[TOTAL_BUTTONS];
LTexture::LTexture() {
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}
LTexture::~LTexture() { free(); }
bool LTexture::loadFromFile(std::string path) {
    free();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
    newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    mWidth = loadedSurface->w;
    mHeight = loadedSurface->h;
    SDL_FreeSurface(loadedSurface);
    mTexture = newTexture;
    return mTexture != NULL;
}
void LTexture::free() {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
}
void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
   SDL_Rect renderQuad = { x, y, mWidth, mHeight };
      renderQuad.w = clip->w;
     renderQuad.h = clip->h;
   SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}
int LTexture::getWidth() { return mWidth; }
int LTexture::getHeight() { return mHeight; }
LButton::LButton() {
    mPosition.x = 0;
    mPosition.y = 0;
    mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}
void LButton::setPosition(int x, int y) {
    mPosition.x = x;
    mPosition.y = y;
}
void LButton::handleEvent(SDL_Event* e) {
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        bool inside = true;
        if (x < mPosition.x) {
            inside = false;
        } else if (x > mPosition.x + BUTTON_WIDTH) {
            inside = false;
        } else if (y < mPosition.y) {
            inside = false;
        } else if (y > mPosition.y + BUTTON_HEIGHT) {
            inside = false;
        } if (!inside) {
            mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
        } else {
            switch (e->type) {
            case SDL_MOUSEMOTION:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                break;
            case SDL_MOUSEBUTTONDOWN:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                break;
            case SDL_MOUSEBUTTONUP:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
                break;
            }
        }
    }
}
void LButton::render() {
    gButtonSpriteSheetTexture.render(mPosition.x, mPosition.y, &gSpriteClips[mCurrentSprite]);
}
bool init() {
    gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    return true;
}
bool loadMedia() {
    gButtonSpriteSheetTexture.loadFromFile("D:/Project/button.png");
    for (int i = 0; i < BUTTON_SPRITE_TOTAL; ++i) {
        gSpriteClips[i].x = 0;
        gSpriteClips[i].y = i * 200;
        gSpriteClips[i].w = BUTTON_WIDTH;
        gSpriteClips[i].h = BUTTON_HEIGHT;
    }
    gButtons[0].setPosition(0, 0);
    gButtons[1].setPosition(SCREEN_WIDTH - BUTTON_WIDTH, 0);
    gButtons[2].setPosition(0, SCREEN_HEIGHT - BUTTON_HEIGHT);
    gButtons[3].setPosition(SCREEN_WIDTH - BUTTON_WIDTH, SCREEN_HEIGHT - BUTTON_HEIGHT);
    return true;
}
void close() {
    gButtonSpriteSheetTexture.free();
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* args[]) {
    init();
    loadMedia();
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            for (int i = 0; i < TOTAL_BUTTONS; ++i) {
                gButtons[i].handleEvent(&e);
            }
        }
        SDL_RenderClear(gRenderer);
        for (int i = 0; i < TOTAL_BUTTONS; ++i) {
            gButtons[i].render();
        }
        SDL_RenderPresent(gRenderer);
    }
    close();
    return 0;
}*/