
#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class UIManager
{
public:
    UIManager();
    ~UIManager();
    void RenderUI(SDL_Renderer *renderer, int score);

private:
    TTF_Font *font = TTF_OpenFont("./assets/font/LazenbyCompSmooth.ttf", 32);
};

#endif
