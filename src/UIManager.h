
#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <glm/glm.hpp>

#include "Logger/Logger.h"
#include "Player.h"
#include "Pickup.h"

class UIManager
{
private:
    double pickupTextDisplayTime = 0.0;
    Uint8 greenChannel = 0;
    int greenChannelDirection = 10;
    std::string pickupText;

public:
    UIManager();
    ~UIManager();
    void RenderText(SDL_Renderer *renderer, const std::string &text, glm::vec2 textPos, Uint8 r = 255, Uint8 g = 255, Uint8 b = 255);
    void RenderImage(SDL_Renderer *renderer, const char *imgPath, glm::vec2 imgPos, int imgSize);
    void RenderUI(SDL_Renderer *renderer, Player *mainPlayer, int score, int wave, bool isGameStarted, bool isWaveComplete, bool isGameOver, double deltaTime);
    void DisplayExtraLives(SDL_Renderer *renderer, int amount, int size);
    void DisplayRocketAmount(SDL_Renderer *renderer, int amount, int size);
    void ActivatePickupText(PickupType pickupType);
    void DisplayPickupText(SDL_Renderer *renderer, const std::string &text, glm::vec2 textPos);

private:
    TTF_Font *font = TTF_OpenFont("./assets/font/LazenbyCompSmooth.ttf", 32);
};

#endif
