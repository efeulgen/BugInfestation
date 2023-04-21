
#include "Game.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include "Player.h"
#include "SpaceBug.h"

Game::Game()
{
    std::cout << "Game Constructor" << std::endl;
}

Game::~Game()
{
    std::cout << "Game Destructor" << std::endl;
}

void Game::Init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "SDL_Init fails." << std::endl;
        return;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cout << "SDL_mixer init fails : " << Mix_GetError() << std::endl;
    }

    window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, backgroundWidth, backgroundHeight, SDL_WINDOW_BORDERLESS);
    if (!window)
    {
        std::cerr << "SDL_Window creation fails." << std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
    {
        std::cerr << "SDL_Renderer creation fails." << std::endl;
        return;
    }

    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    isRunning = true;
}

void Game::Display()
{
    SetupGameAssets();
    while (isRunning)
    {
        ProcessInput();
        UpdateGameAssets();
        Render();
    }
}

void Game::SetupGameAssets()
{
    // setup audio

    audio = Mix_LoadWAV("./audio/game_music.wav");
    bugSplashSound = Mix_LoadWAV("./audio/smash.wav");
    bugScreamSound = Mix_LoadWAV("./audio/scream.wav");
    if (audio == NULL || bugSplashSound == NULL || bugScreamSound == NULL)
    {
        std::cout << "Failed to load audio : " << Mix_GetError() << std::endl;
    }
    Mix_PlayChannel(-1, audio, -1);

    // setup player
    mainPlayer = new Player();

    // setup spacebugs
    GenerateSpaceBugs(5);
}

void Game::ProcessInput()
{
    SDL_Event gameEvent;
    while (SDL_PollEvent(&gameEvent))
    {
        if (gameEvent.type == SDL_QUIT)
        {
            isRunning = false;
        }
        if (gameEvent.type == SDL_KEYDOWN)
        {
            if (gameEvent.key.keysym.sym == SDLK_ESCAPE)
            {
                isRunning = false;
            }
            if (gameEvent.key.keysym.sym == SDLK_w && mainPlayer)
            {
                mainPlayer->MoveUp();
            }
            if (gameEvent.key.keysym.sym == SDLK_s && mainPlayer)
            {
                mainPlayer->MoveDown();
            }
            if (gameEvent.key.keysym.sym == SDLK_RETURN && mainPlayer)
            {
                mainPlayer->Fire();
            }
        }
    }
}

void Game::UpdateGameAssets()
{
    int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
    if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME)
    {
        SDL_Delay(timeToWait);
    }
    millisecsPreviousFrame = SDL_GetTicks();

    // *************** update background ******************************
    bg1_xPos--;
    bg2_xPos--;
    if (bg1_xPos <= -1280.0f)
    {
        bg1_xPos = 1280.0f;
    }
    if (bg2_xPos <= -1280.0f)
    {
        bg2_xPos = 1280.0f;
    }

    // *************** check hit ******************************
    if (mainPlayer && (!bugs.empty() || !mainPlayer->GetProjectileArray().empty()))
    {
        for (auto bug : bugs)
        {
            for (auto projectile : mainPlayer->GetProjectileArray())
            {
                if (bug->CheckCollision(projectile->GetProjectileRect()))
                {
                    Mix_PlayChannel(-1, bugScreamSound, 0);
                    Mix_PlayChannel(-1, bugSplashSound, 0);
                    bugs.erase(std::remove(bugs.begin(), bugs.end(), bug), bugs.end());
                    bug->Destroy();
                    bug = nullptr;
                    mainPlayer->EraseElementFromProjarray(projectile);
                    projectile->Destroy();
                    projectile = nullptr;
                    break;
                }
            }
        }
    }

    if (!bugs.empty() && mainPlayer)
    {
        for (auto bug : bugs)
        {
            if (bug->CheckCollision(mainPlayer->GetPlayerRect()))
            {
                bugs.erase(std::remove(bugs.begin(), bugs.end(), bug), bugs.end());
                bug->Destroy();
                bug = nullptr;
                mainPlayer->GetDamage(1.0);
                break;
            }
        }
    }

    // *************** update main player ******************************
    if (mainPlayer)
    {
        mainPlayer->Update();
        if (mainPlayer->GetIsDead())
        {
            delete mainPlayer;
            mainPlayer = nullptr;
        }
    }

    // *************** update space bugs ******************************
    for (auto bug : bugs)
    {
        bug->UpdateSpaceBug();
    }
}

void Game::Render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // background
    SDL_Surface *backgroundSurface = IMG_Load("./assets/deep_space_bg_1280x720.png");
    SDL_Texture *backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);
    SDL_Rect bgRect_1 = {bg1_xPos, 0, 1280, 720};
    SDL_Rect bgRect_2 = {bg2_xPos, 0, 1280, 720};
    SDL_RenderCopy(renderer, backgroundTexture, NULL, &bgRect_1);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, &bgRect_2);
    SDL_DestroyTexture(backgroundTexture);

    // render player
    if (mainPlayer)
    {
        mainPlayer->RenderPlayer(renderer);
    }

    // render spacebugs
    if (!bugs.empty())
    {
        for (auto bug : bugs)
        {
            bug->RenderSpaceBug(renderer);
        }
    }

    SDL_RenderPresent(renderer);
}

void Game::Destroy()
{
    if (mainPlayer)
    {
        delete mainPlayer;
        mainPlayer = nullptr;
    }
    Mix_FreeChunk(audio);
    Mix_FreeChunk(bugScreamSound);
    Mix_FreeChunk(bugSplashSound);
    audio = nullptr;
    bugScreamSound = nullptr;
    bugSplashSound = nullptr;
    Mix_CloseAudio();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::GenerateSpaceBugs(int amount)
{
    int seed = 0;
    for (int i = 0; i < amount; i++)
    {
        srand(seed);
        int randomYPos = (rand() % 500) + 20;
        int randomXDirection = (rand() % 2) + 2;
        int randomYDirection = (rand() % 2) + 2;
        bugs.push_back(new SpaceBug(glm::vec2(1000, randomYPos), glm::vec2(randomXDirection, randomYDirection)));
        seed++;
    }
}
