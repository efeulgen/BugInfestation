
#include "UIManager.h"
#include "Player.h"

UIManager::UIManager()
{
    Logger::Log("UIManager Constructor");
}

UIManager::~UIManager()
{
    Logger::Log("UIManager Destructor");
}

void UIManager::RenderText(SDL_Renderer *renderer, const std::string &text, glm::vec2 textPos, Uint8 r, Uint8 g, Uint8 b)
{
    SDL_Color color = {r, g, b};
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

void UIManager::RenderUI(SDL_Renderer *renderer, Player *mainPlayer, int score, int wave, bool isGameStarted, bool isWaveComplete, bool isGameOver, double deltaTime)
{
    // *************** score ******************************
    std::string scoreStr = "Score : " + std::to_string(score);
    RenderText(renderer, scoreStr, glm::vec2(28, 28), 150, 0, 0);
    RenderText(renderer, scoreStr, glm::vec2(30, 30));

    // *************** wave ******************************
    std::string waveStr = "Wave : " + std::to_string(wave);
    RenderText(renderer, waveStr, glm::vec2(28, 78), 150, 0, 0);
    RenderText(renderer, waveStr, glm::vec2(30, 80));

    // *************** health ******************************
    int playerHealth = mainPlayer ? mainPlayer->GetHealth() : 100.0;
    std::string healthStr = "Health : " + std::to_string(playerHealth);
    RenderText(renderer, healthStr, glm::vec2(998, 28), 150, 0, 0);
    RenderText(renderer, healthStr, glm::vec2(1000, 30));

    // *************** game over text ******************************
    if (!mainPlayer && isGameStarted)
    {
        std::string gameOverStr = "Game Over. Play Again (Y/N)?";
        RenderText(renderer, gameOverStr, glm::vec2(400, 650), 150, 0, 0);
        RenderText(renderer, gameOverStr, glm::vec2(398, 648));

        RenderImage(renderer, "./assets/game_over.png", glm::vec2(280, 50), 720);
    }

    // *************** start game text ******************************
    if (!isGameStarted)
    {
        std::string startGamestr = "Press 'Space' to start the game";
        RenderText(renderer, startGamestr, glm::vec2(378, 648), 150, 0, 0);
        RenderText(renderer, startGamestr, glm::vec2(380, 650));

        RenderImage(renderer, "./assets/opening.png", glm::vec2(280, 80), 720);
    }

    // *************** next wave text ******************************
    if (isWaveComplete)
    {
        std::string nextWaveStr = "Wave of Space Bugs defeated. Ready for next wave (Y/N)?";
        RenderText(renderer, nextWaveStr, glm::vec2(178, 298), 150, 0, 0);
        RenderText(renderer, nextWaveStr, glm::vec2(180, 300));
    }

    // *************** display images ******************************
    if (mainPlayer)
    {
        DisplayExtraLives(renderer, mainPlayer->GetExtraLives(), 50);
        DisplayRocketAmount(renderer, mainPlayer->GetRocketAmount(), 50);
    }

    // *************** display pickup text ******************************
    if (pickupTextDisplayTime > 0.0 && !isGameOver)
    {
        pickupTextDisplayTime -= deltaTime;
        DisplayPickupText(renderer, pickupText, glm::vec2(150, 650));
    }
    else
    {
        pickupTextDisplayTime = 0.0;
    }
}

// *********************************************************************************************************************************************************************
// *********************************************************************************************************************************************************************

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

void UIManager::ActivatePickupText(PickupType pickupType)
{
    switch (pickupType)
    {
    case PickupType::ExtraLifePickup:
        pickupText = "Extra Life";
        break;
    case PickupType::FireRateBoost:
        pickupText = "Fire Rate Boost";
        break;
    case PickupType::HealthPickup:
        pickupText = "Increase Health";
        break;
    case PickupType::RocketPickup:
        pickupText = "Rocket Ammo";
        break;
    case PickupType::SpeedBoostPickup:
        pickupText = "Speed Boost";
        break;
    default:
        break;
    }

    pickupTextDisplayTime = 5.0;
}

void UIManager::DisplayPickupText(SDL_Renderer *renderer, const std::string &text, glm::vec2 textPos)
{
    greenChannel += greenChannelDirection;
    if (greenChannel > 255 || greenChannel < 0)
    {
        greenChannelDirection *= -1;
    }
    RenderText(renderer, text, textPos, 255, greenChannel, 0);
}
