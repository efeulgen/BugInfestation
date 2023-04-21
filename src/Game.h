
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <vector>
#include "Player.h"
#include "SpaceBug.h"

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

    // sounds
    Mix_Chunk *audio = nullptr;
    Mix_Chunk *bugSplashSound = nullptr;
    Mix_Chunk *bugScreamSound = nullptr;

    // background
    const int backgroundWidth = 1280;
    const int backgroundHeight = 720;
    int bg1_xPos = 0.0;
    int bg2_xPos = 1280.0;

    Player *mainPlayer = nullptr;
    std::vector<SpaceBug *> bugs;

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
};

#endif
