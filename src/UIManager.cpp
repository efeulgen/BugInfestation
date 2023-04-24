
#include "UIManager.h"
#include <iostream>
#include "Player.h"

UIManager::UIManager()
{
    std::cout << "UIManager Constructor" << std::endl;
}

UIManager::~UIManager()
{
    std::cout << "UIManager Destructor" << std::endl;
}

void UIManager::RenderUI(SDL_Renderer *renderer, int score)
{
    // score
    SDL_Color color = {255, 255, 255};
    std::string score_string = "Score : " + std::to_string(score);
    SDL_Surface *scoreSurface = TTF_RenderText_Solid(font, score_string.c_str(), color); //
    SDL_Texture *scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
    SDL_Rect scoreRect = {30, 30, scoreSurface->w, scoreSurface->h};
    SDL_FreeSurface(scoreSurface);
    SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
    SDL_DestroyTexture(scoreTexture);
}
