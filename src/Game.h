
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <glm/glm.hpp>
#include "./Logger/Logger.h"
#include "Player.h"
#include "SpaceBug.h"
#include "HeavySpaceBug.h"
#include "BladedSpaceBug.h"
#include "Pickup.h"
#include "./Drones/Drone.h"
#include "./Drones/FighterDrone.h"
#include "./Drones/SeekAndDestroyDrone.h"
#include "./Drones/TrippleLaserShootingDrone.h"
#include "UIManager.h"

const int FPS = 60;
const int MILLISECS_PER_FRAME = 1000 / FPS;
const int SPACE_BUG_INIT_AMOUNT = 5;
const int SPACE_BUG_INIT_MIN_SPEED = 100;
const int SPACE_BUG_INIT_MAX_SPEED = 150;

enum WaveType
{
    RegularWave,
    MiniBossWave
};

class Game
{
private:
    bool isRunning;
    int millisecsPreviousFrame = 0;
    double deltaTime = 0.0;

    SDL_Window *window;
    SDL_Renderer *renderer;
    int windowWidth, windowHeight;

    bool isGameOver = false;
    bool isWaveComplete = false;
    bool isGameStarted = false;

    int spawnSeed = 0;
    int spaceBugAmount = 0;
    int spaceBugMinSpeed;
    int spaceBugMaxSpeed;
    int score = 0;
    int wave = 0;
    WaveType waveType = WaveType::RegularWave;

    double generateDroneCounter = 7.5;

    // sounds
    Mix_Chunk *audio = nullptr;
    Mix_Chunk *gameOverSound = nullptr;
    Mix_Chunk *bugSplashSound = nullptr;
    Mix_Chunk *bugScreamSound = nullptr;
    Mix_Chunk *explosionSound = nullptr;
    Mix_Chunk *playerHurtSound = nullptr;

    // background
    const int backgroundWidth = 1280;
    const int backgroundHeight = 720;
    double bg1_xPos = 0.0;
    double bg2_xPos = 1280.0;
    double bgSpeed = 120.0;

    // game objects
    Player *mainPlayer = nullptr;
    std::vector<SpaceBug *> bugs;
    std::vector<Drone *> drones;
    Pickup *pickup = nullptr;
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
    void GeneratePickup();
    void GenerateDrones();
    void ResetGame();
    void BringNextWave();

    int GetWave() { return wave; }
    int GetScore() { return score; }
    void IncrementScore() { score++; }
};

#endif
