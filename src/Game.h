
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include "Player.h"
#include "SpaceBug.h"
#include "HeavySpaceBug.h"
#include "UIManager.h"

#ifndef GAME_H
#define GAME_H

const int FPS = 60;
const int MILLISECS_PER_FRAME = 1000 / FPS;
const int SPACE_BUG_INIT_AMOUNT = 1;
const int SPACE_BUG_INIT_MIN_SPEED = 100;
const int SPACE_BUG_INIT_MAX_SPEED = 150;

class Game
{
private:
    bool isRunning;
    int millisecsPreviousFrame = 0;
    double deltaTime = 0.0;

    SDL_Window *window;
    SDL_Renderer *renderer;

    bool isGameOver = false;
    bool isWaveComplete = false;
    bool isGameStarted = false;

    int spaceBugAmount = 5;
    int spaceBugMinSpeed;
    int spaceBugMaxSpeed;
    int score = 0;
    int wave = 0;

    // sounds
    Mix_Chunk *audio = nullptr;
    Mix_Chunk *bugSplashSound = nullptr;
    Mix_Chunk *bugScreamSound = nullptr;

    // background
    const int backgroundWidth = 1280;
    const int backgroundHeight = 720;
    double bg1_xPos = 0.0;
    double bg2_xPos = 1280.0;
    double bgSpeed = 120.0;

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

    void StartGame();
    void GenerateSpaceBugs(int amount, int minSpeed, int maxSpeed);
    void ResetGame();
    void BringNextWave();

    int GetScore() { return score; }
    void IncrementScore() { score++; }
};

#endif
