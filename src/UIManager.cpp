
#include "UIManager.h"
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

void UIManager::RenderImage(SDL_Renderer *renderer, const char *imgPath, glm::vec2 imgPos, int imgSize)
{
    SDL_Surface *surf = IMG_Load(imgPath);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
    SDL_Rect rect = {static_cast<int>(imgPos.x), static_cast<int>(imgPos.y), imgSize, imgSize};
    SDL_RenderCopy(renderer, tex, NULL, &rect);
    SDL_DestroyTexture(tex);
}

void UIManager::RenderUI(SDL_Renderer *renderer, Player *mainPlayer, int score, int wave, bool isGameStarted, bool isWaveComplete)
{
    // score
    std::string scoreStr = "Score : " + std::to_string(score);
    RenderText(renderer, scoreStr, glm::vec2(30, 30));

    // wave
    std::string waveStr = "Wave : " + std::to_string(wave);
    RenderText(renderer, waveStr, glm::vec2(30, 80));

    // health
    int playerHealth = mainPlayer ? mainPlayer->GetHealth() : 0.0;
    std::string healthStr = "Health : " + std::to_string(playerHealth);
    RenderText(renderer, healthStr, glm::vec2(1000, 30));

    // game over text
    if (!mainPlayer && isGameStarted)
    {
        std::string gameOverStr = "Game Over. Play Again (Y/N)?";
        RenderText(renderer, gameOverStr, glm::vec2(400, 650));

        RenderImage(renderer, "./assets/game_over.png", glm::vec2(280, 50), 720);
    }

    // start game text
    if (!isGameStarted)
    {
        std::string startGamestr = "Press 'Space' to start the game";
        RenderText(renderer, startGamestr, glm::vec2(380, 650));

        RenderImage(renderer, "./assets/opening.png", glm::vec2(280, 80), 720);
    }

    // next wave text
    if (isWaveComplete)
    {
        std::string nextWaveStr = "Wave of Space Bugs defeated. Ready for next wave (Y/N)?";
        RenderText(renderer, nextWaveStr, glm::vec2(180, 300));
    }

    // *************** display images *********************************************
    if (mainPlayer)
    {
        DisplayExtraLives(renderer, mainPlayer->GetExtraLives(), 50);
        DisplayRocketAmount(renderer, mainPlayer->GetRocketAmount(), 50);
    }
}

void UIManager::DisplayExtraLives(SDL_Renderer *renderer, int amount, int size)
{
    for (int i = 0; i < amount; i++)
    {
        RenderImage(renderer, "./assets/sprites/pickups/extra_life.png", glm::vec2(300 + (size + 10) * i, 5), size);
    }
}

void UIManager::DisplayRocketAmount(SDL_Renderer *renderer, int amount, int size)
{
    for (int i = 0; i < amount; i++)
    {
        RenderImage(renderer, "./assets/sprites/pickups/extra_rocket.png", glm::vec2(300 + (size + 10) * i, 60), size);
    }
}
