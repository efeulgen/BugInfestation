
#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <glm/glm.hpp>
#include "Player.h"

class UIManager
{
public:
    UIManager();
    ~UIManager();
    void RenderText(SDL_Renderer *renderer, const std::string &text, glm::vec2 textPos);
    void RenderUI(SDL_Renderer *renderer, Player *mainPlayer, int score, int wave, bool isGameStarted, bool isWaveComplete);

private:
    TTF_Font *font = TTF_OpenFont("./assets/font/LazenbyCompSmooth.ttf", 32);
};

#endif
