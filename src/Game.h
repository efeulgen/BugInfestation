
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include "Player.h"
#include "SpaceBug.h"
#include "UIManager.h"

#ifndef GAME_H
#define GAME_H

const int FPS = 60;
const int MILLISECS_PER_FRAME = 1000 / FPS;

class Game
{
private:
    bool isRunning;
    int millisecsPreviousFrame = 0;

    SDL_Window *window;
    SDL_Renderer *renderer;

    bool isGameOver = false;
    bool isWaveComplete = false;
    const int spaceBugInitAmount = 5;
    int spaceBugAmount = 5;
    int score;

    // sounds
    Mix_Chunk *audio = nullptr;
    Mix_Chunk *bugSplashSound = nullptr;
    Mix_Chunk *bugScreamSound = nullptr;

    // background
    const int backgroundWidth = 1280;
    const int backgroundHeight = 720;
    int bg1_xPos = 0.0;
    int bg2_xPos = 1280.0;

    // game objects
    Player *mainPlayer = nullptr;
    std::vector<SpaceBug *> bugs;
    UIManager *uiManager = nullptr;

public:
    Game();
    ~Game();
    void Init();
    void Display();
    void SetupGameAssets();
    void ProcessInput();
    void UpdateGameAssets();
    void Render();
    void Destroy();

    void GenerateSpaceBugs(int amount);
    void ResetGame();
    void BringNextWave();

    int GetScore() { return score; }
    void IncrementScore() { score++; }
};

#endif
