
#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <glm/glm.hpp>

#include "Player.h"

class UIManager
{
public:
    UIManager();
    ~UIManager();
    void RenderText(SDL_Renderer *renderer, const std::string &text, glm::vec2 textPos);
    void RenderImage(SDL_Renderer *renderer, const char *imgPath, glm::vec2 imgPos, int imgSize);
    void RenderUI(SDL_Renderer *renderer, Player *mainPlayer, int score, int wave, bool isGameStarted, bool isWaveComplete);
    void DisplayExtraLives(SDL_Renderer *renderer, int amount, int size);
    void DisplayRocketAmount(SDL_Renderer *renderer, int amount, int size);

private:
    TTF_Font *font = TTF_OpenFont("./assets/font/LazenbyCompSmooth.ttf", 32);
};

#endif
