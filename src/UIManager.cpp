
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

void UIManager::RenderText(SDL_Renderer *renderer, const std::string &text, glm::vec2 textPos)
{
    SDL_Color color = {255, 255, 255};
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect textRect = {static_cast<int>(textPos.x), static_cast<int>(textPos.y), textSurface->w, textSurface->h};
    SDL_FreeSurface(textSurface);
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_DestroyTexture(textTexture);
}

void UIManager::RenderUI(SDL_Renderer *renderer, Player *mainPlayer, int score, bool isGameStarted, bool isWaveComplete)
{
    // score
    std::string scoreStr = "Score : " + std::to_string(score);
    RenderText(renderer, scoreStr, glm::vec2(30, 30));

    // health
    int playerHealth = mainPlayer ? mainPlayer->GetHealth() : 0.0;
    std::string healthStr = "Health : " + std::to_string(playerHealth);
    RenderText(renderer, healthStr, glm::vec2(1000, 30));

    // game over text
    if (!mainPlayer)
    {
        std::string gameOverStr = "Game Over. Play Again (Y/N)?";
        RenderText(renderer, gameOverStr, glm::vec2(400, 300));
    }

    // start game text
    if (!isGameStarted)
    {
        std::string startGamestr = "Press 'Space' to start the game";
        RenderText(renderer, startGamestr, glm::vec2(300, 300));
    }

    // next wave text
    if (isWaveComplete)
    {
        std::string nextWaveStr = "Wave of Space Bugs defeated. Ready for next wave (Y/N)?";
        RenderText(renderer, nextWaveStr, glm::vec2(150, 300));
    }
}
